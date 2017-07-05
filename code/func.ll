; ModuleID = 'func.cc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@s = global i32 200, align 4

; Function Attrs: nounwind uwtable
define i32 @_Z4funcv() #0 {
  %ret = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %ret, align 4
  store i32 1, i32* %a, align 4
  store i32 2, i32* %b, align 4
  %1 = load i32, i32* %a, align 4
  %2 = load i32, i32* %b, align 4
  %3 = mul nsw i32 %1, %2
  store i32 %3, i32* %c, align 4
  store i32 0, i32* %i, align 4
  br label %4

; <label>:4                                       ; preds = %26, %0
  %5 = load i32, i32* %i, align 4
  %6 = load i32, i32* @s, align 4
  %7 = icmp slt i32 %5, %6
  br i1 %7, label %8, label %29

; <label>:8                                       ; preds = %4
  %9 = load i32, i32* %i, align 4
  %10 = srem i32 %9, 5
  %11 = icmp ne i32 %10, 0
  br i1 %11, label %12, label %15

; <label>:12                                      ; preds = %8
  %13 = load i32, i32* %ret, align 4
  %14 = and i32 %13, 3
  store i32 %14, i32* %ret, align 4
  br label %15

; <label>:15                                      ; preds = %12, %8
  %16 = load i32, i32* %ret, align 4
  switch i32 %16, label %24 [
    i32 1, label %17
    i32 4, label %20
  ]

; <label>:17                                      ; preds = %15
  %18 = load i32, i32* %ret, align 4
  %19 = add nsw i32 %18, 3
  store i32 %19, i32* %ret, align 4
  br label %25

; <label>:20                                      ; preds = %15
  %21 = load i32, i32* @s, align 4
  %22 = load i32, i32* %ret, align 4
  %23 = mul nsw i32 %22, %21
  store i32 %23, i32* %ret, align 4
  br label %25

; <label>:24                                      ; preds = %15
  br label %25

; <label>:25                                      ; preds = %24, %20, %17
  br label %26

; <label>:26                                      ; preds = %25
  %27 = load i32, i32* %i, align 4
  %28 = add nsw i32 %27, 1
  store i32 %28, i32* %i, align 4
  br label %4

; <label>:29                                      ; preds = %4
  %30 = load i32, i32* %ret, align 4
  %31 = load i32, i32* %c, align 4
  %32 = sdiv i32 %30, %31
  ret i32 %32
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}
