; ModuleID = 'omega_calc.opt.o'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

define float @omega_calc(float %Lm, float %iq, float %tau_r, float %flux_rotor) nounwind {
  %1 = tail call float @fpmul32f(float %Lm, float %iq) nounwind
  %2 = tail call float @fpmul32f(float %tau_r, float %flux_rotor) nounwind
  %3 = fpext float %1 to double
  %4 = fpext float %2 to double
  %5 = tail call i32 (...)* @fdiv32(double %3, double %4) nounwind
  %6 = sitofp i32 %5 to float
  ret float %6
}

declare float @fpmul32f(float, float)

declare i32 @fdiv32(...)
