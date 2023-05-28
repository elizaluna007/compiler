	.data
RADIUS:
	.word	1085276160
PI:
	.word	1078530011
EPS:
	.word	897988541
PI_HEX:
	.word	1078530011
HEX2:
	.word	1033895936
t0:
	.word	0
t1:
	.word	0
FACT:
	.word	0
EVAL1:
	.word	0
EVAL2:
	.word	0
EVAL3:
	.word	0
CONV1:
	.word	0
CONV2:
	.word	0
MAX:
	.word	1000000000
TWO:
	.word	0
THREE:
	.word	0
t14:
	.word	0
FIVE:
	.word	0
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-56
	sw	ra,0(sp)
	la	a0,t0
	flw	ft4,0(a0)
	la	a0,FLOAT0
	flw	ft5,0(a0)
	fsub.s	ft3,ft4,ft5
	la	a0,t1
	fsw	ft3,0(a0)
	la	a0,t1
	flw	fa0,0(a0)
	la	a1,FACT
	fsw	fa0,0(a1)
	la	a0,PI
	flw	ft4,0(a0)
	la	a0,RADIUS
	flw	ft5,0(a0)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,4(sp)
	flw	ft4,4(sp)
	la	a0,RADIUS
	flw	ft5,0(a0)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,8(sp)
	flw	fa0,8(sp)
	la	a1,EVAL1
	fsw	fa0,0(a1)
	li	t4,2
	fcvt.s.w	fa0,t4
	fsw	fa0,12(sp)
	flw	ft4,12(sp)
	la	a0,PI_HEX
	flw	ft5,0(a0)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,16(sp)
	flw	ft4,16(sp)
	la	a0,RADIUS
	flw	ft5,0(a0)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,20(sp)
	flw	fa0,20(sp)
	la	a1,EVAL2
	fsw	fa0,0(a1)
	li	t4,2
	fcvt.s.w	fa0,t4
	fsw	fa0,24(sp)
	la	a0,PI
	flw	ft4,0(a0)
	flw	ft5,24(sp)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,28(sp)
	flw	ft4,28(sp)
	la	a0,RADIUS
	flw	ft5,0(a0)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,32(sp)
	flw	fa0,32(sp)
	la	a1,EVAL3
	fsw	fa0,0(a1)
	li	t4,233
	fcvt.s.w	fa0,t4
	fsw	fa0,36(sp)
	flw	fa0,36(sp)
	la	a1,CONV1
	fsw	fa0,0(a1)
	li	t4,4095
	fcvt.s.w	fa0,t4
	fsw	fa0,40(sp)
	flw	fa0,40(sp)
	la	a1,CONV2
	fsw	fa0,0(a1)
	la	a0,FLOAT1
	flw	ft4,0(a0)
	fcvt.w.s	a0,ft4
	sw	a0,44(sp)
	la	a1,FLOAT2
	flw	fa0,0(a1)
	fsub.s	fa0,ft4,fa0
	fcvt.w.s	a2,fa0
	beq	a2,a0,.L0
	sw	a2,44(sp)
.L0:
	la	a0,FLOAT3
	flw	ft4,0(a0)
	fcvt.w.s	a0,ft4
	sw	a0,48(sp)
	la	a1,FLOAT4
	flw	fa0,0(a1)
	fsub.s	fa0,ft4,fa0
	fcvt.w.s	a2,fa0
	beq	a2,a0,.L1
	sw	a2,48(sp)
.L1:
	la	t4,TWO
	lw	t4,0(t4)
	la	t5,THREE
	lw	t5,0(t5)
	lw	t3,52(sp)
	add	t3,t4,t5
	la	t4,t14
	sw	t3,0(t4)
	la	t3,t14
	lw	t3,0(t3)
	la	t4,FIVE
	sw	t3,0(t4)
	lw	ra,0(sp)
	addi	sp,sp,56
	jr	ra
	.global	float_abs
	.type	float_abs, @function
float_abs:
	addi	sp,sp,-24
	sw	ra,0(sp)
	fsw	fa0,4(sp)
	li	t4,0
	fcvt.s.w	fa0,t4
	fsw	fa0,8(sp)
	flw	ft4,4(sp)
	flw	ft5,8(sp)
	flt.s	t3,ft4,ft5
	fcvt.s.w	ft3,t3
	fsw	ft3,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L2
	li	a0,1
	bne	a0,zero,.L3
