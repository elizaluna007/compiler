	.data
a:
	.word	5
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-12
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,5
	sw	t3,4(sp)
	la	t4,a
	lw	t4,0(t4)
	lw	t5,4(sp)
	lw	t3,8(sp)
	mul	t3,t4,t5
	sw	t3,8(sp)
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
