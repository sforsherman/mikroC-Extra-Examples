#line 1 "C:/Program Files (x86)/Mikroelektronika/mikroC PRO for PIC/Examples/Development Systems/EASYPIC7/External Devices (I2C)/INA219/INA219.c"
#line 1 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/examples/development systems/easypic7/external devices (i2c)/ina219/ina219.h"
#line 29 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/examples/development systems/easypic7/external devices (i2c)/ina219/ina219.h"
enum{
 INA219_CONFIG_BVOLTAGERANGE_16V = (0x0000),
 INA219_CONFIG_BVOLTAGERANGE_32V = (0x2000)
};
#line 42 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/examples/development systems/easypic7/external devices (i2c)/ina219/ina219.h"
enum {
 INA219_CONFIG_GAIN_1_40MV = (0x0000),
 INA219_CONFIG_GAIN_2_80MV = (0x0800),
 INA219_CONFIG_GAIN_4_160MV = (0x1000),
 INA219_CONFIG_GAIN_8_320MV = (0x1800)
};
#line 57 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/examples/development systems/easypic7/external devices (i2c)/ina219/ina219.h"
enum {
 INA219_CONFIG_BADCRES_9BIT = (0x0000),
 INA219_CONFIG_BADCRES_10BIT = (0x0080),
 INA219_CONFIG_BADCRES_11BIT = (0x0100),
 INA219_CONFIG_BADCRES_12BIT = (0x0180)
};
#line 72 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/examples/development systems/easypic7/external devices (i2c)/ina219/ina219.h"
enum {
 INA219_CONFIG_SADCRES_9BIT_1S_84US = (0x0000),
 INA219_CONFIG_SADCRES_10BIT_1S_148US = (0x0008),
 INA219_CONFIG_SADCRES_11BIT_1S_276US = (0x0010),
 INA219_CONFIG_SADCRES_12BIT_1S_532US = (0x0018),
 INA219_CONFIG_SADCRES_12BIT_2S_1060US = (0x0048),
 INA219_CONFIG_SADCRES_12BIT_4S_2130US = (0x0050),
 INA219_CONFIG_SADCRES_12BIT_8S_4260US = (0x0058),
 INA219_CONFIG_SADCRES_12BIT_16S_8510US = (0x0060),
 INA219_CONFIG_SADCRES_12BIT_32S_17MS = (0x0068),
 INA219_CONFIG_SADCRES_12BIT_64S_34MS = (0x0070),
 INA219_CONFIG_SADCRES_12BIT_128S_69MS = (0x0078)
};
#line 94 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/examples/development systems/easypic7/external devices (i2c)/ina219/ina219.h"
enum {
 INA219_CONFIG_MODE_POWERDOWN = (0x0000),
 INA219_CONFIG_MODE_SVOLT_TRIGGERED = (0x0001),
 INA219_CONFIG_MODE_BVOLT_TRIGGERED = (0x0002),
 INA219_CONFIG_MODE_SANDBVOLT_TRIGGERED = (0x0003),
 INA219_CONFIG_MODE_ADCOFF = (0x0004),
 INA219_CONFIG_MODE_SVOLT_CONTINUOUS = (0x0005),
 INA219_CONFIG_MODE_BVOLT_CONTINUOUS = (0x0006),
 INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS = (0x0007)
};
#line 130 "c:/program files (x86)/mikroelektronika/mikroc pro for pic/examples/development systems/easypic7/external devices (i2c)/ina219/ina219.h"
void writeRegister (unsigned char reg, unsigned int value);
void readRegister (unsigned char reg, unsigned int *value);
short getBusVoltage_raw (void);
short getShuntVoltage_raw (void);
short getCurrent_raw (void);
short getPower_raw (void);

void setCalibration_32V_2A (void);
void setCalibration_32V_1A (void);
void setCalibration_16V_400mA (void);
float getBusVoltage_V (void);
float getShuntVoltage_mV (void);
float getCurrent_mA (void);
float getPower_mW (void);


void INA219_Init (void);

static int ina219_i2cAddress;
static int ina219_calibrationValue;
static int ina219_currentDivider_mA;
static int ina219_powerMultiplier_mW;
#line 3 "C:/Program Files (x86)/Mikroelektronika/mikroC PRO for PIC/Examples/Development Systems/EASYPIC7/External Devices (I2C)/INA219/INA219.c"
void test(char err){
 if(err == _I2C_TIMEOUT_RD)
 RA0_bit = 1;
 if(err == _I2C_TIMEOUT_WR)
 RA1_bit = 1;
}

void INA219_Init (void) {
 I2C1_Init(100000);
 I2C1_SetTimeoutCallback(1000,&test);
}

void writeRegister (unsigned char reg, unsigned short value) {
 I2C1_Start();
 I2C1_Wr( (0x40) );
 I2C1_Wr((value >> 8) & 0xFF);
 I2C1_Wr(value & 0xFF);
 I2C1_Stop();
}

void readRegister (unsigned char reg, unsigned int *value) {

 I2C1_Start();
 I2C1_Wr( (0x40) );
 I2C1_Wr(reg);
 I2C1_Repeated_Start();
 *value = ((I2C1_Rd(1) << 8) | I2C1_Rd(0));
}

void setCalibration_32V_2A (void)
{
 ina219_calibrationValue = 4096;

 ina219_currentDivider_mA = 100;
 ina219_powerMultiplier_mW = 2;

 writeRegister( (0x05) , ina219_calibrationValue);

 writeRegister( (0x00) , (INA219_CONFIG_BVOLTAGERANGE_32V |
 INA219_CONFIG_GAIN_8_320MV |
 INA219_CONFIG_BADCRES_12BIT |
 INA219_CONFIG_SADCRES_12BIT_1S_532US |
 INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS));
}
