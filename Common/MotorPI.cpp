/*
 * MotorPI.cpp
 *
 *  Created on: May 24, 2023
 *      Author: josue
 */

#include "MotorPI.h"



Motor_PI::Motor_PI(Encoder e, TIM_HandleTypeDef * htim) {
	// TODO Auto-generated constructor stub
	this->enc = e;
	this->htimPWM = htim;

}

Motor_PI::~Motor_PI() {
	// TODO Auto-generated destructor stub
}

// ===== Setters =====

Motor_PI::set_MaxVel(float nMax){
	this->maxVel = nMax;
}
Motor_PI::set_MinVel(float nMin){
	this->minVel = nMin;
}
Motor_PI::set_Ks(float k_i, float k_p){
	this->k_i = k_i;
	this->k_p = k_p;
}
// ===== Getters =====
Motor_PI::get_vel(){

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
Motor_PI::map(float x){
	this->map(x, this->minVel, this->maxVel, this->minFreqPWM, this->maxFreqPWM);
}


Motor_PI::go_to(float nRef){

	// Limit the value if the ref is bigger
	if (nRef > maxVel){
		nRef = maxVel;
	}else if (wl < minVel){
		wl = minVel;
	}

	float error = nRef - get(vel);

	// Since we are not working with tasks, we can't actually make whiles
	if (error <= threshold && error >= -threshold){
		return;
	}else{
		// If we are not on the threshold, keep altering PWM pulse
	}

}


