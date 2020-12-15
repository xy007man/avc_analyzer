#include "stream.h"
#include <iostream>

int main(int argc, char* argv[])
{	
	StreamFile avcFile(argv[1]);
	avcFile.ParseBitStream();

	return 0;
}