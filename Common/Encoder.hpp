/*
 * Encoder.h
 *
 *  Created on: May 24, 2023
 *      Author: josue
 */

#ifndef ENCODER_HPP_
#define ENCODER_HPP_
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
#include "stm32l4xx_hal.h"
#include <stdio.h>

namespace LL_Control
{
    
class Encoder {
	TIM_HandleTypeDef * htimCounter;

    // Enchoder characterization 
    float encoderRes;
	int ticksPerRevolution;

    // Readings freq
    int int_freq;

    // Compute signal 
    static const float pi = 3.1416;
	int lastTick;
    float vel;

	// ===== Methods
    void update();
    void set_ticksPR(int ticks);

public:
	Encoder(TIM_HandleTypeDef * htimCounter, int int_freq);
	
    void set_encoderRes(float res);

    
    float get_vel();
    int get_frequency();


	virtual ~Encoder();
};

} // namespace LL_Control


#endif /* ENCODER_HPP_ */
