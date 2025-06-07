; ModuleID = 'my_module'
source_filename = "my_module"

%Person = type { i32, i8 }

@0 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@2 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@3 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@4 = private unnamed_addr constant [10 x i8] c"Both true\00", align 1
@5 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@6 = private unnamed_addr constant [10 x i8] c"Both true\00", align 1
@7 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@8 = private unnamed_addr constant [9 x i8] c"One true\00", align 1
@9 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@10 = private unnamed_addr constant [9 x i8] c"One true\00", align 1
@11 = private unnamed_addr constant [4 x i8] c"%c\0A\00", align 1
@12 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@13 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@14 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@15 = private unnamed_addr constant [9 x i8] c"Positive\00", align 1
@16 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@17 = private unnamed_addr constant [13 x i8] c"Non-positive\00", align 1
@18 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@19 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@20 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@21 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@22 = private unnamed_addr constant [4 x i8] c"One\00", align 1
@23 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@24 = private unnamed_addr constant [4 x i8] c"Two\00", align 1
@25 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@26 = private unnamed_addr constant [6 x i8] c"Other\00", align 1
@27 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@28 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@29 = private unnamed_addr constant [4 x i8] c"%c\0A\00", align 1
@30 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@31 = private unnamed_addr constant [6 x i8] c"hello\00", align 1

