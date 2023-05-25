	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.comm	g,4,4
	.comm	h,4,4
	.comm	f,4,4
	.comm	e,4,4
	.global	EightWhile
	.type	EightWhile, @function
EightWhile:
	addi	sp,sp,-204
	sw	ra,0(sp)
	li	a0,5
	sw	a0,4(sp)
	li	a0,6
	sw	a0,8(sp)
	li	a0,7
	sw	a0,12(sp)
	li	a0,10
	sw	a0,16(sp)
.L0:
	nop
	li	a0,20
	sw	a0,20(sp)
	lw	t4,4(sp)
	lw	t5,20(sp)
	slt	t3,t4,t5
	sw	t3,24(sp)
	lw	t4,24(sp)
	seqz	t4,t4
	sw	t4,28(sp)
	lw	a0,28(sp)
	bne	a0,zero,.L15
	lw	t4,4(sp)
	addi	t3,t4,3
	sw	t3,32(sp)
	lw	t4,32(sp)
	sw	t4,4(sp)
.L1:
	nop
	li	a0,10
	sw	a0,36(sp)
	lw	t4,8(sp)
	lw	t5,36(sp)
	slt	t3,t4,t5
	sw	t3,40(sp)
	lw	t4,40(sp)
	seqz	t4,t4
	sw	t4,44(sp)
	lw	a0,44(sp)
	bne	a0,zero,.L14
	lw	t4,8(sp)
	addi	t3,t4,1
	sw	t3,48(sp)
	lw	t4,48(sp)
	sw	t4,8(sp)
