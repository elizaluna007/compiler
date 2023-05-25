	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.comm	a,4,4
	.comm	b,4,4
	.global	inc_a
	.type	inc_a, @function
inc_a:
	addi	sp,sp,-12
	sw	ra,0(sp)
	la	a0,a
	lw	t4,0(a0)
	sw	t4,4(sp)
	lw	t4,4(sp)
	addi	t3,t4,1
	sw	t3,8(sp)
	lw	t4,8(sp)
	sw	t4,4(sp)
	lw	t4,4(sp)
	la	a1,a
	sw	t4,0(a1)
	la	a0,a
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-136
	sw	ra,0(sp)
	call	global
	li	a0,5
	sw	a0,4(sp)
.L0:
	nop
	li	a0,0
	sw	a0,8(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,12(sp)
	lw	t4,12(sp)
	seqz	t4,t4
	sw	t4,16(sp)
	lw	a0,16(sp)
	bne	a0,zero,.L8
	call	inc_a
	sw	a0,20(sp)
	lw	t4,20(sp)
	sw	t4,24(sp)
	lw	t4,24(sp)
	seqz	t4,t4
	sw	t4,28(sp)
	lw	a0,28(sp)
	bne	a0,zero,.L2
	call	inc_a
	sw	a0,32(sp)
	lw	t4,32(sp)
	sw	t4,36(sp)
	lw	t4,36(sp)
	seqz	t4,t4
	sw	t4,40(sp)
	lw	a0,40(sp)
	bne	a0,zero,.L1
	call	inc_a
	sw	a0,44(sp)
	lw	t4,36(sp)
	snez	t4,t4
	lw	t5,44(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,36(sp)
.L1:
	nop
	lw	t4,24(sp)
	snez	t4,t4
	lw	t5,36(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,24(sp)
.L2:
	nop
	lw	t4,24(sp)
	seqz	t4,t4
	sw	t4,48(sp)
	lw	a0,48(sp)
	bne	a0,zero,.L3
	la	a0,a
	lw	a0,0(a0)
	call	putint
	li	a0,32
	sw	a0,52(sp)
	lw	a0,52(sp)
	call	putch
	la	a0,b
	lw	a0,0(a0)
	call	putint
	li	a0,10
	sw	a0,56(sp)
	lw	a0,56(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L3
.L3:
	nop
	call	inc_a
	sw	a0,60(sp)
	li	a0,14
	sw	a0,64(sp)
	lw	t4,60(sp)
	lw	t5,64(sp)
	slt	t3,t4,t5
	sw	t3,68(sp)
	lw	t4,68(sp)
	sw	t4,72(sp)
	lw	a0,72(sp)
	bne	a0,zero,.L5
	call	inc_a
	sw	a0,76(sp)
	lw	t4,76(sp)
	sw	t4,80(sp)
	lw	t4,80(sp)
	seqz	t4,t4
	sw	t4,84(sp)
	lw	a0,84(sp)
	bne	a0,zero,.L4
	call	inc_a
	sw	a0,88(sp)
	call	inc_a
	sw	a0,92(sp)
	lw	t4,88(sp)
	lw	t5,92(sp)
	sub	t3,t4,t5
	sw	t3,96(sp)
	lw	t4,96(sp)
	addi	t3,t4,1
	sw	t3,100(sp)
	lw	t4,80(sp)
	snez	t4,t4
	lw	t5,100(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,80(sp)
.L4:
	nop
	lw	t4,72(sp)
	snez	t4,t4
	lw	t5,80(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,72(sp)
.L5:
	nop
	lw	t4,72(sp)
	seqz	t4,t4
	sw	t4,104(sp)
	lw	a0,104(sp)
	bne	a0,zero,.L6
	la	a0,a
	lw	a0,0(a0)
	call	putint
	li	a0,10
	sw	a0,108(sp)
	lw	a0,108(sp)
	call	putch
	li	a0,2
	sw	a0,112(sp)
	la	a0,b
	lw	t4,0(a0)
	lw	t5,112(sp)
	mul	t3,t4,t5
	sw	t3,116(sp)
	lw	t4,116(sp)
	la	a1,b
	sw	t4,0(a1)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L7
.L6:
	nop
	call	inc_a
	sw	a0,120(sp)
.L7:
	nop
	lw	t4,4(sp)
	addi	t3,t4,-1
	sw	t3,124(sp)
	lw	t4,124(sp)
	sw	t4,4(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L0
.L8:
	nop
	la	a0,a
	lw	a0,0(a0)
	call	putint
	li	a0,32
	sw	a0,128(sp)
	lw	a0,128(sp)
	call	putch
	la	a0,b
	lw	a0,0(a0)
	call	putint
	li	a0,10
	sw	a0,132(sp)
	lw	a0,132(sp)
	call	putch
	la	a0,a
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,136
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
	li	a0,-1
	la	a1,a
	sw	a0,0(a1)
	li	a0,1
	la	a1,b
	sw	a0,0(a1)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
FLOAT0:
	.word	0
