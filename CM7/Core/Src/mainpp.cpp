/*
 * main.cpp
 *  Created on: 2023/04/31
 *      Author: Jorge Pérez
 */

	// ROS
#include <ros.h>
	// Standard msgs
//#include <std_msgs/String.h>
//#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
	// Geometry msgs
#include <geometry_msgs/PoseStamped.h>
	// Our libraries
#include <mainpp.h>
#include <Encoder.hpp>
#include <MotorPI.hpp>
	// Extra ones
#include <stdlib.h>

/* --- Motors & Encoders --- */
extern LL_Control::Encoder encoderL;
extern LL_Control::Encoder encoderR;
extern LL_Control::Motor_PI motorL;
extern LL_Control::Motor_PI motorR;


/* --- Node handler --- */
ros::NodeHandle nh;

/* --- Messages --- */
std_msgs::Float32 wl;
std_msgs::Float32 wr;

const float encoderTickpRev = 537.667;

/* --- Callback functions --- */
void vel_wl_Callback( const std_msgs::Float32 &input_msg){
	float wl = input_msg.data;
	motorL.set_reference(wl);
}

void vel_wr_Callback( const std_msgs::Float32 &input_msg){
	float wr = input_msg.data;
	motorR.set_reference(wr);
}

/* --- Publishers and subscribers --- */
ros::Subscriber <std_msgs::Float32> wl_sub("/robot/set_wl", &vel_wl_Callback );
ros::Subscriber <std_msgs::Float32> wr_sub("/robot/set_wr", &vel_wr_Callback );

ros::Publisher wl_pub("/robot/wl", &wl);
ros::Publisher wr_pub("/robot/wr", &wr);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void setup(void)
{
	// Stop motors when init
	motorL.stop();
	motorR.stop();

	HAL_GPIO_TogglePin (GPIOE, GPIO_PIN_1);  // LED Yellow
	HAL_Delay(1200);

	nh.initNode();

	nh.advertise(wl_pub);
	nh.advertise(wr_pub);

	nh.subscribe(wl_sub);
	nh.subscribe(wr_sub);

	// Time to negotiate topics
	//nh.negotiateTopics();

	HAL_GPIO_TogglePin (GPIOE, GPIO_PIN_1);  // LED Yellow

}

void loop(void)
{
	// Turn on Green LED if connected
	if (nh.connected()){
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  // LED Green
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);  // LED RED
	}else{
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);  // LED Green
		HAL_GPIO_WritePin (GPIOB, GPIO_PIN_14, GPIO_PIN_SET);  // LED RED

		// Stop motors when disconnected
		motorL.stop();
		motorR.stop();
	}

		// Update data on ros msg
		wr.data = motorR.get_vel();
		wl.data = motorL.get_vel();

		// Send Message
		wl_pub.publish(&wl);
		wr_pub.publish(&wr);

		// TODO: Should we put this at a higher Freq?
		motorL.go_to_ref();
		motorR.go_to_ref();

	nh.spinOnce();

	// By trial and error, we decided 100 is the correct one
	HAL_Delay(40);
}

