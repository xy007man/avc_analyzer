#include "stream.h"
#include <iostream>

int main(int argc, char* argv[])
{	
	StreamFile avcFile(argv[1]);
	std::vector<uint8_t> naulByte;

	avcFile.ParseBitStream(naulByte);
	

	avcFile.ParseBitStream(naulByte);
	for (int i = 0; i < naulByte.size(); i++) {
		printf("%x ", naulByte[i]);
	}

	return 0;
}