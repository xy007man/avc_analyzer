#include "MacroBlock.h"
#include "PicParmSet.h"
#include "Residual.h"
#include "ISlice.h"
#include "utils.h"

MacroBlock::MacroBlock(uint8_t* pSODB, uint8_t mbIdx, uint8_t offset, PicParmSet* pps, ISlice *slice)
{
	this->pSODB = pSODB;
	this->byteOffset = offset / 8;
	this->bitOffset = offset % 8;
	this->pps = pps;
	this->mbIdx = mbIdx;
	this->mbSize = offset;
	this->slice = slice;
}

MacroBlock::~MacroBlock()
{
	if (intraPred != nullptr) {
		delete intraPred;
	}

	if (residual != nullptr) {
		delete residual;
	}
}

uint8_t MacroBlock::GetCbpLuma()
{
	return this->cbpLuma;
}

uint8_t MacroBlock::GetCbpChroma()
{
	return this->cbpChroma;
}

PicParmSet* MacroBlock::GetPps()
{
	return this->pps;
}

int MacroBlock::ParseMacroBlock()
{
	mbType = GetUECode(pSODB, byteOffset, bitOffset);
	if (mbType == 25) {
		// PCM
	}
	else if (mbType == 0) {
		// Intra NxN
		if (pps->GetTransform8x8ModeFlag()) {
			transformSize8x8Flag = GetBitByPos(pSODB, byteOffset, bitOffset);
		}
		// Ã¿¸öºê¿é16x16£¬4x4 or 8x8 ±àÂë
		if (transformSize8x8Flag) {
			// Intra 8x8
			intraPred = new IntraPred[4];
			for (int luma8x8BlkIdx = 0; luma8x8BlkIdx < 4; luma8x8BlkIdx++) {
				intraPred[luma8x8BlkIdx].is8x8blockMode = false;
				intraPred[luma8x8BlkIdx].prevIntraPredModeFlag = GetBitByPos(pSODB, byteOffset, bitOffset);
				if (!intraPred[luma8x8BlkIdx].prevIntraPredModeFlag) {
					intraPred[luma8x8BlkIdx].remIntraPredMode = GetUINTCode(pSODB, byteOffset, bitOffset, 3);
				}
			}
			intraChromaPredMode = GetUECode(pSODB, byteOffset, bitOffset);
		}
		else {
			// Intra 4x4
			intraPred = new IntraPred[16];
			for (int luma4x4BlkIdx = 0; luma4x4BlkIdx < 16; luma4x4BlkIdx++) {
				intraPred[luma4x4BlkIdx].is8x8blockMode = false;
				intraPred[luma4x4BlkIdx].prevIntraPredModeFlag = GetBitByPos(pSODB, byteOffset, bitOffset);
				if (!intraPred[luma4x4BlkIdx].prevIntraPredModeFlag) {
					intraPred[luma4x4BlkIdx].remIntraPredMode = GetUINTCode(pSODB, byteOffset, bitOffset, 3);
				}
			}
			intraChromaPredMode = GetUECode(pSODB, byteOffset, bitOffset);
		}
	}
	else {
		// Intra 16x16
	}

	if (mbType == 0 || mbType == 25) {
		codedBlockPattern = GetMECode(pSODB, byteOffset, bitOffset);
		cbpLuma = codedBlockPattern % 16;
		cbpChroma = codedBlockPattern / 16;
	}

	if (cbpLuma > 0 || cbpChroma > 0 || (mbType > 0 && mbType < 25)) {
		mbQpDelta = GetSECode(pSODB, byteOffset, bitOffset);
		residual = new Residual(pSODB, byteOffset * 8 + bitOffset, this);
		residual->ParseMacroBlockResidual();
	}

	mbSize = byteOffset * 8 + bitOffset - mbSize;

	return mbSize;
}

int MacroBlock::GetNumberCurrent(int subX, int subY)
{
	int nC = 0;
	int topIdx;
	int leftIdx;
	int topNum = 0;
	int leftNum = 0;

	bool availableTop = false;
	bool availableLeft = false;

	GetNeighborAvailable(subX, subY, topIdx, leftIdx, availableTop, availableLeft);
	if (!availableTop && !availableLeft) {
		return 0;
	}

	if (availableLeft) {
		nC = leftNum = GetLeftNeighborCoeff(leftIdx, subX, subY);
	}
	if (availableTop) {
		nC = topNum = GetTopNeighborCoeff(topIdx, subX, subY);
	}
	if (availableTop && availableLeft) {
		return (leftNum + topNum + 1) >> 1;
	}

	return nC;
}

void MacroBlock::GetNeighborAvailable(int x, int y, int &topIdx, int &leftIdx, bool& availableTop, bool& availableLeft)
{
	int mbIdx = this->mbIdx;
	uint16_t picWidthInMBs = slice->GetSps()->GetPicWidthInMBs();
	uint16_t picHeightInMBs = slice->GetSps()->GetPicHeightInMBs();

	bool isLeftEdge = (mbIdx % picWidthInMBs) == 0;
	bool isTopEdge = mbIdx < picWidthInMBs;

	if (!isTopEdge) {
		availableTop = true;
		topIdx = mbIdx - picWidthInMBs;
	}
	else {
		if (y == 0) {
			availableTop = false;
		}
		else {
			availableTop = true;
			topIdx = mbIdx;
		}
	}

	if (!isLeftEdge) {
		availableLeft = true;
		leftIdx = mbIdx - 1;
	}
	else {
		if (x == 0) {
			availableLeft = false;
		}
		else {
			availableLeft = true;
			leftIdx = mbIdx;
		}
	}
}

int MacroBlock::GetTopNeighborCoeff(int topIdx, int subX, int subY)
{
	if (topIdx == mbIdx) {
		return residual->GetSubBlockNumCoeff(subX, subY - 1);
	}

	return 0;
}

int MacroBlock::GetLeftNeighborCoeff(int leftIdx, int subX, int subY)
{
	if (leftIdx == mbIdx) {
		return residual->GetSubBlockNumCoeff(subX - 1, subY);
	}
	return 0;
}

