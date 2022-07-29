/* ***************************************************************************************************************
 * Model : ADC
 *
 * Name : adc.c
 *
 * Author: Mohamed Faryed
 *
 * Description: adc driver source file for AVR
 *
 * Created on: Feb 21, 2022
 *
 ******************************************************************************************************************/

#include "adc.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
#if(ADC_INT==1)
static volatile uint16 g_adcVar=0;
static volatile uint8 adcFlag=0;
#endif
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
#if(ADC_INT==1)
ISR(ADC_vect)
{
	g_adcVar=ADC;
	adcFlag=1;
}
#endif
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType *s_ptr)
{
	/* s_ptr Description:
	 * s_ptr->ref_Vol  : to choose reference voltage
	 * s_ptr->ch_Clock : choose ADC_Clock
	 * s_ptr->adc_Int  : ADC Interrupt
	 * s_ptr->adc_en   : ADC enable
	 * Disable Auto Trigger
	 * channel 0 as initialization
	 * right adjusted
	 */
	ADMUX =(ADMUX & 0x0)|((s_ptr->ref_vol)<<6);
	ADCSRA = (ADCSRA & 0x0)|((s_ptr->prescaler)<<0)|((s_ptr->adc_int)<<3)|((s_ptr->adc_en)<<7);
}
#if(ADC_INT==0)
uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
#endif

#if(ADC_INT==1)
uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(adcFlag==0);
	adcFlag=0;
	return g_adcVar;
}
#endif
