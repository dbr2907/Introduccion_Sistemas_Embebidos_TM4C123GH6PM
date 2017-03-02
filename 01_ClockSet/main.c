//********************************Librerias*****************************************//
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
//******************************Librerias Extras************************************//
#include "driverlib/sysctl.h"
//*********************************Definiciones*************************************//

//**********************************Variables***************************************//
//int temp=0;
//***********************************Metodos****************************************//


//************************************Main******************************************//
int main(void){

	SysCtlClockSet(SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_2_5);
	while(1){
	}

}
