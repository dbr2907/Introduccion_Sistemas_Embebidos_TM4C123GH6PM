//********************************Librerias*****************************************//
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
//******************************Librerias Extras************************************//
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"
//*********************************Definiciones*************************************//

//**********************************Variables***************************************//
uint32_t sample[4];
int Promedio;
short Centigrados;
//***********************************Metodos****************************************//

//************************************Main******************************************//
int main(void){
	SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_XTAL_16MHZ);
	//ADC Setup
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 3,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);

	while(1)  {

		ADCIntClear(ADC0_BASE, 1);
		ADCProcessorTrigger(ADC0_BASE, 1);
		while(!ADCIntStatus(ADC0_BASE, 1, false)){ }
    ADCSequenceDataGet(ADC0_BASE, 1, sample);
    Promedio = (sample[0] + sample[1] + sample[2] + sample[3])/4;
    Centigrados = (1475 - ((2475 * Promedio)) / 4096)/10;
	}
}
