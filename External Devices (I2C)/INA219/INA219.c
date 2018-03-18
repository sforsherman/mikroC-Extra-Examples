#include "INA219.h"

void test(char err){
  if(err == _I2C_TIMEOUT_RD)
    RA0_bit = 1;
  if(err == _I2C_TIMEOUT_WR)
    RA1_bit = 1;
}

void INA219_Init (void) {
    I2C1_Init(100000);
  	I2C1_SetTimeoutCallback(1000,&test);
  	
  	ina219_currentDivider_mA = 0;
 	ina219_powerMultiplier_mW = 0;
 	
 	// Option 1: setCalibration_32V_2A();
 	// Option 2: setCalibration_32V_1A();
 	setCalibration_16V_400mA(); // Option 3
}

void writeRegister (unsigned char reg, unsigned short value) {
    I2C1_Start();
    I2C1_Wr(ina219_i2cAddress);
    I2C1_Wr((value >> 8) & 0xFF);
    I2C1_Wr(value & 0xFF);
	I2C1_Stop();
}

void readRegister (unsigned char reg, unsigned int *value) {

	I2C1_Start();
    I2C1_Wr(ina219_i2cAddress);
    I2C1_Wr(reg);
    I2C1_Repeated_Start();
    *value = ((I2C1_Rd(1) << 8) | I2C1_Rd(0));
}

void setCalibration_32V_2A (void) {
	ina219_calibrationValue = 4096;
	
	ina219_currentDivider_mA = 100;
 	ina219_powerMultiplier_mW = 2;
 	
 	writeRegister(INA219_REG_CALIBRATION, ina219_calibrationValue);
 	
 	writeRegister(INA219_REG_CONFIG, (INA219_CONFIG_BVOLTAGERANGE_32V |
 	INA219_CONFIG_GAIN_8_320MV |
 	INA219_CONFIG_BADCRES_12BIT |
 	INA219_CONFIG_SADCRES_12BIT_1S_532US |
 	INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS));
}

void setCalibration_32V_1A (void) {
    ina219_calibrationValue = 10240;
    
    ina219_currentDivider_mA = 25;
 	ina219_powerMultiplier_mW = 1;
 	
 	writeRegister(INA219_REG_CALIBRATION, ina219_calibrationValue);
 	
 	writeRegister(INA219_REG_CONFIG, (INA219_CONFIG_BVOLTAGERANGE_32V |
                    INA219_CONFIG_GAIN_8_320MV |
                    INA219_CONFIG_BADCRES_12BIT |
                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS));
}

void setCalibration_16V_400mA (void) {
    ina219_calibrationValue = 8192;
    
    ina219_currentDivider_mA = 20;
 	ina219_powerMultiplier_mW = 1;
 	
 	writeRegister(INA219_REG_CALIBRATION, ina219_calibrationValue);
 	
	writeRegister(INA219_REG_CONFIG, (INA219_CONFIG_BVOLTAGERANGE_16V |
                    INA219_CONFIG_GAIN_1_40MV |
                    INA219_CONFIG_BADCRES_12BIT |
                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS));
}

short getBusVoltage_raw (void) {
	short value;
	
	readRegister(INA219_REG_BUSVOLTAGE, &value);
	
	return (short)((value >> 3) * 4);
}

short getShuntVoltage_raw (void) {
	short value;
	
	readRegister(INA219_REG_SHUNTVOLTAGE, &value);
	
	return (short) value;
}

short getCurrent_raw (void) {
	short value;
	
	writeRegister(INA219_REG_CALIBRATION, ina219_calibrationValue);
	
	readRegister(INA219_REG_CURRENT, &value);
	
	return (short) value;
}

short getPower_raw (void) {
    short value;
    
    writeRegister(INA219_REG_CALIBRATION, ina219_calibrationValue);
    
    writeRegister(INA219_REG_POWER, &value);
    
    return (short) value;
}

float getBusVoltage_V (void) {
	short value = getBusVoltage_raw();
	return value * 0.001;
}

float getShuntVoltage_mV (void) {
	short value = getShuntVoltage_raw();
	
	return value * 0.01;
}

float getCurrent_mA (void) {
    float valueDec = getCurrent_raw();
    
    valueDec /= ina219_currentDivider_mA;
    
    return valueDec;
}

float getPower_mW (void) {
    float valueDec = getPower_raw();
  	valueDec *= ina219_powerMultiplier_mW;
  	return valueDec;
}