.L2:
	la	a0,FLOAT5
	flw	fa0,0(a0)
	fsw	fa0,16(sp)
	flw	ft4,16(sp)
	flw	ft5,4(sp)
	fsub.s	ft3,ft4,ft5
	fsw	ft3,20(sp)
	flw	fa0,20(sp)
	lw	ra,0(sp)
	addi	sp,sp,24
	jr	ra
	li	a0,1
	bne	a0,zero,.L3
.L3:
	flw	fa0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,24
	jr	ra
	.global	circle_area
	.type	circle_area, @function
circle_area:
	addi	sp,sp,-48
	sw	ra,0(sp)
	sw	a0,4(sp)
	lw	t4,4(sp)
	fcvt.s.w	fa0,t4
	fsw	fa0,8(sp)
	la	a0,PI
	flw	ft4,0(a0)
	flw	ft5,8(sp)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,12(sp)
	lw	t4,4(sp)
	fcvt.s.w	fa0,t4
	fsw	fa0,16(sp)
	flw	ft4,12(sp)
	flw	ft5,16(sp)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,20(sp)
	lw	t4,4(sp)
	lw	t5,4(sp)
	lw	t3,24(sp)
	mul	t3,t4,t5
	sw	t3,24(sp)
	lw	t4,24(sp)
	fcvt.s.w	fa0,t4
	fsw	fa0,28(sp)
	flw	ft4,28(sp)
	la	a0,PI
	flw	ft5,0(a0)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,32(sp)
	flw	ft4,20(sp)
	flw	ft5,32(sp)
	fadd.s	ft3,ft4,ft5
	fsw	ft3,36(sp)
	li	t4,2
	fcvt.s.w	fa0,t4
	fsw	fa0,40(sp)
	flw	ft4,36(sp)
	flw	ft5,40(sp)
	fdiv.s	ft3,ft4,ft5
	fsw	ft3,44(sp)
	flw	fa0,44(sp)
	lw	ra,0(sp)
	addi	sp,sp,48
	jr	ra
	.global	float_eq
	.type	float_eq, @function
float_eq:
	addi	sp,sp,-48
	sw	ra,0(sp)
	fsw	fa0,4(sp)
	fsw	fa1,8(sp)
	flw	ft4,4(sp)
	flw	ft5,8(sp)
	fsub.s	ft3,ft4,ft5
	fsw	ft3,12(sp)
	flw	fa0,12(sp)
	call	float_abs
	fsw	fa0,16(sp)
	flw	ft4,16(sp)
	la	a0,EPS
	flw	ft5,0(a0)
	flt.s	t3,ft4,ft5
	fcvt.s.w	ft3,t3
	fsw	ft3,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L5
	li	a0,1
	bne	a0,zero,.L6
.L5:
	li	t4,1
	fcvt.s.w	fa0,t4
	fsw	fa0,24(sp)
	la	a0,FLOAT6
	flw	fa0,0(a0)
	fsw	fa0,28(sp)
	flw	ft4,24(sp)
	flw	ft5,28(sp)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,32(sp)
	li	t4,2
	fcvt.s.w	fa0,t4
	fsw	fa0,36(sp)
	flw	ft4,32(sp)
	flw	ft5,36(sp)
	fdiv.s	ft3,ft4,ft5
	fsw	ft3,40(sp)
	flw	ft4,40(sp)
	fcvt.w.s	a0,ft4
	sw	a0,44(sp)
	la	a1,FLOAT7
	flw	fa0,0(a1)
	fsub.s	fa0,ft4,fa0
	fcvt.w.s	a2,fa0
	beq	a2,a0,.L4
	sw	a2,44(sp)
.L4:
	lw	a0,44(sp)
	lw	ra,0(sp)
	addi	sp,sp,48
	jr	ra
	li	a0,1
	bne	a0,zero,
.L6:
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,48
	jr	ra
	.global	error
	.type	error, @function
error:
	addi	sp,sp,-4
	sw	ra,0(sp)
	li	a0,101
	call	putch
	li	a0,114
	call	putch
	li	a0,114
	call	putch
	li	a0,111
	call	putch
	li	a0,114
	call	putch
	li	a0,10
	call	putch
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	ok
	.type	ok, @function
ok:
	addi	sp,sp,-4
	sw	ra,0(sp)
	li	a0,111
	call	putch
	li	a0,107
	call	putch
	li	a0,10
	call	putch
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	assert
	.type	assert, @function
