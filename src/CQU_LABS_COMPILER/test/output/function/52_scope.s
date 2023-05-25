	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.comm	a,4,4
	.global	func
	.type	func, @function
func:
	addi	sp,sp,-32
	sw	ra,0(sp)
	la	a0,a
	lw	t4,0(a0)
	sw	t4,4(sp)
	li	a0,1
	sw	a0,8(sp)
	lw	t4,8(sp)
	lw	t5,4(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,12(sp)
	lw	t4,12(sp)
	seqz	t4,t4
	sw	t4,16(sp)
	lw	a0,16(sp)
	bne	a0,zero,.L0
	lw	t4,8(sp)
	addi	t3,t4,1
	sw	t3,20(sp)
	lw	t4,20(sp)
	sw	t4,8(sp)
	li	a0,1
	sw	a0,24(sp)
	lw	a0,24(sp)
	lw	ra,0(sp)
	addi	sp,sp,32
	jr	ra
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L1
.L0:
	nop
	li	a0,0
	sw	a0,28(sp)
	lw	a0,28(sp)
	lw	ra,0(sp)
	addi	sp,sp,32
	jr	ra
.L1:
	nop
	la	a0,zero
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,32
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-72
	sw	ra,0(sp)
	call	global
	li	a0,0
	sw	a0,4(sp)
	li	a0,0
	sw	a0,8(sp)
.L2:
	nop
	li	a0,100
	sw	a0,12(sp)
	lw	t4,8(sp)
	lw	t5,12(sp)
	slt	t3,t4,t5
	sw	t3,16(sp)
	lw	t4,16(sp)
	seqz	t4,t4
	sw	t4,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L4
	call	func
	sw	a0,24(sp)
	li	a0,1
	sw	a0,28(sp)
	lw	t4,24(sp)
	lw	t5,28(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,32(sp)
	lw	t4,32(sp)
	seqz	t4,t4
	sw	t4,36(sp)
	lw	a0,36(sp)
	bne	a0,zero,.L3
	lw	t4,4(sp)
	addi	t3,t4,1
	sw	t3,40(sp)
	lw	t4,40(sp)
	sw	t4,4(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L3
.L3:
	nop
	lw	t4,8(sp)
	addi	t3,t4,1
	sw	t3,44(sp)
	lw	t4,44(sp)
	sw	t4,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L2
.L4:
	nop
	li	a0,100
	sw	a0,48(sp)
	lw	t4,4(sp)
	lw	t5,48(sp)
	slt	t3,t4,t5
	sw	t3,52(sp)
	lw	t4,52(sp)
	seqz	t4,t4
	sw	t4,56(sp)
	lw	a0,56(sp)
	bne	a0,zero,.L5
	li	a0,1
	sw	a0,60(sp)
	lw	a0,60(sp)
	call	putint
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L6
.L5:
	nop
	li	a0,0
	sw	a0,64(sp)
	lw	a0,64(sp)
	call	putint
.L6:
	nop
	li	a0,0
	sw	a0,68(sp)
	lw	a0,68(sp)
	lw	ra,0(sp)
	addi	sp,sp,72
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
	li	a0,7
	la	a1,a
	sw	a0,0(a1)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
FLOAT0:
	.word	0
