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
	.global	ifElseIf
	.type	ifElseIf, @function
ifElseIf:
	addi	sp,sp,-88
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,4(sp)
	li	t3,5
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,8(sp)
	li	t3,10
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,6
	sw	t3,12(sp)
	lw	t4,4(sp)
	lw	t5,12(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,16(sp)
	lw	t4,16(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L0
	lw	t3,24(sp)
	li	t3,11
	sw	t3,24(sp)
	lw	t4,8(sp)
	lw	t5,24(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,28(sp)
	lw	t4,16(sp)
	snez	t4,t4
	lw	t5,28(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,20(sp)
.L0:
	lw	a0,20(sp)
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L2
.L1:
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,88
	jr	ra
	li	a0,1
	bne	a0,zero,.L11
.L2:
	lw	t3,32(sp)
	li	t3,10
	sw	t3,32(sp)
	lw	t4,8(sp)
	lw	t5,32(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,36(sp)
	lw	t4,36(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,40(sp)
	lw	a0,40(sp)
	bne	a0,zero,.L3
	li	a0,1
	bne	a0,zero,.L4
.L3:
	lw	t3,44(sp)
	li	t3,1
	sw	t3,44(sp)
	lw	t4,4(sp)
	lw	t5,44(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,48(sp)
	lw	t4,36(sp)
	snez	t4,t4
	lw	t5,48(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,40(sp)
.L4:
	lw	a0,40(sp)
	bne	a0,zero,.L5
	li	a0,1
	bne	a0,zero,.L6
.L5:
	lw	t3,4(sp)
	li	t3,25
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L11
.L6:
	lw	t3,52(sp)
	li	t3,10
	sw	t3,52(sp)
	lw	t4,8(sp)
	lw	t5,52(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,56(sp)
	lw	t4,56(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,60(sp)
	lw	a0,60(sp)
	bne	a0,zero,.L7
	li	a0,1
	bne	a0,zero,.L8
.L7:
	lw	t3,64(sp)
	li	t3,0
	sw	t3,64(sp)
	lw	t4,64(sp)
	lw	t3,68(sp)
	addi	t3,t4,-5
	sw	t3,68(sp)
	lw	t4,4(sp)
	lw	t5,68(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,72(sp)
	lw	t4,56(sp)
	snez	t4,t4
	lw	t5,72(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,60(sp)
.L8:
	lw	a0,60(sp)
	bne	a0,zero,.L9
	li	a0,1
	bne	a0,zero,.L10
.L9:
	lw	t4,4(sp)
	lw	t3,76(sp)
	addi	t3,t4,15
	sw	t3,76(sp)
	lw	t3,76(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L11
.L10:
	lw	t3,80(sp)
	li	t3,0
	sw	t3,80(sp)
	lw	t4,80(sp)
	lw	t5,4(sp)
	lw	t3,84(sp)
	sub	t3,t4,t5
	sw	t3,84(sp)
	lw	t3,84(sp)
	sw	t3,4(sp)
.L11:
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,88
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	ifElseIf
	sw	a0,4(sp)
	lw	a0,4(sp)
	call	putint
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
