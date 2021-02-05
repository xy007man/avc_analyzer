#include "SliceHeader.h"
#include "utils.h"

SliceHeader::SliceHeader(uint8_t* pSODB, SeqParmSet* sps, PicParmSet* pps, int naluType)
	: pSODB(pSODB), sps(sps), pps(pps), naluType(naluType)
{
}

SliceHeader::~SliceHeader()
{
}

int SliceHeader::ParseSlice()
{
	uint8_t bytePos = 0;
	uint8_t bitPos = 0;

	firstMbInSlice = GetUECode(pSODB, bytePos, bitPos);
	sliceType = GetUECode(pSODB, bytePos, bitPos);
	ppsId = GetUECode(pSODB, bytePos, bitPos);
	frameNum = GetUINTCode(pSODB, bytePos, bitPos, sps->GetLog2MaxFrameNum());

	if (!sps->GetFrameMBsOnlyFlag()) {
		sliceHeaderFlag.fieldPicFlag = GetUINTCode(pSODB, bytePos, bitPos, 1);
		if (sliceHeaderFlag.fieldPicFlag) {
			sliceHeaderFlag.bottomFieldFlag = GetUINTCode(pSODB, bytePos, bitPos, 1);
		}
	}

	if (naluType == 5) {
		idrPicId = GetUECode(pSODB, bytePos, bitPos);
	}

	if (sps->GetPocType() != 0) {
		// TODO
		return -1;
	}
	picOrderCntLsb = GetUINTCode(pSODB, bytePos, bitPos, sps->GetLog2MaxLog2PocCnt());
	if (pps->GetPicOrderPresentFlag() && !sliceHeaderFlag.fieldPicFlag) {
		deltaPicOrderCntBottom = GetSECode(pSODB, bytePos, bitPos);
	}

	if (pps->GetRedundantPicCntPresentFlag()) {
		return -1;
	}

	// nal_ref_id
	if (naluType == 5) {
		sliceHeaderFlag.noOutputOfPriorPicsFlag = GetUINTCode(pSODB, bytePos, bitPos, 1);
		sliceHeaderFlag.longTermReferenceFlag = GetUINTCode(pSODB, bytePos, bitPos, 1);
	}

	sliceQpDelta = GetSECode(pSODB, bytePos, bitPos);

	return bytePos * 8 + bitPos;
}

uint8_t SliceHeader::GetSliceType()
{
	return this->sliceType;
}
