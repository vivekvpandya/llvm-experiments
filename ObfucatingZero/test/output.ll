; ModuleID = 'test/output.bc'
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.11.0"

; Function Attrs: nounwind ssp uwtable
define i32 @addZero(i32 %x) #0 {
  %1 = alloca i32, align 4
  %y = alloca i32, align 4
  %t = alloca i32, align 4
  store i32 %x, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  %3 = alloca i32
  store i32 2, i32* %3
  %4 = load i32, i32* %3
  %5 = xor i32 %4, %4
  %6 = add nsw i32 %2, %5
  store i32 %6, i32* %y, align 4
  %7 = load i32, i32* %y, align 4
  %8 = alloca i32
  store i32 2, i32* %8
  %9 = load i32, i32* %8
  %10 = xor i32 %9, %9
  %11 = add nsw i32 %7, %10
  store i32 %11, i32* %t, align 4
  %12 = load i32, i32* %t, align 4
  ret i32 %12
}

attributes #0 = { nounwind ssp uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+ssse3,+cx16,+sse,+sse2,+sse3" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"Apple LLVM version 7.0.0 (clang-700.1.74)"}
