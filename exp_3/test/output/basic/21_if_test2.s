	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	ifElseIf
	.type	ifElseIf, @function
ifElseIf:
	addi	sp,sp,-40
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,6
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,0
	sw	t3,16(sp)
	la	a0,a
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	lw	t3,20(sp)
	li	t3,10
	sw	t3,20(sp)
	lw	t3,24(sp)
	li	t3,1
	sw	t3,24(sp)
	lw	t3,28(sp)
	li	t3,10
	sw	t3,28(sp)
	lw	t3,32(sp)
	li	t3,0
	sw	t3,32(sp)
	lw	t3,36(sp)
	li	t3,0
	sw	t3,36(sp)
	la	a0,a
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,40
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	ifElseIf
	call	putint
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
