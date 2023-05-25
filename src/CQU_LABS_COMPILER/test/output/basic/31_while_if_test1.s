	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	whileIf
	.type	whileIf, @function
whileIf:
	addi	sp,sp,-60
	sw	ra,0(sp)
	li	a0,0
	sw	a0,4(sp)
	li	a0,0
	sw	a0,8(sp)
.L0:
	nop
	li	a0,100
	sw	a0,12(sp)
	lw	t4,4(sp)
	lw	t5,12(sp)
	slt	t3,t4,t5
	sw	t3,16(sp)
	lw	t4,16(sp)
	seqz	t4,t4
	sw	t4,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L5
	li	a0,5
	sw	a0,24(sp)
	lw	t4,4(sp)
	lw	t5,24(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,28(sp)
	lw	t4,28(sp)
	seqz	t4,t4
	sw	t4,32(sp)
	lw	a0,32(sp)
	bne	a0,zero,.L1
	li	a0,25
	sw	a0,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L4
.L1:
	nop
	li	a0,10
	sw	a0,36(sp)
	lw	t4,4(sp)
	lw	t5,36(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,40(sp)
	lw	t4,40(sp)
	seqz	t4,t4
	sw	t4,44(sp)
	lw	a0,44(sp)
	bne	a0,zero,.L2
	li	a0,42
	sw	a0,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L3
.L2:
	nop
	li	a0,2
	sw	a0,48(sp)
	lw	t4,4(sp)
	lw	t5,48(sp)
	mul	t3,t4,t5
	sw	t3,52(sp)
	lw	t4,52(sp)
	sw	t4,8(sp)
.L3:
	nop
.L4:
	nop
	lw	t4,4(sp)
	addi	t3,t4,1
	sw	t3,56(sp)
	lw	t4,56(sp)
	sw	t4,4(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L0
.L5:
	nop
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,60
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	whileIf
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
