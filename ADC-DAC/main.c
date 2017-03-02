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
#include "driverlib/ssi.h"
#include "driverlib/pin_map.h"
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

void SSI_Init(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	// Configurar los pines
	GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5);
	GPIOPinConfigure(GPIO_PA2_SSI0CLK);
	GPIOPinConfigure(GPIO_PA3_SSI0FSS);
	GPIOPinConfigure(GPIO_PA5_SSI0TX);
	SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_TI, SSI_MODE_MASTER, 2000000, 16);
	SSIEnable(SSI0_BASE);
}


void DataGet(void) {
	ADCIntClear(ADC0_BASE, 3);
	ADCSequenceDataGet(ADC0_BASE, 3, &sample);
	SSIDataPut(SSI0_BASE, sample);
}


//************************************Main******************************************//
int main(void){
	SysCtlClockSet(SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_4);
	IntMasterEnable();
	//Inits
	Timer_Init(1133);
	SSI_Init();

	//ADC Pin Setup
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_5);
	//ADC Periph Setup
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_TIMER, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH11 | ADC_CTL_IE | ADC_CTL_END);
	//ADC Interrupts
	ADCIntEnable(ADC0_BASE, 3);\
	IntEnable(INT_ADC0SS3);


	ADCSequenceEnable(ADC0_BASE, 3);

	while(1){
	}

}


