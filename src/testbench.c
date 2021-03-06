#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <pipeHandler.h>
#include "math.h"
#ifndef SW
#include "vhdlCStubs.h"
#endif

void vector_control_daemon();

void im_zep(double *iq, double *iq_prev, double *id, double *id_prev, double *flq, double *flq_prev, double *fld, double *fld_prev, double *spd_prev, double vd,double vq,double *torque,double load_torque,double *time, double *spd, double *theta, double *theta_prev, double *theta_prev_prev)   
{

	double	alpha = 0,
		beta = 0,
		sigma = 0,
		mu = 0,
		gamma = 0,
		omega = 314.15,
		inertia = 0.013,
		rs = 4.9,
		rr = 8.1,
		lls = 0.03215,
		llr = 0.03215,
		ls = 0,
		lr = 0,
		lm = 0.8096,
		poles = 4,
		cont = 0,
		time_period = 25e-6;
                                                   
	double k1 = 0,k2 = 0,k3 = 0,k4 = 0;
	double l1 = 0,l2 = 0,l3 = 0,l4 = 0;
	double m1 = 0,m2 = 0,m3 = 0,m4 = 0;
	double n1 = 0,n2 = 0,n3 = 0,n4 = 0;
	double o1 = 0,o2 = 0,o3 = 0,o4 = 0;
	double delta = 0;
	
	ls = lm + lls;
	lr = lm + llr;
	alpha = rr/lr;
	sigma = ls - lm*lm/lr;
	beta = lm/(sigma*lr);
	mu = (3/2)*(poles/2)*(lm/(inertia*lr));
	gamma = lm*lm*rr/(sigma*lr*lr)+rs/sigma;
	cont = (3*poles*lm/(4*lr));
	
        if ( 0.0 == *time ) {           
                  
		*iq_prev = 0.0;
		*id_prev = 0.0;
		*flq_prev = 0.0;
		*fld_prev = 0.0;
		*spd_prev = 0.0;
		*iq = 0.0;
		*id = 0.0;
		*flq = 0.0;
		*fld = 0.0;
		*spd = 0.0;
		*torque = 0.0;
		*iq_prev = *iq;
		*id_prev = *id;
		*flq_prev = *flq;
		*fld_prev = *fld;
		*spd_prev = *spd;
		delta = time_period;
		*time = *time + delta;
		*theta = 0;
		*theta_prev = 0;
		*theta_prev_prev = 0;
  
        }
        else {       
	
		delta = time_period;

		k1 = -gamma*(*iq_prev) - omega*(*id_prev) + alpha*beta*(*flq_prev) - beta*(*spd_prev)*(*fld_prev) + (vq)/sigma;
		l1 = omega*(*iq_prev) - gamma*(*id_prev) + beta*(*spd_prev)*(*flq_prev) + alpha*beta*(*fld_prev) + (vd)/sigma;
		m1 = alpha*lm*(*iq_prev) - alpha*(*flq_prev) - (omega-(*spd_prev))*(*fld_prev);
		n1 = alpha*lm*(*id_prev) + (omega-(*spd_prev))*(*flq_prev) - alpha*(*fld_prev);
		o1 = ((cont*((*fld_prev)*(*iq_prev) - (*flq_prev)*(*id_prev)))-load_torque)/inertia;

		k2 = -gamma*((*iq_prev) + delta/2*k1) - omega*((*id_prev)+delta/2*l1) + alpha*beta*((*flq_prev)+delta/2*m1) - beta*((*spd_prev)+delta/2*o1)*((*fld_prev)+delta/2*n1) + (vq)/sigma;
		l2 = omega*((*iq_prev) + delta/2*k1) - gamma*((*id_prev) + delta/2*l1) + beta*((*spd_prev) + delta/2*o1)*((*flq_prev) + delta/2*m1) + alpha*beta*((*fld_prev) + delta/2*n1) + (vd)/sigma;
		m2 = alpha*lm*((*iq_prev) + delta/2*k1) - alpha*((*flq_prev) + delta/2*m1) - (omega-((*spd_prev) + delta/2*o1))*((*fld_prev) + delta/2*n1);
		n2 = alpha*lm*((*id_prev) + delta/2*l1) + (omega-((*spd_prev) + delta/2*o1))*((*flq_prev) + delta/2*m1) - alpha*((*fld_prev) + delta/2*n1);
		o2 = ((cont*(((*fld_prev) + delta/2*n1)*((*iq_prev) + delta/2*k1) - ((*flq_prev) + delta/2*m1)*((*id_prev) + delta/2*l1)))-load_torque)/inertia;

		k3 = -gamma*((*iq_prev) + delta/2*k2) - omega*((*id_prev)+delta/2*l2) + alpha*beta*((*flq_prev)+delta/2*m2) - beta*((*spd_prev)+delta/2*o2)*((*fld_prev)+delta/2*n2) + (vq)/sigma;
		l3 = omega*((*iq_prev) + delta/2*k2) - gamma*((*id_prev) + delta/2*l2) + beta*((*spd_prev) + delta/2*o2)*((*flq_prev) + delta/2*m2) + alpha*beta*((*fld_prev) + delta/2*n2) + (vd)/sigma;
		m3 = alpha*lm*((*iq_prev) + delta/2*k2) - alpha*((*flq_prev) + delta/2*m2) - (omega-((*spd_prev) + delta/2*o2))*((*fld_prev) + delta/2*n2);
		n3 = alpha*lm*((*id_prev) + delta/2*l2) + (omega-((*spd_prev) + delta/2*o2))*((*flq_prev) + delta/2*m2) - alpha*((*fld_prev) + delta/2*n2);
		o3 = ((cont*(((*fld_prev) + delta/2*n2)*((*iq_prev) + delta/2*k2) - ((*flq_prev) + delta/2*m2)*((*id_prev) + delta/2*l2)))-load_torque)/inertia;

		k4 = -gamma*((*iq_prev) + delta*k3) - omega*((*id_prev)+delta*l3) + alpha*beta*((*flq_prev)+delta*m3) - beta*((*spd_prev)+delta*o3)*((*fld_prev)+delta*n3) + (vq)/sigma;
		l4 = omega*((*iq_prev) + delta*k3) - gamma*((*id_prev) + delta*l3) + beta*((*spd_prev) + delta*o3)*((*flq_prev) + delta*m3) + alpha*beta*((*fld_prev) + delta*n3) + (vd)/sigma;
		m4 = alpha*lm*((*iq_prev) + delta*k3) - alpha*((*flq_prev) + delta*m3) - (omega-((*spd_prev) + delta*o3))*((*fld_prev) + delta*n3);
		n4 = alpha*lm*((*id_prev) + delta*l3) + (omega-((*spd_prev) + delta*o3))*((*flq_prev) + delta*m3) - alpha*((*fld_prev) + delta*n3);
		o4 = ((cont*(((*fld_prev) + delta*n3)*((*iq_prev) + delta*k3) - ((*flq_prev) + delta*m3)*((*id_prev) + delta*l3)))-load_torque)/inertia;

		*iq = (*iq_prev) + delta*(k1 + 2*k2 + 2*k3 + k4)/6;
		*id = (*id_prev) + delta*(l1 + 2*l2 + 2*l3 + l4)/6;
		*flq = (*flq_prev) + delta*(m1 + 2*m2 + 2*m3 + m4)/6;
		*fld = (*fld_prev) + delta*(n1 + 2*n2 + 2*n3 + n4)/6;
		*spd = (*spd_prev) + delta*(o1 + 2*o2 + 2*o3 + o4)/6;
		*torque = cont*((*iq)*(*fld) - (*id)*(*flq));

		*theta = *theta_prev + *spd * delta;
		
		*time = *time + delta;
		*iq_prev = *iq;
		*id_prev = *id;
		*flq_prev = *flq;
		*fld_prev = *fld;
		*spd_prev = *spd;
		*theta_prev_prev = *theta_prev;
		*theta_prev = *theta;
	}
}


