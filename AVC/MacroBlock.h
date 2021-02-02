#ifndef _MACRO_BLOCK_H_
#define _MACRO_BLOCK_H_
#include <cstdint>
#include "PicParmSet.h"

class ISlice;
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
	MacroBlock(uint8_t* pSODB, uint8_t offset, uint8_t mbIdx, PicParmSet* pps, ISlice *slice);
	~MacroBlock();
	uint8_t GetCbpLuma();
	uint8_t GetCbpChroma();
	PicParmSet* GetPps();
	int ParseMacroBlock();
	int GetNumberCurrent(int x, int y);
	
private:

	void GetNeighborAvailable(int x, int y, int &topIdx, int &leftIdx, bool &availableTop, bool &availableLeft);
	int GetTopNeighborCoeff(int topIdx, int subX, int subY);
	int GetLeftNeighborCoeff(int topIdx, int subX, int subY);
	uint8_t *pSODB;
	uint8_t byteOffset;
	uint8_t bitOffset;
	uint8_t mbIdx;
	uint8_t mbSize;
	uint8_t mbType = 0;
	ISlice* slice = nullptr;
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

