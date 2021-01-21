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
	void setPpsId(uint8_t ppsId);
	void setSpsId(uint8_t spsId);
	void setNumSliceGroups(uint8_t numSliceGroups);
	void setNumRefIdxl0Active(uint8_t numRefIdxl0Active);
	void setNumRefIdxl1Active(uint8_t numRefIdxl1Active);
	void setWeightedBipredIdc(uint8_t weightedBipredIdc);
	void setPicInitQp(int picInitQp);
	void setPicInitQs(int picInitQs);
	void setChromaQpIndexOffset(int chromaQpIndexOffset);
	void setPpsMultipleFlags(PicParmSetFlag& ppsFlag);

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