assert:
	addi	sp,sp,-12
	sw	ra,0(sp)
	sw	a0,4(sp)
	lw	t4,4(sp)
	seqz	t4,t4
	sw	t4,8(sp)
	lw	a0,8(sp)
	bne	a0,zero,.L7
	li	a0,1
	bne	a0,zero,.L8
.L7:
	call	error
	li	a0,1
	bne	a0,zero,.L9
.L8:
	call	ok
.L9:
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	assert_not
	.type	assert_not, @function
assert_not:
	addi	sp,sp,-8
	sw	ra,0(sp)
	sw	a0,4(sp)
	lw	a0,4(sp)
	bne	a0,zero,.L10
	li	a0,1
	bne	a0,zero,.L11
.L10:
	call	error
	li	a0,1
	bne	a0,zero,.L12
.L11:
	call	ok
.L12:
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-272
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,2
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,16
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	lw	t3,12(sp)
	mul	t3,t4,t5
	sw	t3,12(sp)
	lw	t4,12(sp)
	lw	t3,16(sp)
	addi	t3,t4,32
	sw	t3,16(sp)
	lw	t4,16(sp)
	lw	t3,20(sp)
	addi	t3,t4,-64
	sw	t3,20(sp)
	lw	t4,20(sp)
	fcvt.s.w	fa0,t4
	fsw	fa0,24(sp)
	flw	ft4,24(sp)
	la	a0,FLOAT8
	flw	ft5,0(a0)
	fsub.s	ft3,ft4,ft5
	fsw	ft3,28(sp)
	flw	fa0,28(sp)
	fsw	fa0,32(sp)
	la	a0,HEX2
	flw	fa0,0(a0)
	la	a0,FACT
	flw	fa1,0(a0)
	call	float_eq
	sw	a0,36(sp)
	lw	a0,36(sp)
	call	assert_not
	la	a0,EVAL1
	flw	fa0,0(a0)
	la	a0,EVAL2
	flw	fa1,0(a0)
	call	float_eq
	sw	a0,40(sp)
	lw	a0,40(sp)
	call	assert_not
	la	a0,EVAL2
	flw	fa0,0(a0)
	la	a0,EVAL3
	flw	fa1,0(a0)
	call	float_eq
	sw	a0,44(sp)
	li	a0,1
	sw	a0,44(sp)
	lw	a0,44(sp)
	call	assert
	li	a0,1
	sw	a0,48(sp)
	la	a0,RADIUS
	flw	ft4,0(a0)
	fcvt.w.s	a0,ft4
	sw	a0,52(sp)
	la	a1,FLOAT9
	flw	fa0,0(a1)
	fsub.s	fa0,ft4,fa0
	fcvt.w.s	a2,fa0
	beq	a2,a0,.L13
	sw	a2,52(sp)
.L13:
	lw	a0,52(sp)
	call	circle_area
	fsw	fa0,56(sp)
	li	a0,1
	sw	a0,56(sp)
	la	a0,FIVE
	lw	a0,0(a0)
	call	circle_area
	fsw	fa0,60(sp)
	li	a0,1
	sw	a0,60(sp)
	flw	fa0,56(sp)
	flw	fa1,60(sp)
	call	float_eq
	sw	a0,64(sp)
	li	a0,1
	sw	a0,64(sp)
	lw	a0,64(sp)
	call	assert
	li	a0,1
	sw	a0,68(sp)
	la	a0,CONV1
	flw	fa0,0(a0)
	la	a0,CONV2
	flw	fa1,0(a0)
	call	float_eq
	sw	a0,72(sp)
	lw	a0,72(sp)
	call	assert_not
	li	a0,1
	bne	a0,zero,.L19
	li	a0,1
	bne	a0,zero,.L20
.L19:
	call	ok
	li	a0,1
	bne	a0,zero,.L20
.L20:
	la	a0,FLOAT10
	flw	ft4,0(a0)
	fcvt.w.s	a0,ft4
	sw	a0,76(sp)
	la	a1,FLOAT11
	flw	fa0,0(a1)
	fsub.s	fa0,ft4,fa0
	fcvt.w.s	a2,fa0
	beq	a2,a0,.L14
	sw	a2,76(sp)
.L14:
	lw	t4,76(sp)
	seqz	t4,t4
	sw	t4,80(sp)
	lw	t4,80(sp)
	seqz	t4,t4
	sw	t4,84(sp)
	lw	a0,84(sp)
	bne	a0,zero,.L21
	li	a0,1
	bne	a0,zero,.L22
