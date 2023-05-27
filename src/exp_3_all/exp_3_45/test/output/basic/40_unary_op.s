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
	addi	sp,sp,-52
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,4(sp)
	li	t3,10
	sw	t3,4(sp)
	lw	t4,4(sp)
	seqz	t4,t4
	sw	t4,8(sp)
	lw	t4,8(sp)
	seqz	t4,t4
	sw	t4,12(sp)
	lw	t4,12(sp)
	seqz	t4,t4
	sw	t4,16(sp)
	lw	t3,20(sp)
	li	t3,0
	sw	t3,20(sp)
	lw	t4,20(sp)
	lw	t5,16(sp)
	lw	t3,24(sp)
	sub	t3,t4,t5
	sw	t3,24(sp)
	lw	a0,24(sp)
	bne	a0,zero,.L0
	li	a0,1
	bne	a0,zero,.L1
.L0:
	lw	t3,28(sp)
	li	t3,0
	sw	t3,28(sp)
	lw	t4,28(sp)
	lw	t3,32(sp)
	addi	t3,t4,-1
	sw	t3,32(sp)
	lw	t3,36(sp)
	li	t3,0
	sw	t3,36(sp)
	lw	t4,36(sp)
	lw	t5,32(sp)
	lw	t3,40(sp)
	sub	t3,t4,t5
	sw	t3,40(sp)
	lw	t3,44(sp)
	li	t3,0
	sw	t3,44(sp)
	lw	t4,44(sp)
	lw	t5,40(sp)
	lw	t3,48(sp)
	sub	t3,t4,t5
	sw	t3,48(sp)
	lw	t3,48(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L2
.L1:
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
.L2:
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,52
	jr	ra
