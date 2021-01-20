#include <cstdint>
#ifndef _SEQ_PARM_SET_H_
#define _SEQ_PARM_SET_H_

struct SeqParmSetFlag {
	uint32_t residualColourTransformFlag : 1;
	uint32_t qpprimeYZeroTransformBypassFlag : 1;
	uint32_t seqScalingMatrixPresentFlag : 1; // 量化矩阵是否存在
	uint32_t gapInframeNumValueAllowFlag : 1; // frame num 是否允许不连续
	uint32_t frameMBsOnlyFlag : 1;
	uint32_t mbAdaptiveFrameFieldFlag : 1;
	uint32_t direct8x8InferenceFlag : 1;
	uint32_t frameCroppingFlag : 1;
	uint32_t vuiParametersPresentFlag : 1;
};

class SeqParmSet
{
public:
	SeqParmSet();
	~SeqParmSet();
	void setProfileLevel(uint8_t profileIdc, uint8_t levelIdc);
	void setSpsId(uint8_t spsId);
	void setChromaFormatIdc(uint8_t chromaFormatIdc);
	void setBitDepth(uint8_t bitDepthLuma, uint8_t bitDepthChroma);
	
	void setMaxFrameNum(uint32_t maxFrameNum);
	void setPocType(uint8_t pocType);
	void setMaxPocCnt(uint32_t maxPocCnt);
	void setMaxNumRefFrames(uint32_t maxNumRefFrames);
	void setSpsMultipleFlags(struct SeqParmSetFlag &spsFlag);
	void setPicReslutionInMbs(uint16_t widthInMBs, uint16_t picHeightInMapUnits);
	void setFrameCropOffset(uint32_t offsets[4]);
private:
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
	uint16_t picHeightInMBs;
	uint32_t frameCropOffset[4];

	struct SeqParmSetFlag spsFlag;
};

#endif

