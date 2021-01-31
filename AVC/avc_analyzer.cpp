#include "stream.h"
#include <iostream>
#include "utils.h"
#include <cassert>

void testUE()
{
	uint8_t array[] = { 0xA6, 0x42, 0x98, 0xE2, 0x04, 0x8A };
	uint8_t bytePos = 0;
	uint8_t bitPos = 0;

	while ((bytePos * 8 + bitPos) < sizeof(array) * 8) {
		printf("%x ", GetUECode(array, bytePos, bitPos));
	}
}

const std::string coeffTokenMap[1][62] = {
	{ "1", "000101", "01", "00000111", "000100", "001", "000000111", "00000110", "0000101", "00011", "0000000111", "000110", "00000101", "000011", "00000000111", "0000000110", "000000101", "0000100", "0000000001111", "00000000110", "0000000101", "00000100", "0000000001011", "0000000001110", "00000000101", "000000100", "0000000001000", "0000000001010", "0000000001101", "0000000100", "00000000001111", "00000000001110", "0000000001001", "00000000100", "00000000001011", "00000000001010", "00000000001101", "0000000001100", "000000000001111", "000000000001110", "00000000001001", "00000000001100", "000000000001011", "000000000001010", "000000000001101", "00000000001000", "0000000000001111", "000000000000001", "000000000001001", "000000000001100", "0000000000001011", "0000000000001110", "0000000000001101", "000000000001000", "0000000000000111", "0000000000001010", "0000000000001001", "0000000000001100", "0000000000000100", "0000000000000110", "0000000000000101", "0000000000001000" }
};

const std::string totalZerosMap[16][16] = {
	{ "", "1", "111", "0101", "00011", "0101", "000001", "000001", "000001", "000001", "00001", "0000", "0000", "000", "00", "0" },
	{ "", "011", "110", "111", "111", "0100", "00001", "00001", "0001", "000000", "00000", "0001", "0001", "001", "01", "1" },
	{ "", "010", "101", "110", "0101", "0011", "111", "101", "00001", "0001", "001", "001", "01", "1", "1" },
	{ "", "0011", "100", "101", "0100", "111", "110", "100", "011", "11", "11", "010", "1", "01" },
	{ "", "0010", "011", "0100", "110", "110", "101", "101", "11", "10", "10", "1", "001" },
	{ "", "00011", "0101", "0011", "101", "101", "100", "11", "10", "001", "01", "011" },
	{ "", "00010", "0100", "100", "100", "100", "011", "010", "010", "01", "0001" },
	{ "", "000011", "0011", "011", "0011", "011", "010", "0001", "001", "0000", "1" },
	{ "", "000010", "0010", "0010", "011", "0010", "0001", "001", "000000" },
	{ "", "0000011", "00011", "00011", "0010", "00001", "001", "000000" },
	{ "", "0000010", "00010", "00010", "00010", "0001", "000000" },
	{ "", "00000011", "000011", "000001", "00001", "00000" },
	{ "", "00000010", "000010", "00001", "00000" },
	{ "", "000000011", "000001", "000000" },
	{ "", "000000010", "000000" },
	{ "", "000000001" }
};

const std::string runBeforeMap[15][8] = {
	{ "", "1", "1", "11", "11", "11", "11", "111" },
	{ "", "0", "01", "10", "10", "10", "000", "110" },
	{ "", "", "00", "01", "01", "011", "001", "101" },
	{ "", "", "", "00", "001", "010", "011", "100" },
	{ "", "", "", "", "000", "001", "010", "011" },
	{ "", "", "", "", "", "000", "101", "010" },
	{ "", "", "", "", "", "", "100", "001" },
	{ "", "", "", "", "", "", "", "0001" },
	{ "", "", "", "", "", "", "", "00001" },
	{ "", "", "", "", "", "", "", "000001" },
	{ "", "", "", "", "", "", "", "0000001" },
	{ "", "", "", "", "", "", "", "00000001" },
	{ "", "", "", "", "", "", "", "000000001" },
	{ "", "", "", "", "", "", "", "0000000001" },
	{ "", "", "", "", "", "", "", "00000000001" }
};

int GetTotalCoeffs(const int coeff[16])
{
	int cnt = 0;
	for (int i = 0; i < 16; i++) {
		if (coeff[i]) {
			cnt++;
		}
	}
	return cnt;
}

int GetTrailingOnes(const int coeff[16], int trailingSign[3])
{
	int cnt = 0;
	for (int i = 15; i >= 0; i--) {
		if (abs(coeff[i]) > 1 || cnt == 3) {
			break;
		}
		if (abs(coeff[i]) == 1) {
			trailingSign[cnt++] = coeff[i];
		}
	}
	return cnt;
}

void GetLevel(const int coeff[16], int* level, int levelCnt)
{
	assert(levelCnt > 0);

	for (int i = 0; i < 16; i++) {
		if (coeff[i] != 0) {
			level[--levelCnt] = coeff[i];
			if (levelCnt == 0) {
				break;
			}
		}
	}
}

