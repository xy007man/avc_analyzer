#ifndef _MACRO_BLOCK_H_
#define _MACRO_BLOCK_H_
#include <cstdint>
#include "PicParmSet.h"

struct IntraPred
{
	bool is8x8blockMode = false; // 4x4 or 8x8
	bool prevIntraPredModeFlag = false;
	uint8_t remIntraPredMode = 0;
};

class MacroBlock
{
public:
	MacroBlock(uint8_t *pSODB, uint8_t offset, PicParmSet *pps);
	~MacroBlock();
	int ParseMacroBlock();
private:
	uint8_t *pSODB;
	uint8_t byteOffset;
	uint8_t bitOffset;
	uint8_t mbType = 0;
	bool transformSize8x8Flag = false;
	uint8_t codedBlockPattern = 0;
	uint8_t mbQpDelta = 0;

	IntraPred *intraPred = nullptr;
	PicParmSet *pps = nullptr;
	uint8_t intraChromaPredMode = 0;
};
#endif

