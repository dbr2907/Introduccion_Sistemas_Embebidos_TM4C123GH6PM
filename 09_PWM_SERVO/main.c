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
#define Frequency 50
#define CLOCK 80000000
//**********************************Variables***************************************//
short Switch=0;
volatile uint32_t LoadServo;
volatile uint32_t PWMClock;
volatile uint8_t Duty_Cycle=75;
//***********************************Metodos****************************************//
void PWM_Init(void){
	PWMClock = CLOCK / 64;
	LoadServo = (PWMClock / Frequency) - 1;
	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, LoadServo);
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

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;	// Desbloquear PF0
	GPIO_PORTF_CR_R = 0x0f;

	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);


	PWM_Init();

	while(1)  {
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, Duty_Cycle*LoadServo/1000);

		Switch=GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
		if(Switch==16){
			Duty_Cycle++;
			if(Duty_Cycle>100){
				Duty_Cycle=100;
			}
		}
		else if(Switch==1){
			Duty_Cycle--;
			if(Duty_Cycle<50){
				Duty_Cycle=50;
			}
		}

	}
}
