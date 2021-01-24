#include "utils.h"
#include <cassert>

int GetBitByPos(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos)
{
	// ��ÿ���ֽڵĸ�λ��ʼ(�ֽ��е�bit�Ǵ����)
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
 ��ʽ��[n��0] + 1 + [xxx]��[]��λ����ͬ
 ����
 0 0 0 0 0 1 0 0 0 1 1 <==> 2^5 - 1 + 3 = 34
*/
int GetUECode(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos)
{
	int prefixVal;
	int surfixVal = 0;
	uint8_t prefixZeroCount = 0;

	assert(bitPos < 8);

	// �ҵ���һ����0����
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
