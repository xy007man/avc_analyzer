#include <cstdint>
#ifndef _SEQ_PARM_SET_H_
#define _SEQ_PARM_SET_H_

class SeqParmSet
{
public:
	SeqParmSet();
	~SeqParmSet();
	void SetProfileLevel(uint8_t profileIdc, uint8_t levelIdc);
	void SetSpsId(uint8_t spsId);
	void SetChromaFormatIdc(uint8_t chromaFormatIdc);
	void SetBitDepth(uint8_t bitDepthLuma, uint8_t bitDepthChroma);
	
	void SetMaxFrameNum(uint32_t maxFrameNum);
	void SetPocType(uint8_t pocType);
	void SetMaxPocCnt(uint32_t maxPocCnt);
	void SetMaxNumRefFrames(uint32_t maxNumRefFrames);
	void SetSpsMultipleFlags(uint32_t flags);
	void SetPicReslutionInMbs(uint16_t widthInMBs, uint16_t picHeightInMapUnits);
	void SetFrameCropOffset(uint32_t offsets[4]);
private:
	uint8_t profileIdc;
	uint8_t levelIdc;
	uint8_t spsId;

	uint8_t chromaFormatIdc;
	bool separateColourPlaneFlag;
	uint8_t bitDepthLuma;
	uint8_t bitDepthChroma;
	bool qpprimeYZeroTransformBypassFlag;
	bool seqScalingMatrixPresentFlag; // 量化矩阵是否存在

	uint32_t maxFrameNum;
	uint8_t pocType;
	uint32_t maxPocCnt;
	uint32_t maxNumRefFrames;
	bool gapInframeNumValueAllowFlag; // frame num 是否允许不连续
	uint16_t picWidthInMBs; // picWith = 16 * picWidthInMbs
	uint16_t picHeightInMapUnits;
	uint16_t picHeightInMBs;
	bool frameMBsOnlyFlag;
	bool mbAdaptiveFrameFieldFlag;
	bool direct8x8InferenceFlag;
	bool frameCroppingFlag;
	uint32_t frameCropOffset[4];

	bool vuiParametersPresentFlag;
};

#endif

