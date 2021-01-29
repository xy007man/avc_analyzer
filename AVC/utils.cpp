#include "utils.h"
#include <cassert>

int GetBitByPos(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos)
{
	// 从每个字节的高位开始(字节中的bit是大端序)
	uint8_t mask = 1 << (7 - bitPos);
	int val = (mask & buf[bytePos]) != 0;

	if (++bitPos > 7) {
		bitPos = 0;
		bytePos++;
	}

	return val;
}

/* 
 codeNum = 2^(prefixZeroCount) - 1 + surfixVal
 格式：[n个0] + 1 + [xxx]，[]中位数相同
 例：
 0 0 0 0 0 1 0 0 0 1 1 <==> 2^5 - 1 + 3 = 34
*/
int GetUECode(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos)
{
	int prefixVal;
	int surfixVal = 0;
	uint8_t prefixZeroCount = 0;

	assert(bitPos < 8);

	// 找到第一个非0数字
	while (GetBitByPos(buf, bytePos, bitPos) == 0) {
		prefixZeroCount++;
	}
	prefixVal = (1 << prefixZeroCount) - 1;

	for (uint8_t i = 0; i < prefixZeroCount; i++) {
		surfixVal += GetBitByPos(buf, bytePos, bitPos) << (prefixZeroCount - i - 1);
	}

	return prefixVal + surfixVal;
}

int GetSECode(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos)
{
	int ue = GetUECode(buf, bytePos, bitPos);
	int sign = (ue % 2) ? 1 : -1;

	return sign * ((ue + 1) >> 1);
}

uint32_t GetUINTCode(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos, uint32_t length)
{
	uint32_t val = 0;
	for (int i = 0; i < length; i++) {
		val += GetBitByPos(buf, bytePos, bitPos) << (length - 1 - i);
	}
	return val;
}

int GetMECode(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos)
{
	int intraCbp[48] = { 47, 31, 15, 0, 23, 27, 29, 30, 7, 11, 13, 14, 39, 43, 45, 46, 16, 3, 5, 10, 12, 19, 21, 26, 28, 35, 37, 42, 44, 1, 2 ,4, 8, 17,18,20,24,6,9,22,25,32,33,34,36,40,38,41 };

	return intraCbp[GetUECode(buf, bytePos, bitPos)];
}
