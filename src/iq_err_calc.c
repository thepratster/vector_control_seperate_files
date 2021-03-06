#include "prog.h"
float iq_err_calc(float Lr, float torque_ref, float constant_1, float flux_rotor){

	float temp_d = 0;
	float temp_iq_n = 0,temp_iq_d = 0;
	float iq_err = 0;
/*
	if (flux_rotor<1)
		flux_rotor = 1;
	else flux_rotor = flux_rotor;*/
	
	temp_d = fpmul32f(4.0,Lr);
	temp_iq_n = fpmul32f(temp_d,torque_ref);
	temp_iq_d = fpmul32f(constant_1,flux_rotor);

	iq_err = fdiv32(temp_iq_n,temp_iq_d);
	return(iq_err);
}
