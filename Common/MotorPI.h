/*
 * MotorPI.h
 *
 *  Created on: May 24, 2023
 *      Author: josue
 */

#ifndef MOTORPI_H_
#define MOTORPI_H_

#import <Encoder.h>

/*TODO:
 * ============= Attributes
 * * Max Vel
 * * K_int
 * * k_pro
 * * reference
 * * Max PWM freq
 * * Min PWM freq
 * ============= Methods
 * * Initialize peripherals
 * * Map
 * * Go_to_reference
 *
 * */

class Motor_PI {
private:
	Encoder enc;
	TIM_HandleTypeDef * htimPWM;

	//Should be defined as radians
	float maxVel;
	float minVel;

	float lastVel;

	float threshold;


	// Signal variables
	int maxFreqPWM;
	int minFreqPWM;


	// Control variables
	float k_i;
	float k_p;

	float reference;
	float lastError;

	// ========== Methods
	float map(float x, float in_min, float in_max, float out_min, float out_max);
	void get_vel();
public:
	Motor_PI(Encoder e, TIM_HandleTypeDef * htim);

	float map(float x);

	void set_MaxVel(float nMax);
	void set_MinVel(float nMin);

	float get_vel();

	void set_Ks(float k_i, float k_p);

	void go_to(float nRef);

	virtual ~Motor_PI();
};

#endif /* MOTORPI_H_ */
