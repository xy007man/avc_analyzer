#ifndef _MACRO_BLOCK_H_
#define _MACRO_BLOCK_H_
#include <cstdint>

struct IntraPred
{
	bool is8x8blockMode = false; // 4x4 or 8x8
	bool prevIntraPredModeFlag = false;
	uint8_t remIntraPredMode = 0;
};

class MacroBlock
{
public:
	MacroBlock(uint8_t *pSODB, uint32_t offset);
	~MacroBlock();
private:
	uint8_t* pSODB;
	uint32_t byteOffset;
	uint32_t bitOffset;
	uint8_t mbType;
	bool transformSize8x8Flag;
	uint8_t codedBlockPattern;
	uint8_t mbQpDelta;

	IntraPred* intraPred;
	uint8_t intraChromaPredMode;
};
#endif

