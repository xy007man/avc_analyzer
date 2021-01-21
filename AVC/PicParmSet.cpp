#include "PicParmSet.h"

void PicParmSet::setPpsId(uint8_t ppsId)
{
	this->ppsId = ppsId;
}

void PicParmSet::setSpsId(uint8_t spsId)
{
	this->spsId = spsId;
}

void PicParmSet::setNumSliceGroups(uint8_t numSliceGroups)
{
	this->numSliceGroups = numSliceGroups;
}

void PicParmSet::setNumRefIdxl0Active(uint8_t numRefIdxl0Active)
{
	this->numRefIdxl0Active = numRefIdxl0Active;
}

void PicParmSet::setNumRefIdxl1Active(uint8_t numRefIdxl1Active)
{
	this->numRefIdxl1Active = numRefIdxl1Active;
}

void PicParmSet::setWeightedBipredIdc(uint8_t weightedBipredIdc)
{
	this->weightedBipredIdc = weightedBipredIdc;
}

void PicParmSet::setPicInitQp(int picInitQp)
{
	this->picInitQp = picInitQp;
}

void PicParmSet::setPicInitQs(int picInitQs)
{
	this->picInitQs = picInitQs;
}

void PicParmSet::setChromaQpIndexOffset(int chromaQpIndexOffset)
{
	this->chromaQpIndexOffset = chromaQpIndexOffset;
}

void PicParmSet::setPpsMultipleFlags(PicParmSetFlag& ppsFlag)
{
	this->ppsFlag = ppsFlag;
}
