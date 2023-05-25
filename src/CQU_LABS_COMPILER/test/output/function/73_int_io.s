	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	my_getint
	.type	my_getint, @function
my_getint:
	addi	sp,sp,-100
	sw	ra,0(sp)
	li	a0,0
	sw	a0,4(sp)
.L0:
	nop
	la	a0,one
	lw	t4,0(a0)
	seqz	t4,t4
	sw	t4,8(sp)
	lw	a0,8(sp)
	bne	a0,zero,.L4
	call	getch
	sw	a0,12(sp)
	lw	t4,12(sp)
	addi	t3,t4,-48
	sw	t3,16(sp)
	lw	t4,16(sp)
	sw	t4,20(sp)
	li	a0,0
	sw	a0,24(sp)
	lw	t4,20(sp)
	lw	t5,24(sp)
	slt	t3,t4,t5
	sw	t3,28(sp)
	lw	t4,28(sp)
	sw	t4,32(sp)
	lw	a0,32(sp)
	bne	a0,zero,.L1
	li	a0,9
	sw	a0,36(sp)
	lw	t4,20(sp)
	lw	t5,36(sp)
	slt	t3,t5,t4
	sw	t3,40(sp)
	lw	t4,32(sp)
	snez	t4,t4
	lw	t5,40(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,32(sp)
.L1:
	nop
	lw	t4,32(sp)
	seqz	t4,t4
	sw	t4,44(sp)
	lw	a0,44(sp)
	bne	a0,zero,.L2
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L0
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L3
.L2:
	nop
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L4
.L3:
	nop
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L0
.L4:
	nop
	lw	t4,20(sp)
	sw	t4,4(sp)
.L5:
	nop
	la	a0,one
	lw	t4,0(a0)
	seqz	t4,t4
	sw	t4,48(sp)
	lw	a0,48(sp)
	bne	a0,zero,.L9
	call	getch
	sw	a0,52(sp)
	lw	t4,52(sp)
	addi	t3,t4,-48
	sw	t3,56(sp)
	lw	t4,56(sp)
	sw	t4,20(sp)
	li	a0,0
	sw	a0,60(sp)
	lw	t4,20(sp)
	lw	t5,60(sp)
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,64(sp)
	lw	t4,64(sp)
	sw	t4,68(sp)
	lw	t4,68(sp)
	seqz	t4,t4
	sw	t4,72(sp)
	lw	a0,72(sp)
	bne	a0,zero,.L6
	li	a0,9
	sw	a0,76(sp)
	lw	t4,20(sp)
	lw	t5,76(sp)
	slt	t0,t4,t5
	sub	t1,t4,t5
	seqz	t1,t1
	or	t3,t0,t1
	sw	t3,80(sp)
	lw	t4,68(sp)
	snez	t4,t4
	lw	t5,80(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,68(sp)
.L6:
	nop
	lw	t4,68(sp)
	seqz	t4,t4
	sw	t4,84(sp)
	lw	a0,84(sp)
	bne	a0,zero,.L7
	li	a0,10
	sw	a0,88(sp)
	lw	t4,4(sp)
	lw	t5,88(sp)
	mul	t3,t4,t5
	sw	t3,92(sp)
	lw	t4,92(sp)
	lw	t5,20(sp)
	add	t3,t4,t5
	sw	t3,96(sp)
	lw	t4,96(sp)
	sw	t4,4(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L8
.L7:
	nop
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L9
.L8:
	nop
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L5
.L9:
	nop
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,100
	jr	ra
	.global	my_putint
	.type	my_putint, @function
my_putint:
	addi	sp,sp,-136
	sw	ra,0(sp)
	sw	a0,4(sp)
	addi	a0,sp,12
	sw	a0,8(sp)
	li	a0,0
	sw	a0,76(sp)
.L10:
	nop
	li	a0,0
	sw	a0,80(sp)
	lw	t4,4(sp)
	lw	t5,80(sp)
	slt	t3,t5,t4
	sw	t3,84(sp)
	lw	t4,84(sp)
	seqz	t4,t4
	sw	t4,88(sp)
	lw	a0,88(sp)
	bne	a0,zero,.L11
	li	a0,10
	sw	a0,92(sp)
	lw	t4,4(sp)
	lw	t5,92(sp)
	rem	t3,t4,t5
	sw	t3,96(sp)
	lw	t4,96(sp)
	addi	t3,t4,48
	sw	t3,100(sp)
	lw	a0,76(sp)
	slli	a0,a0,2
	lw	a1,100(sp)
	lw	a2,8(sp)
	add	a2,a2,a0
	sw	a1,0(a2)
	li	a0,10
	sw	a0,104(sp)
	lw	t4,4(sp)
	lw	t5,104(sp)
	div	t3,t4,t5
	sw	t3,108(sp)
	lw	t4,108(sp)
	sw	t4,4(sp)
	lw	t4,76(sp)
	addi	t3,t4,1
	sw	t3,112(sp)
	lw	t4,112(sp)
	sw	t4,76(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L10
.L11:
	nop
.L12:
	nop
	li	a0,0
	sw	a0,116(sp)
	lw	t4,76(sp)
	lw	t5,116(sp)
	slt	t3,t5,t4
	sw	t3,120(sp)
	lw	t4,120(sp)
	seqz	t4,t4
	sw	t4,124(sp)
	lw	a0,124(sp)
	bne	a0,zero,.L13
	lw	t4,76(sp)
	addi	t3,t4,-1
	sw	t3,128(sp)
	lw	t4,128(sp)
	sw	t4,76(sp)
	lw	a0,76(sp)
	slli	a0,a0,2
	lw	a1,8(sp)
	add	a1,a1,a0
	lw	a1,0(a1)
	sw	a1,132(sp)
	lw	a0,132(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L12
.L13:
	nop
	lw	ra,0(sp)
	addi	sp,sp,136
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-44
	sw	ra,0(sp)
	call	global
	call	my_getint
	sw	a0,4(sp)
	lw	t4,4(sp)
	sw	t4,8(sp)
.L14:
	nop
	li	a0,0
	sw	a0,12(sp)
	lw	t4,8(sp)
	lw	t5,12(sp)
	slt	t3,t5,t4
	sw	t3,16(sp)
	lw	t4,16(sp)
	seqz	t4,t4
	sw	t4,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L15
	call	my_getint
	sw	a0,24(sp)
	lw	t4,24(sp)
	sw	t4,28(sp)
	lw	a0,28(sp)
	call	my_putint
	li	a0,10
	sw	a0,32(sp)
	lw	a0,32(sp)
	call	putch
	lw	t4,8(sp)
	addi	t3,t4,-1
	sw	t3,36(sp)
	lw	t4,36(sp)
	sw	t4,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L14
.L15:
	nop
	li	a0,0
	sw	a0,40(sp)
	lw	a0,40(sp)
	lw	ra,0(sp)
	addi	sp,sp,44
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
