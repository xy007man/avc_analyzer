#include "MacroBlock.h"
#include "PicParmSet.h"
#include "utils.h"

MacroBlock::MacroBlock(uint8_t* pSODB, uint8_t mbIdx, uint8_t offset, PicParmSet* pps)
{
	this->pSODB = pSODB;
	this->byteOffset = offset / 8;
	this->bitOffset = offset % 8;
	this->pps = pps;
	this->mbIdx = mbIdx;
	this->mbSize = offset;
}

MacroBlock::~MacroBlock()
{
	if (intraPred != nullptr) {
		delete intraPred;
	}
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
	}

	mbSize = byteOffset * 8 + bitOffset - mbSize;

	return mbSize;
}
