#ifndef _UTILS_H_
#define _UTILS_H_
#include <cstdint> 

int GetBitByPos(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos);
int GetUECode(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos);
int GetSECode(uint8_t* buf, uint8_t& bytePos, uint8_t& bitPos);

#endif
