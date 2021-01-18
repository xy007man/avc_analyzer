#include "utils.h"
#include <cassert>

int GetBitByPos(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos)
{
	// 从每个字节的高位开始
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

	assert(bytePos < 8);

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