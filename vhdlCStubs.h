#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <Pipes.h>
#include <SocketLib.h>
double fdiv32(double a,double b);
float fpadd32f(float x,float y);
uint32_t fpadd32fi(uint32_t x,uint32_t y);
float fpmul32f(float x,float y);
float fpsub32f(float x,float y);
uint32_t fpsub32fi(uint32_t x,uint32_t y);
uint8_t getBit64(uint64_t reg,uint8_t pos);
uint64_t getSlice64(uint64_t reg,uint8_t h,uint8_t l);
void global_storage_initializer_();
float iq_err_calc(float Lr,float torque_ref,float constant_1,float flux_rotor);
float rotor_flux_calc(float del_t,float Lm,float id,float flux_rotor_prev,float tau_new,float tau_r);
uint64_t setBit64(uint64_t reg,uint8_t pos,uint8_t value);
uint64_t setSlice64(uint64_t reg,uint8_t h,uint8_t l,uint64_t value);
float theta_calc(float omega_r,float omega_m,float del_t,float theta_prev);
