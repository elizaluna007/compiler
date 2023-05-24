	.text
	.comm	e,4,4
	.comm	f,4,4
	.comm	g,4,4
	.comm	h,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	EightWhile
	.type	EightWhile, @function
EightWhile:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,t30
	lw	a0,0(a0)
	addi	sp,sp,4
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
	addi	sp,sp,4
	jr	ra
