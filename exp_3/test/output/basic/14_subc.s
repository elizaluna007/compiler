	.data
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
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,4(sp)
	li	t3,10
	sw	t3,4(sp)
	lw	t4,4(sp)
	lw	t3,8(sp)
	addi	t3,t4,-2
	sw	t3,8(sp)
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
