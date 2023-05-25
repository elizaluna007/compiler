	.text
	.comm	CONV1,4,4
	.comm	CONV2,4,4
	.comm	EPS,4,4
	.comm	EVAL1,4,4
	.comm	EVAL2,4,4
	.comm	EVAL3,4,4
	.comm	FACT,4,4
	.comm	FIVE,4,4
	.comm	HEX2,4,4
	.comm	MAX,4,4
	.comm	PI,4,4
	.comm	PI_HEX,4,4
	.comm	RADIUS,4,4
	.comm	THREE,4,4
	.comm	TWO,4,4
	.comm	t0,4,4
	.comm	t1,4,4
	.comm	t14,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-8
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,1000000000
	sw	t3,4(sp)
	la	a0,t12
	lw	a0,0(a0)
	la	a0,t13
	lw	a0,0(a0)
	la	a0,t14
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	float_abs
	.type	float_abs, @function
float_abs:
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	circle_area
	.type	circle_area, @function
circle_area:
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	float_eq
	.type	float_eq, @function
float_eq:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	float_abs
	la	a0,t37
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	error
	.type	error, @function
error:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	ok
	.type	ok, @function
ok:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	putch
	call	putch
	call	putch
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	assert
	.type	assert, @function
assert:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	error
	call	ok
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	assert_not
	.type	assert_not, @function
assert_not:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	error
	call	ok
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-44
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,2
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,16
	sw	t3,8(sp)
	call	float_eq
	call	assert_not
	call	float_eq
	call	assert_not
	call	float_eq
	call	assert
	call	circle_area
	call	circle_area
	call	float_eq
	call	assert
	call	float_eq
	call	assert_not
	call	ok
	call	ok
	lw	t3,12(sp)
	li	t3,3
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,0
	sw	t3,16(sp)
	call	error
	call	ok
	lw	t3,20(sp)
	li	t3,1
	sw	t3,20(sp)
	lw	t3,24(sp)
	li	t3,0
	sw	t3,24(sp)
	lw	t3,28(sp)
	li	t3,1
	sw	t3,28(sp)
	lw	t3,32(sp)
	li	t3,10
	sw	t3,32(sp)
	call	getfarray
	la	a0,t102
	lw	a0,0(a0)
	call	getfloat
	call	circle_area
	call	putfloat
	call	putch
	call	putint
	call	putch
	lw	t3,36(sp)
	li	t3,0
	sw	t3,36(sp)
	lw	t3,40(sp)
	li	t3,0
	sw	t3,40(sp)
	call	putfarray
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,44
	jr	ra