.L21:
	call	ok
	li	a0,1
	bne	a0,zero,.L22
.L22:
	la	a0,FLOAT12
	flw	ft4,0(a0)
	la	a0,FLOAT13
	flw	ft5,0(a0)
	fsub.s	ft3,ft4,ft5
	fcvt.w.s	t3,ft3
	snez	t3,t3
	fcvt.s.w	ft3,t3
	fsw	ft3,88(sp)
	flw	ft4,88(sp)
	fcvt.w.s	a0,ft4
	sw	a0,92(sp)
	la	a1,FLOAT14
	flw	fa0,0(a1)
	fsub.s	fa0,ft4,fa0
	fcvt.w.s	a2,fa0
	beq	a2,a0,.L15
	sw	a2,92(sp)
.L15:
	lw	t4,92(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,96(sp)
	lw	a0,96(sp)
	bne	a0,zero,.L23
	li	a0,1
	bne	a0,zero,.L24
.L23:
	lw	t3,100(sp)
	li	t3,3
	sw	t3,100(sp)
	lw	t3,104(sp)
	li	t3,0
	sw	t3,104(sp)
	lw	t4,100(sp)
	lw	t5,104(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,108(sp)
	lw	t4,92(sp)
	snez	t4,t4
	lw	t5,108(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,96(sp)
.L24:
	lw	a0,96(sp)
	bne	a0,zero,.L25
	li	a0,1
	bne	a0,zero,.L26
.L25:
	call	error
	li	a0,1
	bne	a0,zero,.L26
.L26:
	li	t4,0
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,112(sp)
	lw	a0,112(sp)
	bne	a0,zero,.L27
	la	a0,FLOAT15
	flw	ft4,0(a0)
	la	a0,FLOAT16
	flw	ft5,0(a0)
	fsub.s	ft3,ft4,ft5
	fcvt.w.s	t3,ft3
	snez	t3,t3
	fcvt.s.w	ft3,t3
	fsw	ft3,116(sp)
	flw	ft4,116(sp)
	fcvt.w.s	a0,ft4
	sw	a0,120(sp)
	la	a1,FLOAT17
	flw	fa0,0(a1)
	fsub.s	fa0,ft4,fa0
	fcvt.w.s	a2,fa0
	beq	a2,a0,.L16
	sw	a2,120(sp)
.L16:
	li	t4,0
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,112(sp)
.L27:
	lw	a0,112(sp)
	bne	a0,zero,.L28
	li	a0,1
	bne	a0,zero,.L29
.L28:
	call	ok
	li	a0,1
	bne	a0,zero,.L29
.L29:
	lw	t3,124(sp)
	li	t3,1
	sw	t3,124(sp)
	lw	t3,128(sp)
	li	t3,0
	sw	t3,128(sp)
	lw	t3,132(sp)
	li	t3,1
	sw	t3,132(sp)
	lw	t3,136(sp)
	li	t3,10
	sw	t3,136(sp)
	lw	t4,132(sp)
	lw	t5,136(sp)
	lw	t3,140(sp)
	mul	t3,t4,t5
	sw	t3,140(sp)
	addi	t3,sp,148
	sw	t3,144(sp)
	li	t4,0
	li	t4,0
	la	t5,FLOAT18
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,1
	li	t4,0
	la	t5,FLOAT19
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,2
	li	t4,0
	la	t5,FLOAT20
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,3
	li	t4,0
	la	t5,FLOAT21
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,4
	li	t4,0
	la	t5,FLOAT22
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,5
	li	t4,0
	la	t5,FLOAT23
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,6
	li	t4,0
	la	t5,FLOAT24
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,7
	li	t4,0
	la	t5,FLOAT25
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,8
	li	t4,0
	la	t5,FLOAT26
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,9
	li	t4,0
	la	t5,FLOAT27
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,0
	li	t4,1
	la	t5,FLOAT28
	flw	ft3,0(t5)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	li	t4,2
	fcvt.s.w	fa0,t4
	fsw	fa0,188(sp)
	li	t4,1
	flw	ft3,188(sp)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	lw	a0,144(sp)
	call	getfarray
	sw	a0,192(sp)
	lw	t3,192(sp)
	sw	t3,196(sp)
.L30:
	lw	t4,124(sp)
	la	a0,MAX
	lw	t5,0(a0)
	slt	t3,t4,t5
	sw	t3,200(sp)
	lw	a0,200(sp)
	bne	a0,zero,.L31
	li	a0,1
	bne	a0,zero,.L32
.L31:
	call	getfloat
	fsw	fa0,204(sp)
	flw	fa0,204(sp)
	fsw	fa0,208(sp)
	la	a0,PI
	flw	ft4,0(a0)
	flw	ft5,208(sp)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,212(sp)
	flw	ft4,212(sp)
	flw	ft5,208(sp)
	fmul.s	ft3,ft4,ft5
	fsw	ft3,216(sp)
	flw	fa0,216(sp)
	fsw	fa0,220(sp)
	flw	ft4,208(sp)
	fcvt.w.s	a0,ft4
	sw	a0,224(sp)
	la	a1,FLOAT29
	flw	fa0,0(a1)
	fsub.s	fa0,ft4,fa0
	fcvt.w.s	a2,fa0
	beq	a2,a0,.L17
	sw	a2,224(sp)
.L17:
	lw	a0,224(sp)
	call	circle_area
	fsw	fa0,228(sp)
	flw	fa0,228(sp)
	fsw	fa0,232(sp)
	lw	t3,144(sp)
	lw	t4,128(sp)
	slli	t4,t4,2
	add	t4,t4,t3
	flw	ft5,0(t4)
	fsw	ft5,236(sp)
	flw	ft4,236(sp)
	flw	ft5,208(sp)
	fadd.s	ft3,ft4,ft5
	fsw	ft3,240(sp)
	lw	t4,128(sp)
	flw	ft3,240(sp)
	lw	t5,144(sp)
	slli	t4,t4,2
	add	t4,t4,t5
	fsw	ft3,0(t4)
	flw	fa0,220(sp)
	call	putfloat
	li	a0,32
	call	putch
	flw	ft4,232(sp)
	fcvt.w.s	a0,ft4
	sw	a0,244(sp)
	la	a1,FLOAT30
	flw	fa0,0(a1)
	fsub.s	fa0,ft4,fa0
	fcvt.w.s	a2,fa0
	beq	a2,a0,.L18
	sw	a2,244(sp)
.L18:
	lw	a0,244(sp)
	call	putint
	li	a0,10
	call	putch
	lw	t3,248(sp)
	li	t3,0
	sw	t3,248(sp)
	lw	t4,248(sp)
	lw	t3,252(sp)
	addi	t3,t4,-10
	sw	t3,252(sp)
	lw	t3,256(sp)
	li	t3,0
	sw	t3,256(sp)
	lw	t4,256(sp)
	lw	t5,252(sp)
	lw	t3,260(sp)
	sub	t3,t4,t5
	sw	t3,260(sp)
	lw	t4,124(sp)
	lw	t5,260(sp)
	lw	t3,264(sp)
	mul	t3,t4,t5
	sw	t3,264(sp)
	lw	t3,264(sp)
	sw	t3,124(sp)
	lw	t4,128(sp)
	lw	t3,268(sp)
	addi	t3,t4,1
	sw	t3,268(sp)
	lw	t3,268(sp)
	sw	t3,128(sp)
	li	a0,1
	bne	a0,zero,.L30
.L32:
	lw	a0,196(sp)
	lw	a1,144(sp)
	call	putfarray
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,272
	jr	ra
FLOAT0:
	.word	1191241728
FLOAT1:
	.word	1077516698
FLOAT2:
	.word	1056964608
FLOAT3:
	.word	1078774989
FLOAT4:
	.word	1056964608
FLOAT5:
	.word	0
FLOAT6:
	.word	1073741824
FLOAT7:
	.word	1056964608
FLOAT8:
	.word	1036831949
FLOAT9:
	.word	1056964608
FLOAT10:
	.word	1079194419
FLOAT11:
	.word	1056964608
FLOAT12:
	.word	0
FLOAT13:
	.word	0
FLOAT14:
	.word	1056964608
FLOAT15:
	.word	1050253722
FLOAT16:
	.word	0
FLOAT17:
	.word	1056964608
FLOAT18:
	.word	0
FLOAT19:
	.word	0
FLOAT20:
	.word	0
FLOAT21:
	.word	0
FLOAT22:
	.word	0
FLOAT23:
	.word	0
FLOAT24:
	.word	0
FLOAT25:
	.word	0
FLOAT26:
	.word	0
FLOAT27:
	.word	0
FLOAT28:
	.word	1065353216
FLOAT29:
	.word	1056964608
FLOAT30:
	.word	1056964608
