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

    // Enchoder characterization 
    float encoderRes;
	int ticksPerRevolution;

    // Readings freq
    int int_freq;

    // Compute signal 
    const float pi = 3.1416;
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

#endif /* ENCODER_H_ */
