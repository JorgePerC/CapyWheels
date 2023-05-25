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
//#include <geometry_msgs/Twist.h>
//#include <geometry_msgs/Vector3.h>

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
void resetEncoder(){

	int tick_l = TIM4 -> CNT;
	int tick_r = TIM8 -> CNT;

	//uint32_t cur_time = HAL_GetTick();

	// Do so for left wheel
	if (abs(lastTick_l - tick_l) > 537){
		tick_l -= 537;
	}
	// Do so for left wheel
	if (abs(lastTick_r - tick_r) > 537){
		tick_r -= 537;
	}

	// Update angular velocities:
	w_rightWheel = 2*pi*(lastTick_r - tick_r)/(encoderTickpRev*(0.02));
	w_leftWheel = 2*pi*(lastTick_l - tick_l)/(encoderTickpRev*(0.02));

	// If the calculated value is bigger than our maximum velocity
	if (w_rightWheel >  32.0 || w_rightWheel < -32.0){
		w_rightWheel = w_rightWheel_last;
	}
	if (w_leftWheel >  32.0 || w_leftWheel < -32.0 ){
		w_leftWheel = w_leftWheel_last;
	}

	// Update tick readout
	lastTick_r = tick_r;
	lastTick_l = tick_l;

	w_rightWheel_last = w_rightWheel;
	w_leftWheel_last = w_leftWheel;


}

float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* Since our prescaler was determined to count
	 * 1 picosecond, we set the pulse by alternating the
	 * CCR value.
	 * */
void vel_wl_Callback( const std_msgs::Float32 &input_msg){
	float wl = input_msg.data;

	// Limit wl ranges
	if (wl > 1.0){
		wl = 1.0;
	}else if (wl < -1.0){
		wl = -1.0;
	}
	TIM3->CCR1 = (int) map(wl, -1, 1, 1050, 1950);
}

void vel_wr_Callback( const std_msgs::Float32 &input_msg){
	float wr = input_msg.data;

	// We invert the rotation to keep all the math happy :D
	wr *= -1;

	// Limit wl ranges
	if (wr > 1.0){
		wr = 1.0;
	}else if (wr < -1.0){
		wr = -1.0;
	}
	TIM2->CCR1 = (int) map(wr, -1, 1, 1050, 1950);
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