int GetTotalZerosRunBefore(const int coeff[16], int* runBefore, int* zeroLeft, int totalCoeffs)
{
	int totalZeros = 0;
	int j = 0;
	int idx = 15;

	for (; idx >= 0; idx--) {
		if (coeff[idx]) { // 第一个非0系数的位置
			break;
		}
	}

	totalZeros = idx - totalCoeffs + 1; // 去除高频连续0之后，当前剩余0的数目
	for (; idx >= 0; idx--) {
		if (coeff[idx] == 0) {
			continue;
		}
		for (int i = 0; i < idx; i++) { // coeff[idx] 不是0， idx前有多少连续0
			if (coeff[idx - i - 1] != 0) {
				j++;
				break;
			}
			runBefore[j]++; // 连续0个数
			zeroLeft[j]++;
		}
	}

	for (int i = 0; i < j; i++) {
		for (int k = i + 1; k < j; k++) {
			zeroLeft[i] += zeroLeft[k];
		}
	}

	return totalZeros;
}

std::string EncodeLevel(int level, int& suffixLength)
{
	std::string code;
	int levelCode;

	if (level > 0) {
		levelCode = (level << 1) - 2;
	}
	else {
		levelCode = -(level << 1) - 1;
	}

	int levelPrefix = levelCode / (1 << suffixLength);
	int levelSuffix = levelCode % (1 << suffixLength);
	for (int idx = 0; idx < levelPrefix; idx++) {
		code += "0";
	}
	code += "1";

	for (int idx = 0; idx < suffixLength; idx++) {
		if ((levelSuffix >> (suffixLength - idx - 1) & 1) == 1) {
			code += "1";
		} else {
			code += "0";
		}
	}

	return code;
}

std::string Encode16x16Cavlc(const int coeff[16])
{
	std::string cavlcCode;
	int totalCoeffs = GetTotalCoeffs(coeff); // 非0系数
	int trailingOnes; // 拖尾系数个数(从末尾高频读取-1或者1，直到系数大于1或者已经读取到3个-1或1为止)
	int trailingSign[3]; // 拖尾系数个数

	trailingOnes = GetTrailingOnes(coeff, trailingSign);
	int levelCnt = totalCoeffs - trailingOnes; // 非-1，1的，其他非0系数，从末尾高频开始计算
	int* level = new int[levelCnt];
	int* runBefore = new int[totalCoeffs]; // 非0系数前面有多少连续0
	int* zeroLeft = new int[totalCoeffs]; // 非0系数前面有一共有多少0

	memset(level, 0, sizeof(int) * levelCnt);
	memset(runBefore, 0, sizeof(int) * totalCoeffs);
	memset(zeroLeft, 0, sizeof(int) * totalCoeffs);

	GetLevel(coeff, level, levelCnt);
	int totalZeros = GetTotalZerosRunBefore(coeff, runBefore, zeroLeft, totalCoeffs);

	// coeff_token (trailingOnes / totalCoeffs)
	if (totalCoeffs >= 3) {
		cavlcCode += coeffTokenMap[0][(totalCoeffs - 3) * 4 + trailingOnes + 6];
	}
	else if (totalCoeffs == 2)
	{
		cavlcCode += coeffTokenMap[0][totalCoeffs + trailingOnes + 1];
	}
	else
	{
		cavlcCode += coeffTokenMap[0][totalCoeffs + trailingOnes];
	}
	
	// trailingOnes/trailingSign
	for (int i = 0; i < trailingOnes; i++) {
		cavlcCode += trailingSign[i] == 1 ? "0" : "1";
	}

	// level
	int suffixLength = 0;
	if (totalCoeffs > 10 && trailingOnes < 3) {
		suffixLength = 1;
	}

	for (int i = 0; i < levelCnt; i++) {
		cavlcCode += EncodeLevel(level[i], suffixLength);
		if ((abs(level[i]) > (suffixLength == 0 ? 0 : (3 << (suffixLength - 1)))) && suffixLength < 6) {
			suffixLength++;
		}
	}

	// totalZeros
	cavlcCode += totalZerosMap[totalZeros][totalCoeffs];

	// runBefore
	for (int i = 0; i < totalCoeffs - 1; i++) {
		if (zeroLeft[i] == 0) {
			break;
		}
		cavlcCode += runBeforeMap[runBefore[i]][zeroLeft[i]];
	}

	delete[] level;
	delete[] runBefore;
	delete[] zeroLeft;
	return cavlcCode;
}

void testCAVLC() 
{
	// 低频 --> 高频
	int coeff[16] = { 3, 2, 1, -1, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::string cavlcCode = Encode16x16Cavlc(coeff);
	std::cout << cavlcCode << std::endl;
}

int main(int argc, char* argv[])
{	
	StreamFile avcFile(argv[1]);
	avcFile.ParseBitStream();
	//testUE();
	//testCAVLC();

	return 0;
}