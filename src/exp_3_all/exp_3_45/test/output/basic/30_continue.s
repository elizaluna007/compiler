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
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
.L0:
	lw	t4,4(sp)
	li	t5,100
	slt	t3,t4,t5
	sw	t3,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L4
.L1:
	lw	t3,16(sp)
	li	t3,50
	sw	t3,16(sp)
	lw	t4,4(sp)
	lw	t5,16(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L2
	li	a0,1
	bne	a0,zero,.L3
.L2:
	lw	t4,4(sp)
	lw	t3,24(sp)
	addi	t3,t4,1
	sw	t3,24(sp)
	lw	t3,24(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L3
.L3:
	lw	t4,8(sp)
	lw	t5,4(sp)
	lw	t3,28(sp)
	add	t3,t4,t5
	sw	t3,28(sp)
	lw	t3,28(sp)
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t3,32(sp)
	addi	t3,t4,1
	sw	t3,32(sp)
	lw	t3,32(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L0
.L4:
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,36
	jr	ra
