#include "PicParmSet.h"

void PicParmSet::SetPpsId(uint8_t ppsId)
{
	this->ppsId = ppsId;
}

void PicParmSet::SetSpsId(uint8_t spsId)
{
	this->spsId = spsId;
}

void PicParmSet::SetNumSliceGroups(uint8_t numSliceGroups)
{
	this->numSliceGroups = numSliceGroups;
}

void PicParmSet::SetNumRefIdxl0Active(uint8_t numRefIdxl0Active)
{
	this->numRefIdxl0Active = numRefIdxl0Active;
}

void PicParmSet::SetNumRefIdxl1Active(uint8_t numRefIdxl1Active)
{
	this->numRefIdxl1Active = numRefIdxl1Active;
}

void PicParmSet::SetWeightedBipredIdc(uint8_t weightedBipredIdc)
{
	this->weightedBipredIdc = weightedBipredIdc;
}

void PicParmSet::SetPicInitQp(int picInitQp)
{
	this->picInitQp = picInitQp;
}

void PicParmSet::SetPicInitQs(int picInitQs)
{
	this->picInitQs = picInitQs;
}

void PicParmSet::SetChromaQpIndexOffset(int chromaQpIndexOffset)
{
	this->chromaQpIndexOffset = chromaQpIndexOffset;
}

void PicParmSet::SetPpsMultipleFlags(PicParmSetFlag& ppsFlag)
{
	this->ppsFlag = ppsFlag;
}

bool PicParmSet::GetRedundantPicCntPresentFlag()
{
	return ppsFlag.redundantPicCntPresentFlag;
}

bool PicParmSet::GetPicOrderPresentFlag()
{
	return ppsFlag.picOrderPresentFlag;
}

bool PicParmSet::GetTransform8x8ModeFlag()
{
	return false;
}

bool PicParmSet::GetEntropyCodingModeFlag()
{
	return ppsFlag.entropyCodingModeFlag;
}
