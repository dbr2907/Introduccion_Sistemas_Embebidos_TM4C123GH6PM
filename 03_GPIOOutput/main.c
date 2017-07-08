//********************************Librerias*****************************************//
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
//******************************Librerias Extras************************************//
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
//*********************************Definiciones*************************************//

//**********************************Variables***************************************//
//int temp=0;
//***********************************Metodos****************************************//


//************************************Main******************************************//
int main(void){

	SysCtlClockSet(SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_2_5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	while(1){
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
	SysCtlDelay(SysCtlClockGet()/3)
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
	SysCtlDelay(SysCtlClockGet()/3)
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);
	SysCtlDelay(SysCtlClockGet()/3)
	}

}




