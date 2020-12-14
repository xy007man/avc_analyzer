#ifndef _STREAM_H_
#define _STREAM_H_

#include <vector>
#include <cstdio>

class StreamFile
{
public:
	StreamFile(char *fileName);
	~StreamFile();
	int ParseBitStream(std::vector<uint8_t>& naulByte);
private:
	FILE *m_inputFile;
};

#endif