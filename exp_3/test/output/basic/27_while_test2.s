	.text
	.global	global
	.type	global, @function
global:
	jr	ra
	.global	FourWhile
	.type	FourWhile, @function
FourWhile:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,t14
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	FourWhile
	la	a0,t15
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
