#include "prog.h"

float theta_calc(float omega_r, float omega_m, float del_t, float theta_prev){
	float temp_a = 0, temp_b = 0;
	float theta = 0;
	temp_a = fpmul32f(omega_r,omega_m);
	temp_b = fpmul32f(omega_m,del_t);
	theta = fpadd32f(theta_prev,temp_a);
	return(theta);
}

