	.data
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-40
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
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,4(sp)
	li	t3,10
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,30
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	lw	t4,12(sp)
	lw	t3,16(sp)
	addi	t3,t4,-5
	sw	t3,16(sp)
	lw	t4,4(sp)
	lw	t5,16(sp)
	lw	t3,20(sp)
	sub	t3,t4,t5
	sw	t3,20(sp)
	lw	t4,20(sp)
	lw	t5,8(sp)
	lw	t3,24(sp)
	add	t3,t4,t5
	sw	t3,24(sp)
	lw	t3,28(sp)
	li	t3,0
	sw	t3,28(sp)
	lw	t4,28(sp)
	lw	t3,32(sp)
	addi	t3,t4,-5
	sw	t3,32(sp)
	lw	t4,24(sp)
	lw	t5,32(sp)
	lw	t3,36(sp)
	add	t3,t4,t5
	sw	t3,36(sp)
	lw	a0,36(sp)
	lw	ra,0(sp)
	addi	sp,sp,40
	jr	ra
