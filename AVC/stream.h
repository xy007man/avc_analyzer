#ifndef _STREAM_H_
#define _STREAM_H_

#include <vector>
#include <cstdio>
#include "SeqParmSet.h"

class StreamFile
{
public:
	StreamFile(char *fileName);
	~StreamFile();
	int ParseBitStream();
	int FindNaul();
	void EBSPToSODB();
private:
	FILE *inputFile;
	std::vector<uint8_t> nalu;
	SeqParmSet *sps;
};

#endif