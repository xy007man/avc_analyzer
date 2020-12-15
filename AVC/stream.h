#ifndef _STREAM_H_
#define _STREAM_H_

#include <vector>
#include <cstdio>

class StreamFile
{
public:
	StreamFile(char *fileName);
	~StreamFile();
	int ParseBitStream();
	int FindNaul();
	void EBSPToSODB();
private:
	FILE *m_inputFile;
	std::vector<uint8_t> m_nalu;
};

#endif