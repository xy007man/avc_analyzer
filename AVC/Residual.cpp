#include "Residual.h"

Residual::Residual(uint8_t* pSODB, uint8_t offset, MacroBlock* macroBlock)
{
	this->pSODB = pSODB;
	this->byteOffset = offset / 8;
	this->bitOffset = offset % 8;
	this->macroBlock = macroBlock;
}

Residual::~Residual()
{
}

int Residual::ParseMacroBlockResidual()
{
	return 0;
}
