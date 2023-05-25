/*
 * Encoder.cpp
 *
 *  Created on: May 24, 2023
 *      Author: josue
 */

#include "Encoder.h"

Encoder::Encoder(TIM_HandleTypeDef * htimCounter, int int_freq) {
	// TODO Auto-generated constructor stub
	this->htimCounter = htimCounter;
	this->int_freq = int_freq;
}

Encoder::~Encoder() {
	// TODO Auto-generated destructor stub
}

float Encoder::get_vel(){
	return vel;
}

int Encoder::get_frequency(){
	return int_freq;
}

void Encoder::update(){
    	int tick = htimCounter -> CNT;

	// Code to avoid jumps when a revolution is completed
		// This basically happens when the encoder value changes drastically
		// from the last value to the new one
	if (abs(lastTick - tick) > 510){
		tick -= 537;
	}

	// Update angular velocities:
	//w_rightWheel = 2*pi*(lastTick_r - tick_r)/(encoderTickpRev*(0.02));
	vel = 2*pi*(lastTick - tick)*1000/(encoderRes*int_freq);

	// Update last readout
	lastTick = tick;
}
