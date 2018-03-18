#include "INA219.h"

void PrintHandler(char c) {
  UART1_Write(c);
}


void main() {
	INA219_Init();
	UART1_Init(9600);
  	Delay_ms(100);

	
	while (1) {
	    float current_mA = getCurrent_mA();
	    float shuntVoltage_mV = getShuntVoltage_mV();
		float busVoltage_V = getBusVoltage_V();
		
        PrintOut(PrintHandler, "Current: %.2f", current_mA);
        Delay_ms(2000);
	}
}