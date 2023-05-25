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
	addi	sp,sp,-28
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	la	a0,t1
	lw	a0,0(a0)
	lw	t3,8(sp)
	li	t3,1
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,2
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,4
	sw	t3,16(sp)
	lw	t3,20(sp)
	li	t3,99
	sw	t3,20(sp)
	lw	t3,24(sp)
	li	t3,99
	sw	t3,24(sp)
	lw	ra,0(sp)
	addi	sp,sp,28
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-12
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	la	a0,sum
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
