#include "stream.h"
#include <iostream>
#include "utils.h"

void testUE()
{
	uint8_t array[] = { 0xA6, 0x42, 0x98, 0xE2, 0x04, 0x8A };
	uint8_t bytePos = 0;
	uint8_t bitPos = 0;

	while ((bytePos * 8 + bitPos) < sizeof(array) * 8) {
		printf("%x ", GetUECode(array, bytePos, bitPos));
	}
}

int main(int argc, char* argv[])
{	
	StreamFile avcFile(argv[1]);
	avcFile.ParseBitStream();
	//testUE();
	return 0;
}