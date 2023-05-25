	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	if_ifElse_
	.type	if_ifElse_, @function
if_ifElse_:
	addi	sp,sp,-40
	sw	ra,0(sp)
	li	a0,5
	sw	a0,4(sp)
	li	a0,10
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
	li	a0,10
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
	bne	a0,zero,.L0
	li	a0,25
	sw	a0,4(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L1
.L0:
	nop
	lw	t4,4(sp)
	addi	t3,t4,15
	sw	t3,36(sp)
	lw	t4,36(sp)
	sw	t4,4(sp)
.L1:
	nop
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L2
.L2:
	nop
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,40
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	if_ifElse_
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
