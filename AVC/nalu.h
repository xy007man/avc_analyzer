
#ifndef _NAUL_H_
#define _NAUL_H_
#include <cstdint>
class NALU {
public:
	NALU(uint8_t *pSODB, uint32_t length);
	~NALU();
private:
	uint8_t *m_pSODB;
	uint32_t m_length;
};
#endif

