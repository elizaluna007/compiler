	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-168
	sw	ra,0(sp)
	call	global
	li	a0,5
	sw	a0,4(sp)
	li	a0,5
	sw	a0,8(sp)
	li	a0,1
	sw	a0,12(sp)
	li	a0,-2
	sw	a0,16(sp)
	li	a0,2
	sw	a0,20(sp)
	li	a0,1
	sw	a0,24(sp)
	lw	t4,16(sp)
	lw	t5,24(sp)
	mul	t3,t4,t5
	sw	t3,28(sp)
	li	a0,2
	sw	a0,32(sp)
	lw	t4,28(sp)
	lw	t5,32(sp)
	div	t3,t4,t5
	sw	t3,36(sp)
	li	a0,0
	sw	a0,40(sp)
	lw	t4,36(sp)
	lw	t5,40(sp)
	slt	t3,t4,t5
	sw	t3,44(sp)
	lw	t4,44(sp)
	sw	t4,48(sp)
	lw	a0,48(sp)
	bne	a0,zero,.L1
	lw	t4,4(sp)
	lw	t5,8(sp)
	sub	t3,t4,t5
	sw	t3,52(sp)
	li	a0,0
	sw	a0,56(sp)
	lw	t4,52(sp)
	lw	t5,56(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,60(sp)
	lw	t4,60(sp)
	sw	t4,64(sp)
	lw	t4,64(sp)
	seqz	t4,t4
	sw	t4,68(sp)
	lw	a0,68(sp)
	bne	a0,zero,.L0
	lw	t4,12(sp)
	addi	t3,t4,3
	sw	t3,72(sp)
	li	a0,2
	sw	a0,76(sp)
	lw	t4,72(sp)
	lw	t5,76(sp)
	rem	t3,t4,t5
	sw	t3,80(sp)
	li	a0,0
	sw	a0,84(sp)
	lw	t4,80(sp)
	lw	t5,84(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,88(sp)
	lw	t4,64(sp)
	snez	t4,t4
	lw	t5,88(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,64(sp)
.L0:
	nop
	lw	t4,48(sp)
	snez	t4,t4
	lw	t5,64(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,48(sp)
.L1:
	nop
	lw	t4,48(sp)
	seqz	t4,t4
	sw	t4,92(sp)
	lw	a0,92(sp)
	bne	a0,zero,.L2
	lw	a0,20(sp)
	call	putint
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L2
.L2:
	nop
	li	a0,2
	sw	a0,96(sp)
	lw	t4,16(sp)
	lw	t5,96(sp)
	rem	t3,t4,t5
	sw	t3,100(sp)
	lw	t4,100(sp)
	addi	t3,t4,67
	sw	t3,104(sp)
	li	a0,0
	sw	a0,108(sp)
	lw	t4,104(sp)
	lw	t5,108(sp)
	slt	t3,t4,t5
	sw	t3,112(sp)
	lw	t4,112(sp)
	sw	t4,116(sp)
	lw	a0,116(sp)
	bne	a0,zero,.L4
	lw	t4,4(sp)
	lw	t5,8(sp)
	sub	t3,t4,t5
	sw	t3,120(sp)
	li	a0,0
	sw	a0,124(sp)
	lw	t4,120(sp)
	lw	t5,124(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,128(sp)
	lw	t4,128(sp)
	sw	t4,132(sp)
	lw	t4,132(sp)
	seqz	t4,t4
	sw	t4,136(sp)
	lw	a0,136(sp)
	bne	a0,zero,.L3
	lw	t4,12(sp)
	addi	t3,t4,2
	sw	t3,140(sp)
	li	a0,2
	sw	a0,144(sp)
	lw	t4,140(sp)
	lw	t5,144(sp)
	rem	t3,t4,t5
	sw	t3,148(sp)
	li	a0,0
	sw	a0,152(sp)
	lw	t4,148(sp)
	lw	t5,152(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,156(sp)
	lw	t4,132(sp)
	snez	t4,t4
	lw	t5,156(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,132(sp)
.L3:
	nop
	lw	t4,116(sp)
	snez	t4,t4
	lw	t5,132(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,116(sp)
.L4:
	nop
	lw	t4,116(sp)
	seqz	t4,t4
	sw	t4,160(sp)
	lw	a0,160(sp)
	bne	a0,zero,.L5
	li	a0,4
	sw	a0,20(sp)
	lw	a0,20(sp)
	call	putint
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L5
.L5:
	nop
	li	a0,0
	sw	a0,164(sp)
	lw	a0,164(sp)
	lw	ra,0(sp)
	addi	sp,sp,168
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
