	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	ifWhile
	.type	ifWhile, @function
ifWhile:
	addi	sp,sp,-68
	sw	ra,0(sp)
	li	a0,0
	sw	a0,4(sp)
	li	a0,3
	sw	a0,8(sp)
	li	a0,5
	sw	a0,12(sp)
	lw	t4,4(sp)
	lw	t5,12(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,16(sp)
	lw	t4,16(sp)
	seqz	t4,t4
	sw	t4,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L2
.L0:
	nop
	li	a0,2
	sw	a0,24(sp)
	lw	t4,8(sp)
	lw	t5,24(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,28(sp)
	lw	t4,28(sp)
	seqz	t4,t4
	sw	t4,32(sp)
	lw	a0,32(sp)
	bne	a0,zero,.L1
	lw	t4,8(sp)
	addi	t3,t4,2
	sw	t3,36(sp)
	lw	t4,36(sp)
	sw	t4,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L0
.L1:
	nop
	lw	t4,8(sp)
	addi	t3,t4,25
	sw	t3,40(sp)
	lw	t4,40(sp)
	sw	t4,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L5
.L2:
	nop
.L3:
	nop
	li	a0,5
	sw	a0,44(sp)
	lw	t4,4(sp)
	lw	t5,44(sp)
	slt	t3,t4,t5
	sw	t3,48(sp)
	lw	t4,48(sp)
	seqz	t4,t4
	sw	t4,52(sp)
	lw	a0,52(sp)
	bne	a0,zero,.L4
	li	a0,2
	sw	a0,56(sp)
	lw	t4,8(sp)
	lw	t5,56(sp)
	mul	t3,t4,t5
	sw	t3,60(sp)
	lw	t4,60(sp)
	sw	t4,8(sp)
	lw	t4,4(sp)
	addi	t3,t4,1
	sw	t3,64(sp)
	lw	t4,64(sp)
	sw	t4,4(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L3
.L4:
	nop
.L5:
	nop
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,68
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
