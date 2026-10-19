// uart0_driver.c
#include <LPC21xx.H>
#include "header.h"
void uart0_init(unsigned  int baud)
{
	int a[]={15,60,30,15,15};
	unsigned int pclk, result=0 ;
	pclk=a[VPBDIV]*1000000;
	result=pclk/(16*baud);
	PINSEL0|=0x5; // TxD0(P0.0), RxD0(P0.1)
	U0LCR=0x83; // unlock baudrate
	U0DLL=result&0xff; //setting 9600bps if freq 15Mhz
	U0DLM=(result>>8)&0xff; //setting 9600bps if freq 15Mhz
	U0LCR=0x03;//lock baudrate
}



#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
}

void uart0_tx_string(char *ptr){
	while(*ptr){
		U0THR=*ptr;
		while(THRE==0);
		//delay_ms(10);
		ptr++;
	}
}



#define RDR (U0LSR&1)
unsigned char uart0_rx(void){
	while(RDR==0);
	return U0RBR;
}

#include <stdio.h>
void uart0_tx_float(float f){
	char arr[10];
	sprintf(arr,"%.1f",f);
	uart0_tx_string(arr);
}


void uart0_tx_integer(int n){
	char arr[10];
	sprintf(arr,"%d",n);
	uart0_tx_string(arr);
}








