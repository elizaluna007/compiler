	.text
	.comm	a,4,4
	.comm	b,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	la	a0,c
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
