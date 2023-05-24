	.text
	.global	global
	.type	global, @function
global:
	jr	ra
	.global	deepWhileBr
	.type	deepWhileBr, @function
deepWhileBr:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,c
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	deepWhileBr
	la	a0,t12
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
