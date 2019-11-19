/*
 * File:   UART_Communication.c
 * Author: felix
 *
 * Created on November 18, 2019, 10:31 AM
 */

#include <xc.h>
#include <stdint.h>

#define  BAUD 9600
#define _XTAL_FREQ  4000000 //Frecuencia de 4MHz  

void Communication_BITsConfiguration(void);

void main(void) {
	Communication_BITsConfiguration();
	return;
}