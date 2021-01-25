#include "SeqParmSet.h"

void SeqParmSet::SetProfileLevel(uint8_t profileIdc, uint8_t levelIdc)
{
	this->profileIdc = profileIdc;
	this->levelIdc = levelIdc;
}

void SeqParmSet::SetSpsId(uint8_t spsId)
{
	this->spsId = spsId;
}

void SeqParmSet::SetChromaFormatIdc(uint8_t chromaFormatIdc)
{
	this->chromaFormatIdc = chromaFormatIdc;
}

void SeqParmSet::SetBitDepth(uint8_t bitDepthLuma, uint8_t bitDepthChroma)
{
	this->bitDepthLuma = bitDepthLuma;
	this->bitDepthChroma = bitDepthChroma;
}

void SeqParmSet::SetLog2MaxFrameNum(uint32_t log2MaxFrameNum)
{
	this->log2MaxFrameNum = log2MaxFrameNum;
}

void SeqParmSet::SetPocType(uint8_t pocType)
{
	this->pocType = pocType;
}

void SeqParmSet::SetLog2MaxPocCnt(uint32_t maxLog2PocCnt)
{
	this->maxLog2PocCnt = maxLog2PocCnt;
}

void SeqParmSet::SetMaxNumRefFrames(uint32_t maxNumRefFrames)
{
	this->maxNumRefFrames = maxNumRefFrames;
}

void SeqParmSet::SetSpsMultipleFlags(struct SeqParmSetFlag &spsFlag)
{
	this->spsFlag = spsFlag;
}

void SeqParmSet::SetPicReslutionInMbs(uint16_t widthInMBs, uint16_t picHeightInMapUnits)
{
	this->picWidthInMBs = widthInMBs;
	this->picHeightInMapUnits = picHeightInMapUnits;
	this->picHeightInMBs = this->spsFlag.frameMBsOnlyFlag ? this->picHeightInMapUnits : 2 * this->picHeightInMapUnits;
}

void SeqParmSet::SetFrameCropOffset(uint32_t offsets[4])
{
	for (int i = 0; i < 4; i++) {
		this->frameCropOffset[i] = offsets[i];
	}
}

uint32_t SeqParmSet::GetLog2MaxFrameNum()
{
	return log2MaxFrameNum;
}

bool SeqParmSet::GetFrameMBsOnlyFlag()
{
	return spsFlag.frameMBsOnlyFlag;
}

uint8_t SeqParmSet::GetPocType()
{
	return pocType;
}

uint32_t SeqParmSet::GetLog2MaxLog2PocCnt()
{
	return maxLog2PocCnt;
}

uint16_t SeqParmSet::GetPicWidthInMBs()
{
	return picWidthInMBs;
}

uint16_t SeqParmSet::GetPicHeightInMBs()
{
	return picHeightInMBs;
}

