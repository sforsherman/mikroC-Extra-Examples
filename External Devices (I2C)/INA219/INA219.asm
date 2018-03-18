
_test:

;INA219.c,3 :: 		void test(char err){
;INA219.c,4 :: 		if(err == _I2C_TIMEOUT_RD)
	MOVF        FARG_test_err+0, 0 
	XORLW       3
	BTFSS       STATUS+0, 2 
	GOTO        L_test0
;INA219.c,5 :: 		RA0_bit = 1;
	BSF         RA0_bit+0, BitPos(RA0_bit+0) 
L_test0:
;INA219.c,6 :: 		if(err == _I2C_TIMEOUT_WR)
	MOVF        FARG_test_err+0, 0 
	XORLW       4
	BTFSS       STATUS+0, 2 
	GOTO        L_test1
;INA219.c,7 :: 		RA1_bit = 1;
	BSF         RA1_bit+0, BitPos(RA1_bit+0) 
L_test1:
;INA219.c,8 :: 		}
L_end_test:
	RETURN      0
; end of _test

_INA219_Init:

;INA219.c,10 :: 		void INA219_Init (void) {
;INA219.c,11 :: 		I2C1_Init(100000);
	MOVLW       40
	MOVWF       SSPADD+0 
	CALL        _I2C1_Init+0, 0
;INA219.c,12 :: 		I2C1_SetTimeoutCallback(1000,&test);
	MOVLW       232
	MOVWF       FARG_I2C1_SetTimeoutCallback_timeout+0 
	MOVLW       3
	MOVWF       FARG_I2C1_SetTimeoutCallback_timeout+1 
	MOVLW       0
	MOVWF       FARG_I2C1_SetTimeoutCallback_timeout+2 
	MOVWF       FARG_I2C1_SetTimeoutCallback_timeout+3 
	MOVLW       _test+0
	MOVWF       FARG_I2C1_SetTimeoutCallback_i2c1_timeout+0 
	MOVLW       hi_addr(_test+0)
	MOVWF       FARG_I2C1_SetTimeoutCallback_i2c1_timeout+1 
	MOVLW       FARG_test_err+0
	MOVWF       FARG_I2C1_SetTimeoutCallback_i2c1_timeout+2 
	MOVLW       hi_addr(FARG_test_err+0)
	MOVWF       FARG_I2C1_SetTimeoutCallback_i2c1_timeout+3 
	CALL        _I2C1_SetTimeoutCallback+0, 0
;INA219.c,13 :: 		}
L_end_INA219_Init:
	RETURN      0
; end of _INA219_Init

_writeRegister:

;INA219.c,15 :: 		void writeRegister (unsigned char reg, unsigned short value) {
;INA219.c,16 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;INA219.c,17 :: 		I2C1_Wr(INA219_ADDRESS);
	MOVLW       64
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;INA219.c,18 :: 		I2C1_Wr((value >> 8) & 0xFF);
	CLRF        FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;INA219.c,19 :: 		I2C1_Wr(value & 0xFF);
	MOVLW       255
	ANDWF       FARG_writeRegister_value+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;INA219.c,20 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;INA219.c,21 :: 		}
L_end_writeRegister:
	RETURN      0
; end of _writeRegister

_readRegister:

;INA219.c,23 :: 		void readRegister (unsigned char reg, unsigned int *value) {
;INA219.c,25 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;INA219.c,26 :: 		I2C1_Wr(INA219_ADDRESS);
	MOVLW       64
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;INA219.c,27 :: 		I2C1_Wr(reg);
	MOVF        FARG_readRegister_reg+0, 0 
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;INA219.c,28 :: 		I2C1_Repeated_Start();
	CALL        _I2C1_Repeated_Start+0, 0
;INA219.c,29 :: 		*value = ((I2C1_Rd(1) << 8) | I2C1_Rd(0));
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       FLOC__readRegister+1 
	CLRF        FLOC__readRegister+0 
	CLRF        FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVLW       0
	MOVWF       R1 
	MOVF        FLOC__readRegister+0, 0 
	IORWF       R0, 1 
	MOVF        FLOC__readRegister+1, 0 
	IORWF       R1, 1 
	MOVFF       FARG_readRegister_value+0, FSR1
	MOVFF       FARG_readRegister_value+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	MOVF        R1, 0 
	MOVWF       POSTINC1+0 
;INA219.c,30 :: 		}
L_end_readRegister:
	RETURN      0
; end of _readRegister

_setCalibration_32V_2A:

;INA219.c,32 :: 		void setCalibration_32V_2A (void)
;INA219.c,34 :: 		ina219_calibrationValue = 4096;
	MOVLW       0
	MOVWF       INA219_ina219_calibrationValue+0 
	MOVLW       16
	MOVWF       INA219_ina219_calibrationValue+1 
;INA219.c,36 :: 		ina219_currentDivider_mA = 100;
	MOVLW       100
	MOVWF       INA219_ina219_currentDivider_mA+0 
	MOVLW       0
	MOVWF       INA219_ina219_currentDivider_mA+1 
;INA219.c,37 :: 		ina219_powerMultiplier_mW = 2;
	MOVLW       2
	MOVWF       INA219_ina219_powerMultiplier_mW+0 
	MOVLW       0
	MOVWF       INA219_ina219_powerMultiplier_mW+1 
;INA219.c,39 :: 		writeRegister(INA219_REG_CALIBRATION, ina219_calibrationValue);
	MOVLW       5
	MOVWF       FARG_writeRegister_reg+0 
	MOVLW       0
	MOVWF       FARG_writeRegister_value+0 
	CALL        _writeRegister+0, 0
;INA219.c,41 :: 		writeRegister(INA219_REG_CONFIG, (INA219_CONFIG_BVOLTAGERANGE_32V |
	CLRF        FARG_writeRegister_reg+0 
;INA219.c,45 :: 		INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS));
	MOVLW       159
	MOVWF       FARG_writeRegister_value+0 
	CALL        _writeRegister+0, 0
;INA219.c,46 :: 		}
L_end_setCalibration_32V_2A:
	RETURN      0
; end of _setCalibration_32V_2A
