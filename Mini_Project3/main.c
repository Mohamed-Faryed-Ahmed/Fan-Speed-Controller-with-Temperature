/* ***************************************************************************************************************
 * Name : main.c
 *
 * Author: Mohamed Faryed
 *
 * Description: Source file for main project
 *
 * Created on: Feb 23, 2022
 *
 ******************************************************************************************************************/



#include "main.h"

int main (void)
{
	ADC_ConfigType s_adcInt={Div8,INTERNAL,INT_DIS,EN_ADC};
	uint8 tempData=0;

	ADC_init(&s_adcInt);
	DcMotor_Init();
	LCD_init();

	while(1)
	{
		tempData = LM35_getTemperature();

		if(tempData>=30 && tempData < 60)
		{
			DcMotor_Rotate(CW,25);
		}
		else if(tempData>=60 && tempData < 90)
		{
			DcMotor_Rotate(CW,50);
		}
		else if(tempData>=90 && tempData < 120)
		{
			DcMotor_Rotate(CW,75);
		}
		else if(tempData>=120)
		{
			DcMotor_Rotate(CW,100);
		}
		else
		{
			DcMotor_Rotate(STOP,0);
		}

		if(tempData>=30)
		{
			LCD_displayStringRowColumn(1,5,"FAN IS ON ");
			LCD_displayStringRowColumn(0,5,"TEMP :");
			LCD_intgerToString(tempData);
			LCD_displayString("C ");
		}
		else
		{
			LCD_displayStringRowColumn(1,5,"FAN IS OFF");
			LCD_displayStringRowColumn(0,5,"TEMP :");
			LCD_intgerToString(tempData);
			LCD_displayString("C ");
		}

	}
}

