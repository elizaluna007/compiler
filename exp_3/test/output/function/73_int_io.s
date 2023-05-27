	.data
ascii_0:
	.word	48
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
	.global	my_getint
	.type	my_getint, @function
my_getint:
	addi	sp,sp,-64
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
.L0:
	li	a0,1
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L6
.L1:
	call	getch
	sw	a0,12(sp)
	lw	t4,12(sp)
	la	t5,ascii_0
	lw	t5,0(t5)
	lw	t3,16(sp)
	sub	t3,t4,t5
	sw	t3,16(sp)
	lw	t3,16(sp)
	sw	t3,8(sp)
	lw	t4,8(sp)
	li	t5,0
	slt	t3,t4,t5
	sw	t3,20(sp)
	lw	t4,20(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,24(sp)
	lw	a0,24(sp)
	bne	a0,zero,.L2
	lw	t4,8(sp)
	li	t5,9
	slt	t3,t5,t4
	sw	t3,28(sp)
	lw	t4,20(sp)
	snez	t4,t4
	lw	t5,28(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,24(sp)
.L2:
	lw	a0,24(sp)
	bne	a0,zero,.L3
	li	a0,1
	bne	a0,zero,.L4
.L3:
	li	a0,1
	bne	a0,zero,.L5
.L4:
	li	a0,1
	bne	a0,zero,.L6
.L5:
	li	a0,1
	bne	a0,zero,.L0
.L6:
	lw	t3,8(sp)
	sw	t3,4(sp)
.L7:
	li	a0,1
	bne	a0,zero,.L8
	li	a0,1
	bne	a0,zero,.L14
.L8:
	call	getch
	sw	a0,32(sp)
	lw	t4,32(sp)
	la	t5,ascii_0
	lw	t5,0(t5)
	lw	t3,36(sp)
	sub	t3,t4,t5
	sw	t3,36(sp)
	lw	t3,36(sp)
	sw	t3,8(sp)
	lw	t4,8(sp)
	li	t5,0
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,40(sp)
	lw	t4,40(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,44(sp)
	lw	a0,44(sp)
	bne	a0,zero,.L9
	li	a0,1
	bne	a0,zero,.L10
.L9:
	lw	t4,8(sp)
	li	t5,9
	slt	t0,t4,t5
	sub	t1,t4,t5
	seqz	t1,t1
	or	t3,t0,t1
	sw	t3,48(sp)
	lw	t4,40(sp)
	snez	t4,t4
	lw	t5,48(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,44(sp)
.L10:
	lw	a0,44(sp)
	bne	a0,zero,.L11
	li	a0,1
	bne	a0,zero,.L12
.L11:
	lw	t3,52(sp)
	li	t3,10
	sw	t3,52(sp)
	lw	t4,4(sp)
	lw	t5,52(sp)
	lw	t3,56(sp)
	mul	t3,t4,t5
	sw	t3,56(sp)
	lw	t4,56(sp)
	lw	t5,8(sp)
	lw	t3,60(sp)
	add	t3,t4,t5
	sw	t3,60(sp)
	lw	t3,60(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L13
.L12:
	li	a0,1
	bne	a0,zero,.L14
.L13:
	li	a0,1
	bne	a0,zero,.L7
.L14:
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,64
	jr	ra
	.global	my_putint
	.type	my_putint, @function
my_putint:
	addi	sp,sp,-132
	sw	ra,0(sp)
	sw	a0,4(sp)
	lw	t3,8(sp)
	li	t3,1
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,16
	sw	t3,12(sp)
	lw	t4,8(sp)
	lw	t5,12(sp)
	lw	t3,16(sp)
	mul	t3,t4,t5
	sw	t3,16(sp)
	sw	t3,20(sp)
	lw	t3,24(sp)
	li	t3,0
	sw	t3,24(sp)
	lw	t3,28(sp)
	li	t3,0
	sw	t3,28(sp)
	lw	t3,32(sp)
	li	t3,0
	sw	t3,32(sp)
	lw	t3,36(sp)
	li	t3,0
	sw	t3,36(sp)
	lw	t3,40(sp)
	li	t3,0
	sw	t3,40(sp)
	lw	t3,44(sp)
	li	t3,0
	sw	t3,44(sp)
	lw	t3,48(sp)
	li	t3,0
	sw	t3,48(sp)
	lw	t3,52(sp)
	li	t3,0
	sw	t3,52(sp)
	lw	t3,56(sp)
	li	t3,0
	sw	t3,56(sp)
	lw	t3,60(sp)
	li	t3,0
	sw	t3,60(sp)
	lw	t3,64(sp)
	li	t3,0
	sw	t3,64(sp)
	lw	t3,68(sp)
	li	t3,0
	sw	t3,68(sp)
	lw	t3,72(sp)
	li	t3,0
	sw	t3,72(sp)
	lw	t3,76(sp)
	li	t3,0
	sw	t3,76(sp)
	lw	t3,80(sp)
	li	t3,0
	sw	t3,80(sp)
	lw	t3,84(sp)
	li	t3,0
	sw	t3,84(sp)
	lw	t3,88(sp)
	li	t3,0
	sw	t3,88(sp)
.L15:
	lw	t4,4(sp)
	li	t5,0
	slt	t3,t5,t4
	sw	t3,92(sp)
	lw	a0,92(sp)
	bne	a0,zero,.L16
	li	a0,1
	bne	a0,zero,.L17
.L16:
	lw	t3,96(sp)
	li	t3,10
	sw	t3,96(sp)
	lw	t4,4(sp)
	lw	t5,96(sp)
	lw	t3,100(sp)
	rem	t3,t4,t5
	sw	t3,100(sp)
	lw	t4,100(sp)
	la	t5,ascii_0
	lw	t5,0(t5)
	lw	t3,104(sp)
	add	t3,t4,t5
	sw	t3,104(sp)
	li	t3,0
	lw	t3,104(sp)
	sw	t3,24(sp)
	lw	t3,108(sp)
	li	t3,10
	sw	t3,108(sp)
	lw	t4,4(sp)
	lw	t5,108(sp)
	lw	t3,112(sp)
	div	t3,t4,t5
	sw	t3,112(sp)
	lw	t3,112(sp)
	sw	t3,4(sp)
	lw	t4,88(sp)
	lw	t3,116(sp)
	addi	t3,t4,1
	sw	t3,116(sp)
	lw	t3,116(sp)
	sw	t3,88(sp)
	li	a0,1
	bne	a0,zero,.L15
.L17:
	lw	t4,88(sp)
	li	t5,0
	slt	t3,t5,t4
	sw	t3,120(sp)
	lw	a0,120(sp)
	bne	a0,zero,.L18
	li	a0,1
	bne	a0,zero,.L19
.L18:
	lw	t4,88(sp)
	lw	t3,124(sp)
	addi	t3,t4,-1
	sw	t3,124(sp)
	lw	t3,124(sp)
	sw	t3,88(sp)
	lw	t4,88(sp)
	lw	t3,128(sp)
	lw	t3,24(sp)
	sw	t3,128(sp)
	lw	a0,128(sp)
	call	putch
	li	a0,1
	bne	a0,zero,.L17
.L19:
	lw	ra,0(sp)
	addi	sp,sp,132
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-28
	sw	ra,0(sp)
	call	global
	call	my_getint
	sw	a0,4(sp)
	lw	t3,4(sp)
	sw	t3,8(sp)
.L20:
	lw	t4,8(sp)
	li	t5,0
	slt	t3,t5,t4
	sw	t3,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L21
	li	a0,1
	bne	a0,zero,.L22
.L21:
	call	my_getint
	sw	a0,16(sp)
	lw	t3,16(sp)
	sw	t3,20(sp)
	lw	a0,20(sp)
	call	my_putint
	li	a0,10
	call	putch
	lw	t4,8(sp)
	lw	t3,24(sp)
	addi	t3,t4,-1
	sw	t3,24(sp)
	lw	t3,24(sp)
	sw	t3,8(sp)
	li	a0,1
	bne	a0,zero,.L20
.L22:
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,28
	jr	ra
