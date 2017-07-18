/*
 * Timers_drv.cpp
 *
 * Created: 4/13/2017 3:15:05 PM
 * Author : rafa
 */ 

//#include "Init.h"
#include "defines.h"
#include "functions.h"
#include "USART.h"
#include "ADC.h"
#include "TIMER.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>

int timer=0;
void PWM_update(uint8_t &);
int USART0SendByte(char u8Data);
uint8_t currentEnableA=0;
uint8_t currentEnableB=85;
uint8_t currentEnableC=170;
uint8_t currentStepA=0;
uint8_t currentStepB=0;
uint8_t currentStepC=0;

uint8_t lowByte=0;
uint16_t ADC_value=0;
uint8_t debug_8bit=0;

uint8_t state_counter=0;

uint8_t phase_state=1;//global state 1,2,3,4,5,6
uint8_t reverse=0;
int main(void)
{	
	
	OCR4B=0x255;//Counter top value. Freq = 8 MHz/prescaler/(OCR0A + 1)
	//ADC_Init();
	USART_Init(MY_UBRR);
	//setup_timer3();
	setup_timer4();
	//Enable_timer3_interrupt();
	Enable_timer4_compare_interrupt();
	init_gpio();
	//GTCCR = 0;//release all timers
	sei();
    while (1) 
    {
	
    }
}

//ISR(TIMER3_OVF_vect)//Timer interrupt routine
//{
//	//PWM_update(phase_state);
//	//SWITCH_PHASE_STATE(phase_state);
//	//UDR0=0x15;
//}

ISR(TIMER4_COMPA_vect)
{
	PWM_update(phase_state);
	SWITCH_PHASE_STATE(phase_state);
	UDR0=0x15;
}

//ISR(ADC_vect)//ADC interrupt routine
//{
//		ADCSRA |= (1<<ADSC);//start ADC conversion 
//		//UDR0=ADC;
//}



