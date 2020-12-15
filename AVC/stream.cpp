#include <iostream>
#include "stream.h"
#include "nalu.h"

StreamFile::StreamFile(char* fileName) {
	m_inputFile = fopen(fileName, "rb");
	if (m_inputFile == NULL)
		std::cout << "open file failed" << std::endl;
}

StreamFile::~StreamFile() {
	if (m_inputFile)
		fclose(m_inputFile);
}

int StreamFile::ParseBitStream() {
	int ret;

	do {
		ret = FindNaul();
		if (m_nalu.size() > 0) {
			int naulType = m_nalu[0] & 0x1f;
			EBSPToSODB();
			printf("naul type %x\n", naulType);
			NALU nalu(&m_nalu[1], m_nalu.size() - 1);
		}
	} while (!ret);

	return 0;
}

int StreamFile::FindNaul() {
	int pos = 0;
	uint8_t byteValue;
	uint8_t prefix[3] = { 0 };

	m_nalu.clear();
	for (int i = 0; i < 3; i++) {
		prefix[i] = fgetc(m_inputFile);
		m_nalu.push_back(prefix[i]);
		if (prefix[i] == EOF)
			return -1;
	}
	
	while (!feof(m_inputFile)) {

		// 00 00 01
		if (prefix[pos % 3] == 0 
			&& prefix[(pos + 1) % 3] == 0 && prefix[(pos + 2) % 3] == 1) {
			m_nalu.pop_back();
			m_nalu.pop_back();
			m_nalu.pop_back();
			return 0;
		}

		// 00 00 00 01
		if (prefix[pos % 3] == 0 
			&& prefix[(pos + 1) % 3] == 0 && prefix[(pos + 2) % 3] == 0) {
			if (fgetc(m_inputFile) == 1) {
				m_nalu.pop_back();
				m_nalu.pop_back();
				m_nalu.pop_back();
				return 0;
			}
		}

		byteValue = fgetc(m_inputFile);
		prefix[pos % 3] = byteValue;
		pos++;
		m_nalu.push_back(byteValue);
	}

	return -1;
}

void StreamFile::EBSPToSODB() {
	if (m_nalu.size() < 3) {
		return;
	}

	auto it = m_nalu.begin();
	while (it != m_nalu.end()) {
		if (*it == 3 && *(it - 1) == 0 && *(it - 2) == 0) {
			it = m_nalu.erase(it);
			continue;
		} 
		it++;
	}
}
