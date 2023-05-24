	.text
	.comm	array,440,4
	.comm	n,4,4
	.comm	t1,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	init
	.type	init, @function
init:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	findfa
	.type	findfa, @function
findfa:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,a
	lw	a0,0(a0)
	addi	sp,sp,0
	jr	ra
	call	findfa
	la	a0,t123
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	mmerge
	.type	mmerge, @function
mmerge:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	findfa
	call	findfa
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	init
	call	getint
	call	getint
	call	mmerge
	call	mmerge
	call	mmerge
	call	mmerge
	call	mmerge
	call	mmerge
	call	findfa
	call	findfa
	call	putint
	call	putch
	call	putint
	call	putch
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