#ifdef SW
DEFINE_THREAD(vector_control_daemon)
#endif

int main(int argc, char* argv[]){

	#ifdef SW
	init_pipe_handler();
	PTHREAD_DECL(vector_control_daemon);
	PTHREAD_CREATE(vector_control_daemon);
	#endif
	
	char buffer[BUFSIZ];
	char filename_id[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/id1.m";
	char filename_id_err[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/id_err1.m";
	char filename_iq[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/iq1.m";
	char filename_iq_err[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/iq_err1.m";
	char filename_f_ref[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/f_ref1.m";
	char filename_t_ref[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/t_ref1.m";
	char filename_time[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/time1.m";
	char filename_spd[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/spd1.m";	
	char filename_spd_ref[] = "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/spd_ref1.m";
	char filename_vd[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/vd1.m";
	char filename_vq[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/vq1.m";
	char filename_theta[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/theta1.m";
	char filename_torque[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/torque1.m";
	char filename_fld[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/fld1.m";
	char filename_flq[] 	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/flq1.m";
	char filename_test[]	= "/home/pratik/Files/MTP/ahir-master/MTP_Project/Vector_Control_double_work/test.txt";	

	FILE *fp_id = NULL;
	FILE *fp_id_err = NULL;
	FILE *fp_iq = NULL;
	FILE *fp_iq_err = NULL;
	FILE *fp_f_ref = NULL;
	FILE *fp_t_ref = NULL;
	FILE *fp_time = NULL;
	FILE *fp_spd = NULL;
	FILE *fp_spd_ref = NULL;
	FILE *fp_vd = NULL;
	FILE *fp_vq = NULL;
	FILE *fp_theta = NULL;
	FILE *fp_torque = NULL;
	FILE *fp_fld = NULL;
	FILE *fp_flq = NULL;
	
	FILE *fp_test = NULL;
	
	fp_test = fopen(filename_test, "w"); 
	if(fp_test == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("test_ref Values Generated\n", fp_test); 
	fclose(fp_test);
	
	fp_id = fopen(filename_id, "w"); 
	if(fp_id == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("Id = [ ", fp_id); 
	fclose(fp_id);
	
	fp_id_err = fopen(filename_id_err, "w"); 
	if(fp_id_err == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("id_err = [ ", fp_id_err); 
	fclose(fp_id_err);
	
	fp_iq = fopen(filename_iq, "w"); 
	if(fp_iq == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("iq = [ ", fp_iq); 
	fclose(fp_iq);
	
	fp_iq_err = fopen(filename_iq_err, "w"); 
	if(fp_iq_err == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("iq_err = [ ", fp_iq_err); 
	fclose(fp_iq_err);
	
	fp_f_ref = fopen(filename_f_ref, "w"); 
	if(fp_f_ref == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("f_ref = [ ", fp_f_ref); 
	fclose(fp_f_ref);
	
	fp_t_ref = fopen(filename_t_ref, "w"); 
	if(fp_t_ref == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("t_ref = [ ", fp_t_ref); 
	fclose(fp_t_ref);
	
	fp_time = fopen(filename_time, "w"); 
	if(fp_time == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("time = [ ", fp_time); 
	fclose(fp_time);
	
	fp_spd = fopen(filename_spd, "w"); 
	if(fp_spd == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("spd = [ ", fp_spd); 
	fclose(fp_spd);
	
	fp_spd_ref = fopen(filename_spd_ref, "w"); 
	if(fp_spd_ref == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("spd_ref = [ ", fp_spd_ref); 
	fclose(fp_spd_ref);
	
	fp_vd = fopen(filename_vd, "w"); 
	if(fp_vd == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("vd = [ ", fp_vd); 
	fclose(fp_vd);
	
	fp_vq = fopen(filename_vq, "w"); 
	if(fp_vq == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("vq = [ ", fp_vq); 
	fclose(fp_vq);
	
	fp_theta = fopen(filename_theta, "w"); 
	if(fp_theta == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("theta = [ ", fp_theta); 
	fclose(fp_theta);
	
	fp_torque = fopen(filename_torque, "w"); 
	if(fp_torque == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("torque = [ ", fp_torque); 
	fclose(fp_torque);
	
	fp_fld = fopen(filename_fld, "w"); 
	if(fp_fld == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("fld = [ ", fp_fld); 
	fclose(fp_fld);
	
	fp_flq = fopen(filename_flq, "w"); 
	if(fp_flq == NULL) {
		printf("Failed to open file for writing\n");
	}
	fputs("flq = [ ", fp_flq); 
	fclose(fp_flq);

	double id_err = 0,iq_err = 0, theta = 0, speed = 0,temp_1 = 0,temp_2 = 0,temp_3 = 0,temp_4 = 0,temp_5 = 0,temp_6 = 0,temp_7 = 0,temp_8 = 0;
	double voltage_iteration = 150;
	double tol_error = 0.05;
	double t_ref = 0,f_ref = 0;
	double	iq = 0, 
	iq_prev = 0,
	id =0,
	id_prev = 0,
	flq = 0,
	flq_prev = 0,
	fld = 0,
	fld_prev = 0,
	spd=0,
	spd_prev = 0,
	vd = 0,
	vq = 0,
	torque = 0,
	load_torque = 0,
	time = 0;
	double va=0, vb=0, vc=0;
	double valpha =0, vbeta=0;
	float iq_float,id_float,spd_float,spd_ref_float,omega_m_float;
	float id_err_float,iq_err_float,t_ref_float,f_ref_float;
	double spd_ref = 1400;
	int i=0,count = 0;
	double theta_m = 0, theta_prev =0,theta_prev_prev =0;
	double v_alpha =0, v_beta =0;
	double i_alpha =0, i_beta =0;
	double i_alpha_err =0, i_beta_err =0;
	double ia = 0, ib=0, ic =0;
	double ia_err = 0, ib_err=0, ic_err =0;
	double link_voltage = 415/3;
	int no_of_cycles = 2 ; // 50u/500n (Ideal time necessary for conputation for FPGA/Motor_iteration_step)
	uint32_t temp_var = 0,temp_var1 = 0;
	uint32_t a=0,b=0,c=0,d=0,e=0,f=0;
	
	while(time < 11){
		

		for(i = 0; i< no_of_cycles; i++){
			im_zep(&iq,&iq_prev,&id,&id_prev,&flq,&flq_prev,&fld,&fld_prev,&spd_prev,vd,vq,&torque,load_torque,&time,&spd,&theta_m,&theta_prev,&theta_prev_prev);
		}
		
		i_alpha = cos(theta_m)*id - sin(theta_m)*iq;
		i_beta = sin(theta_m)*id + cos(theta_m)*iq;
		
		ia = i_alpha;
		ib = -0.5*i_alpha +0.866*i_beta;
		ic = -0.5*i_alpha - 0.866*i_beta;	
		
		id_float = id;
		iq_float = iq;
		spd_float = (spd*60)/6.28;
		spd_ref_float = spd_ref;
		omega_m_float = spd;
		
		write_float32("in_data1",id_float);
		write_float32("in_data2",iq_float);
		write_float32("in_data3",spd_float);
		write_float32("in_data4",spd_ref_float);
		write_float32("in_data5",omega_m_float);

		id_err_float = read_float32("out_data1");
		iq_err_float = read_float32("out_data2");
		t_ref_float = read_float32("out_data3");
		f_ref_float = read_float32("out_data4");
		
		id_err = id_err_float;
		iq_err = iq_err_float;
		t_ref = t_ref_float;
		f_ref = f_ref_float;
		
		/*
		write_float64("in_data1",id);
		write_float64("in_data2",iq);
		write_float64("in_data3",(spd*60)/6.28);
		write_float64("in_data4",spd_ref);

		id_err = read_float64("out_data1");
		iq_err = read_float64("out_data2");
		t_ref = read_float64("out_data3");
		f_ref = read_float64("out_data4");
		*/
		
		i_alpha_err = cos(t_ref)*id_err - sin(t_ref)*iq_err;
		i_beta_err = sin(t_ref)*id_err + cos(t_ref)*iq_err;
		
		ia_err = i_alpha_err;
		ib_err = -0.5*i_alpha_err +0.866*i_beta_err;
		ic_err = -0.5*i_alpha_err - 0.866*i_beta_err;	
		
		
	
		if ((ia_err - ia) > (tol_error) )
			va = link_voltage;
		else if ((ia_err - ia) < (-tol_error) ) 
			va = -link_voltage;
		else va = va;
		
		if ((ib_err - ib) > (tol_error) )
			vb = link_voltage;
		else if ((ib_err - ib) < (-tol_error) ) 
			vb = -link_voltage;
		else vb = vb;
		
		if ((ic_err - ic) > (tol_error) )
			vc = link_voltage;
		else if ((ic_err - ic) < (-tol_error) ) 
			vc = -link_voltage;
		else vc = vc;
		
		valpha = va - (vb + vc)*0.5;
          	vbeta = 0.866*(vb - vc);
          
          	vd = valpha * cos(theta_m) + vbeta * sin(theta_m);  
          	vq = -valpha * sin(theta_m) + vbeta * cos(theta_m);
		
		
		if (load_torque == 0)
			load_torque=0.5;
		else
			load_torque=load_torque;
			
		if (time>1){
			load_torque = 5;
		}
		if (time>2){
			spd_ref = 500;
		}
		if (time>3){
			spd_ref = 1400;			
		}
		if (time>4){
			spd_ref = 500;			
		}		
		if (time>5){
			load_torque = 0;			
		}
		if (time>6){
			spd_ref = 900;
		}
		if (time>7){
			load_torque = 5;			
		}
		if (time>8){
			spd_ref = 1610;			
		}
		if (time>9){
			spd_ref = 1400;
		}		
		if (time>10){
			load_torque = 0;			
		}
		
		vd = vd;
		vq = vq;
		

		fp_id = fopen(filename_id, "a"); // open file for appending !!! 
		fprintf(fp_id," %20.18f ",id);
		fclose(fp_id);
		
		fp_id_err = fopen(filename_id_err, "a"); // open file for appending !!! 
		fprintf(fp_id_err," %20.18f ",id_err);
		fclose(fp_id_err);
		
		fp_iq_err = fopen(filename_iq_err, "a"); // open file for appending !!! 
		fprintf(fp_iq_err," %20.18f ",iq_err);
		fclose(fp_iq_err);
		
		fp_f_ref = fopen(filename_f_ref, "a"); // open file for appending !!! 
		fprintf(fp_f_ref," %20.18f ",f_ref);
		fclose(fp_f_ref);
		
		fp_t_ref = fopen(filename_t_ref, "a"); // open file for appending !!! 
		fprintf(fp_t_ref," %20.18f ",t_ref);
		fclose(fp_t_ref);
		
		fp_spd_ref = fopen(filename_spd_ref, "a"); // open file for appending !!! 
		fprintf(fp_spd_ref," %20.18f ",theta_m);
		fclose(fp_spd_ref);
		
		fp_time = fopen(filename_time, "a"); // open file for appending !!! 
		fprintf(fp_time," %20.18f ",time);
		fclose(fp_time);
		
		fp_theta = fopen(filename_theta, "a"); // open file for appending !!! 
		fprintf(fp_theta," %20.18f ",t_ref);
		fclose(fp_theta);
		
		fp_torque = fopen(filename_torque, "a"); // open file for appending !!! 
		fprintf(fp_torque," %20.18f ",torque);
		fclose(fp_torque);
		
		fp_vd = fopen(filename_vd, "a"); // open file for appending !!! 
		fprintf(fp_vd," %20.18f ",vd);
		fclose(fp_vd);
		
		fp_vq = fopen(filename_vq, "a"); // open file for appending !!! 
		fprintf(fp_vq," %20.18f ",vq);
		fclose(fp_vq);
		
		fp_fld = fopen(filename_fld, "a"); // open file for appending !!! 
		fprintf(fp_fld," %20.18f ",fld);
		fclose(fp_fld);
		
		fp_flq = fopen(filename_flq, "a"); // open file for appending !!! 
		fprintf(fp_flq," %20.18f ",flq);
		fclose(fp_flq);
		
		fp_iq = fopen(filename_iq, "a"); // open file for appending !!! 
		fprintf(fp_iq," %20.18f ",iq);
		fclose(fp_iq);
		
		fp_spd = fopen(filename_spd, "a"); // open file for appending !!! 
		fprintf(fp_spd," %20.18f ",((spd*60)/6.28));
		fclose(fp_spd);
		
		fp_test = fopen(filename_test, "a"); // open file for appending !!! 
		if(fp_test == NULL)
		{
			printf("Failed to open file for appending\n");
		}
		fprintf(fp_test,"-------------------\n");
		fprintf(fp_test,"id = %20.18f id_err=%20.18f iq = %20.18f iq_err=%20.18f speed=%20.18f torque=%20.18f id_prev=%20.18f time = %20.33f vd = %20.18f vq = %20.18f \n t_ref = %20.18f \n f_ref = %20.18f \n", id,id_err,iq,iq_err,((spd*60)/6.28),torque,id_prev, time,vd,vq, t_ref, f_ref); // write a formatted string to file 
		fprintf(fp_test,"-------------------\n");
		fclose(fp_test);
		
		
		fprintf(stdout," ------------------------- \n 1 = %20.45f \n 2 = %20.18f \n ", id_err,iq_err); 

	}
	
	fp_id = fopen(filename_id, "a"); // open file for appending !!! 
	fprintf(fp_id," ]; ");
	fclose(fp_id);

	fp_id_err = fopen(filename_id_err, "a"); // open file for appending !!! 
	fprintf(fp_id_err," ]; ");
	fclose(fp_id_err);

	fp_iq_err = fopen(filename_iq_err, "a"); // open file for appending !!! 
	fprintf(fp_iq_err," ]; ");
	fclose(fp_iq_err);

	fp_f_ref = fopen(filename_f_ref, "a"); // open file for appending !!! 
	fprintf(fp_f_ref," ]; ");
	fclose(fp_f_ref);

	fp_t_ref = fopen(filename_t_ref, "a"); // open file for appending !!! 
	fprintf(fp_t_ref," ]; ");
	fclose(fp_t_ref);

	fp_spd_ref = fopen(filename_spd_ref, "a"); // open file for appending !!! 
	fprintf(fp_spd_ref," ]; ");
	fclose(fp_spd_ref);

	fp_time = fopen(filename_time, "a"); // open file for appending !!! 
	fprintf(fp_time," ]; ");
	fclose(fp_time);

	fp_theta = fopen(filename_theta, "a"); // open file for appending !!! 
	fprintf(fp_theta," ]; ");
	fclose(fp_theta);

	fp_torque = fopen(filename_torque, "a"); // open file for appending !!! 
	fprintf(fp_torque," ]; ");
	fclose(fp_torque);

	fp_vd = fopen(filename_vd, "a"); // open file for appending !!! 
	fprintf(fp_vd," ]; ");
	fclose(fp_vd);

	fp_vq = fopen(filename_vq, "a"); // open file for appending !!! 
	fprintf(fp_vq," ]; ");
	fclose(fp_vq);

	fp_fld = fopen(filename_fld, "a"); // open file for appending !!! 
	fprintf(fp_fld," ]; ");
	fclose(fp_fld);

	fp_flq = fopen(filename_flq, "a"); // open file for appending !!! 
	fprintf(fp_flq," ]; ");
	fclose(fp_flq);

	fp_iq = fopen(filename_iq, "a"); // open file for appending !!! 
	fprintf(fp_iq," ]; ");
	fclose(fp_iq);

	fp_spd = fopen(filename_spd, "a"); // open file for appending !!! 
	fprintf(fp_spd," ]; ");
	fclose(fp_spd);
	

	#ifdef SW
	close_pipe_handler();
	PTHREAD_CANCEL(vector_control_daemon);
#endif
    return 0;
}

