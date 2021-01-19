#include "SeqParmSet.h"

SeqParmSet::SeqParmSet()
{

}
SeqParmSet::~SeqParmSet()
{
}

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

void SeqParmSet::SetMaxFrameNum(uint32_t maxFrameNum)
{
	this->maxFrameNum = maxFrameNum;
}

void SeqParmSet::SetPocType(uint8_t pocType)
{
	this->pocType = pocType;
}

void SeqParmSet::SetMaxPocCnt(uint32_t maxPocCnt)
{
	this->maxPocCnt = maxPocCnt;
}

void SeqParmSet::SetMaxNumRefFrames(uint32_t maxNumRefFrames)
{
	this->maxNumRefFrames = maxNumRefFrames;
}

void SeqParmSet::SetSpsMultipleFlags(uint32_t flags)
{
	
}

void SeqParmSet::SetPicReslutionInMbs(uint16_t widthInMBs, uint16_t picHeightInMapUnits)
{
	this->picWidthInMBs = picWidthInMBs;
	this->picHeightInMapUnits = picHeightInMapUnits;
	this->picHeightInMBs = this->frameMBsOnlyFlag ? this->picHeightInMapUnits : 2 * this->picHeightInMapUnits;
}

void SeqParmSet::SetFrameCropOffset(uint32_t offsets[4])
{
	for (int i = 0; i < 4; i++) {
		this->frameCropOffset[i] = offsets[i];
	}
}