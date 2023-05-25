	.text
	.comm	a,20,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-12
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,5
	sw	t3,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,4
	sw	t3,4(sp)
	la	a0,t9
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
