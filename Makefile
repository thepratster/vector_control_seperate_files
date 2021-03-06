#Mak library file .. Use it. .

# build software version of testbench (to check the "desired behaviour")
AHIR_RELEASE=/home/pratik/Files/MTP/ahir-master/release
SOCKETLIB_INCLUDE=$(AHIR_RELEASE)/CtestBench/include
SOCKETLIB_LIB=$(AHIR_RELEASE)/CtestBench/lib
PIPEHANDLER_INCLUDE=$(AHIR_RELEASE)/pipeHandler/include
PIPEHANDLER_LIB=$(AHIR_RELEASE)/pipeHandler/lib
PTHREADUTILS_INCLUDE=$(AHIR_RELEASE)/pthreadUtils/include
VHDL_LIB=$(AHIR_RELEASE)/vhdl
VHDL_VHPI_LIB=$(AHIR_RELEASE)/CtestBench/vhdl
FUNCTIONLIB=$(AHIR_RELEASE)/functionLibrary/
SRC=./src
all: SW HW 
TOAA:c2llvmbc llvmbc2aa
TOVC:c2llvmbc llvmbc2aa  aalink aa2vc 
VC2VHDL: vc2vhdl  vhdlsim
AA2VHDLSIM:aalink aa2vc vc2vhdl  vhdlsim
TOVHDL:TOVC vc2vhdl

LLVM2AAOPTS=

# the top-level module.
TOPMODULES=-T vector_control_daemon


# compile with SW defined.
SW: $(SRC)/prog.h $(SRC)/testbench.c $(SRC)/prog.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/prog.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/fpsub32fi.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/fpadd32fi.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/fpsub32f.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/fpadd32f.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/fpmul32f.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/fdiv32.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/iq_err_calc.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/rotor_flux_calc.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/omega_calc.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(FUNCTIONLIB)/include -I$(SRC) $(SRC)/theta_calc.c
	gcc -g -c -DSW $(PROGDEFS) -I$(PIPEHANDLER_INCLUDE) -I$(PTHREADUTILS_INCLUDE) -I$(SRC) $(SRC)/testbench.c
	gcc -g -o testbench_sw prog.o fpsub32fi.o fpadd32fi.o fpsub32f.o fpadd32f.o fpmul32f.o fdiv32.o iq_err_calc.o rotor_flux_calc.o omega_calc.o theta_calc.o testbench.o -L$(PIPEHANDLER_LIB) -lPipeHandler -lpthread -lrt

# five steps from C to vhdl simulator.
#HW: c2llvmbc llvmbc2aa  aa2vc  vc2vhdl  vhdlsim
HW: c2llvmbc llvmbc2aa  aalink aa2vc  vc2vhdl  vhdlsim
TOAA: c2llvmbc llvmbc2aa  aalink
TOVC: TOAA aa2vc 
TOVHDL: TOVC vc2vhdl

#AA2VHDL: aa2vc vc2vhdl vhdlsim
AA2VHDL: aa2vc vc2vhdl vhdlsim

# C to llvm byte-code.. use clang.
c2llvmbc: $(SRC)/prog.c $(SRC)/prog.h $(SRC)/fpsub32fi.c $(SRC)/fpadd32fi.c $(SRC)/iq_err_calc.c $(SRC)/rotor_flux_calc.c $(SRC)/omega_calc.c $(SRC)/fpadd32f.c $(SRC)/fpsub32f.c
	clang -O3 -std=gnu89 -I$(SOCKETLIB_INCLUDE) -I$(FUNCTIONLIB)/include -emit-llvm -c $(SRC)/prog.c
	opt --indvars --loopsimplify prog.o -o prog.opt.o 
	llvm-dis prog.opt.o
	
		
# llvm byte-code to Aa..
llvmbc2aa:  prog.opt.o fpsub32fi.opt.o fpadd32fi.opt.o fpsub32f.opt.o fpadd32f.opt.o fpmul32f.opt.o  fdiv32.opt.o  iq_err_calc.opt.o  rotor_flux_calc.opt.o  theta_calc.opt.o  omega_calc.opt.o  
	llvm2aa  prog.opt.o | vcFormat >  prog.aa
