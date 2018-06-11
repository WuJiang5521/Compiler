; ModuleID = 'LLVM_IR'
source_filename = "main"

@f = global i32 0
@k = global i32 0
@.str = private constant [4 x i8] c"%d\0A\00"
@.str.1 = private constant [4 x i8] c"%d\0A\00"

define internal void @main() {
entry:
  %0 = load i32, i32* @k
  %1 = load i32, i32* @k
  store i32 0, i32* @k
  %2 = load i32, i32* @f
  %3 = load i32, i32* @f
  %4 = call i32 @go(i32* @k, i32 5)
  store i32 %4, i32* @f
  %5 = load i32, i32* @f
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %5)
  %7 = load i32, i32* @k
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 %7)
  ret void
}

declare i32 @printf(i8*, ...)

define internal i32 @go(i32* %b1, i32 %a2) {
entry:
  %b = alloca i32*
  store i32* %b1, i32** %b
  %a = alloca i32
  store i32 %a2, i32* %a
  %go = alloca i32
  %fk = alloca i32
  %t = alloca float
  %0 = load i32, i32* %a
  %1 = icmp sgt i32 %0, 0
  br i1 %1, label %thenStmt, label %elseStmt

thenStmt:                                         ; preds = %entry
  %2 = load i32, i32* %go
  %3 = load i32, i32* %go
  %4 = load i32, i32* %a
  %5 = load i32*, i32** %b
  %6 = load i32, i32* %a
  %7 = sub i32 %6, 1
  %8 = call i32 @go(i32* %5, i32 %7)
  %9 = mul i32 %4, %8
  store i32 %9, i32* %go
  br label %mergeStmt

elseStmt:                                         ; preds = %entry
  %10 = load i32, i32* %go
  %11 = load i32, i32* %go
  store i32 1, i32* %go
  br label %mergeStmt

mergeStmt:                                        ; preds = %elseStmt, %thenStmt
  %12 = load i32*, i32** %b
  %13 = load i32, i32* %12
  %14 = load i32*, i32** %b
  %15 = load i32, i32* %14
  %16 = load i32*, i32** %b
  %17 = load i32, i32* %16
  %18 = load i32, i32* %go
  %19 = add i32 %17, %18
  store i32 %19, i32* %14
  %20 = load i32, i32* @k
  %21 = load i32, i32* @k
  %22 = load i32, i32* @k
  %23 = load i32, i32* %go
  %24 = add i32 %22, %23
  store i32 %24, i32* @k
  %25 = load i32, i32* %go
  ret i32 %25
}
