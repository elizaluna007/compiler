	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	FourWhile
	.type	FourWhile, @function
FourWhile:
	addi	sp,sp,-108
	sw	ra,0(sp)
	li	a0,5
	sw	a0,4(sp)
	li	a0,6
	sw	a0,8(sp)
	li	a0,7
	sw	a0,12(sp)
	li	a0,10
	sw	a0,16(sp)
.L0:
	nop
	li	a0,20
	sw	a0,20(sp)
	lw	t4,4(sp)
	lw	t5,20(sp)
	slt	t3,t4,t5
	sw	t3,24(sp)
	lw	t4,24(sp)
	seqz	t4,t4
	sw	t4,28(sp)
	lw	a0,28(sp)
	bne	a0,zero,.L7
	lw	t4,4(sp)
	addi	t3,t4,3
	sw	t3,32(sp)
	lw	t4,32(sp)
	sw	t4,4(sp)
.L1:
	nop
	li	a0,10
	sw	a0,36(sp)
	lw	t4,8(sp)
	lw	t5,36(sp)
	slt	t3,t4,t5
	sw	t3,40(sp)
	lw	t4,40(sp)
	seqz	t4,t4
	sw	t4,44(sp)
	lw	a0,44(sp)
	bne	a0,zero,.L6
	lw	t4,8(sp)
	addi	t3,t4,1
	sw	t3,48(sp)
	lw	t4,48(sp)
	sw	t4,8(sp)
.L2:
	nop
	li	a0,7
	sw	a0,52(sp)
	lw	t4,12(sp)
	lw	t5,52(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,56(sp)
	lw	t4,56(sp)
	seqz	t4,t4
	sw	t4,60(sp)
	lw	a0,60(sp)
	bne	a0,zero,.L5
	lw	t4,12(sp)
	addi	t3,t4,-1
	sw	t3,64(sp)
	lw	t4,64(sp)
	sw	t4,12(sp)
.L3:
	nop
	li	a0,20
	sw	a0,68(sp)
	lw	t4,16(sp)
	lw	t5,68(sp)
	slt	t3,t4,t5
	sw	t3,72(sp)
	lw	t4,72(sp)
	seqz	t4,t4
	sw	t4,76(sp)
	lw	a0,76(sp)
	bne	a0,zero,.L4
	lw	t4,16(sp)
	addi	t3,t4,3
	sw	t3,80(sp)
	lw	t4,80(sp)
	sw	t4,16(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L3
.L4:
	nop
	lw	t4,16(sp)
	addi	t3,t4,-1
	sw	t3,84(sp)
	lw	t4,84(sp)
	sw	t4,16(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L2
.L5:
	nop
	lw	t4,12(sp)
	addi	t3,t4,1
	sw	t3,88(sp)
	lw	t4,88(sp)
	sw	t4,12(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L1
.L6:
	nop
	lw	t4,8(sp)
	addi	t3,t4,-2
	sw	t3,92(sp)
	lw	t4,92(sp)
	sw	t4,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L0
.L7:
	nop
	lw	t4,8(sp)
	lw	t5,16(sp)
	add	t3,t4,t5
	sw	t3,96(sp)
	lw	t4,4(sp)
	lw	t5,96(sp)
	add	t3,t4,t5
	sw	t3,100(sp)
	lw	t4,100(sp)
	lw	t5,12(sp)
	add	t3,t4,t5
	sw	t3,104(sp)
	lw	a0,104(sp)
	lw	ra,0(sp)
	addi	sp,sp,108
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	FourWhile
	sw	a0,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
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
