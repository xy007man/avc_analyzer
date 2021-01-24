#include "ISlice.h"

ISlice::ISlice(uint8_t* pSODB, SeqParmSet* sps, PicParmSet* pps, int naulType)
	:pSODB(pSODB), sps(sps), pps(pps), naulType(naulType), sliceHeader(nullptr)
{
}

ISlice::~ISlice()
{
	if (sliceHeader != nullptr) {
		delete sliceHeader;
	}
}

int ISlice::ParseSlice()
{
	sliceHeader = new SliceHeader(pSODB, sps, pps, naulType); 
	sliceHeader->ParseSlice();
	return 0;
}
