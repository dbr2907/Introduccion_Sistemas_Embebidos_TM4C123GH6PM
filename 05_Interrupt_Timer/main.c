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
//*********************************Definiciones*************************************//

//**********************************Variables***************************************//
int temp=0;
short led=0;
//***********************************Metodos****************************************//
void Accion(void){
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2*led);
	led= led^1;
}

//************************************Main******************************************//
int main(void){
	SysCtlClockSet(SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_2_5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	//Timer
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	//Interrupciones
	IntMasterEnable();
	IntEnable(INT_TIMER0A);
	IntPrioritySet(INT_TIMER0A, 0);

	//Inicio Timer
	TimerEnable(TIMER0_BASE, TIMER_A);

	while(1){
	}

}
