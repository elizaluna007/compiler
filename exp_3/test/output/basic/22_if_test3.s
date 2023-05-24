	.text
	.global	global
	.type	global, @function
global:
	jr	ra
	.global	ififElse
	.type	ififElse, @function
ififElse:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,a
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	ififElse
	la	a0,t5
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
