	.data
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
	addi	sp,sp,-16
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,4(sp)
	li	t3,10
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,3
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	lw	t3,12(sp)
	rem	t3,t4,t5
	sw	t3,12(sp)
	lw	a0,12(sp)
	lw	ra,0(sp)
	addi	sp,sp,16
	jr	ra
