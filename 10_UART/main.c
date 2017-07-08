//********************************Librerias*****************************************//
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
//******************************Librerias Extras************************************//
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
//*********************************Definiciones*************************************//

//**********************************Variables***************************************//
char car;
//***********************************Metodos****************************************//
void UARTIntHandler(void) {
	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
	UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
	while(UARTCharsAvail(UART0_BASE))
		{
		car = UARTCharGetNonBlocking(UART0_BASE);
		UARTCharPut(UART0_BASE, car);
		SysCtlDelay(SysCtlClockGet() / (1000 * 3)); //delay ~1 msec
		}
}
//************************************Main******************************************//
int main(void){

	SysCtlClockSet(SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_2_5);
//******************UART****************************//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
//**************************GPIO*****************************************//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //enable pin for LED PF2
//********Interrupcion*************//
	IntMasterEnable();
	IntEnable(INT_UART0);
	UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

	UARTCharPut(UART0_BASE, 'I');
	UARTCharPut(UART0_BASE, 'n');
	UARTCharPut(UART0_BASE, 's');
	UARTCharPut(UART0_BASE, 't');
	UARTCharPut(UART0_BASE, 'r');
	UARTCharPut(UART0_BASE, 'u');
	UARTCharPut(UART0_BASE, 'c');
	UARTCharPut(UART0_BASE, 'c');
	UARTCharPut(UART0_BASE, 'i');
	UARTCharPut(UART0_BASE, 'o');
	UARTCharPut(UART0_BASE, 'n');
	UARTCharPut(UART0_BASE, ':');
	UARTCharPut(UART0_BASE, ' ');


	while (1){
		switch(car){
		    case 'w':
		       GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x02);
		       break;
		    case 'a'  :
		       GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x04);
		       break;
		    case 's'  :
		       GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);
		       break;
		    case 'v'  :
		       GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0C);
		       break;
		    case 'm'  :
   		       GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x06);
   		       break;
		    default:
		    	GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
		}
	}
}
