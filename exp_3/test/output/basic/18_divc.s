	.data
a:
	.word	10
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-8
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,10
	sw	t3,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,5
	sw	t3,4(sp)
	la	a0,t1
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
