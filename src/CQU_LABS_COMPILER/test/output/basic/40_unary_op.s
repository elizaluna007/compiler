	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,0(sp)
	call	global
	li	a0,10
	sw	a0,4(sp)
	lw	t4,4(sp)
	seqz	t4,t4
	sw	t4,8(sp)
	lw	t4,8(sp)
	seqz	t4,t4
	sw	t4,12(sp)
	lw	t4,12(sp)
	seqz	t4,t4
	sw	t4,16(sp)
	li	a0,0
	sw	a0,20(sp)
	lw	t4,20(sp)
	lw	t5,16(sp)
	sub	t3,t4,t5
	sw	t3,24(sp)
	lw	t4,24(sp)
	seqz	t4,t4
	sw	t4,28(sp)
	lw	a0,28(sp)
	bne	a0,zero,.L0
	li	a0,-1
	sw	a0,4(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L1
.L0:
	nop
	li	a0,0
	sw	a0,4(sp)
.L1:
	nop
	lw	a0,4(sp)
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
