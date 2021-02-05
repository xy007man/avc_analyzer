#ifndef _MACRO_BLOCK_H_
#define _MACRO_BLOCK_H_
#include <cstdint>
#include "PicParmSet.h"

class Slice;
class Residual;

// MB_Type
#define P8x8    8
#define I4MB    9
#define I16MB   10
#define IBLOCK  11
#define SI4MB   12
#define MAXMODE 13
#define IPCM    14

// Quantization parameter range
#define MIN_QP          0
#define MAX_QP          51

struct IntraPred
{
	bool is8x8blockMode = false; // 4x4 or 8x8
	bool prevIntraPredModeFlag = false;
	uint8_t remIntraPredMode = 0;
};

class MacroBlock
{
public:
	MacroBlock(uint8_t* pSODB, uint8_t offset, uint8_t mbIdx, PicParmSet* pps, Slice *slice);
	~MacroBlock();
	uint8_t GetCbpLuma();
	uint8_t GetCbpChroma();
	uint8_t GetMbType();
	PicParmSet* GetPps();
	int ParseMacroBlock();
	int GetNumberCurrent(int x, int y);
	
private:

	void GetNeighborAvailable(int x, int y, int &topIdx, int &leftIdx, bool &availableTop, bool &availableLeft);
	int GetTopNeighborCoeff(int topIdx, int subX, int subY);
	int GetLeftNeighborCoeff(int topIdx, int subX, int subY);
	void InterpretMbMode();

	uint8_t *pSODB;
	uint8_t byteOffset;
	uint8_t bitOffset;
	uint8_t mbIdx;
	uint8_t mbSize;
	uint8_t mbType = 0;
	Slice* slice = nullptr;
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

