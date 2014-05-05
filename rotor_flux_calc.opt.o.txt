; ModuleID = 'rotor_flux_calc.opt.o'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

define float @rotor_flux_calc(float %del_t, float %Lm, float %id, float %flux_rotor_prev, float %tau_new, float %tau_r) nounwind {
  %1 = tail call float @fpmul32f(float 5.000000e+04, float %Lm) nounwind
  %2 = tail call float @fpmul32f(float %id, float %1) nounwind
  %3 = tail call float @fpmul32f(float 0x40F95EFC00000000, float %flux_rotor_prev) nounwind
  %4 = tail call float @fpadd32f(float %3, float %2) nounwind
  %5 = fpext float %4 to double
  %6 = tail call i32 (...)* @fdiv32(double %5, double 0x40F9621C0C49BA5E) nounwind
  %7 = sitofp i32 %6 to float
  ret float %7
}

declare float @fpmul32f(float, float)

declare float @fpadd32f(float, float)

declare i32 @fdiv32(...)
