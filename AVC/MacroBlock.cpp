#include "MacroBlock.h"

MacroBlock::MacroBlock(uint8_t* pSODB, uint32_t offset)
{
	this->pSODB = pSODB;
	byteOffset = offset / 8;
	bitOffset = offset % 8;
}

MacroBlock::~MacroBlock()
{
}
