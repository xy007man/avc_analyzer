#include "stream.h"
#include <iostream>

int GetBitByPos(uint8_t *buf, uint8_t &bytePos, uint8_t &bitPos) {
	
	// 从每个字节的高位开始
	uint8_t mask = 1 << (7 - bitPos);
	int val = (mask & buf[bytePos]) != 0;

	if (++bitPos > 7) {
		bitPos = 0;
		bytePos++;
	}
	
	return val;
}

int GetUECode(uint8_t *buf, uint8_t &bytePos, uint8_t &bitPos) {

	int prefixVal;
	int surfixVal = 0;
	uint8_t prefixZeroCount = 0;

	while (GetBitByPos(buf, bytePos, bitPos) == 0) {
		prefixZeroCount++;
	}
	prefixVal = (1 << prefixZeroCount) - 1;

	for (uint8_t i = 0; i < prefixZeroCount; i++) {
		surfixVal += GetBitByPos(buf, bytePos, bitPos) << (prefixZeroCount - i - 1);
	}

	return prefixVal + surfixVal;
}

void testUE() {
	uint8_t array[] = {0xA6, 0x42, 0x98, 0xE2, 0x04, 0x8A};
	uint8_t bytePos = 0;
	uint8_t bitPos = 0;

	while ((bytePos * 8 + bitPos) < sizeof(array) * 8) {
		printf("%x ", GetUECode(array, bytePos, bitPos));
	}
}

int main(int argc, char* argv[])
{	
	//StreamFile avcFile(argv[1]);
	//avcFile.ParseBitStream();
	testUE();
	return 0;
}