#ifndef _SEQ_PARM_SET_H_
#define _SEQ_PARM_SET_H_
#include <cstdint>
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
	void SetProfileLevel(uint8_t profileIdc, uint8_t levelIdc);
	void SetSpsId(uint8_t spsId);
	void SetChromaFormatIdc(uint8_t chromaFormatIdc);
	void SetBitDepth(uint8_t bitDepthLuma, uint8_t bitDepthChroma);
	
	void SetLog2MaxFrameNum(uint32_t maxFrameNum);
	void SetPocType(uint8_t pocType);
	void SetLog2MaxPocCnt(uint32_t maxLog2PocCnt);
	void SetMaxNumRefFrames(uint32_t maxNumRefFrames);
	void SetSpsMultipleFlags(SeqParmSetFlag &spsFlag);
	void SetPicReslutionInMbs(uint16_t widthInMBs, uint16_t picHeightInMapUnits);
	void SetFrameCropOffset(uint32_t offsets[4]);
	uint32_t GetLog2MaxFrameNum();
	bool GetFrameMBsOnlyFlag();
	uint8_t GetPocType();
	uint32_t GetLog2MaxLog2PocCnt();
private:
	uint8_t profileIdc;
	uint8_t levelIdc;
	uint8_t spsId;

	uint8_t chromaFormatIdc = 1;
	uint8_t bitDepthLuma;
	uint8_t bitDepthChroma;

	uint32_t log2MaxFrameNum;
	uint8_t pocType;
	uint32_t maxLog2PocCnt;
	uint32_t maxNumRefFrames;
	uint16_t picWidthInMBs; // picWith = 16 * picWidthInMbs
	uint16_t picHeightInMapUnits;
	uint16_t picHeightInMBs;
	uint32_t frameCropOffset[4];

	struct SeqParmSetFlag spsFlag;
};

#endif

