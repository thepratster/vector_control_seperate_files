; ModuleID = 'prog.opt.o'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

@.str = private constant [9 x i8] c"in_data1\00"
@.str1 = private constant [9 x i8] c"in_data2\00"
@.str2 = private constant [9 x i8] c"in_data3\00"
@.str3 = private constant [9 x i8] c"in_data4\00"
@.str4 = private constant [10 x i8] c"out_data1\00"
@.str5 = private constant [10 x i8] c"out_data2\00"
@.str6 = private constant [10 x i8] c"out_data3\00"
@.str7 = private constant [10 x i8] c"out_data4\00"

define void @vector_control_daemon() noreturn nounwind {
; <label>:0
  %1 = tail call float @fpmul32f(float 3.000000e+03, float 4.000000e+00) nounwind
  %2 = tail call float @fpmul32f(float %1, float 0x3FE9E83E40000000) nounwind
  br label %3

; <label>:3                                       ; preds = %64, %0
  %flux_rotor_prev.0 = phi float [ 0.000000e+00, %0 ], [ %45, %64 ]
  %theta_prev.0 = phi float [ 0.000000e+00, %0 ], [ %47, %64 ]
  %int_flux_err.0 = phi float [ 0.000000e+00, %0 ], [ %int_flux_err.1, %64 ]
  %int_speed_err.0 = phi float [ 0.000000e+00, %0 ], [ %int_speed_err.1, %64 ]
  %4 = tail call float @read_float32(i8* getelementptr inbounds ([9 x i8]* @.str, i64 0, i64 0)) nounwind
  %5 = tail call float @read_float32(i8* getelementptr inbounds ([9 x i8]* @.str1, i64 0, i64 0)) nounwind
  %6 = tail call float @read_float32(i8* getelementptr inbounds ([9 x i8]* @.str2, i64 0, i64 0)) nounwind
  %7 = tail call float @read_float32(i8* getelementptr inbounds ([9 x i8]* @.str3, i64 0, i64 0)) nounwind
  %8 = tail call float @fpsub32f(float %7, float %6) nounwind
  %9 = tail call float @fpmul32f(float 0x3F0A36E2E0000000, float %8) nounwind
  %10 = tail call float @fpadd32f(float %9, float %int_speed_err.0) nounwind
  %11 = tail call float @fpmul32f(float 5.000000e+01, float %10) nounwind
  %12 = fpext float %11 to double
  %13 = fcmp olt double %12, -1.500000e+01
  br i1 %13, label %17, label %14

; <label>:14                                      ; preds = %3
  %15 = fcmp ogt double %12, 1.500000e+01
  br i1 %15, label %17, label %16

; <label>:16                                      ; preds = %14
  br label %17

; <label>:17                                      ; preds = %16, %14, %3
  %int_speed_err.1 = phi float [ %11, %16 ], [ -1.500000e+01, %3 ], [ 1.500000e+01, %14 ]
  %18 = tail call float @fpmul32f(float %8, float 4.000000e+01) nounwind
  %19 = tail call float @fpadd32f(float %int_speed_err.1, float %18) nounwind
  %20 = fcmp olt float %19, -3.000000e+01
  br i1 %20, label %24, label %21

; <label>:21                                      ; preds = %17
  %22 = fcmp ogt float %19, 3.000000e+01
  br i1 %22, label %24, label %23

; <label>:23                                      ; preds = %21
  br label %24

; <label>:24                                      ; preds = %23, %21, %17
  %torque_ref.0 = phi float [ %19, %23 ], [ -3.000000e+01, %17 ], [ 3.000000e+01, %21 ]
  %25 = fpext float %7 to double
  %26 = fcmp ugt double %25, 2.000000e+03
  br i1 %26, label %27, label %43

; <label>:27                                      ; preds = %24
  %28 = fcmp ugt double %25, 2.500000e+03
  br i1 %28, label %33, label %29

; <label>:29                                      ; preds = %27
  %30 = tail call float @fpmul32f(float 0xBF2A36E2E0000000, float %7) nounwind
  %31 = tail call float @fpadd32f(float %30, float 0x3FF6666660000000) nounwind
  %32 = tail call float @fpmul32f(float %31, float 3.000000e+02) nounwind
  br label %43

; <label>:33                                      ; preds = %27
  %34 = fcmp ugt double %25, 3.000000e+03
  br i1 %34, label %39, label %35

; <label>:35                                      ; preds = %33
  %36 = tail call float @fpmul32f(float 0xBF3797CC40000000, float %7) nounwind
  %37 = tail call float @fpadd32f(float %36, float 0x3FFCCCCCC0000000) nounwind
  %38 = tail call float @fpmul32f(float %37, float 3.000000e+02) nounwind
  br label %43

; <label>:39                                      ; preds = %33
  %40 = tail call float @fpmul32f(float 0xBF3B866E40000000, float %7) nounwind
  %41 = tail call float @fpadd32f(float %40, float 0x3FFFAE1480000000) nounwind
  %42 = tail call float @fpmul32f(float %41, float 3.000000e+02) nounwind
  br label %43

; <label>:43                                      ; preds = %39, %35, %29, %24
  %flux_ref.0 = phi float [ %32, %29 ], [ %38, %35 ], [ %42, %39 ], [ 3.000000e+02, %24 ]
  %44 = tail call float @fpadd32f(float 0x3F0A36E2E0000000, float 0x3FBA9A7C20000000) nounwind
  %45 = tail call float @rotor_flux_calc(float 0x3F0A36E2E0000000, float 0x3FE9E83E40000000, float %4, float %flux_rotor_prev.0, float %44, float 0x3FBA9A7C20000000) nounwind
  %46 = tail call float @omega_calc(float 0x3FE9E83E40000000, float %5, float 0x3FBA9A7C20000000, float %45) nounwind
  %47 = tail call float @theta_calc(float %46, float 0x4073A28C60000000, float 0x3F0A36E2E0000000, float %theta_prev.0) nounwind
  %48 = tail call float @iq_err_calc(float 0x3FEAEF9DC0000000, float %torque_ref.0, float %2, float %45) nounwind
  %49 = tail call float @fpsub32f(float %flux_ref.0, float %45) nounwind
  %50 = tail call float @fpmul32f(float 0x3E6AD7F2A0000000, float %49) nounwind
  %51 = tail call float @fpadd32f(float %50, float %int_flux_err.0) nounwind
  %52 = tail call float @fpmul32f(float 5.000000e+07, float %51) nounwind
  %53 = fcmp olt float %52, -1.000000e+06
  br i1 %53, label %57, label %54

; <label>:54                                      ; preds = %43
  %55 = fcmp ogt float %52, 1.000000e+06
  br i1 %55, label %57, label %56

; <label>:56                                      ; preds = %54
  br label %57

; <label>:57                                      ; preds = %56, %54, %43
  %int_flux_err.1 = phi float [ %52, %56 ], [ -1.000000e+06, %43 ], [ 1.000000e+06, %54 ]
  %58 = tail call float @fpmul32f(float %49, float 4.000000e+07) nounwind
  %59 = tail call float @fpadd32f(float %int_flux_err.1, float %58) nounwind
  %60 = fcmp olt float %59, -2.000000e+06
  br i1 %60, label %64, label %61

; <label>:61                                      ; preds = %57
  %62 = fcmp ogt float %59, 2.000000e+06
  br i1 %62, label %64, label %63

; <label>:63                                      ; preds = %61
  %phitmp = fpext float %59 to double
  br label %64

; <label>:64                                      ; preds = %63, %61, %57
  %flux_add.0 = phi double [ %phitmp, %63 ], [ -2.000000e+06, %57 ], [ 2.000000e+06, %61 ]
  %65 = tail call i32 (...)* @fdiv32(double %flux_add.0, double 8.096000e+05) nounwind
  %66 = sitofp i32 %65 to float
  tail call void @write_float32(i8* getelementptr inbounds ([10 x i8]* @.str4, i64 0, i64 0), float %66) nounwind
  tail call void @write_float32(i8* getelementptr inbounds ([10 x i8]* @.str5, i64 0, i64 0), float %48) nounwind
  tail call void @write_float32(i8* getelementptr inbounds ([10 x i8]* @.str6, i64 0, i64 0), float %46) nounwind
  tail call void @write_float32(i8* getelementptr inbounds ([10 x i8]* @.str7, i64 0, i64 0), float %45) nounwind
  br label %3
}

declare float @fpmul32f(float, float)

declare float @read_float32(i8*)

declare float @fpsub32f(float, float)

declare float @fpadd32f(float, float)

declare float @rotor_flux_calc(float, float, float, float, float, float)

declare float @omega_calc(float, float, float, float)

declare float @theta_calc(float, float, float, float)

declare float @iq_err_calc(float, float, float, float)

declare i32 @fdiv32(...)

declare void @write_float32(i8*, float)
