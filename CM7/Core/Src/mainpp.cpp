/*
 * main.cpp
 *  Created on: 2023/04/31
 *      Author: Jorge Pérez
 */

#include <ros.h>

	// Standard msgs
//#include <std_msgs/String.h>
//#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>

	// Geometry msgs
#include <geometry_msgs/PoseStamped.h>

#include <mainpp.h>
#include <stdlib.h>

//Our libs:
#include <Encoder.hpp>
#include <MotorPI.hpp>

/* --- Node handler --- */
ros::NodeHandle nh;

/* --- Messages --- */
std_msgs::Float32 wl;
std_msgs::Float32 wr;
//geometry_msgs::PoseStamped poseMsg;

int lastTick_l = 0;
int lastTick_r = 0;

uint32_t lastTime_l = 0;
uint32_t lastTime_r = 0;

float pi = 3.1416;

float w_leftWheel = 0;
float w_rightWheel = 0;

float w_leftWheel_last = 0;
float w_rightWheel_last = 0;

const float encoderTickpRev = 537.667;

/* --- Callback functions --- */

/* Since our prescaler was determined to count
	 * 1 picosecond, we set the pulse by alternating the
	 * CCR value.
	 * */
void vel_wl_Callback( const std_msgs::Float32 &input_msg){
	float wl = input_msg.data;

}

void vel_wr_Callback( const std_msgs::Float32 &input_msg){
	float wr = input_msg.data;
}

/* --- Publishers and subscribers --- */
ros::Subscriber <std_msgs::Float32> wl_sub("/robot/set_wl", &vel_wl_Callback );
ros::Subscriber <std_msgs::Float32> wr_sub("/robot/set_wr", &vel_wr_Callback );

//ros::Publisher odom_pub("odometry", &robotPose_msg);
ros::Publisher wl_pub("/robot/wl", &wl);
ros::Publisher wr_pub("/robot/wr", &wr);

//ros::Publisher pose_pub("/robot/pose", &poseMsg);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void setup(void)
{
	// Stop motors when init
	TIM3->CCR1 = 1500;
	TIM2->CCR1 = 1500;

	HAL_GPIO_TogglePin (GPIOE, GPIO_PIN_1);  // LED Yellow
	HAL_Delay(1200);

	nh.initNode();

	nh.advertise(wl_pub);
	nh.advertise(wr_pub);

	//nh.advertise(tick_pub);
	//nh.advertise(wr_tick_pub);

	nh.subscribe(wl_sub);
	nh.subscribe(wr_sub);
	// stamped wheels
	//nh.advertise(pose_pub);


	// Time to negociate topics
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
		// Stop motors when disconected
		TIM3->CCR1 = 1500;
		TIM2->CCR1 = 1500;
	}

		// Update data on ros msg
		wl.data = w_leftWheel;
		wr.data = w_rightWheel;

		// Send Message
		wl_pub.publish(&wl);
		wr_pub.publish(&wr);

		/*
		poseMsg.header.stamp = nh.now();
		poseMsg.pose.position.x = w_leftWheel;
		poseMsg.pose.position.y = w_rightWheel;

		pose_pub.publish(&poseMsg);
		*/

	nh.spinOnce();

	// By trial and error, we decided 100 is the corect one
	HAL_Delay(40);
}

