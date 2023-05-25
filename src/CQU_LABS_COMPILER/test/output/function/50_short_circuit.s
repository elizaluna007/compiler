	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.comm	g,4,4
	.global	func
	.type	func, @function
func:
	addi	sp,sp,-12
	sw	ra,0(sp)
	sw	a0,4(sp)
	la	a0,g
	lw	t4,0(a0)
	lw	t5,4(sp)
	add	t3,t4,t5
	sw	t3,8(sp)
	lw	t4,8(sp)
	la	a1,g
	sw	t4,0(a1)
	la	a0,g
	lw	a0,0(a0)
	call	putint
	la	a0,g
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-148
	sw	ra,0(sp)
	call	global
	call	getint
	sw	a0,4(sp)
	lw	t4,4(sp)
	sw	t4,8(sp)
	li	a0,10
	sw	a0,12(sp)
	lw	t4,8(sp)
	lw	t5,12(sp)
	slt	t3,t5,t4
	sw	t3,16(sp)
	lw	t4,16(sp)
	sw	t4,20(sp)
	lw	t4,20(sp)
	seqz	t4,t4
	sw	t4,24(sp)
	lw	a0,24(sp)
	bne	a0,zero,.L0
	lw	a0,8(sp)
	call	func
	sw	a0,28(sp)
	lw	t4,20(sp)
	snez	t4,t4
	lw	t5,28(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,20(sp)
.L0:
	nop
	lw	t4,20(sp)
	seqz	t4,t4
	sw	t4,32(sp)
	lw	a0,32(sp)
	bne	a0,zero,.L1
	li	a0,1
	sw	a0,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L2
.L1:
	nop
	li	a0,0
	sw	a0,8(sp)
.L2:
	nop
	call	getint
	sw	a0,36(sp)
	lw	t4,36(sp)
	sw	t4,8(sp)
	li	a0,11
	sw	a0,40(sp)
	lw	t4,8(sp)
	lw	t5,40(sp)
	slt	t3,t5,t4
	sw	t3,44(sp)
	lw	t4,44(sp)
	sw	t4,48(sp)
	lw	t4,48(sp)
	seqz	t4,t4
	sw	t4,52(sp)
	lw	a0,52(sp)
	bne	a0,zero,.L3
	lw	a0,8(sp)
	call	func
	sw	a0,56(sp)
	lw	t4,48(sp)
	snez	t4,t4
	lw	t5,56(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,48(sp)
.L3:
	nop
	lw	t4,48(sp)
	seqz	t4,t4
	sw	t4,60(sp)
	lw	a0,60(sp)
	bne	a0,zero,.L4
	li	a0,1
	sw	a0,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L5
.L4:
	nop
	li	a0,0
	sw	a0,8(sp)
.L5:
	nop
	call	getint
	sw	a0,64(sp)
	lw	t4,64(sp)
	sw	t4,8(sp)
	li	a0,99
	sw	a0,68(sp)
	lw	t4,8(sp)
	lw	t5,68(sp)
	slt	t0,t4,t5
	sub	t1,t4,t5
	seqz	t1,t1
	or	t3,t0,t1
	sw	t3,72(sp)
	lw	t4,72(sp)
	sw	t4,76(sp)
	lw	a0,76(sp)
	bne	a0,zero,.L6
	lw	a0,8(sp)
	call	func
	sw	a0,80(sp)
	lw	t4,76(sp)
	snez	t4,t4
	lw	t5,80(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,76(sp)
.L6:
	nop
	lw	t4,76(sp)
	seqz	t4,t4
	sw	t4,84(sp)
	lw	a0,84(sp)
	bne	a0,zero,.L7
	li	a0,1
	sw	a0,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L8
.L7:
	nop
	li	a0,0
	sw	a0,8(sp)
.L8:
	nop
	call	getint
	sw	a0,88(sp)
	lw	t4,88(sp)
	sw	t4,8(sp)
	li	a0,100
	sw	a0,92(sp)
	lw	t4,8(sp)
	lw	t5,92(sp)
	slt	t0,t4,t5
	sub	t1,t4,t5
	seqz	t1,t1
	or	t3,t0,t1
	sw	t3,96(sp)
	lw	t4,96(sp)
	sw	t4,100(sp)
	lw	a0,100(sp)
	bne	a0,zero,.L9
	lw	a0,8(sp)
	call	func
	sw	a0,104(sp)
	lw	t4,100(sp)
	snez	t4,t4
	lw	t5,104(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,100(sp)
.L9:
	nop
	lw	t4,100(sp)
	seqz	t4,t4
	sw	t4,108(sp)
	lw	a0,108(sp)
	bne	a0,zero,.L10
	li	a0,1
	sw	a0,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L11
.L10:
	nop
	li	a0,0
	sw	a0,8(sp)
.L11:
	nop
	li	a0,99
	sw	a0,112(sp)
	lw	a0,112(sp)
	call	func
	sw	a0,116(sp)
	lw	t4,116(sp)
	seqz	t4,t4
	sw	t4,120(sp)
	lw	t4,120(sp)
	sw	t4,124(sp)
	lw	t4,124(sp)
	seqz	t4,t4
	sw	t4,128(sp)
	lw	a0,128(sp)
	bne	a0,zero,.L12
	li	a0,100
	sw	a0,132(sp)
	lw	a0,132(sp)
	call	func
	sw	a0,136(sp)
	lw	t4,124(sp)
	snez	t4,t4
	lw	t5,136(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,124(sp)
.L12:
	nop
	lw	t4,124(sp)
	seqz	t4,t4
	sw	t4,140(sp)
	lw	a0,140(sp)
	bne	a0,zero,.L13
	li	a0,1
	sw	a0,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L14
.L13:
	nop
	li	a0,0
	sw	a0,8(sp)
.L14:
	nop
	li	a0,0
	sw	a0,144(sp)
	lw	a0,144(sp)
	lw	ra,0(sp)
	addi	sp,sp,148
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
	li	a0,0
	la	a1,g
	sw	a0,0(a1)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
FLOAT0:
	.word	0