.L2:
	nop
	li	a0,7
	sw	a0,52(sp)
	lw	t4,12(sp)
	lw	t5,52(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,56(sp)
	lw	t4,56(sp)
	seqz	t4,t4
	sw	t4,60(sp)
	lw	a0,60(sp)
	bne	a0,zero,.L13
	lw	t4,12(sp)
	addi	t3,t4,-1
	sw	t3,64(sp)
	lw	t4,64(sp)
	sw	t4,12(sp)
.L3:
	nop
	li	a0,20
	sw	a0,68(sp)
	lw	t4,16(sp)
	lw	t5,68(sp)
	slt	t3,t4,t5
	sw	t3,72(sp)
	lw	t4,72(sp)
	seqz	t4,t4
	sw	t4,76(sp)
	lw	a0,76(sp)
	bne	a0,zero,.L12
	lw	t4,16(sp)
	addi	t3,t4,3
	sw	t3,80(sp)
	lw	t4,80(sp)
	sw	t4,16(sp)
.L4:
	nop
	li	a0,1
	sw	a0,84(sp)
	la	a0,e
	lw	t4,0(a0)
	lw	t5,84(sp)
	slt	t3,t5,t4
	sw	t3,88(sp)
	lw	t4,88(sp)
	seqz	t4,t4
	sw	t4,92(sp)
	lw	a0,92(sp)
	bne	a0,zero,.L11
	la	a0,e
	lw	t4,0(a0)
	addi	t3,t4,-1
	sw	t3,96(sp)
	lw	t4,96(sp)
	la	a1,e
	sw	t4,0(a1)
.L5:
	nop
	li	a0,2
	sw	a0,100(sp)
	la	a0,f
	lw	t4,0(a0)
	lw	t5,100(sp)
	slt	t3,t5,t4
	sw	t3,104(sp)
	lw	t4,104(sp)
	seqz	t4,t4
	sw	t4,108(sp)
	lw	a0,108(sp)
	bne	a0,zero,.L10
	la	a0,f
	lw	t4,0(a0)
	addi	t3,t4,-2
	sw	t3,112(sp)
	lw	t4,112(sp)
	la	a1,f
	sw	t4,0(a1)
.L6:
	nop
	li	a0,3
	sw	a0,116(sp)
	la	a0,g
	lw	t4,0(a0)
	lw	t5,116(sp)
	slt	t3,t4,t5
	sw	t3,120(sp)
	lw	t4,120(sp)
	seqz	t4,t4
	sw	t4,124(sp)
	lw	a0,124(sp)
	bne	a0,zero,.L9
	la	a0,g
	lw	t4,0(a0)
	addi	t3,t4,10
	sw	t3,128(sp)
	lw	t4,128(sp)
	la	a1,g
	sw	t4,0(a1)
.L7:
	nop
	li	a0,10
	sw	a0,132(sp)
	la	a0,h
	lw	t4,0(a0)
	lw	t5,132(sp)
	slt	t3,t4,t5
	sw	t3,136(sp)
	lw	t4,136(sp)
	seqz	t4,t4
	sw	t4,140(sp)
	lw	a0,140(sp)
	bne	a0,zero,.L8
	la	a0,h
	lw	t4,0(a0)
	addi	t3,t4,8
	sw	t3,144(sp)
	lw	t4,144(sp)
	la	a1,h
	sw	t4,0(a1)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L7
.L8:
	nop
	la	a0,h
	lw	t4,0(a0)
	addi	t3,t4,-1
	sw	t3,148(sp)
	lw	t4,148(sp)
	la	a1,h
	sw	t4,0(a1)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L6
.L9:
	nop
	la	a0,g
	lw	t4,0(a0)
	addi	t3,t4,-8
	sw	t3,152(sp)
	lw	t4,152(sp)
	la	a1,g
	sw	t4,0(a1)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L5
.L10:
	nop
	la	a0,f
	lw	t4,0(a0)
	addi	t3,t4,1
	sw	t3,156(sp)
	lw	t4,156(sp)
	la	a1,f
	sw	t4,0(a1)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L4
.L11:
	nop
	la	a0,e
	lw	t4,0(a0)
	addi	t3,t4,1
	sw	t3,160(sp)
	lw	t4,160(sp)
	la	a1,e
	sw	t4,0(a1)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L3
.L12:
	nop
	lw	t4,16(sp)
	addi	t3,t4,-1
	sw	t3,164(sp)
	lw	t4,164(sp)
	sw	t4,16(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L2
.L13:
	nop
	lw	t4,12(sp)
	addi	t3,t4,1
	sw	t3,168(sp)
	lw	t4,168(sp)
	sw	t4,12(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L1
.L14:
	nop
	lw	t4,8(sp)
	addi	t3,t4,-2
	sw	t3,172(sp)
	lw	t4,172(sp)
	sw	t4,8(sp)
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L0
.L15:
	nop
	lw	t4,8(sp)
	lw	t5,16(sp)
	add	t3,t4,t5
	sw	t3,176(sp)
	lw	t4,4(sp)
	lw	t5,176(sp)
	add	t3,t4,t5
	sw	t3,180(sp)
	lw	t4,180(sp)
	lw	t5,12(sp)
	add	t3,t4,t5
	sw	t3,184(sp)
	la	a0,e
	lw	t4,0(a0)
	lw	t5,16(sp)
	add	t3,t4,t5
	sw	t3,188(sp)
	lw	t4,188(sp)
	la	a0,g
	lw	t5,0(a0)
	sub	t3,t4,t5
	sw	t3,192(sp)
	lw	t4,192(sp)
	la	a0,h
	lw	t5,0(a0)
	add	t3,t4,t5
	sw	t3,196(sp)
	lw	t4,184(sp)
	lw	t5,196(sp)
	sub	t3,t4,t5
	sw	t3,200(sp)
	lw	a0,200(sp)
	lw	ra,0(sp)
	addi	sp,sp,204
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	li	a0,1
	la	a1,g
	sw	a0,0(a1)
	li	a0,2
	la	a1,h
	sw	a0,0(a1)
	li	a0,4
	la	a1,e
	sw	a0,0(a1)
	li	a0,6
	la	a1,f
	sw	a0,0(a1)
	call	EightWhile
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
