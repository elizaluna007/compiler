	.text
	.comm	e,4,4
	.comm	f,4,4
	.comm	g,4,4
	.comm	h,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-20
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,0
	sw	t3,16(sp)
	lw	ra,0(sp)
	addi	sp,sp,20
	jr	ra
	.global	EightWhile
	.type	EightWhile, @function
EightWhile:
	addi	sp,sp,-24
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,0
	sw	t3,16(sp)
	lw	t3,20(sp)
	li	t3,7
	sw	t3,20(sp)
	la	a0,t30
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,24
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	EightWhile
	la	a0,t31
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
