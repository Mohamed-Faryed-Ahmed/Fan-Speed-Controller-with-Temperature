/* ***************************************************************************************************************
 * module : motor
 *
 * Name   : motor.c
 *
 * Author: Mohamed Faryed
 *
 * Description: Source file for motor driver
 *
 * Created on: Feb 23, 2022
 *
 ******************************************************************************************************************/
#include"motor.h"


/********************************************************************************************************
 *                                 Function Definition
 *******************************************************************************************************/
/*
*Description:
*            The Function responsible for setup the direction for the two
*            motor pins through the GPIO driver.
*            Stop at the DC-Motor at the beginning through the GPIO driver.
********************************************************************************************************/
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(MOTOR_PORT_ID1,MOTOR_PIN_ID1,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID2,MOTOR_PIN_ID2,PIN_OUTPUT);
	GPIO_writePin(MOTOR_PORT_ID1,MOTOR_PIN_ID1,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID2,MOTOR_PIN_ID2,LOGIC_LOW);
}

/*
* Description:
*              The function responsible for rotate the DC Motor CW/ or A-CW or
*              stop the motor based on the state input state value.
*              Send the required duty cycle to the PWM driver based on the required speed value.
*********************************************************************************************************/
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	if(state==CW)
	{
		speed=(uint8)(((float)speed/100)*255);
		PWM_Timer0_Start(speed);
		GPIO_writePin(MOTOR_PORT_ID1,MOTOR_PIN_ID1,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID2,MOTOR_PIN_ID2,LOGIC_HIGH);
	}
	else if(state==A_CW)
	{
		speed=(uint8)(((float)speed/100)*255);
		PWM_Timer0_Start(speed);
		GPIO_writePin(MOTOR_PORT_ID1,MOTOR_PIN_ID1,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID2,MOTOR_PIN_ID2,LOGIC_LOW);
	}
	else if(state==STOP)
		{
			PWM_Timer0_Start(0);
			GPIO_writePin(MOTOR_PORT_ID1,MOTOR_PIN_ID1,LOGIC_LOW);
			GPIO_writePin(MOTOR_PORT_ID2,MOTOR_PIN_ID2,LOGIC_LOW);
		}
}

/*
 * Description:
 *              The function responsible for trigger the Timer0 with the PWM Mode.
 *              Setup the PWM mode with Non-Inverting.
 *              Setup the prescaler with F_CPU/8.
 *              Setup the compare value based on the required input duty cycle
 *              Setup the direction for OC0 as output pin through the GPIO driver.
 *              The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0;           // Set Timer Initial Value to 0

	OCR0  = duty_cycle;  // Set Compare Value

	DDRB  = DDRB | (1<<PB3); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC

	/* Configure timer control register
     * 1. Fast PWM mode FOC0=0
     * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 ************************************************************************/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

}
