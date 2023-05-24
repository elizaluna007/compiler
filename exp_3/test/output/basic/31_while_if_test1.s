	.text
	.global	global
	.type	global, @function
global:
	jr	ra
	.global	whileIf
	.type	whileIf, @function
whileIf:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,b
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	whileIf
	la	a0,t8
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
