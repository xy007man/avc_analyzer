#ifndef _MACRO_BLOCK_H_
#define _MACRO_BLOCK_H_
#include <cstdint>
#include "PicParmSet.h"

class Residual;
struct IntraPred
{
	bool is8x8blockMode = false; // 4x4 or 8x8
	bool prevIntraPredModeFlag = false;
	uint8_t remIntraPredMode = 0;
};

class MacroBlock
{
public:
	MacroBlock(uint8_t* pSODB, uint8_t offset, uint8_t mbIdx, PicParmSet* pps);
	~MacroBlock();
	int ParseMacroBlock();
private:
	uint8_t *pSODB;
	uint8_t byteOffset;
	uint8_t bitOffset;
	uint8_t mbIdx;
	uint8_t mbSize;
	uint8_t mbType = 0;
	bool transformSize8x8Flag = false;
	uint8_t codedBlockPattern = 0;
	int mbQpDelta = 0;

	IntraPred *intraPred = nullptr;
	PicParmSet *pps = nullptr;
	uint8_t intraChromaPredMode = 0;
	uint8_t cbpLuma = 0;
	uint8_t cbpChroma = 0;

	Residual* residual = nullptr;
};
#endif

