	.data
a:
	.word	10
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
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	lw	t4,a
	lw	t3,4(sp)
	addi	t3,t4,5
	sw	t3,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
