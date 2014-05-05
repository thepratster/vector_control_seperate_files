; ModuleID = 'fdiv32.opt.o'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

define i64 @getSlice64(i64 %reg, i8 zeroext %h, i8 zeroext %l) nounwind readnone {
  %1 = zext i8 %h to i64
  %2 = sub i64 63, %1
  %3 = and i64 %2, 4294967295
  %4 = shl i64 %reg, %3
  %5 = zext i8 %l to i64
  %6 = add i64 %2, %5
  %7 = and i64 %6, 4294967295
  %8 = lshr i64 %4, %7
  ret i64 %8
}

define zeroext i8 @getBit64(i64 %reg, i8 zeroext %pos) nounwind readnone {
  %1 = zext i8 %pos to i64
  %2 = sub i64 63, %1
  %3 = and i64 %2, 4294967295
  %4 = shl i64 %reg, %3
  %5 = lshr i64 %4, 63
  %6 = trunc i64 %5 to i8
  ret i8 %6
}

define i64 @setSlice64(i64 %reg, i8 zeroext %h, i8 zeroext %l, i64 %value) nounwind readnone {
  %1 = zext i8 %h to i64
  %2 = zext i8 %l to i64
  %3 = sub i64 63, %1
  %4 = add i64 %3, %2
  %5 = and i64 %4, 4294967295
  %6 = lshr i64 -1, %5
  %7 = and i64 %6, %value
  %8 = shl i64 %7, %2
  %9 = shl i64 %6, %2
  %10 = xor i64 %9, -1
  %11 = and i64 %10, %reg
  %12 = or i64 %11, %8
  ret i64 %12
}

define i64 @setBit64(i64 %reg, i8 zeroext %pos, i8 zeroext %value) nounwind readnone {
  %1 = zext i8 %value to i64
  %2 = zext i8 %pos to i64
  %3 = and i64 %1, 1
  %4 = shl i64 %3, %2
  %5 = shl i64 1, %2
  %6 = xor i64 %5, -1
  %7 = and i64 %6, %reg
  %8 = or i64 %7, %4
  ret i64 %8
}

define double @fdiv32(double %a, double %b) nounwind readnone {
; <label>:0
  %tmp17 = bitcast double %a to i64
  %tmp15 = bitcast double %b to i64
  %1 = and i64 %tmp17, 9223372036854775807
  %2 = and i64 %tmp15, 9223372036854775807
  %3 = icmp eq i64 %1, 0
  br i1 %3, label %7, label %4

; <label>:4                                       ; preds = %0
  %5 = and i64 %tmp15, 9218868437227405312
  %tmp17.mask = and i64 %tmp17, 9218868437227405312
  %6 = add i64 %tmp17.mask, 4602678819172646912
  %phitmp = sub i64 %6, %5
  %phitmp20 = and i64 %phitmp, 9218868437227405312
  br label %7

; <label>:7                                       ; preds = %4, %0
  %8 = phi i64 [ %phitmp20, %4 ], [ 0, %0 ]
  %9 = and i64 %tmp17, 4503599627370495
  %10 = or i64 %tmp15, 4602678819172646912
  %11 = or i64 %8, %9
  %12 = and i64 %10, 4607182418800017407
  %tmp13 = bitcast i64 %11 to double
  %tmp11 = bitcast i64 %12 to double
  %13 = fmul double %tmp11, 0x3FFE1E1E20000000
  %14 = fsub double 0x40069696A0000000, %13
  %15 = fmul double %tmp11, %14
  %16 = fsub double 2.000000e+00, %15
  %17 = fmul double %14, %16
  %18 = fmul double %tmp11, %17
  %19 = fsub double 2.000000e+00, %18
  %20 = fmul double %17, %19
  %21 = fmul double %tmp11, %20
  %22 = fsub double 2.000000e+00, %21
  %23 = fmul double %20, %22
  %24 = fmul double %tmp11, %23
  %25 = fsub double 2.000000e+00, %24
  %26 = fmul double %23, %25
  %27 = icmp eq i64 %2, 0
  %or.cond = or i1 %3, %27
  br i1 %or.cond, label %30, label %28

; <label>:28                                      ; preds = %7
  %29 = fmul double %tmp13, %26
  %phitmp19 = bitcast double %29 to i64
  %phitmp21 = and i64 %phitmp19, 9223372036854775807
  br label %30

; <label>:30                                      ; preds = %28, %7
  %31 = phi i64 [ %phitmp21, %28 ], [ 0, %7 ]
  %32 = xor i64 %tmp15, %tmp17
  %33 = and i64 %32, -9223372036854775808
  %34 = or i64 %31, %33
  %tmp4 = bitcast i64 %34 to double
  ret double %tmp4
}
