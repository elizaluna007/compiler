	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	doubleWhile
	.type	doubleWhile, @function
doubleWhile:
	addi	sp,sp,-48
	sw	ra,0(sp)
	li	a0,5
	sw	a0,4(sp)
	li	a0,7
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
	bne	a0,zero,.L3
	lw	t4,4(sp)
	addi	t3,t4,30
	sw	t3,24(sp)
	lw	t4,24(sp)
	sw	t4,4(sp)
.L1:
	nop
	li	a0,100
	sw	a0,28(sp)
	lw	t4,8(sp)
	lw	t5,28(sp)
	slt	t3,t4,t5
	sw	t3,32(sp)
	lw	t4,32(sp)
	seqz	t4,t4
	sw	t4,36(sp)
	lw	a0,36(sp)
	bne	a0,zero,.L2
	lw	t4,8(sp)
	addi	t3,t4,6
	sw	t3,40(sp)
	lw	t4,40(sp)
	sw	t4,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L1
.L2:
	nop
	lw	t4,8(sp)
	addi	t3,t4,-100
	sw	t3,44(sp)
	lw	t4,44(sp)
	sw	t4,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L0
.L3:
	nop
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,48
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	doubleWhile
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
