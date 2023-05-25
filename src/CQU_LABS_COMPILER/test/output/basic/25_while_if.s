	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	get_one
	.type	get_one, @function
get_one:
	addi	sp,sp,-12
	sw	ra,0(sp)
	sw	a0,4(sp)
	li	a0,1
	sw	a0,8(sp)
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	deepWhileBr
	.type	deepWhileBr, @function
deepWhileBr:
	addi	sp,sp,-104
	sw	ra,0(sp)
	sw	a0,4(sp)
	sw	a1,8(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	add	t3,t4,t5
	sw	t3,12(sp)
	lw	t4,12(sp)
	sw	t4,16(sp)
.L0:
	nop
	li	a0,75
	sw	a0,20(sp)
	lw	t4,16(sp)
	lw	t5,20(sp)
	slt	t3,t4,t5
	sw	t3,24(sp)
	lw	t4,24(sp)
	seqz	t4,t4
	sw	t4,28(sp)
	lw	a0,28(sp)
	bne	a0,zero,.L4
	li	a0,42
	sw	a0,32(sp)
	li	a0,100
	sw	a0,36(sp)
	lw	t4,16(sp)
	lw	t5,36(sp)
	slt	t3,t4,t5
	sw	t3,40(sp)
	lw	t4,40(sp)
	seqz	t4,t4
	sw	t4,44(sp)
	lw	a0,44(sp)
	bne	a0,zero,.L3
	lw	t4,16(sp)
	lw	t5,32(sp)
	add	t3,t4,t5
	sw	t3,48(sp)
	lw	t4,48(sp)
	sw	t4,16(sp)
	li	a0,99
	sw	a0,52(sp)
	lw	t4,16(sp)
	lw	t5,52(sp)
	slt	t3,t5,t4
	sw	t3,56(sp)
	lw	t4,56(sp)
	seqz	t4,t4
	sw	t4,60(sp)
	lw	a0,60(sp)
	bne	a0,zero,.L2
	li	a0,2
	sw	a0,64(sp)
	lw	t4,32(sp)
	lw	t5,64(sp)
	mul	t3,t4,t5
	sw	t3,68(sp)
	lw	t4,68(sp)
	sw	t4,72(sp)
	li	a0,0
	sw	a0,76(sp)
	lw	a0,76(sp)
	call	get_one
	sw	a0,80(sp)
	li	a0,1
	sw	a0,84(sp)
	lw	t4,80(sp)
	lw	t5,84(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,88(sp)
	lw	t4,88(sp)
	seqz	t4,t4
	sw	t4,92(sp)
	lw	a0,92(sp)
	bne	a0,zero,.L1
	li	a0,2
	sw	a0,96(sp)
	lw	t4,72(sp)
	lw	t5,96(sp)
	mul	t3,t4,t5
	sw	t3,100(sp)
	lw	t4,100(sp)
	sw	t4,16(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L1
.L1:
	nop
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L2
.L2:
	nop
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L3
.L3:
	nop
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L0
.L4:
	nop
	lw	a0,16(sp)
	lw	ra,0(sp)
	addi	sp,sp,104
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-16
	sw	ra,0(sp)
	call	global
	li	a0,2
	sw	a0,4(sp)
	lw	a0,4(sp)
	lw	a1,4(sp)
	call	deepWhileBr
	sw	a0,8(sp)
	lw	t4,8(sp)
	sw	t4,4(sp)
	lw	a0,4(sp)
	call	putint
	li	a0,0
	sw	a0,12(sp)
	lw	a0,12(sp)
	lw	ra,0(sp)
	addi	sp,sp,16
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
