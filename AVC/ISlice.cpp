#include "ISlice.h"
#include <memory>

ISlice::ISlice(uint8_t* pSODB, SeqParmSet* sps, PicParmSet* pps, int naulType)
	:pSODB(pSODB), sps(sps), pps(pps), naulType(naulType), sliceHeader(nullptr)
{
	maxMBNum = sps->GetPicHeightInMBs() * sps->GetPicWidthInMBs();
	mbs = new MacroBlock*[maxMBNum];
	memset(mbs, 0, sizeof(MacroBlock*) * maxMBNum);
}

ISlice::~ISlice()
{
	if (sliceHeader != nullptr) {
		delete sliceHeader;
	}

	for (int i = 0; i < maxMBNum; i++) {
		if (mbs[i] != nullptr)
			delete mbs[i];
	}
	delete mbs;
}

int ISlice::ParseSlice()
{
	int bitLength;
	uint8_t macroBlockOffset;
	sliceHeader = new SliceHeader(pSODB, sps, pps, naulType); 
	bitLength = sliceHeader->ParseSlice();
	if (bitLength <= 0) {
		return -1;
	}
	macroBlockOffset = bitLength;
	for (int i = 0; i < maxMBNum; i++) {
		mbs[i] = new MacroBlock(pSODB, macroBlockOffset, pps);
		bitLength = mbs[i]->ParseMacroBlock();
		if (bitLength <= 0) {
			return -1;
		}
		macroBlockOffset += bitLength;
	}

	return 0;
}
