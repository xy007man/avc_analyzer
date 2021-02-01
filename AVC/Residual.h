#ifndef _RESIDUAL_H_
#define _RESIDUAL_H_
#include "MacroBlock.h"

struct Coeff4x4Block {
	bool emptyBlock = false;
	uint16_t coeffToken = 0;
	uint8_t numCoeff = 0;
	uint8_t trailingOnes = 0;
	uint8_t trailingSign[3] = { 0 };
	int level[16] = { 0 };
	uint8_t totalZero = 0;
	uint8_t runBefore[16] = { 0 };
};

class Residual
{
public:
	Residual(uint8_t* pSODB, uint8_t offset, MacroBlock* macroBlock);
	~Residual();

	int ParseMacroBlockResidual();
	int ParseLumaResidual(uint8_t cbpLuma);
private:
	MacroBlock* macroBlock;
	uint8_t* pSODB;
	uint8_t byteOffset;
	uint8_t bitOffset;

	Coeff4x4Block lumaResidual[4][4];
};
#endif

