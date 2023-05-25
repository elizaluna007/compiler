	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	ifWhile
	.type	ifWhile, @function
ifWhile:
	addi	sp,sp,-24
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,5
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,2
	sw	t3,16(sp)
	lw	t3,20(sp)
	li	t3,2
	sw	t3,20(sp)
	la	a0,b
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
	call	ifWhile
	la	a0,t10
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
