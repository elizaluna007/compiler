	.text
	.comm	a,4,4
	.comm	b,4,4
	.comm	c,4,4
	.comm	d,4,4
	.comm	e,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-24
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,1
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,2
	sw	t3,16(sp)
	lw	t3,20(sp)
	li	t3,4
	sw	t3,20(sp)
	lw	ra,0(sp)
	addi	sp,sp,24
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	la	a0,flag
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
