/*
 * Encoder.h
 *
 *  Created on: May 24, 2023
 *      Author: josue
 */

#ifndef ENCODER_H_
#define ENCODER_H_
/*
 * Create class for encoder
 * * Encoder Resolution
 * * Timer encoder Mode
 * * Interrupt frequency
 * * Pins
 * ============== Methods
 * * Initialize peripherals
 * * Invert polarity
 *
*/
class Encoder {
	TIM_HandleTypeDef * htimCounter;

	int lastTick;

	float encoderRes;
	int ticksPerRevolution;

	int int_freq;

	// ===== Methods

public:
	Encoder(TIM_HandleTypeDef * htimCounter, int int_freq);
	float get_vel();

	virtual ~Encoder();
};

#endif /* ENCODER_H_ */
