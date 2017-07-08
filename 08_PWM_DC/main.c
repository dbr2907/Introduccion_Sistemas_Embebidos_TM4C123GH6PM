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
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
//*********************************Definiciones*************************************//
#define Frequency 1000
#define CLOCK 80000000
//**********************************Variables***************************************//
volatile uint32_t LoadDC;
volatile uint32_t PWMClock;
volatile uint8_t Duty_Cycle=50;
//***********************************Metodos****************************************//
void PWM_Init(void){
	PWMClock = CLOCK / 64;
	LoadDC = (PWMClock / Frequency) - 1;
	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, LoadDC);
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
	PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
	PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}
//************************************Main******************************************//
int main(void){
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_XTAL_16MHZ);
	//PWM Setup
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
	GPIOPinConfigure(GPIO_PB6_M0PWM0);
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
	GPIOPinConfigure(GPIO_PB7_M0PWM1);
	PWM_Init();

	while(1)  {
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, Duty_Cycle*LoadDC/100);
	}
}
