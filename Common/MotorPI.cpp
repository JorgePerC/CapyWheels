/*
 * MotorPI.cpp
 *
 *  Created on: May 24, 2023
 *      Author: josue
 */

#include "MotorPI.hpp"



Motor_PI::Motor_PI(Encoder * e, TIM_HandleTypeDef * htim) {
	// TODO Auto-generated constructor stub
	enc = e;
	htimPWM = htim;
    encoderFrequency = enc.get_frequency();
}

Motor_PI::~Motor_PI() {
	// TODO Auto-generated destructor stub
}

// ===== Setters =====

void Motor_PI::set_MaxVel(float nMax){
	maxVel = nMax;
}
void Motor_PI::set_MinVel(float nMin){
	minVel = nMin;
}
void Motor_PI::set_Ks(float k_i, float k_p){
	this->k_i = k_i;
	this->k_p = k_p;
}
// ===== Getters =====
float Motor_PI::get_vel(){

	float vel = enc.get_vel();
	// Sometimes it overflows into an invalid value
		// We double check to clean even more the data
	// If the calculated value is bigger than our maximum velocity
	if (vel >  maxVel || vel < minVel){
		vel = lastVel;
	}

	// Update last reading
	lastVel = vel;

	return vel;
}

// ===== Others =====
int Motor_PI::map(float x){
	return (int) map(x, minVel, maxVel, minFreqPWM, maxFreqPWM);
}


void Motor_PI::go_to(float nRef){

	// Limit the value if the ref is bigger
        // than our opertarional space
	if (nRef > maxVel){
		nRef = maxVel;
	}else if (nRef < minVel){
		nRef = minVel;
	}
    // ===== #CONTROL =====
	float error = nRef - get_vel();

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
    htimPWM -> CCR1 = (int) map(control);

    // Update integral component
    lastIntegral = intTerm;
        
	

}

void Motor_PI::stop(){
    go_to(0);
}

