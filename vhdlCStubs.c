#include <vhdlCStubs.h>
double fdiv32(double a,double b)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call fdiv32 ");
append_int(buffer,2); ADD_SPACE__(buffer);
append_double(buffer,a); ADD_SPACE__(buffer);
append_double(buffer,b); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,64); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
double ret_val__ = get_double(buffer,&ss);
return(ret_val__);
}
float fpadd32f(float x,float y)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call fpadd32f ");
append_int(buffer,2); ADD_SPACE__(buffer);
append_float(buffer,x); ADD_SPACE__(buffer);
append_float(buffer,y); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,32); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
float ret_val__ = get_float(buffer,&ss);
return(ret_val__);
}
uint32_t fpadd32fi(uint32_t x,uint32_t y)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call fpadd32fi ");
append_int(buffer,2); ADD_SPACE__(buffer);
append_uint32_t(buffer,x); ADD_SPACE__(buffer);
append_uint32_t(buffer,y); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,32); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
uint32_t ret_val__ = get_uint32_t(buffer,&ss);
return(ret_val__);
}
float fpmul32f(float x,float y)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call fpmul32f ");
append_int(buffer,2); ADD_SPACE__(buffer);
append_float(buffer,x); ADD_SPACE__(buffer);
append_float(buffer,y); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,32); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
float ret_val__ = get_float(buffer,&ss);
return(ret_val__);
}
float fpsub32f(float x,float y)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call fpsub32f ");
append_int(buffer,2); ADD_SPACE__(buffer);
append_float(buffer,x); ADD_SPACE__(buffer);
append_float(buffer,y); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,32); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
float ret_val__ = get_float(buffer,&ss);
return(ret_val__);
}
uint32_t fpsub32fi(uint32_t x,uint32_t y)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call fpsub32fi ");
append_int(buffer,2); ADD_SPACE__(buffer);
append_uint32_t(buffer,x); ADD_SPACE__(buffer);
append_uint32_t(buffer,y); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,32); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
uint32_t ret_val__ = get_uint32_t(buffer,&ss);
return(ret_val__);
}
uint8_t getBit64(uint64_t reg,uint8_t pos)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call getBit64 ");
append_int(buffer,2); ADD_SPACE__(buffer);
append_uint64_t(buffer,reg); ADD_SPACE__(buffer);
append_uint8_t(buffer,pos); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,8); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
uint8_t ret_val__ = get_uint8_t(buffer,&ss);
return(ret_val__);
}
uint64_t getSlice64(uint64_t reg,uint8_t h,uint8_t l)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call getSlice64 ");
append_int(buffer,3); ADD_SPACE__(buffer);
append_uint64_t(buffer,reg); ADD_SPACE__(buffer);
append_uint8_t(buffer,h); ADD_SPACE__(buffer);
append_uint8_t(buffer,l); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,64); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
uint64_t ret_val__ = get_uint64_t(buffer,&ss);
return(ret_val__);
}
void global_storage_initializer_()
{
char buffer[1024];  char* ss;  sprintf(buffer, "call global_storage_initializer_ ");
append_int(buffer,0); ADD_SPACE__(buffer);
append_int(buffer,0); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
return;
}
float iq_err_calc(float Lr,float torque_ref,float constant_1,float flux_rotor)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call iq_err_calc ");
append_int(buffer,4); ADD_SPACE__(buffer);
append_float(buffer,Lr); ADD_SPACE__(buffer);
append_float(buffer,torque_ref); ADD_SPACE__(buffer);
append_float(buffer,constant_1); ADD_SPACE__(buffer);
append_float(buffer,flux_rotor); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,32); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
float ret_val__ = get_float(buffer,&ss);
return(ret_val__);
}
float rotor_flux_calc(float del_t,float Lm,float id,float flux_rotor_prev,float tau_new,float tau_r)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call rotor_flux_calc ");
append_int(buffer,6); ADD_SPACE__(buffer);
append_float(buffer,del_t); ADD_SPACE__(buffer);
append_float(buffer,Lm); ADD_SPACE__(buffer);
append_float(buffer,id); ADD_SPACE__(buffer);
append_float(buffer,flux_rotor_prev); ADD_SPACE__(buffer);
append_float(buffer,tau_new); ADD_SPACE__(buffer);
append_float(buffer,tau_r); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,32); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
float ret_val__ = get_float(buffer,&ss);
return(ret_val__);
}
uint64_t setBit64(uint64_t reg,uint8_t pos,uint8_t value)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call setBit64 ");
append_int(buffer,3); ADD_SPACE__(buffer);
append_uint64_t(buffer,reg); ADD_SPACE__(buffer);
append_uint8_t(buffer,pos); ADD_SPACE__(buffer);
append_uint8_t(buffer,value); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,64); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
uint64_t ret_val__ = get_uint64_t(buffer,&ss);
return(ret_val__);
}
uint64_t setSlice64(uint64_t reg,uint8_t h,uint8_t l,uint64_t value)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call setSlice64 ");
append_int(buffer,4); ADD_SPACE__(buffer);
append_uint64_t(buffer,reg); ADD_SPACE__(buffer);
append_uint8_t(buffer,h); ADD_SPACE__(buffer);
append_uint8_t(buffer,l); ADD_SPACE__(buffer);
append_uint64_t(buffer,value); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,64); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
uint64_t ret_val__ = get_uint64_t(buffer,&ss);
return(ret_val__);
}
float theta_calc(float omega_r,float omega_m,float del_t,float theta_prev)
{
char buffer[1024];  char* ss;  sprintf(buffer, "call theta_calc ");
append_int(buffer,4); ADD_SPACE__(buffer);
append_float(buffer,omega_r); ADD_SPACE__(buffer);
append_float(buffer,omega_m); ADD_SPACE__(buffer);
append_float(buffer,del_t); ADD_SPACE__(buffer);
append_float(buffer,theta_prev); ADD_SPACE__(buffer);
append_int(buffer,1); ADD_SPACE__(buffer);
append_int(buffer,32); ADD_SPACE__(buffer);
send_packet_and_wait_for_response(buffer,strlen(buffer)+1,"localhost",9999);
float ret_val__ = get_float(buffer,&ss);
return(ret_val__);
}
