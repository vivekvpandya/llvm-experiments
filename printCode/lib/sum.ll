; ModuleID = 'lib/sum.bc'
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.11.0"

@.str = private unnamed_addr constant [9 x i8] c"sum: %d\0A\00", align 1

; Function Attrs: nounwind ssp uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %n = alloca i32, align 4
  %sum = alloca i32, align 4
  store i32 0, i32* %1
  store i32 0, i32* %sum, align 4
  store i32 0, i32* %n, align 4
  br label %2

; <label>:2                                       ; preds = %11, %0
  %3 = load i32, i32* %n, align 4
  %4 = icmp slt i32 %3, 10
  br i1 %4, label %5, label %14

; <label>:5                                       ; preds = %2
  %6 = load i32, i32* %sum, align 4
  %7 = load i32, i32* %n, align 4
  %8 = load i32, i32* %n, align 4
  %9 = mul nsw i32 %7, %8
  %10 = add nsw i32 %6, %9
  store i32 %10, i32* %sum, align 4
  br label %11

; <label>:11                                      ; preds = %5
  %12 = load i32, i32* %n, align 4
  %13 = add nsw i32 %12, 1
  store i32 %13, i32* %n, align 4
  br label %2

; <label>:14                                      ; preds = %2
  %15 = load i32, i32* %sum, align 4
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i32 0, i32 0), i32 %15)
  %17 = load i32, i32* %1
  ret i32 %17
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind ssp uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+ssse3,+cx16,+sse,+sse2,+sse3" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+ssse3,+cx16,+sse,+sse2,+sse3" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"Apple LLVM version 7.0.0 (clang-700.1.74)"}
