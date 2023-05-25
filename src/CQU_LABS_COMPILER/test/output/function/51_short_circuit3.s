	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.comm	a,4,4
	.comm	b,4,4
	.comm	d,4,4
	.global	set_a
	.type	set_a, @function
set_a:
	addi	sp,sp,-8
	sw	ra,0(sp)
	sw	a0,4(sp)
	lw	t4,4(sp)
	la	a1,a
	sw	t4,0(a1)
	la	a0,a
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	set_b
	.type	set_b, @function
set_b:
	addi	sp,sp,-8
	sw	ra,0(sp)
	sw	a0,4(sp)
	lw	t4,4(sp)
	la	a1,b
	sw	t4,0(a1)
	la	a0,b
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	set_d
	.type	set_d, @function
set_d:
	addi	sp,sp,-8
	sw	ra,0(sp)
	sw	a0,4(sp)
	lw	t4,4(sp)
	la	a1,d
	sw	t4,0(a1)
	la	a0,d
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-324
	sw	ra,0(sp)
	call	global
	li	a0,2
	la	a1,a
	sw	a0,0(a1)
	li	a0,3
	la	a1,b
	sw	a0,0(a1)
	li	a0,0
	sw	a0,4(sp)
	lw	a0,4(sp)
	call	set_a
	sw	a0,8(sp)
	lw	t4,8(sp)
	sw	t4,12(sp)
	lw	t4,12(sp)
	seqz	t4,t4
	sw	t4,16(sp)
	lw	a0,16(sp)
	bne	a0,zero,.L0
	li	a0,1
	sw	a0,20(sp)
	lw	a0,20(sp)
	call	set_b
	sw	a0,24(sp)
	lw	t4,12(sp)
	snez	t4,t4
	lw	t5,24(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,12(sp)
.L0:
	nop
	lw	t4,12(sp)
	seqz	t4,t4
	sw	t4,28(sp)
	lw	a0,28(sp)
	bne	a0,zero,.L1
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L1
.L1:
	nop
	la	a0,a
	lw	a0,0(a0)
	call	putint
	li	a0,32
	sw	a0,32(sp)
	lw	a0,32(sp)
	call	putch
	la	a0,b
	lw	a0,0(a0)
	call	putint
	li	a0,32
	sw	a0,36(sp)
	lw	a0,36(sp)
	call	putch
	li	a0,2
	la	a1,a
	sw	a0,0(a1)
	li	a0,3
	la	a1,b
	sw	a0,0(a1)
	li	a0,0
	sw	a0,40(sp)
	lw	a0,40(sp)
	call	set_a
	sw	a0,44(sp)
	lw	t4,44(sp)
	sw	t4,48(sp)
	lw	t4,48(sp)
	seqz	t4,t4
	sw	t4,52(sp)
	lw	a0,52(sp)
	bne	a0,zero,.L2
	li	a0,1
	sw	a0,56(sp)
	lw	a0,56(sp)
	call	set_b
	sw	a0,60(sp)
	lw	t4,48(sp)
	snez	t4,t4
	lw	t5,60(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,48(sp)
.L2:
	nop
	lw	t4,48(sp)
	seqz	t4,t4
	sw	t4,64(sp)
	lw	a0,64(sp)
	bne	a0,zero,.L3
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L3
.L3:
	nop
	la	a0,a
	lw	a0,0(a0)
	call	putint
	li	a0,32
	sw	a0,68(sp)
	lw	a0,68(sp)
	call	putch
	la	a0,b
	lw	a0,0(a0)
	call	putint
	li	a0,10
	sw	a0,72(sp)
	lw	a0,72(sp)
	call	putch
	li	a0,2
	la	a1,d
	sw	a0,0(a1)
	li	a0,3
	sw	a0,76(sp)
	lw	a0,76(sp)
	call	set_d
	sw	a0,80(sp)
	lw	t4,80(sp)
	seqz	t4,t4
	sw	t4,84(sp)
	lw	a0,84(sp)
	bne	a0,zero,.L4
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L4
.L4:
	nop
	la	a0,d
	lw	a0,0(a0)
	call	putint
	li	a0,32
	sw	a0,88(sp)
	lw	a0,88(sp)
	call	putch
	la	a0,one
	lw	t4,0(a0)
	seqz	t4,t4
	sw	t4,92(sp)
	lw	a0,92(sp)
	bne	a0,zero,.L5
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L5
.L5:
	nop
	la	a0,d
	lw	a0,0(a0)
	call	putint
	li	a0,10
	sw	a0,96(sp)
	lw	a0,96(sp)
	call	putch
	la	a0,one
	lw	t4,0(a0)
	seqz	t4,t4
	sw	t4,100(sp)
	lw	a0,100(sp)
	bne	a0,zero,.L6
	li	a0,65
	sw	a0,104(sp)
	lw	a0,104(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L6
.L6:
	nop
	la	a0,zero
	lw	t4,0(a0)
	seqz	t4,t4
	sw	t4,108(sp)
	lw	a0,108(sp)
	bne	a0,zero,.L7
	li	a0,66
	sw	a0,112(sp)
	lw	a0,112(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L7
.L7:
	nop
	la	a0,zero
	lw	t4,0(a0)
	seqz	t4,t4
	sw	t4,116(sp)
	lw	a0,116(sp)
	bne	a0,zero,.L8
	li	a0,67
	sw	a0,120(sp)
	lw	a0,120(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L8
.L8:
	nop
	la	a0,one
	lw	t4,0(a0)
	seqz	t4,t4
	sw	t4,124(sp)
	lw	a0,124(sp)
	bne	a0,zero,.L9
	li	a0,68
	sw	a0,128(sp)
	lw	a0,128(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L9
.L9:
	nop
	la	a0,zero
	lw	t4,0(a0)
	seqz	t4,t4
	sw	t4,132(sp)
	lw	a0,132(sp)
	bne	a0,zero,.L10
	li	a0,69
	sw	a0,136(sp)
	lw	a0,136(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L10
.L10:
	nop
	la	a0,one
	lw	t4,0(a0)
	seqz	t4,t4
	sw	t4,140(sp)
	lw	a0,140(sp)
	bne	a0,zero,.L11
	li	a0,70
	sw	a0,144(sp)
	lw	a0,144(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L11
.L11:
	nop
	li	a0,10
	sw	a0,148(sp)
	lw	a0,148(sp)
	call	putch
	li	a0,0
	sw	a0,152(sp)
	li	a0,1
	sw	a0,156(sp)
	li	a0,2
	sw	a0,160(sp)
	li	a0,3
	sw	a0,164(sp)
	li	a0,4
	sw	a0,168(sp)
.L12:
	nop
	lw	t4,152(sp)
	sw	t4,172(sp)
	lw	t4,172(sp)
	seqz	t4,t4
	sw	t4,176(sp)
	lw	a0,176(sp)
	bne	a0,zero,.L13
	lw	t4,172(sp)
	snez	t4,t4
	lw	t5,156(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,172(sp)
.L13:
	nop
	lw	t4,172(sp)
	seqz	t4,t4
	sw	t4,180(sp)
	lw	a0,180(sp)
	bne	a0,zero,.L14
	li	a0,32
	sw	a0,184(sp)
	lw	a0,184(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L12
.L14:
	nop
	lw	t4,152(sp)
	sw	t4,188(sp)
	lw	a0,188(sp)
	bne	a0,zero,.L15
	lw	t4,188(sp)
	snez	t4,t4
	lw	t5,156(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,188(sp)
.L15:
	nop
	lw	t4,188(sp)
	seqz	t4,t4
	sw	t4,192(sp)
	lw	a0,192(sp)
	bne	a0,zero,.L16
	li	a0,67
	sw	a0,196(sp)
	lw	a0,196(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L16
.L16:
	nop
	lw	t4,152(sp)
	lw	t5,156(sp)
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,200(sp)
	lw	t4,200(sp)
	sw	t4,204(sp)
	lw	a0,204(sp)
	bne	a0,zero,.L17
	lw	t4,156(sp)
	lw	t5,152(sp)
	slt	t0,t4,t5
	sub	t1,t4,t5
	seqz	t1,t1
	or	t3,t0,t1
	sw	t3,208(sp)
	lw	t4,204(sp)
	snez	t4,t4
	lw	t5,208(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,204(sp)
.L17:
	nop
	lw	t4,204(sp)
	seqz	t4,t4
	sw	t4,212(sp)
	lw	a0,212(sp)
	bne	a0,zero,.L18
	li	a0,72
	sw	a0,216(sp)
	lw	a0,216(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L18
.L18:
	nop
	lw	t4,160(sp)
	lw	t5,156(sp)
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,220(sp)
	lw	t4,220(sp)
	sw	t4,224(sp)
	lw	t4,224(sp)
	seqz	t4,t4
	sw	t4,228(sp)
	lw	a0,228(sp)
	bne	a0,zero,.L19
	lw	t4,168(sp)
	lw	t5,164(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,232(sp)
	lw	t4,224(sp)
	snez	t4,t4
	lw	t5,232(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,224(sp)
.L19:
	nop
	lw	t4,224(sp)
	seqz	t4,t4
	sw	t4,236(sp)
	lw	a0,236(sp)
	bne	a0,zero,.L20
	li	a0,73
	sw	a0,240(sp)
	lw	a0,240(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L20
.L20:
	nop
	lw	t4,156(sp)
	seqz	t4,t4
	sw	t4,244(sp)
	lw	t4,152(sp)
	lw	t5,244(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,248(sp)
	lw	t4,248(sp)
	sw	t4,252(sp)
	lw	t4,252(sp)
	seqz	t4,t4
	sw	t4,256(sp)
	lw	a0,256(sp)
	bne	a0,zero,.L21
	lw	t4,164(sp)
	lw	t5,164(sp)
	slt	t3,t4,t5
	sw	t3,260(sp)
	lw	t4,252(sp)
	snez	t4,t4
	lw	t5,260(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,252(sp)
.L21:
	nop
	lw	t4,252(sp)
	sw	t4,264(sp)
	lw	a0,264(sp)
	bne	a0,zero,.L22
	lw	t4,168(sp)
	lw	t5,168(sp)
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,268(sp)
	lw	t4,264(sp)
	snez	t4,t4
	lw	t5,268(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,264(sp)
.L22:
	nop
	lw	t4,264(sp)
	seqz	t4,t4
	sw	t4,272(sp)
	lw	a0,272(sp)
	bne	a0,zero,.L23
	li	a0,74
	sw	a0,276(sp)
	lw	a0,276(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L23
.L23:
	nop
	lw	t4,156(sp)
	seqz	t4,t4
	sw	t4,280(sp)
	lw	t4,152(sp)
	lw	t5,280(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,284(sp)
	lw	t4,284(sp)
	sw	t4,288(sp)
	lw	a0,288(sp)
	bne	a0,zero,.L25
	lw	t4,164(sp)
	lw	t5,164(sp)
	slt	t3,t4,t5
	sw	t3,292(sp)
	lw	t4,292(sp)
	sw	t4,296(sp)
	lw	t4,296(sp)
	seqz	t4,t4
	sw	t4,300(sp)
	lw	a0,300(sp)
	bne	a0,zero,.L24
	lw	t4,168(sp)
	lw	t5,168(sp)
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,304(sp)
	lw	t4,296(sp)
	snez	t4,t4
	lw	t5,304(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,296(sp)
.L24:
	nop
	lw	t4,288(sp)
	snez	t4,t4
	lw	t5,296(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,288(sp)
.L25:
	nop
	lw	t4,288(sp)
	seqz	t4,t4
	sw	t4,308(sp)
	lw	a0,308(sp)
	bne	a0,zero,.L26
	li	a0,75
	sw	a0,312(sp)
	lw	a0,312(sp)
	call	putch
	la	a0,one
	lw	a0,0(a0)
	bne	a0,zero,.L26
.L26:
	nop
	li	a0,10
	sw	a0,316(sp)
	lw	a0,316(sp)
	call	putch
	li	a0,0
	sw	a0,320(sp)
	lw	a0,320(sp)
	lw	ra,0(sp)
	addi	sp,sp,324
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
