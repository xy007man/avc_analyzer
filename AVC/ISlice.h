#ifndef _I_SLICE_H_
#define _I_SLICE_H_

#include "SeqParmSet.h"
#include "PicParmSet.h"
#include "SliceHeader.h"
#include "MacroBlock.h"

class ISlice
{
public:
	ISlice(uint8_t *pSODB, SeqParmSet *sps, PicParmSet *pps, int naulType);
	~ISlice();
	int ParseSlice();
private:
	uint8_t *pSODB;
	int naulType;
	SeqParmSet *sps;
	PicParmSet *pps;
	SliceHeader *sliceHeader;
	uint16_t maxMBNum;

	MacroBlock **mbs;
};
#endif

