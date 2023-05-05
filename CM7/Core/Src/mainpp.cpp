/*
 * main.cpp
 *  Created on: 2023/04/31
 *      Author: Jorge Pérez
 */
#include <mainpp.h>
#include <ros.h>
	// Standard msgs
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
	// Geometry msgs
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>

/* --- Node handler --- */
ros::NodeHandle nh;

/* --- Messages --- */
std_msgs::String str_msg;
std_msgs::Int16 reading;
std_msgs::Float32 wl;
std_msgs::Float32 wr;

geometry_msgs::Pose robotPose_msg;

char hello[] = "Hello world!";

int lastTick_l = 0;
int lastTick_r = 0;

float pi = 3.1416;
float w_leftWheel = 0;
float w_rightWheel = 0;
const int encoderTickpr = 538;

int countsL = 0;

/* --- Callback functions --- */
void readEncoderVel (float readoutPeriod){
	int tick_l = TIM8 -> CNT;
	int tick_r = TIM4 -> CNT;

	// Update angular velocities:
	w_leftWheel = (2*pi*(lastTick_l - tick_l)/encoderTickpr)/(readoutPeriod);
	w_rightWheel = (2*pi*(lastTick_r - tick_r)/encoderTickpr)/(readoutPeriod);

	// Update tick readout
	lastTick_l = tick_l;
	lastTick_r = tick_r;

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
//ros::Publisher try_pub("encoder", &reading);

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

	nh.subscribe(wl_sub);
	nh.subscribe(wr_sub);

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
	}

	//tickCount_r = TIM1 -> CNT;

	bool tocaEnviar = true;

	if (tocaEnviar){
		// Update data on ros msg
		wl.data = w_leftWheel;
		wr.data = w_rightWheel;
		// Send Message
		wl_pub.publish(&wl);
		wr_pub.publish(&wr);
	}

	/*
	robotPose_msg.position.x = 10;
	robotPose_msg.position.y = 20;

	robotPose_msg.orientation.w = 0;

	odom_pub.publish(&robotPose_msg);
	*/
	nh.spinOnce();

	// By trial and error, we decided 100 is the corect one
	HAL_Delay(500);
}

