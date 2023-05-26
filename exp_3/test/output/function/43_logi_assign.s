	.data
a:
	.word	0
b:
	.word	0
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-12
	sw	ra,0(sp)
	lw	ra,0(sp)
	jr	ra
	.global	main
	.type	main, @function
main:
	sw	ra,0(sp)
	call	global
	li	t4,4
	la	t3,a
	sw	t4,0(t3)
	li	t4,4
	la	t3,b
	sw	t4,0(t3)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,3
	sw	t3,8(sp)
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
