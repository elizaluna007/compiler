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
FACT:
	.word	3338725376
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
t12:
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
	la	a0,FLOAT0
	flw	ft4,0(a0)
	fcvt.w.s	a0,ft4
	sw	a0,44(sp)
	la	a0,FLOAT1
	flw	ft4,0(a0)
	fcvt.w.s	a0,ft4
	sw	a0,48(sp)
	la	t4,TWO
	lw	t4,0(t4)
	la	t5,THREE
	lw	t5,0(t5)
	lw	t3,52(sp)
	add	t3,t4,t5
	la	t4,t12
	sw	t3,0(t4)
	la	t3,t12
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
	fsw	ft0,4(sp)
	li	t4,0
	fcvt.s.w	fa0,t4
	fsw	fa0,8(sp)
	flw	ft4,4(sp)
	flw	ft5,8(sp)
	flt.s	t3,ft4,ft5
	fcvt.s.w	ft3,t3
	fsw	ft3,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L0
	li	a0,1
	bne	a0,zero,.L1
.L0:
	la	a0,FLOAT2
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
	bne	a0,zero,.L1
.L1:
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
	fsw	ft0,4(sp)
	fsw	ft0,8(sp)
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
	bne	a0,zero,.L2
	li	a0,1
	bne	a0,zero,.L3
.L2:
	li	t4,1
	fcvt.s.w	fa0,t4
	fsw	fa0,24(sp)
	la	a0,FLOAT3
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
	lw	a0,44(sp)
	lw	ra,0(sp)
	addi	sp,sp,48
	jr	ra
	li	a0,1
	bne	a0,zero,
.L3:
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
	bne	a0,zero,.L4
	li	a0,1
	bne	a0,zero,.L5
.L4:
	call	error
	li	a0,1
	bne	a0,zero,.L6
.L5:
	call	ok
.L6:
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
	addi	sp,sp,8
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-76
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
	la	a0,FLOAT4
	flw	ft5,0(a0)
	fsub.s	ft3,ft4,ft5
	fsw	ft3,28(sp)
	flw	fa0,28(sp)
	fsw	fa0,32(sp)
	la	a0,HEX2
	flw	fa0,0(a0)
	call	putfloat
	li	a0,10
	call	putch
	la	a0,FACT
	flw	fa0,0(a0)
	call	putfloat
	li	a0,10
	call	putch
	la	a0,FLOAT5
	flw	fa0,0(a0)
	fsw	fa0,36(sp)
	la	a0,FLOAT6
	flw	fa0,0(a0)
	fsw	fa0,40(sp)
	flw	fa0,36(sp)
	call	putfloat
	li	a0,10
	call	putch
	flw	fa0,40(sp)
	call	putfloat
	li	a0,10
	call	putch
	la	a0,HEX2
	flw	fa0,0(a0)
	la	a0,FACT
	flw	fa1,0(a0)
	call	float_eq
	sw	a0,44(sp)
	lw	a0,44(sp)
	call	assert_not
	la	a0,EVAL1
	flw	fa0,0(a0)
	la	a0,EVAL2
	flw	fa1,0(a0)
	call	float_eq
	sw	a0,48(sp)
	lw	a0,48(sp)
	call	assert_not
	la	a0,EVAL2
	flw	fa0,0(a0)
	la	a0,EVAL3
	flw	fa1,0(a0)
	call	float_eq
	sw	a0,52(sp)
	lw	a0,52(sp)
	call	assert
	la	a0,RADIUS
	flw	ft4,0(a0)
	fcvt.w.s	a0,ft4
	sw	a0,56(sp)
	lw	a0,56(sp)
	call	circle_area
	fsw	fa0,60(sp)
	la	a0,FIVE
	lw	a0,0(a0)
	call	circle_area
	fsw	fa0,64(sp)
	flw	fa0,60(sp)
	flw	fa1,64(sp)
	call	float_eq
	sw	a0,68(sp)
	lw	a0,68(sp)
	call	assert
	la	a0,CONV1
	flw	fa0,0(a0)
	la	a0,CONV2
	flw	fa1,0(a0)
	call	float_eq
	sw	a0,72(sp)
	lw	a0,72(sp)
	call	assert_not
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,76
	jr	ra
FLOAT0:
	.word	1077516698
FLOAT1:
	.word	1078774989
FLOAT2:
	.word	0
FLOAT3:
	.word	1073741824
FLOAT4:
	.word	1036831949
FLOAT5:
	.word	1033895936
FLOAT6:
	.word	3338725376