#	llvm2aa  fpsub32fi.opt.o | vcFormat >  fpsub32fi.aa
#	llvm2aa  fpadd32fi.opt.o | vcFormat >  fpadd32fi.aa
#	llvm2aa  fpsub32f.opt.o | vcFormat >  fpsub32f.aa
#	llvm2aa  fpadd32f.opt.o | vcFormat >  fpadd32f.aa
#	llvm2aa  fpmul32f.opt.o | vcFormat >  fpmul32f.aa
#	llvm2aa  fdiv32.opt.o | vcFormat >  fdiv32.aa
#	llvm2aa  iq_err_calc.opt.o | vcFormat >  iq_err_calc.aa
#	llvm2aa  rotor_flux_calc.opt.o | vcFormat >  rotor_flux_calc.aa
#	llvm2aa  theta_calc.opt.o | vcFormat >  theta_calc.aa
#	llvm2aa  omega_calc.opt.o | vcFormat >  omega_calc.aa
	
# Aa to vC
aalink:  fpsub32fi.aa fpadd32fi.aa fpsub32f.aa fpadd32f.aa fpmul32f.aa fdiv32.aa iq_err_calc.aa rotor_flux_calc.aa theta_calc.aa
	AaLinkExtMem fpsub32fi.aa fpadd32fi.aa fpsub32f.aa fpadd32f.aa fpmul32f.aa fdiv32.aa iq_err_calc.aa rotor_flux_calc.aa theta_calc.aa | vcFormat > prog.linked.aa
	AaOpt prog.linked.aa | vcFormat > prog.linked.opt.aa
	
aa2vc: prog.linked.opt.aa
	Aa2VC -O -C prog.linked.opt.aa | vcFormat > prog.vc
#	Aa2VC  fpsub32fi.opt.aa | vcFormat >  fpsub32fi.vc
#	Aa2VC  fpadd32fi.opt.aa | vcFormat >  fpadd32fi.vc
#	Aa2VC  fpsub32f.opt.aa | vcFormat >  fpsub32f.vc
#	Aa2VC  fpadd32f.opt.aa | vcFormat >  fpadd32f.vc
#	Aa2VC  fpmul32f.opt.aa | vcFormat >  fpmul32f.vc
#	Aa2VC  fdiv32.opt.aa | vcFormat >  fdiv32.vc
#	Aa2VC  iq_err_calc.opt.aa | vcFormat >  iq_err_calc.vc
#	Aa2VC  rotor_flux_calc.opt.aa | vcFormat >  rotor_flux_calc.vc
#	Aa2VC  theta_calc.opt.aa | vcFormat >  theta_calc.vc

# vC to VHDL
vc2vhdl: prog.vc
	vc2vhdl -O -S 4 -I 2 -v -a -C -e ahir_system -w -s ghdl $(TOPMODULES) -f prog.vc -L $(FUNCTIONLIB)/fpu.list
	vhdlFormat < ahir_system_global_package.unformatted_vhdl > ahir_system_global_package.vhdl
	vhdlFormat < ahir_system.unformatted_vhdl > ahir_system.vhdl
	vhdlFormat < ahir_system_test_bench.unformatted_vhdl > ahir_system_test_bench.vhdl

# build testbench and ghdl executable
# note the use of SOCKETLIB in building the testbench.
vhdlsim: ahir_system.vhdl ahir_system_test_bench.vhdl $(SRC)/testbench.c vhdlCStubs.h vhdlCStubs.c
	gcc -c vhdlCStubs.c  -I$(SRC) -I./ -I$(SOCKETLIB_INCLUDE)
	gcc -c $(SRC)/testbench.c -I$(PTHREADUTILS_INCLUDE) -I$(SRC) -I./ -I$(SOCKETLIB_INCLUDE)
	gcc -o testbench_hw testbench.o vhdlCStubs.o  -L$(SOCKETLIB_LIB) -lSocketLib -lpthread
	ghdl --clean
	ghdl --remove
	ghdl -i --work=GhdlLink  $(VHDL_LIB)/GhdlLink.vhdl
	ghdl -i --work=ahir  $(VHDL_LIB)/ahir.vhdl
	ghdl -i --work=aHiR_ieee_proposed  $(VHDL_LIB)/aHiR_ieee_proposed.vhdl
	ghdl -i --work=work ahir_system_global_package.vhdl
	ghdl -i --work=work ahir_system.vhdl
	ghdl -i --work=work ahir_system_test_bench.vhdl
	ghdl -m --work=work -Wl,-L$(SOCKETLIB_LIB) -Wl,-lVhpi ahir_system_test_bench 

clean:
	rm -rf *.o* *.cf *.*vhdl vhdlCStubs.* *.vcd in_data* out_data* testbench_sw testbench_hw ahir_system_test_bench vhpi.log *.aa *.vc *.lso xst *.ngc *_xmsgs *.xrpt pipeHandler.log *.srp *.ghw *.dot

PHONY: all clean	
