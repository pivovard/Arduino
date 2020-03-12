#include "MAX30003.h"

int CS_PIN = 7;

void initSPI() {
	pinMode(CS_PIN, OUTPUT);
	digitalWrite(CS_PIN, HIGH);

	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void initSPI(int cs) {
	CS_PIN = cs;
	initSPI();
}

static uint8_t _checkAddr(uint8_t registerAddr)
{
	switch (registerAddr)
	{
	case _ECG3_NO_OP_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_STAT_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_EN_INT_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_EN_INT2_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_MNGR_INT_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_MNGR_DYN_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_SW_RST_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_SYNC_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_FIFO_RST_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_INFO_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_CNFG_GEN_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_CNFG_CAL_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_CNFG_EMUX_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_CNFG_ECG_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_CNFG_RTOR1_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_CNFG_RTOR2_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_ECG_FIFO_BURST_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_ECG_FIFO_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_RTOR_REG:
	{
		return _ECG3_OK;
	}
	case _ECG3_NO_OP2_REG:
	{
		return _ECG3_OK;
	}
	default:
	{
		return _ECG3_WRONG_ADDR;
	}
	}
}

uint8_t ecg3_writeReg(uint8_t regAddr, uint32_t dataIn)
{
	uint8_t tempData[4];
	uint8_t addrCheck;

	addrCheck = _checkAddr(regAddr);
	if (addrCheck)
	{
		return addrCheck;
	}

	tempData[0] = regAddr << 1;
	tempData[1] = dataIn >> 16;
	tempData[2] = dataIn >> 8;
	tempData[3] = dataIn;

	digitalWrite(CS_PIN, LOW);
	delay(1);
	//hal_spiWrite(tempData, 4);
	for (int i = 0; i < 4; ++i)
	{
		SPI.transfer(tempData[i]);
	}
	digitalWrite(CS_PIN, HIGH);
	delay(1);

	return addrCheck;
}

uint8_t ecg3_readReg(uint8_t regAddr, uint32_t *dataOut)
{
	uint8_t tempIn[4];
	uint8_t tempOut[4];
	uint8_t addrCheck;

	addrCheck = _checkAddr(regAddr);
	if (addrCheck)
	{
		return addrCheck;
	}

	tempIn[0] = regAddr << 1;
	tempIn[0] |= 1;
	tempIn[1] = _ECG3_DUMMY_BYTE;
	tempIn[2] = _ECG3_DUMMY_BYTE;
	tempIn[3] = _ECG3_DUMMY_BYTE;

	digitalWrite(CS_PIN, LOW);
	delay(1);
	//hal_spiTransfer(tempIn, tempOut, 4);
	for (int i = 0; i < 4; ++i)
	{
		tempOut[i] = SPI.transfer(tempIn[i]);
	}
	digitalWrite(CS_PIN, HIGH);
	delay(1);

	*dataOut = tempOut[1];
	*dataOut <<= 8;
	*dataOut |= tempOut[2];
	*dataOut <<= 8;
	*dataOut |= tempOut[3];

	return addrCheck;
}

uint8_t ecg3_checkStatus(uint32_t bitMask)
{
	uint32_t statData;

	ecg3_readReg(_ECG3_STAT_REG, &statData);

	if (statData & bitMask)
	{
		return _ECG3_INT_OCCURRED;
	}

	return _ECG3_INT_NOT_OCCURRED;
}

void ecg3_swReset(void)
{
	ecg3_writeReg(_ECG3_SW_RST_REG, _ECG3_SW_RST_CMD);
}

void ecg3_fifoReset(void)
{
	ecg3_writeReg(_ECG3_FIFO_RST_REG, _ECG3_FIFO_RST_CMD);
}

void ecg3_sync(void)
{
	ecg3_writeReg(_ECG3_SYNC_REG, _ECG3_SYNCH_CMD);
}

void ecg3_init(void)
{
	ecg3_writeReg(_ECG3_CNFG_GEN_REG, _ECG3_FMSTR_32768HZ_ECG_512HZ | _ECG3_ECG_CHANN_EN | _ECG3_DCLOFF_EN | _ECG3_RBIAS_100M_OHM | _ECG3_RBIASP_EN | _ECG3_RBIASN_EN);
	ecg3_writeReg(_ECG3_CNFG_CAL_REG, _ECG3_VCAL_EN | _ECG3_VMODE_BIPOL | _ECG3_VMAG_500MICROV);
	ecg3_writeReg(_ECG3_CNFG_EMUX_REG, _ECG3_ECGP_EN | _ECG3_ECGN_EN | _ECG3_ECGP_CAL_VCALP | _ECG3_ECGN_CAL_VCALN);
	ecg3_writeReg(_ECG3_CNFG_ECG_REG, 0x800000 | _ECG3_DHPF_500MILIHZ | _ECG3_DLPF_40HZ);
	ecg3_writeReg(_ECG3_CNFG_RTOR1_REG, _ECG3_WNDW_12 | _ECG3_RRGAIN_AUTO_SCALE | _ECG3_RTOR_EN | _ECG3_PAVG_8 | 0x000600);
}

void ecg3_getECG(uint32_t *outECG)
{
	ecg3_readReg(_ECG3_ECG_FIFO_REG, outECG);
	*outECG >>= 6;
}

void ecg3_getRTOR(uint16_t *outHR, uint16_t *outRR)
{
	uint32_t rtorTemp;
	float res;
	uint16_t resInt;

	ecg3_readReg(_ECG3_RTOR_REG, &rtorTemp);
	rtorTemp >>= 10;
	res = 60 / ((float)rtorTemp * 0.008);
	resInt = res;
	*outHR = resInt;

	resInt = (uint16_t)rtorTemp * 8;
	*outRR = resInt;
}

