	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	ifElseIf
	.type	ifElseIf, @function
ifElseIf:
	addi	sp,sp,-104
	sw	ra,0(sp)
	li	a0,5
	sw	a0,4(sp)
	li	a0,10
	sw	a0,8(sp)
	li	a0,6
	sw	a0,12(sp)
	lw	t4,4(sp)
	lw	t5,12(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,16(sp)
	lw	t4,16(sp)
	sw	t4,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L0
	li	a0,11
	sw	a0,24(sp)
	lw	t4,8(sp)
	lw	t5,24(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,28(sp)
	lw	t4,20(sp)
	snez	t4,t4
	lw	t5,28(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,20(sp)
.L0:
	nop
	lw	t4,20(sp)
	seqz	t4,t4
	sw	t4,32(sp)
	lw	a0,32(sp)
	bne	a0,zero,.L1
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,104
	jr	ra
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L8
.L1:
	nop
	li	a0,10
	sw	a0,36(sp)
	lw	t4,8(sp)
	lw	t5,36(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,40(sp)
	lw	t4,40(sp)
	sw	t4,44(sp)
	lw	t4,44(sp)
	seqz	t4,t4
	sw	t4,48(sp)
	lw	a0,48(sp)
	bne	a0,zero,.L2
	li	a0,1
	sw	a0,52(sp)
	lw	t4,4(sp)
	lw	t5,52(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,56(sp)
	lw	t4,44(sp)
	snez	t4,t4
	lw	t5,56(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,44(sp)
.L2:
	nop
	lw	t4,44(sp)
	seqz	t4,t4
	sw	t4,60(sp)
	lw	a0,60(sp)
	bne	a0,zero,.L3
	li	a0,25
	sw	a0,4(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L7
.L3:
	nop
	li	a0,10
	sw	a0,64(sp)
	lw	t4,8(sp)
	lw	t5,64(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,68(sp)
	lw	t4,68(sp)
	sw	t4,72(sp)
	lw	t4,72(sp)
	seqz	t4,t4
	sw	t4,76(sp)
	lw	a0,76(sp)
	bne	a0,zero,.L4
	li	a0,-5
	sw	a0,80(sp)
	lw	t4,4(sp)
	lw	t5,80(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,84(sp)
	lw	t4,72(sp)
	snez	t4,t4
	lw	t5,84(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,72(sp)
.L4:
	nop
	lw	t4,72(sp)
	seqz	t4,t4
	sw	t4,88(sp)
	lw	a0,88(sp)
	bne	a0,zero,.L5
	lw	t4,4(sp)
	addi	t3,t4,15
	sw	t3,92(sp)
	lw	t4,92(sp)
	sw	t4,4(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L6
.L5:
	nop
	li	a0,0
	sw	a0,96(sp)
	lw	t4,96(sp)
	lw	t5,4(sp)
	sub	t3,t4,t5
	sw	t3,100(sp)
	lw	t4,100(sp)
	sw	t4,4(sp)
.L6:
	nop
.L7:
	nop
.L8:
	nop
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,104
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-12
	sw	ra,0(sp)
	call	global
	call	ifElseIf
	sw	a0,4(sp)
	lw	a0,4(sp)
	call	putint
	li	a0,0
	sw	a0,8(sp)
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	li	a0,0
	la	a1,zero
	sw	a0,0(a1)
	la	a0,FLOAT0
	flw	fa0,0(a0)
	la	a1,fzero
	fsw	fa0,0(a1)
	li	a0,1
	la	a1,one
	sw	a0,0(a1)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
FLOAT0:
	.word	0
