#ifndef _PIC_PARM_SET_H_
#define _PIC_PARM_SET_H_
#include <cstdint>

struct PicParmSetFlag {
	uint32_t entropyCodingModeFlag : 1;
	uint32_t picOrderPresentFlag : 1;
	uint32_t weightedPredFlag : 1;
	uint32_t deblockingFilterControlPresentFlag : 1;
	uint32_t constrainedIntraPredFlag : 1;
	uint32_t redundantPicCntPresentFlag : 1;
};

class PicParmSet
{
public:
	void SetPpsId(uint8_t ppsId);
	void SetSpsId(uint8_t spsId);
	void SetNumSliceGroups(uint8_t numSliceGroups);
	void SetNumRefIdxl0Active(uint8_t numRefIdxl0Active);
	void SetNumRefIdxl1Active(uint8_t numRefIdxl1Active);
	void SetWeightedBipredIdc(uint8_t weightedBipredIdc);
	void SetPicInitQp(int picInitQp);
	void SetPicInitQs(int picInitQs);
	void SetChromaQpIndexOffset(int chromaQpIndexOffset);
	void SetPpsMultipleFlags(PicParmSetFlag& ppsFlag);
	bool GetRedundantPicCntPresentFlag();
	bool GetPicOrderPresentFlag();
	bool GetTransform8x8ModeFlag();
	bool GetEntropyCodingModeFlag();
private:
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
};
#endif

