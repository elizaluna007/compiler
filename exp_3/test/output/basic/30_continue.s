	.text
	.global	global
	.type	global, @function
global:
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	la	a0,sum
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
