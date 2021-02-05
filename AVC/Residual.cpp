#include "Residual.h"
#include "cavlc.h"

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
	uint8_t cbpLuma = macroBlock->GetCbpLuma();
	uint8_t cbpChroma = macroBlock->GetCbpChroma();

	if (cbpLuma) {
		ParseLumaResidual(cbpLuma);
	}

	return 0;
}



int Residual::ParseLumaResidual(uint8_t cbpLuma)
{

	int idx8x8;

	for (int y = 0; y < 4; y += 2) {
		for (int x = 0; x < 4; x += 2) {
			// 16x16 -> 4 * 8x8
			if (macroBlock->GetPps()->GetEntropyCodingModeFlag()) {
				// cavac
			}
			else {
				// (0, 0) (2, 0) (0, 2) (2, 2) 8x8 -> 4 * 4x4
				for (int subY = y; subY < y + 2; subY++) {
					for (int subX = x; subX < x + 2; subX++) {
						idx8x8 = y + x / 2; // 8x8¿éµÄË÷Òý
						if (cbpLuma & (1 << idx8x8)) {
							this->lumaResidual[subX][subY].emptyBlock = false;
							if (GetLuma4x4Coeffs(subX, subY) < 0) {
								return -1;
							}
						}
						else {
							this->lumaResidual[subX][subY].emptyBlock = true;
						}
					}
				}
			}
		}
	}

	return 0;
}

int Residual::GetLuma4x4Coeffs(int subX, int subY)
{
	uint8_t mbType = macroBlock->GetMbType();
	uint8_t blockType = (mbType == IPCM || mbType == I16MB) ? LUMA_INTRA16x16AC : LUMA;
	int maxCoeffNum = 0;
	int numCoeffVlcIdx = 0;
	int prefixLength = 0;
	int suffixLength = 0;
	int levelPrefix = 0;
	int levelSuffix = 0;
	int levelSuffixSize = 0;
	int levelCode = 0;
	
	switch (blockType) {
		case LUMA:
			maxCoeffNum = 16;

		case LUMA_INTRA16x16AC:
			break;
		case LUMA_INTRA16x16DC:
			break;
		default:
			break;
	}

	int nC = macroBlock->GetNumberCurrent(subX, subY);
	return 0;
}

int Residual::GetSubBlockNumCoeff(int subX, int subY)
{
	return this->lumaResidual[subX][subY].numCoeff;
}
