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
uint32_t sample;
//***********************************Metodos****************************************//
void Timer_Init(uint32_t Value) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A, Value - 1);
	TimerControlTrigger(TIMER0_BASE, TIMER_A, true);
	TimerEnable(TIMER0_BASE, TIMER_A);
}


void DataGet(void) {
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 16);
	ADCIntClear(ADC0_BASE, 3);
	ADCSequenceDataGet(ADC0_BASE, 3, &sample);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);
}


//************************************Main******************************************//
int main(void){
	SysCtlClockSet(SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_4);
	IntMasterEnable();
	//Timer Setup
	Timer_Init(1133);

	//Pin para medidas

	//ADC Pin Setup
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4);

	//ADC Periph Setup
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_TIMER, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH11 | ADC_CTL_IE | ADC_CTL_END);
	//ADC Interrupts
	ADCIntEnable(ADC0_BASE, 3);
	IntEnable(INT_ADC0SS3);


	ADCSequenceEnable(ADC0_BASE, 3);

	while(1){
	}

}


