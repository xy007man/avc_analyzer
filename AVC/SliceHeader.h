#ifndef _SLICE_HEADER_H_
#define _SLICE_HEADER_H_
#include "SeqParmSet.h"
#include "PicParmSet.h"

struct SliceHeaderFlag {
	uint32_t fieldPicFlag : 1;
	uint32_t bottomFieldFlag : 1;
	uint32_t noOutputOfPriorPicsFlag : 1;
	uint32_t longTermReferenceFlag : 1;
};

class SliceHeader
{
public:
	SliceHeader(uint8_t* pSODB, SeqParmSet* sps, PicParmSet* pps, int naluType);
	~SliceHeader();
	int ParseSlice();

private:
	uint8_t *pSODB;
	int naluType;
	SeqParmSet *sps;
	PicParmSet *pps;

	uint16_t firstMbInSlice;
	uint8_t sliceType;
	uint8_t ppsId;
	uint32_t frameNum;
	uint16_t idrPicId;
	uint32_t picOrderCntLsb;
	int deltaPicOrderCntBottom;
	int sliceQpDelta;

	struct SliceHeaderFlag sliceHeaderFlag;
};
#endif
