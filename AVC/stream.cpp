#include <iostream>
#include "stream.h"

StreamFile::StreamFile(char* fileName) {
	m_inputFile = fopen(fileName, "rb");
	if (m_inputFile == NULL)
		std::cout << "open file failed" << std::endl;
}

StreamFile::~StreamFile() {
	if (m_inputFile)
		fclose(m_inputFile);
}

int StreamFile::ParseBitStream(std::vector<uint8_t> &naulByte)
{
	int pos = 0;
	uint8_t byteValue;
	uint8_t prefix[3] = { 0 };

	naulByte.clear();
	for (int i = 0; i < 3; i++) {
		prefix[i] = fgetc(m_inputFile);
		naulByte.push_back(prefix[i]);
		if (prefix[i] == EOF)
			return -1;
	}
	
	while (!feof(m_inputFile)) {

		// 00 00 01
		if (prefix[pos % 3] == 0 
			&& prefix[(pos + 1) % 3] == 0 && prefix[(pos + 2) % 3] == 1) {
			naulByte.pop_back();
			naulByte.pop_back();
			naulByte.pop_back();
			break;
		}

		// 00 00 00 01
		if (prefix[pos % 3] == 0 
			&& prefix[(pos + 1) % 3] == 0 && prefix[(pos + 2) % 3] == 0) {
			if (fgetc(m_inputFile) == 1) {
				naulByte.pop_back();
				naulByte.pop_back();
				naulByte.pop_back();
				break;
			}
		}

		byteValue = fgetc(m_inputFile);
		prefix[pos % 3] = byteValue;
		pos++;
		naulByte.push_back(byteValue);
	}

	return 0;
}
