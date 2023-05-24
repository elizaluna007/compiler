	.text
	.global	global
	.type	global, @function
global:
	jr	ra
	.global	exgcd
	.type	exgcd, @function
exgcd:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,a
	lw	a0,0(a0)
	addi	sp,sp,0
	jr	ra
	call	exgcd
	la	a0,r
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	exgcd
	call	putint
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
