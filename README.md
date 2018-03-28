# Introduccion_Sistemas_Embebidos_TM4C123GH6PM

Simple CCS Codes for the TM4C123GH6PM. 
These codes were made in order to teach step by step how to use this microcontroller and its peripherals using the TivaWare.

Desarrollo de códigos simples en CCS para el controlador TM4C123GH6PM. 
El propósito de estos códigos es brindar la base, de la manera mas sencilla posible, para realizar cualquier proyecto que requiera estos perifericos.


01. ClockSet:

Code to set the Clock using an external crystal (16 MHz), PLL (400 MHz) and SysDiv(Defined by user).
The Clock Frequency will be:

Clock_F= (200MHz/SysDiv)
In this example
80MHz= (200MHz/2.5)

The Clock Frequency can be checked using a breakpoint to verify the value on variable F_Reloj.

Codigo para establecer la frecuencia de reloj del sistema utilizando un cristal externo (16 MHz), el PLL(400MHz) y SysDiv(Definido por el usuario).
La frecuencia del reloj sera:

Clock_F= (200MHz/SysDiv)
In this example
80MHz= (200MHz/2.5)

La frecuencia de reloj se puede verificar utilizando un breakpoint para mostar el valor en la variable F_Reloj.

02. GPIOInput

Code to setup a GPIO as an Input. GPIOPadConfigSet must be used always on inputs, as you have to set the Pull-up or Pull-down resistors. 
Digital Pin Value can be verified using a breakpoint the check the value of variable "temp".
PF0 pin es blocked so must be unblocked first to use it.

Codigo para configurar los GPIO como entradas. GPIOPadConfigSet se debe usar siempre en entradas dado que se debe especificar si se usaran resistencias Pull-up o Pull-down.
El valor digital del pin puede ser verificado con un breakpoint para mostrar el valor de la variable "temp".
El Pin PF0 viene bloqueado por defecto, por lo cual es necesario desbloquearlo para su uso

02. GPIOOutput

Code to setup a GPIO as an Output. PF1,PF2 and PF3 are used as the have an RBG Led connected on the Develpoment Board.
These code turns on each of the RBG Leds in order.

Codigo para configurar los GPIO como salidas. Se utilizan los pines PF1,PF2 y PF3 dado que traen conectado un Led RBG en la tarjeta de desarrollo. Este codigo enciende cada led en orden.

03. Timer

Code to setup a Timer to count one second.
Timer Value can be verified using a breakpoint the check the value of variable "temp".

Codigo para configurar un Timer periodico para contar un segundo. 
El valor del timer puede ser verificado con un breakpoint para mostrar el valor de la variable "temp".

04. Timer

Code to setup a Timer to count one second.
Timer Value can be verified using a breakpoint the check the value of variable "temp".

Codigo para configurar un Timer periodico para contar un segundo. 
El valor del timer puede ser verificado con un breakpoint para mostrar el valor de la variable "temp".




Author: David Josue Barrientos Rojas

This work is licensed under a Creative Commons Attribution 4.0 International

This license lets others remix, tweak, and build upon this work non-commercially, as long as they credit the AUTHOR.

[![License: CC BY 4.0](https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)
