; ModuleID = 'iq_err_calc.opt.o'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

define float @iq_err_calc(float %Lr, float %torque_ref, float %constant_1, float %flux_rotor) nounwind {
  %1 = fcmp olt float %flux_rotor, 1.000000e+00
  %.0 = select i1 %1, float 1.000000e+00, float %flux_rotor
  %2 = tail call float @fpmul32f(float 2.000000e+06, float %Lr) nounwind
  %3 = tail call float @fpmul32f(float %2, float %torque_ref) nounwind
  %4 = tail call float @fpmul32f(float %constant_1, float %.0) nounwind
  %5 = fpext float %3 to double
  %6 = fpext float %4 to double
  %7 = tail call i32 (...)* @fdiv32(double %5, double %6) nounwind
  %8 = sitofp i32 %7 to float
  ret float %8
}

declare float @fpmul32f(float, float)

declare i32 @fdiv32(...)
