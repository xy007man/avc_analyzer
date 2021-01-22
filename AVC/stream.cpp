#include <iostream>
#include "stream.h"
#include "nalu.h"

StreamFile::StreamFile(char* fileName) {
	inputFile = fopen(fileName, "rb");
	if (inputFile == NULL)
		std::cout << "open file failed" << std::endl;
}

StreamFile::~StreamFile() {

	if (inputFile) {
		fclose(inputFile);
	}

	if (sps != nullptr) {
		delete sps;
	}

	if (pps != nullptr) {
		delete pps;
	}
}

int StreamFile::ParseBitStream() {
	int ret;

	do {
		ret = FindNaul();
		if (nalu.size() > 0) {
			int naulType = nalu[0] & 0x1f;
			EBSPToSODB();
			printf("naul type %x\n", naulType);

			NALU nalu(&nalu[1], nalu.size() - 1);
			switch (naulType)
			{
				case 7:
					sps = new SeqParmSet();
					nalu.parseSeqParmSet(sps);
					break;
				case 8:
					pps = new PicParmSet();
					nalu.parsePicParmSet(pps);
					break;
				default:
					break;
			}
		}
	} while (!ret);

	return 0;
}

int StreamFile::FindNaul() {
	int pos = 0;
	uint8_t byteValue;
	uint8_t prefix[3] = { 0 };

	nalu.clear();
	for (int i = 0; i < 3; i++) {
		prefix[i] = fgetc(inputFile);
		nalu.push_back(prefix[i]);
		if (prefix[i] == EOF)
			return -1;
	}
	
	while (!feof(inputFile)) {

		// 00 00 01
		if (prefix[pos % 3] == 0 
			&& prefix[(pos + 1) % 3] == 0 && prefix[(pos + 2) % 3] == 1) {
			nalu.pop_back();
			nalu.pop_back();
			nalu.pop_back();
			return 0;
		}

		// 00 00 00 01
		if (prefix[pos % 3] == 0 
			&& prefix[(pos + 1) % 3] == 0 && prefix[(pos + 2) % 3] == 0) {
			if (fgetc(inputFile) == 1) {
				nalu.pop_back();
				nalu.pop_back();
				nalu.pop_back();
				return 0;
			}
		}

		byteValue = fgetc(inputFile);
		prefix[pos % 3] = byteValue;
		pos++;
		nalu.push_back(byteValue);
	}

	return -1;
}

void StreamFile::EBSPToSODB() {
	if (nalu.size() < 3) {
		return;
	}
	// È¥³ý¾ºÕùÂë0x03
	auto it = nalu.begin();
	while (it != nalu.end()) {
		if (*it == 3 && *(it - 1) == 0 && *(it - 2) == 0) {
			it = nalu.erase(it);
			continue;
		}
		it++;
	}
}
