	.text
	.comm	N,4,4
	.comm	arr,24,4
	.comm	t0,4,4
	.comm	t1,4,4
	.comm	t10,4,4
	.comm	t3,4,4
	.comm	t4,4,4
	.comm	t6,4,4
	.comm	t7,4,4
	.comm	t8,4,4
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
	la	a0,sum
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
