	.data
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-20
	sw	ra,0(sp)
	lw	ra,0(sp)
	jr	ra
	.global	main
	.type	main, @function
main:
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,10
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,2
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	lw	t3,12(sp)
	mul	t3,t4,t5
	sw	t3,12(sp)
	lw	t4,12(sp)
	lw	t3,16(sp)
	addi	t3,t4,1
	sw	t3,16(sp)
	lw	a0,16(sp)
	lw	ra,0(sp)
	addi	sp,sp,20
	jr	ra
