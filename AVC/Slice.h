#ifndef _SLICE_H_
#define _SLICE_H_

#include "SeqParmSet.h"
#include "PicParmSet.h"
#include "SliceHeader.h"
#include "MacroBlock.h"

class Slice
{
public:
	Slice(uint8_t *pSODB, SeqParmSet *sps, PicParmSet *pps, int naulType);
	~Slice();
	int ParseSlice();
	SeqParmSet* GetSps();
	SliceHeader* GetSliceHeader();
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

