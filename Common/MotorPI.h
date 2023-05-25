/*
 * MotorPI.h
 *
 *  Created on: May 24, 2023
 *      Author: josue
 */

#ifndef MOTORPI_H_
#define MOTORPI_H_

#include <Encoder.h>

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
        // Cleans encoder reading
	float lastVel;



	// Signal variables
	int maxFreqPWM;
	int minFreqPWM;

    int encoderFrequency;


	// Control variables
        // Gains
	float k_i;
	float k_p;

        // Set-point closeness
	float threshold;

        // PI needed values
	float reference;    // TODO: remove?
	float lastError;
    float intError;
    float lastIntegral;

	// ========== Methods
	float map(float x, float in_min, float in_max, float out_min, float out_max);
public:
	Motor_PI(Encoder e, TIM_HandleTypeDef * htim);

	int map(float x);

	void set_MaxVel(float nMax);
	void set_MinVel(float nMin);
    void set_Ks(float k_i, float k_p);

    void set_encoderFrequency(int f);
    void set_threshold(int f);

	float get_vel();

	void go_to(float nRef);
    void stop();

	virtual ~Motor_PI();
};

#endif /* MOTORPI_H_ */
