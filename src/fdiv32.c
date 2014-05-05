#include <stdio.h>
#include <stdint.h>
#include "prog.h"
#define _BITCAST_(Type,val) *((Type*)&val)

uint64_t getSlice64(uint64_t reg, uint8_t h, uint8_t l)
{
	reg = reg << (63 - h);
	reg = reg >> (63 - h + l);
	return reg;
}

uint8_t getBit64(uint64_t reg, uint8_t pos)
{
	return getSlice64(reg, pos, pos);
}

uint64_t setSlice64(uint64_t reg, uint8_t h, uint8_t l, uint64_t value)
{
	uint64_t mask = -1;
	mask = mask >> (63 - h + l);
	value = value & mask;
	value = value << l;

	mask = mask << l;
	reg = reg & ~mask;
	reg = reg | value;
	return reg;
}

uint64_t setBit64(uint64_t reg, uint8_t pos, uint8_t value)
{
	return setSlice64(reg, pos, pos, value);
}

double fdiv32(double a, double b)
{
	uint64_t n = _BITCAST_(uint64_t,a);
	uint64_t d = _BITCAST_(uint64_t,b);

	uint64_t n_val = getSlice64(n, 62, 0);
	uint64_t d_val = getSlice64(d, 62, 0);

	uint8_t s_n = getBit64(n, 63);
	uint8_t s_d = getBit64(d, 63);

	uint16_t e1 = getSlice64(n, 62, 52);
	uint16_t e2 = getSlice64(d, 62, 52);

	uint16_t e1_new = (n_val == 0) ? 0 : (e1 - e2 + 1022);
	uint16_t e2_new = 1022;

	uint64_t n1 = setSlice64(n, 62, 52, e1_new);
	uint64_t d1 = setSlice64(d, 62, 52, e2_new);

	uint64_t n_new = setBit64(n1, 63, 0);
	uint64_t d_new = setBit64(d1, 63, 0);

	double a_new = _BITCAST_(double,n_new);
	double b_new = _BITCAST_(double,d_new);

	//double x = fpsub64(2.8235294818878173828125 , fpmul64(1.88235294818878173828125 , b_new));
	//Make initial guess as (48/17 - (32/17)*divisor) for fast convergence
	double x = 2.8235294818878173828125 - (1.88235294818878173828125 * b_new);// (48/17 - (32/17) * b_new)

	int i = 0;

	for(; i < 4; i++)
	{
		//x = fpmul64(x , fpsub64(2 , fpmul64(b_new , x)));
		x = x * (2 - (b_new * x));
	}
		
	// AHIR does not return nan and inf. Hence commented out. Will work in s/w.
	
	//uint64_t tmp = 0x7ff0000000000000;
	//uint64_t tmp1 = 0x7fffffffffffffff;

	//double inf = _BITCAST_(double,tmp);
	//double nan = _BITCAST_(double,tmp1);

	double res = 0;


	//res = ((n_val == 0) && (d_val == 0)) ? nan : res;
	//res = ((n_val != 0) && (d_val == 0)) ? inf : res;

	//res = ((n_val != 0) && (d_val != 0)) ? fpmul64(a_new , x) : res;
	res = ((n_val != 0) && (d_val != 0)) ? (a_new * x) : res;

	//res = (s_n ^ s_d) ? -res : res; Working in s/w. Simulation very slow in AHIR. Provided work around as below.

	uint64_t res_uint = _BITCAST_(uint64_t,res);
	res_uint = setBit64(res_uint, 63, s_n ^ s_d);

	res = _BITCAST_(double,res_uint);

	return res;
}
