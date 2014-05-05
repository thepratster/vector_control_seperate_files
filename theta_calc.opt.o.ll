; ModuleID = 'theta_calc.opt.o'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

define float @theta_calc(float %omega_r, float %omega_m, float %del_t, float %theta_prev) nounwind {
  %1 = tail call float @fpmul32f(float %omega_r, float %omega_m) nounwind
  %2 = tail call float @fpmul32f(float %1, float %del_t) nounwind
  %3 = tail call float @fpadd32f(float %theta_prev, float %1) nounwind
  ret float %3
}

declare float @fpmul32f(float, float)

declare float @fpadd32f(float, float)
