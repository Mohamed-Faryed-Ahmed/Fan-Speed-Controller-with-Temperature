/* ***************************************************************************************************************
 * module : motor
 *
 * Name   : motor.h
 *
 * Author: Mohamed Faryed
 *
 * Description: Header file for motor driver
 *
 * Created on: Feb 23, 2022
 *
 ******************************************************************************************************************/

#ifndef HAL_DC_MOTOR_MOTOR_H_
#define HAL_DC_MOTOR_MOTOR_H_

#include <avr/io.h>
#include"../../std_types.h"
#include"../../mcal/gpio/gpio.h"

/********************************************************************************************************
 *                                  Definition
 *******************************************************************************************************/

#define MOTOR_PORT_ID1        PORTB_ID
#define MOTOR_PORT_ID2        PORTB_ID
#define MOTOR_PIN_ID1         PIN0_ID
#define MOTOR_PIN_ID2         PIN1_ID

/********************************************************************************************************
 *                                 Type Definition
 *******************************************************************************************************/

typedef enum{
	CW,A_CW,STOP
}DcMotor_State;

/********************************************************************************************************
 *                                 Function Proto_type
 *******************************************************************************************************/

/*
*Description:
*            The Function responsible for setup the direction for the two
*            motor pins through the GPIO driver.
*            Stop at the DC-Motor at the beginning through the GPIO driver.
********************************************************************************************************/
void DcMotor_Init(void);

/*
* Description:
*              The function responsible for rotate the DC Motor CW/ or A-CW or
*              stop the motor based on the state input state value.
*              Send the required duty cycle to the PWM driver based on the required speed value.
*********************************************************************************************************/
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

/*
 * Description:
 *             The function responsible for trigger the Timer0 with the PWM Mode.
 *             Setup the PWM mode with Non-Inverting.
 *             Setup the prescaler with F_CPU/8.
 *             Setup the compare value based on the required input duty cycle
 *             Setup the direction for OC0 as output pin through the GPIO driver.
 *             The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* HAL_DC_MOTOR_MOTOR_H_ */

