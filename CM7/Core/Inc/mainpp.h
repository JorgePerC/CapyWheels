/*
 * mainpp.h
 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */

#ifndef MAINPP_H_
#define MAINPP_H_

#ifdef __cplusplus
 extern "C" {
#endif

void setup(void);
void loop(void);
// My functions:

//void readEncoderVel(float readoutPeriod);
void resetEncoder();
void readEncoderVelWl();
void readEncoderVelWr();

double map(double x, double in_min, double in_max, double out_min, double out_max);

#ifdef __cplusplus
}
#endif


#endif /* MAINPP_H_ */
