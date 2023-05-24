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
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	float_abs
	.type	float_abs, @function
float_abs:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,0
	jr	ra
	addi	sp,sp,4
	jr	ra
	.global	circle_area
	.type	circle_area, @function
circle_area:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	float_eq
	.type	float_eq, @function
float_eq:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	float_abs
	la	a0,t37
	lw	a0,0(a0)
	addi	sp,sp,0
	jr	ra
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
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
	addi	sp,sp,4
	jr	ra
	.global	assert
	.type	assert, @function
assert:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	error
	call	ok
	addi	sp,sp,4
	jr	ra
	.global	assert_not
	.type	assert_not, @function
assert_not:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	error
	call	ok
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
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
	call	error
	call	ok
	call	getfarray
	call	getfloat
	call	circle_area
	call	putfloat
	call	putch
	call	putint
	call	putch
	call	putfarray
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
