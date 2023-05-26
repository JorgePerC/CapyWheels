/*
 * MotorPI.cpp
 *
 *  Created on: May 24, 2023
 *      Author: josue
 */

#include "MotorPI.hpp"



LL_Control::Motor_PI::Motor_PI(LL_Control::Encoder * e, TIM_HandleTypeDef * htim) {
	// TODO Auto-generated constructor stub
	enc = e;
	htimPWM = htim;
    encoderFrequency = enc->get_frequency();
}

LL_Control::Motor_PI::~Motor_PI() {
	// TODO Auto-generated destructor stub
}

// ===== Setters =====

void LL_Control::Motor_PI::set_MaxVel(float nMax){
	maxVel = nMax;
}
void LL_Control::Motor_PI::set_MinVel(float nMin){
	minVel = nMin;
}
void LL_Control::Motor_PI::set_reference(float ref){
	// Limit the value if the ref is bigger
        // than our opertarional space
	if (ref > maxVel){
		ref = maxVel;
	}else if (ref < minVel){
		ref = minVel;
	}
    reference = direction*ref;
}
void LL_Control::Motor_PI::set_Ks(float k_i, float k_p){
	this->k_i = k_i;
	this->k_p = k_p;
}
// ===== Getters =====
float LL_Control::Motor_PI::get_vel(){

	float vel = enc->get_vel();
	// Sometimes it overflows into an invalid value
		// We double check to clean even more the data
	// If the calculated value is bigger than our maximum velocity
	if (vel >  maxVel || vel < minVel){
		vel = lastVel;
	}

	// Update last reading
	lastVel = vel;

    // Should we invert this? 
	return vel;
}

// ===== Others =====
void LL_Control::Motor_PI::invert(){
    direction *= -1;
}
int LL_Control::Motor_PI::map(float x){
	return (int) map(x, minVel, maxVel, minFreqPWM, maxFreqPWM);
}


void LL_Control::Motor_PI::go_to_ref(){

    // ===== #CONTROL =====
	float error = reference - get_vel();

	// Since we are not working with tasks, we can't actually make whiles
	if (error <= threshold && error >= -threshold){
        // Stop if we are within boundaries
		return;
	}
    // If we are not on the threshold, keep altering PWM pulse
    
    // Update error on integral term
    intError += error;
    // Calculate integral component
    float intTerm = (1000/encoderFrequency)*intError + lastIntegral;

    // Regulate voltage to motor
        // Sadly, it isn't torque ;(
    float control = k_p*error  + k_i*intTerm;

    // Actually move motor
    htimPWM -> Instance-> CCR1 = (int) map(control);

    // Update integral component
    lastIntegral = intTerm;
        
	

}

void LL_Control::Motor_PI::stop(){
	set_reference(0.0);
}

