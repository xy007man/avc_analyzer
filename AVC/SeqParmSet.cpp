#include "SeqParmSet.h"

SeqParmSet::SeqParmSet()
{

}
SeqParmSet::~SeqParmSet()
{
}

void SeqParmSet::setProfileLevel(uint8_t profileIdc, uint8_t levelIdc)
{
	this->profileIdc = profileIdc;
	this->levelIdc = levelIdc;
}

void SeqParmSet::setSpsId(uint8_t spsId)
{
	this->spsId = spsId;
}

void SeqParmSet::setChromaFormatIdc(uint8_t chromaFormatIdc)
{
	this->chromaFormatIdc = chromaFormatIdc;
}

void SeqParmSet::setBitDepth(uint8_t bitDepthLuma, uint8_t bitDepthChroma)
{
	this->bitDepthLuma = bitDepthLuma;
	this->bitDepthChroma = bitDepthChroma;
}

void SeqParmSet::setMaxFrameNum(uint32_t maxFrameNum)
{
	this->maxFrameNum = maxFrameNum;
}

void SeqParmSet::setPocType(uint8_t pocType)
{
	this->pocType = pocType;
}

void SeqParmSet::setMaxPocCnt(uint32_t maxPocCnt)
{
	this->maxPocCnt = maxPocCnt;
}

void SeqParmSet::setMaxNumRefFrames(uint32_t maxNumRefFrames)
{
	this->maxNumRefFrames = maxNumRefFrames;
}

void SeqParmSet::setSpsMultipleFlags(struct SeqParmSetFlag &spsFlag)
{
	this->spsFlag = spsFlag;
}

void SeqParmSet::setPicReslutionInMbs(uint16_t widthInMBs, uint16_t picHeightInMapUnits)
{
	this->picWidthInMBs = picWidthInMBs;
	this->picHeightInMapUnits = picHeightInMapUnits;
	this->picHeightInMBs = this->spsFlag.frameMBsOnlyFlag ? this->picHeightInMapUnits : 2 * this->picHeightInMapUnits;
}

void SeqParmSet::setFrameCropOffset(uint32_t offsets[4])
{
	for (int i = 0; i < 4; i++) {
		this->frameCropOffset[i] = offsets[i];
	}
}