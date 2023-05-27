	.data
a:
	.word	0
b:
	.word	0
d:
	.word	0
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	set_a
	.type	set_a, @function
set_a:
	addi	sp,sp,-8
	sw	ra,0(sp)
	sw	a0,4(sp)
	lw	t3,4(sp)
	la	t4,a
	sw	t3,0(t4)
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
	lw	t3,4(sp)
	la	t4,b
	sw	t3,0(t4)
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
	lw	t3,4(sp)
	la	t4,d
	sw	t3,0(t4)
	la	a0,d
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-252
	sw	ra,0(sp)
	call	global
	li	t4,2
	la	t3,a
	sw	t4,0(t3)
	li	t4,3
	la	t3,b
	sw	t4,0(t3)
	li	a0,0
	call	set_a
	sw	a0,4(sp)
	lw	t4,4(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,8(sp)
	lw	a0,8(sp)
	bne	a0,zero,.L0
	li	a0,1
	bne	a0,zero,.L1
.L0:
	li	a0,1
	call	set_b
	sw	a0,12(sp)
	lw	t4,4(sp)
	snez	t4,t4
	lw	t5,12(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,8(sp)
.L1:
	lw	a0,8(sp)
	bne	a0,zero,.L2
	li	a0,1
	bne	a0,zero,.L3
.L2:
	li	a0,1
	bne	a0,zero,.L3
.L3:
	la	a0,a
	lw	a0,0(a0)
	call	putint
	li	a0,32
	call	putch
	la	a0,b
	lw	a0,0(a0)
	call	putint
	li	a0,32
	call	putch
	li	t4,2
	la	t3,a
	sw	t4,0(t3)
	li	t4,3
	la	t3,b
	sw	t4,0(t3)
	li	a0,0
	call	set_a
	sw	a0,16(sp)
	lw	t4,16(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L4
	li	a0,1
	bne	a0,zero,.L5
.L4:
	li	a0,1
	call	set_b
	sw	a0,24(sp)
	lw	t4,16(sp)
	snez	t4,t4
	lw	t5,24(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,20(sp)
.L5:
	lw	a0,20(sp)
	bne	a0,zero,.L6
	li	a0,1
	bne	a0,zero,.L7
.L6:
	li	a0,1
	bne	a0,zero,.L7
.L7:
	la	a0,a
	lw	a0,0(a0)
	call	putint
	li	a0,32
	call	putch
	la	a0,b
	lw	a0,0(a0)
	call	putint
	li	a0,10
	call	putch
	lw	t3,28(sp)
	li	t3,1
	sw	t3,28(sp)
	li	t4,2
	la	t3,d
	sw	t4,0(t3)
	lw	t4,28(sp)
	li	t5,1
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,32(sp)
	lw	t4,32(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,36(sp)
	lw	a0,36(sp)
	bne	a0,zero,.L8
	li	a0,1
	bne	a0,zero,.L9
.L8:
	li	a0,3
	call	set_d
	sw	a0,40(sp)
	lw	t4,32(sp)
	snez	t4,t4
	lw	t5,40(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,36(sp)
.L9:
	lw	a0,36(sp)
	bne	a0,zero,.L10
	li	a0,1
	bne	a0,zero,.L11
.L10:
	li	a0,1
	bne	a0,zero,.L11
.L11:
	la	a0,d
	lw	a0,0(a0)
	call	putint
	li	a0,32
	call	putch
	lw	t4,28(sp)
	li	t5,1
	slt	t0,t4,t5
	sub	t1,t4,t5
	seqz	t1,t1
	or	t3,t0,t1
	sw	t3,44(sp)
	lw	t4,44(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,48(sp)
	lw	a0,48(sp)
	bne	a0,zero,.L12
	li	a0,4
	call	set_d
	sw	a0,52(sp)
	lw	t4,44(sp)
	snez	t4,t4
	lw	t5,52(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,48(sp)
.L12:
	lw	a0,48(sp)
	bne	a0,zero,.L13
	li	a0,1
	bne	a0,zero,.L14
.L13:
	li	a0,1
	bne	a0,zero,.L14
.L14:
	la	a0,d
	lw	a0,0(a0)
	call	putint
	li	a0,10
	call	putch
	li	t4,16
	li	t5,0
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,56(sp)
	lw	a0,56(sp)
	bne	a0,zero,.L15
	li	a0,1
	bne	a0,zero,.L16
.L15:
	li	a0,65
	call	putch
	li	a0,1
	bne	a0,zero,.L16
.L16:
	lw	t3,60(sp)
	li	t3,6
	sw	t3,60(sp)
	lw	t3,64(sp)
	li	t3,3
	sw	t3,64(sp)
	lw	t4,60(sp)
	lw	t5,64(sp)
	lw	t3,68(sp)
	mul	t3,t4,t5
	sw	t3,68(sp)
	lw	t3,72(sp)
	li	t3,36
	sw	t3,72(sp)
	li	t4,36
	lw	t5,68(sp)
	lw	t3,76(sp)
	sub	t3,t4,t5
	sw	t3,76(sp)
	lw	t3,80(sp)
	li	t3,18
	sw	t3,80(sp)
	lw	t4,80(sp)
	lw	t5,76(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,84(sp)
	lw	a0,84(sp)
	bne	a0,zero,.L17
	li	a0,1
	bne	a0,zero,.L18
.L17:
	li	a0,66
	call	putch
	li	a0,1
	bne	a0,zero,.L18
.L18:
	li	t4,1
	li	t5,8
	slt	t3,t4,t5
	sw	t3,88(sp)
	lw	t3,92(sp)
	li	t3,7
	sw	t3,92(sp)
	lw	t3,96(sp)
	li	t3,2
	sw	t3,96(sp)
	lw	t4,92(sp)
	lw	t5,96(sp)
	lw	t3,100(sp)
	rem	t3,t4,t5
	sw	t3,100(sp)
	lw	t4,88(sp)
	lw	t5,100(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,104(sp)
	lw	a0,104(sp)
	bne	a0,zero,.L19
	li	a0,1
	bne	a0,zero,.L20
.L19:
	li	a0,67
	call	putch
	li	a0,1
	bne	a0,zero,.L20
.L20:
	li	t4,3
	li	t5,4
	slt	t3,t5,t4
	sw	t3,108(sp)
	lw	t3,112(sp)
	li	t3,0
	sw	t3,112(sp)
	lw	t4,108(sp)
	lw	t5,112(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,116(sp)
	lw	a0,116(sp)
	bne	a0,zero,.L21
	li	a0,1
	bne	a0,zero,.L22
.L21:
	li	a0,68
	call	putch
	li	a0,1
	bne	a0,zero,.L22
.L22:
	li	t4,102
	li	t5,63
	slt	t0,t4,t5
	sub	t1,t4,t5
	seqz	t1,t1
	or	t3,t0,t1
	sw	t3,120(sp)
	lw	t3,124(sp)
	li	t3,1
	sw	t3,124(sp)
	lw	t4,124(sp)
	lw	t5,120(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,128(sp)
	lw	a0,128(sp)
	bne	a0,zero,.L23
	li	a0,1
	bne	a0,zero,.L24
.L23:
	li	a0,69
	call	putch
	li	a0,1
	bne	a0,zero,.L24
.L24:
	li	t4,0
	seqz	t4,t4
	sw	t4,132(sp)
	lw	t3,136(sp)
	li	t3,0
	sw	t3,136(sp)
	lw	t4,136(sp)
	lw	t5,132(sp)
	lw	t3,140(sp)
	sub	t3,t4,t5
	sw	t3,140(sp)
	lw	t3,144(sp)
	li	t3,-1
	sw	t3,144(sp)
	lw	t4,144(sp)
	lw	t5,140(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,148(sp)
	lw	a0,148(sp)
	bne	a0,zero,.L25
	li	a0,1
	bne	a0,zero,.L26
.L25:
	li	a0,70
	call	putch
	li	a0,1
	bne	a0,zero,.L26
.L26:
	li	a0,10
	call	putch
	lw	t3,152(sp)
	li	t3,0
	sw	t3,152(sp)
	lw	t3,156(sp)
	li	t3,1
	sw	t3,156(sp)
	lw	t3,160(sp)
	li	t3,2
	sw	t3,160(sp)
	lw	t3,164(sp)
	li	t3,3
	sw	t3,164(sp)
	lw	t3,168(sp)
	li	t3,4
	sw	t3,168(sp)
.L27:
	lw	t4,152(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,172(sp)
	lw	a0,172(sp)
	bne	a0,zero,.L28
	li	a0,1
	bne	a0,zero,.L29
.L28:
	lw	t4,152(sp)
	snez	t4,t4
	lw	t5,156(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,172(sp)
.L29:
	lw	a0,172(sp)
	bne	a0,zero,.L30
	li	a0,1
	bne	a0,zero,.L31
.L30:
	li	a0,32
	call	putch
	li	a0,1
	bne	a0,zero,.L27
.L31:
	lw	t4,152(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,176(sp)
	lw	a0,176(sp)
	bne	a0,zero,.L32
	lw	t4,152(sp)
	snez	t4,t4
	lw	t5,156(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,176(sp)
.L32:
	lw	a0,176(sp)
	bne	a0,zero,.L33
	li	a0,1
	bne	a0,zero,.L34
.L33:
	li	a0,67
	call	putch
	li	a0,1
	bne	a0,zero,.L34
.L34:
	lw	t4,152(sp)
	lw	t5,156(sp)
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,180(sp)
	lw	t4,180(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,184(sp)
	lw	a0,184(sp)
	bne	a0,zero,.L35
	lw	t4,156(sp)
	lw	t5,152(sp)
	slt	t0,t4,t5
	sub	t1,t4,t5
	seqz	t1,t1
	or	t3,t0,t1
	sw	t3,188(sp)
	lw	t4,180(sp)
	snez	t4,t4
	lw	t5,188(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,184(sp)
.L35:
	lw	a0,184(sp)
	bne	a0,zero,.L36
	li	a0,1
	bne	a0,zero,.L37
.L36:
	li	a0,72
	call	putch
	li	a0,1
	bne	a0,zero,.L37
.L37:
	lw	t4,160(sp)
	lw	t5,156(sp)
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,192(sp)
	lw	t4,192(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,196(sp)
	lw	a0,196(sp)
	bne	a0,zero,.L38
	li	a0,1
	bne	a0,zero,.L39
.L38:
	lw	t4,168(sp)
	lw	t5,164(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,200(sp)
	lw	t4,192(sp)
	snez	t4,t4
	lw	t5,200(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,196(sp)
.L39:
	lw	a0,196(sp)
	bne	a0,zero,.L40
	li	a0,1
	bne	a0,zero,.L41
.L40:
	li	a0,73
	call	putch
	li	a0,1
	bne	a0,zero,.L41
.L41:
	lw	t4,156(sp)
	seqz	t4,t4
	sw	t4,204(sp)
	lw	t4,152(sp)
	lw	t5,204(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,208(sp)
	lw	t4,208(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,212(sp)
	lw	a0,212(sp)
	bne	a0,zero,.L42
	li	a0,1
	bne	a0,zero,.L43
.L42:
	lw	t4,164(sp)
	lw	t5,164(sp)
	slt	t3,t4,t5
	sw	t3,216(sp)
	lw	t4,208(sp)
	snez	t4,t4
	lw	t5,216(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,212(sp)
.L43:
	lw	t4,212(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,220(sp)
	lw	a0,220(sp)
	bne	a0,zero,.L44
	lw	t4,168(sp)
	lw	t5,168(sp)
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,224(sp)
	lw	t4,212(sp)
	snez	t4,t4
	lw	t5,224(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,220(sp)
.L44:
	lw	a0,220(sp)
	bne	a0,zero,.L45
	li	a0,1
	bne	a0,zero,.L46
.L45:
	li	a0,74
	call	putch
	li	a0,1
	bne	a0,zero,.L46
.L46:
	lw	t4,156(sp)
	seqz	t4,t4
	sw	t4,228(sp)
	lw	t4,152(sp)
	lw	t5,228(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,232(sp)
	lw	t4,232(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,236(sp)
	lw	a0,236(sp)
	bne	a0,zero,.L49
	lw	t4,164(sp)
	lw	t5,164(sp)
	slt	t3,t4,t5
	sw	t3,240(sp)
	lw	t4,240(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,244(sp)
	lw	a0,244(sp)
	bne	a0,zero,.L47
	li	a0,1
	bne	a0,zero,.L48
.L47:
	lw	t4,168(sp)
	lw	t5,168(sp)
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,248(sp)
	lw	t4,240(sp)
	snez	t4,t4
	lw	t5,248(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,244(sp)
.L48:
	lw	t4,232(sp)
	snez	t4,t4
	lw	t5,244(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,236(sp)
.L49:
	lw	a0,236(sp)
	bne	a0,zero,.L50
	li	a0,1
	bne	a0,zero,.L51
.L50:
	li	a0,75
	call	putch
	li	a0,1
	bne	a0,zero,.L51
.L51:
	li	a0,10
	call	putch
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,252
	jr	ra
