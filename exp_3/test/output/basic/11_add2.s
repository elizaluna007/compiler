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
	addi	sp,sp,-36
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t4,4(sp)
	lw	t3,12(sp)
	addi	t3,t4,1
	sw	t3,12(sp)
	lw	t3,12(sp)
	sw	t3,4(sp)
	lw	t4,4(sp)
	lw	t3,16(sp)
	addi	t3,t4,2
	sw	t3,16(sp)
	lw	t3,16(sp)
	sw	t3,4(sp)
	lw	t4,4(sp)
	lw	t3,20(sp)
	addi	t3,t4,1
	sw	t3,20(sp)
	lw	t3,20(sp)
	sw	t3,4(sp)
	lw	t4,4(sp)
	lw	t3,24(sp)
	addi	t3,t4,-3
	sw	t3,24(sp)
	lw	t3,24(sp)
	sw	t3,4(sp)
	lw	t4,4(sp)
	lw	t3,28(sp)
	addi	t3,t4,2
	sw	t3,28(sp)
	lw	t3,28(sp)
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,2
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	lw	t3,32(sp)
	div	t3,t4,t5
	sw	t3,32(sp)
	lw	a0,32(sp)
	lw	ra,0(sp)
	addi	sp,sp,36
	jr	ra
