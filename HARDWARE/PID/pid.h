#ifndef  _pid__H
#define  _pid__H
#include "sys.h"


void PID_Init(float angle_X,float angle_Y,float distance_X,float distance_Y);



float X1_distance_pwm(u16 locx);
float Y1_distance_pwm(u16 locy);
float X1_speed_pwm(int locy);
float Y1_speed_pwm(int locy);

float X2_distance_pwm(u16 locx);
float Y2_distance_pwm(u16 locy);
float X2_speed_pwm(int locy);
float Y2_speed_pwm(int locy);


float X3_distance_pwm(u16 locx);
float Y3_distance_pwm(u16 locy);
float X3_speed_pwm(int locy);
float Y3_speed_pwm(int locy);

float X4_distance_pwm(u16 locx);
float Y4_distance_pwm(u16 locy);
float X4_speed_pwm(int locy);
float Y4_speed_pwm(int locy);



typedef struct
{
u8 time;
	
float Sv_angle_X;
float Sv_angle_Y;
	
float Sv_distance_X;
float Sv_distance_Y;
	
float Sv_speed_X;
float Sv_spped_Y;

float Pv_angle_X;
float Pv_angle_Y;
	
float Pv_distance_X;
float Pv_distance_Y;
	
float Pv_speed_X;
float Pv_spped_Y;
	

float X_angle_out;
float Y_angle_out;

float X_distance_out;
float Y_distance_out;

float X_speed_out;
float Y_speed_out;

float X_OUT;
float Y_OUT;

}PID;

extern PID pid;//���pid����



#endif



