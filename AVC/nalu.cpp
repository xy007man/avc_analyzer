#include "nalu.h"
#include "utils.h"
#include <cassert>

NALU::NALU(uint8_t* pSODB, uint32_t length):pSODB(pSODB), length(length) 
{

}

NALU::~NALU()
{

}

int NALU::parseSeqParmSet(SeqParmSet* sps)
{
	uint8_t bytePos = 3;
	uint8_t bitPos = 0;

	uint8_t profileIdc;
	uint8_t levelIdc;
	uint8_t spsId;

	uint8_t chromaFormatIdc;
	uint8_t bitDepthLuma;
	uint8_t bitDepthChroma;

	uint32_t maxFrameNum;
	uint8_t pocType;
	uint32_t maxPocCnt;
	uint32_t maxNumRefFrames;
	uint16_t picWidthInMBs; // picWith = 16 * picWidthInMbs
	uint16_t picHeightInMapUnits;
	uint32_t frameCropOffset[4] = { 0 };

	struct SeqParmSetFlag spsFlag;

	profileIdc = pSODB[0];
	levelIdc = pSODB[2];
	spsId = GetUECode(pSODB, bytePos, bitPos);

	sps->setProfileLevel(profileIdc, levelIdc);
	sps->setSpsId(spsId);

	if (profileIdc == 100 || profileIdc == 110 ||
		profileIdc == 122 || profileIdc == 144) {

		chromaFormatIdc = GetUECode(pSODB, bytePos, bitPos);
		sps->setChromaFormatIdc(chromaFormatIdc);
		if (chromaFormatIdc == 3) {
			spsFlag.residualColourTransformFlag = GetBitByPos(pSODB, bytePos, bitPos);
		}

		bitDepthLuma = GetUECode(pSODB, bytePos, bitPos) + 8;
		bitDepthChroma = GetUECode(pSODB, bytePos, bitPos) + 8;
		sps->setBitDepth(bitDepthLuma, bitDepthChroma);

		spsFlag.qpprimeYZeroTransformBypassFlag = GetBitByPos(pSODB, bytePos, bitPos);

		spsFlag.seqScalingMatrixPresentFlag = GetBitByPos(pSODB, bytePos, bitPos);
		if (spsFlag.seqScalingMatrixPresentFlag) {
			return -1; // TODO:
		}
	}

	maxFrameNum = 1 << (GetUECode(pSODB, bytePos, bitPos) + 4);
	sps->setMaxFrameNum(maxFrameNum);

	pocType = GetUECode(pSODB, bytePos, bitPos);
	sps->setPocType(pocType);

	if (pocType == 0) {
		maxPocCnt = 1 << (GetUECode(pSODB, bytePos, bitPos) + 4);
		sps->setMaxPocCnt(maxPocCnt);
	}
	else {
		return -1; // TODO:
	}

	maxNumRefFrames = GetUECode(pSODB, bytePos, bitPos);
	sps->setMaxFrameNum(maxNumRefFrames);

	spsFlag.gapInframeNumValueAllowFlag = GetBitByPos(pSODB, bytePos, bitPos);

	picWidthInMBs = GetUECode(pSODB, bytePos, bitPos) + 1;
	picHeightInMapUnits = GetUECode(pSODB, bytePos, bitPos) + 1;
	sps->setPicReslutionInMbs(picWidthInMBs, picHeightInMapUnits);

	spsFlag.frameMBsOnlyFlag = GetBitByPos(pSODB, bytePos, bitPos);
	if (!spsFlag.frameMBsOnlyFlag) {
		spsFlag.mbAdaptiveFrameFieldFlag = GetBitByPos(pSODB, bytePos, bitPos);
	}

	spsFlag.direct8x8InferenceFlag = GetBitByPos(pSODB, bytePos, bitPos);

	spsFlag.frameCroppingFlag = GetBitByPos(pSODB, bytePos, bitPos);
	if (spsFlag.frameCroppingFlag) {
		for (int i = 0; i < 4; i++) {
			frameCropOffset[i] = GetUECode(pSODB, bytePos, bitPos);
		}
	}
	sps->setFrameCropOffset(frameCropOffset);

	spsFlag.vuiParametersPresentFlag = GetBitByPos(pSODB, bytePos, bitPos);
	if (spsFlag.vuiParametersPresentFlag) {
		return -1; // TODO:
	}
	sps->setSpsMultipleFlags(spsFlag);

	return 0;
}

int NALU::parsePicParmSet(PicParmSet* picParmSet)
{
	uint8_t bytePos = 0;
	uint8_t bitPos = 0;

	uint8_t ppsId;
	uint8_t spsId;

	uint8_t numSliceGroups;
	uint8_t numRefIdxl0Active;
	uint8_t numRefIdxl1Active;

	uint8_t weightedBipredIdc; // ¼ÓÈ¨Ô¤²âË÷Òý
	int picInitQp;
	int picInitQs;
	int chromaQpIndexOffset;

	struct PicParmSetFlag ppsFlag;

	ppsId = GetUECode(pSODB, bytePos, bitPos);
	spsId = GetUECode(pSODB, bytePos, bitPos);
	ppsFlag.entropyCodingModeFlag = GetBitByPos(pSODB, bytePos, bitPos);
	ppsFlag.picOrderPresentFlag = GetBitByPos(pSODB, bytePos, bitPos);
	numSliceGroups = GetUECode(pSODB, bytePos, bitPos) + 1;

	if (numSliceGroups > 1) {
		return -1;
	}

	numRefIdxl0Active = GetUECode(pSODB, bytePos, bitPos) + 1;
	numRefIdxl1Active = GetUECode(pSODB, bytePos, bitPos) + 1;
	ppsFlag.weightedPredFlag = GetBitByPos(pSODB, bytePos, bitPos);
	weightedBipredIdc = (GetBitByPos(pSODB, bytePos, bitPos) << 1) + 
		GetBitByPos(pSODB, bytePos, bitPos);
	picInitQp = GetSECode(pSODB, bytePos, bitPos) + 26;
	picInitQs = GetSECode(pSODB, bytePos, bitPos) + 26;
	chromaQpIndexOffset = GetSECode(pSODB, bytePos, bitPos);
	ppsFlag.deblockingFilterControlPresentFlag = GetBitByPos(pSODB, bytePos, bitPos);
	ppsFlag.constrainedIntraPredFlag = GetBitByPos(pSODB, bytePos, bitPos);
	ppsFlag.redundantPicCntPresentFlag = GetBitByPos(pSODB, bytePos, bitPos);

	picParmSet->setPpsId(ppsId);
	picParmSet->setSpsId(spsId);
	picParmSet->setNumSliceGroups(numSliceGroups);
	picParmSet->setNumRefIdxl0Active(numRefIdxl0Active);
	picParmSet->setNumRefIdxl1Active(numRefIdxl1Active);
	picParmSet->setWeightedBipredIdc(weightedBipredIdc);
	picParmSet->setPicInitQp(picInitQp);
	picParmSet->setPicInitQs(picInitQs);
	picParmSet->setChromaQpIndexOffset(chromaQpIndexOffset);
	picParmSet->setPpsMultipleFlags(ppsFlag);

	return 0;
}
