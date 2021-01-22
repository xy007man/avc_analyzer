#ifndef _NAUL_H_
#define _NAUL_H_
#include <cstdint>
#include "SeqParmSet.h"
#include "PicParmSet.h"

class NALU {
public:
	NALU(uint8_t *pSODB, uint32_t length);
	~NALU();
	int parseSeqParmSet(SeqParmSet *seqParmSet);
	int parsePicParmSet(PicParmSet* picParmSet);
private:
	uint8_t *pSODB;
	uint32_t length;
};
#endif

