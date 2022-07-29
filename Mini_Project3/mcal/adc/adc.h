/* ***************************************************************************************************************
 * Model : ADC
 *
 * Name : adc.h
 *
 * Author: Mohamed Faryed
 *
 * Description: adc driver header file for AVR
 *
 * Created on: Feb 21, 2022
 *
 ******************************************************************************************************************/

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include <avr/io.h>              /* To use the ADC Registers */
#include <avr/interrupt.h>       /*To use Interrupt*/
#include "../../std_types.h"     /*to use user data type*/
#include "../../common_macros.h" /* To use the macros like SET_BIT */


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   5
#define ADC_INT              (0U)
/*******************************************************************************
 *                                 Types Declaration                           *
 *******************************************************************************/
typedef enum{
	INT_DIS,INT_EN
}ADC_Int;
typedef enum{
	DIS_ADC,EN_ADC
}ADC_En;

typedef enum{
	Div2=1,Div4=2,Div8=3,Div16=4,Div32=5,Div64=6,Div128=7
}ADC_Prescaler;

typedef enum{
	AREF=0,AVCC=1,INTERNAL=3
}ADC_ReferenceVolatge ;

typedef struct{
	ADC_Prescaler          prescaler   :3; /*choose clock*/
	ADC_ReferenceVolatge   ref_vol     :2; /*reference voltage */
	ADC_Int                adc_int     :1; /*Disable/enable ADC Interrupt*/
	ADC_En                 adc_en      :1; /*Adc enable */
}ADC_ConfigType;
/*Adc_Init init={Div8,AREF,INT_DIS,EN};  125KH  */


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType *s_ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */

uint16 ADC_readChannel(uint8 channel_num);


#endif /* MCAL_ADC_ADC_H_ */
