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
	.global	ifWhile
	.type	ifWhile, @function
ifWhile:
	addi	sp,sp,-52
	sw	ra,0(sp)
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
	li	t3,3
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,5
	sw	t3,12(sp)
	lw	t4,4(sp)
	lw	t5,12(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,16(sp)
	lw	a0,16(sp)
	bne	a0,zero,.L0
	li	a0,1
	bne	a0,zero,.L3
.L0:
	lw	t3,20(sp)
	li	t3,2
	sw	t3,20(sp)
	lw	t4,8(sp)
	lw	t5,20(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,24(sp)
	lw	a0,24(sp)
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L2
.L1:
	lw	t4,8(sp)
	lw	t3,28(sp)
	addi	t3,t4,2
	sw	t3,28(sp)
	lw	t3,28(sp)
	sw	t3,8(sp)
	li	a0,1
	bne	a0,zero,.L0
.L2:
	lw	t4,8(sp)
	lw	t3,32(sp)
	addi	t3,t4,25
	sw	t3,32(sp)
	lw	t3,32(sp)
	sw	t3,8(sp)
	li	a0,1
	bne	a0,zero,.L5
.L3:
	lw	t4,4(sp)
	li	t5,5
	slt	t3,t4,t5
	sw	t3,36(sp)
	lw	a0,36(sp)
	bne	a0,zero,.L4
	li	a0,1
	bne	a0,zero,.L5
.L4:
	lw	t3,40(sp)
	li	t3,2
	sw	t3,40(sp)
	lw	t4,8(sp)
	lw	t5,40(sp)
	lw	t3,44(sp)
	mul	t3,t4,t5
	sw	t3,44(sp)
	lw	t3,44(sp)
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t3,48(sp)
	addi	t3,t4,1
	sw	t3,48(sp)
	lw	t3,48(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L3
.L5:
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,52
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	ifWhile
	sw	a0,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
