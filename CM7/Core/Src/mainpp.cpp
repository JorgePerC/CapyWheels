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
	// Geometry msgs
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>

/* --- Node handler --- */
ros::NodeHandle nh;

/* --- Messages --- */
std_msgs::String str_msg;
std_msgs::Int16 reading;

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

long map(long x, long in_min, long in_max, long out_min, long out_max) {

	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void cmd_vel_Callback( const geometry_msgs::Twist &input_msg){
	// Divide the message into left and right wheel velocities

	//

}

/* --- Publishers and subscribers --- */
//ros::Subscriber <geometry_msgs::Twist> cmd_sub("cmd_vel", &cmd_vel_Callback );

//ros::Publisher odom_pub("odometry", &robotPose_msg);
ros::Publisher try_pub("encoder", &reading);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void setup(void)
{

	HAL_GPIO_TogglePin (GPIOE, GPIO_PIN_1);  // LED Yellow
	HAL_Delay(1200);

	nh.initNode();
	//nh.advertise(odom_pub);
	nh.advertise(try_pub);
	//nh.subscribe(cmd_sub);

	HAL_GPIO_TogglePin (GPIOE, GPIO_PIN_1);  // LED Yellow
	//nh.loginfo(hello2);
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


	try_pub.publish(&reading);
	/*
	robotPose_msg.position.x = 10;
	robotPose_msg.position.y = 20;

	robotPose_msg.orientation.w = 0;

	odom_pub.publish(&robotPose_msg);
	*/
	nh.spinOnce();

	// By trial and error, we decided 100 is the corect one
	HAL_Delay(100);
}