define void @main() {
entry:
  %a = alloca i32, align 4
  store i32 2, ptr %a, align 4
  %b = alloca i32, align 4
  store i32 9, ptr %b, align 4
  %c = alloca ptr, align 8
  store ptr @0, ptr %c, align 8
  %i = alloca i32, align 4
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %for.load = load i32, ptr %i, align 4
  %for.exit = icmp sge i32 %for.load, 4
  br i1 %for.exit, label %for.end, label %for.body

for.body:                                         ; preds = %for.cond
  %0 = load i32, ptr %a, align 4
  %1 = load i32, ptr %i, align 4
  %add = add i32 %0, %1
  %2 = call i32 (ptr, ...) @printf(ptr @1, i32 %add)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %3 = load i32, ptr %i, align 4
  %for.step = add i32 %3, 1
  store i32 %for.step, ptr %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  br label %continue

continue:                                         ; preds = %for.end
  %load_str = load ptr, ptr %c, align 8
  %4 = call i32 (ptr, ...) @printf(ptr @2, ptr %load_str)
  %5 = load i32, ptr %a, align 4
  %6 = load i32, ptr %b, align 4
  %bool_lhs = icmp ne i32 %5, 0
  %bool_rhs = icmp ne i32 %6, 0
  %and = and i1 %bool_lhs, %bool_rhs
  %and_result = zext i1 %and to i32
  %ifcond = icmp ne i32 %and_result, 0
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %continue
  %7 = call i32 (ptr, ...) @printf(ptr @3, ptr @4)
  br label %merge

else:                                             ; preds = %continue
  br label %else.body

else.body:                                        ; preds = %else
  br label %merge

merge:                                            ; preds = %else.body, %then
  %8 = load i32, ptr %a, align 4
  %9 = load i32, ptr %b, align 4
  %bool_lhs1 = icmp ne i32 %8, 0
  %bool_rhs2 = icmp ne i32 %9, 0
  %and3 = and i1 %bool_lhs1, %bool_rhs2
  %and_result4 = zext i1 %and3 to i32
  %ifcond6 = icmp ne i32 %and_result4, 0
  br i1 %ifcond6, label %then5, label %else7

then5:                                            ; preds = %merge
  %10 = call i32 (ptr, ...) @printf(ptr @5, ptr @6)
  br label %merge9

else7:                                            ; preds = %merge
  br label %else.body8

else.body8:                                       ; preds = %else7
  br label %merge9

merge9:                                           ; preds = %else.body8, %then5
  %11 = load i32, ptr %a, align 4
  %12 = load i32, ptr %b, align 4
  %bool_lhs10 = icmp ne i32 %11, 0
  %bool_rhs11 = icmp ne i32 %12, 0
  %OR = or i1 %bool_lhs10, %bool_rhs11
  %or_result = zext i1 %OR to i32
  %ifcond13 = icmp ne i32 %or_result, 0
  br i1 %ifcond13, label %then12, label %else14

then12:                                           ; preds = %merge9
  %13 = call i32 (ptr, ...) @printf(ptr @7, ptr @8)
  br label %merge16

else14:                                           ; preds = %merge9
  br label %else.body15

else.body15:                                      ; preds = %else14
  br label %merge16

merge16:                                          ; preds = %else.body15, %then12
  %14 = load i32, ptr %a, align 4
  %15 = load i32, ptr %b, align 4
  %bool_lhs17 = icmp ne i32 %14, 0
  %bool_rhs18 = icmp ne i32 %15, 0
  %OR19 = or i1 %bool_lhs17, %bool_rhs18
  %or_result20 = zext i1 %OR19 to i32
  %ifcond22 = icmp ne i32 %or_result20, 0
  br i1 %ifcond22, label %then21, label %else23

then21:                                           ; preds = %merge16
  %16 = call i32 (ptr, ...) @printf(ptr @9, ptr @10)
  br label %merge25

else23:                                           ; preds = %merge16
  br label %else.body24

else.body24:                                      ; preds = %else23
  br label %merge25

merge25:                                          ; preds = %else.body24, %then21
  %d = alloca i8, align 1
  store i8 65, ptr %d, align 1
  %17 = load i8, ptr %d, align 1
  %18 = call i32 (ptr, ...) @printf(ptr @11, i8 %17)
  %s = alloca ptr, align 8
  store ptr @12, ptr %s, align 8
  %load_str26 = load ptr, ptr %s, align 8
  %19 = call i32 (ptr, ...) @printf(ptr @13, ptr %load_str26)
  %20 = load i32, ptr %a, align 4
  %gt = icmp sgt i32 %20, 0
  %gt_ext = zext i1 %gt to i32
  %ifcond28 = icmp ne i32 %gt_ext, 0
  br i1 %ifcond28, label %then27, label %else29

then27:                                           ; preds = %merge25
  %21 = call i32 (ptr, ...) @printf(ptr @14, ptr @15)
  br label %merge32

else29:                                           ; preds = %merge25
  br label %else.body30

else.body30:                                      ; preds = %else29
  %22 = call i32 (ptr, ...) @printf(ptr @16, ptr @17)
  br label %else.body31

else.body31:                                      ; preds = %else.body30
  br label %merge32

merge32:                                          ; preds = %else.body31, %then27
  %j = alloca i32, align 4
  store i32 0, ptr %j, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %merge32
  %23 = load i32, ptr %j, align 4
  %lt = icmp slt i32 %23, 5
  %lt_ext = zext i1 %lt to i32
  %whilecond = icmp ne i32 %lt_ext, 0
  br i1 %whilecond, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %24 = load i32, ptr %j, align 4
  %25 = call i32 (ptr, ...) @printf(ptr @18, i32 %24)
  %26 = load i32, ptr %j, align 4
  %increment = add i32 %26, 1
  store i32 %increment, ptr %j, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %k = alloca i32, align 4
  store i32 1, ptr %k, align 4
  br label %for.cond33

for.cond33:                                       ; preds = %for.inc35, %while.end
  %for.load37 = load i32, ptr %k, align 4
  %for.exit38 = icmp sge i32 %for.load37, 5
  br i1 %for.exit38, label %for.end36, label %for.body34

for.body34:                                       ; preds = %for.cond33
  %27 = load i32, ptr %k, align 4
  %28 = call i32 (ptr, ...) @printf(ptr @19, i32 %27)
  br label %for.inc35

for.inc35:                                        ; preds = %for.body34
  %29 = load i32, ptr %k, align 4
  %for.step39 = add i32 %29, 1
  store i32 %for.step39, ptr %k, align 4
  br label %for.cond33

for.end36:                                        ; preds = %for.cond33
  br label %continue40

continue40:                                       ; preds = %for.end36
  %l = alloca i32, align 4
  store i32 5, ptr %l, align 4
  br label %for.cond41

for.cond41:                                       ; preds = %for.inc43, %continue40
  %for.load45 = load i32, ptr %l, align 4
  %for.exit46 = icmp sle i32 %for.load45, 1
  br i1 %for.exit46, label %for.end44, label %for.body42

for.body42:                                       ; preds = %for.cond41
  %30 = load i32, ptr %l, align 4
  %31 = call i32 (ptr, ...) @printf(ptr @20, i32 %30)
  br label %for.inc43

for.inc43:                                        ; preds = %for.body42
  %32 = load i32, ptr %l, align 4
  %for.step47 = add i32 %32, -1
  store i32 %for.step47, ptr %l, align 4
  br label %for.cond41

for.end44:                                        ; preds = %for.cond41
  br label %continue48

continue48:                                       ; preds = %for.end44
  %33 = load i32, ptr %a, align 4
  switch i32 %33, label %switch.default [
    i32 1, label %switch.case
    i32 2, label %switch.case49
  ]

switch.default:                                   ; preds = %continue48
  %34 = call i32 (ptr, ...) @printf(ptr @25, ptr @26)
  br label %switch.end

switch.end:                                       ; preds = %switch.default, %switch.case49, %switch.case
  %m = alloca i32, align 4
  store i32 0, ptr %m, align 4
  br label %for.cond50

switch.case:                                      ; preds = %continue48
  %35 = call i32 (ptr, ...) @printf(ptr @21, ptr @22)
  br label %switch.end

switch.case49:                                    ; preds = %continue48
  %36 = call i32 (ptr, ...) @printf(ptr @23, ptr @24)
  br label %switch.end

for.cond50:                                       ; preds = %for.inc52, %switch.end
  %for.load54 = load i32, ptr %m, align 4
  %for.exit55 = icmp sge i32 %for.load54, 10
  br i1 %for.exit55, label %for.end53, label %for.body51

for.body51:                                       ; preds = %for.cond50
  %37 = load i32, ptr %m, align 4
  %eq = icmp eq i32 %37, 5
  %eq_ext = zext i1 %eq to i32
  %ifcond57 = icmp ne i32 %eq_ext, 0
  br i1 %ifcond57, label %then56, label %else58

for.inc52:                                        ; preds = %merge60
  %38 = load i32, ptr %m, align 4
  %for.step61 = add i32 %38, 1
  store i32 %for.step61, ptr %m, align 4
  br label %for.cond50

for.end53:                                        ; preds = %then56, %for.cond50
  br label %continue62

then56:                                           ; preds = %for.body51
  br label %for.end53

after.break:                                      ; No predecessors!
  br label %merge60

else58:                                           ; preds = %for.body51
  br label %else.body59

else.body59:                                      ; preds = %else58
  br label %merge60

merge60:                                          ; preds = %else.body59, %after.break
  %39 = load i32, ptr %m, align 4
  %40 = call i32 (ptr, ...) @printf(ptr @27, i32 %39)
  br label %for.inc52

continue62:                                       ; preds = %for.end53
  %p = alloca %Person, align 8
  %fieldptr = getelementptr inbounds %Person, ptr %p, i32 0, i32 0
  store i32 0, ptr %fieldptr, align 4
  %fieldptr63 = getelementptr inbounds %Person, ptr %p, i32 0, i32 1
  store i8 0, ptr %fieldptr63, align 1
  %fieldptr64 = getelementptr inbounds %Person, ptr %p, i32 0, i32 0
  store i32 10, ptr %fieldptr64, align 4
  %fieldptr65 = getelementptr inbounds %Person, ptr %p, i32 0, i32 1
  store i8 104, ptr %fieldptr65, align 1
  %fieldptr66 = getelementptr inbounds %Person, ptr %p, i32 0, i32 0
  %fieldload = load i32, ptr %fieldptr66, align 4
  %41 = call i32 (ptr, ...) @printf(ptr @28, i32 %fieldload)
  %fieldptr67 = getelementptr inbounds %Person, ptr %p, i32 0, i32 1
  %fieldload68 = load i8, ptr %fieldptr67, align 1
  %42 = call i32 (ptr, ...) @printf(ptr @29, i8 %fieldload68)
  %43 = call i32 (ptr, ...) @printf(ptr @30, ptr @31)
  ret void
}

declare i32 @printf(ptr, ...)
