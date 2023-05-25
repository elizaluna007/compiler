	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.comm	a,4,4
	.comm	b,4,4
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,0(sp)
	call	global
	li	a0,4
	la	a1,a
	sw	a0,0(a1)
	li	a0,4
	la	a1,b
	sw	a0,0(a1)
	la	a0,a
	lw	t4,0(a0)
	la	a0,b
	lw	t5,0(a0)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,4(sp)
	lw	t4,4(sp)
	sw	t4,8(sp)
	lw	t4,8(sp)
	seqz	t4,t4
	sw	t4,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L0
	li	a0,3
	sw	a0,16(sp)
	la	a0,a
	lw	t4,0(a0)
	lw	t5,16(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,20(sp)
	lw	t4,8(sp)
	snez	t4,t4
	lw	t5,20(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,8(sp)
.L0:
	nop
	lw	t4,8(sp)
	seqz	t4,t4
	sw	t4,24(sp)
	lw	a0,24(sp)
	bne	a0,zero,.L1
	li	a0,1
	sw	a0,28(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L2
.L1:
	nop
	li	a0,0
	sw	a0,28(sp)
.L2:
	nop
	lw	a0,28(sp)
	lw	ra,0(sp)
	addi	sp,sp,32
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
