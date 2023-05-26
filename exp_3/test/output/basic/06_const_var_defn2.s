	.data
a:
	.word	10
b:
	.word	5
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	jr	ra
	.global	main
	.type	main, @function
main:
	sw	ra,0(sp)
	call	global
	la	a0,b
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
