	.data
t0:
	.word	0
t1:
	.word	0
a:
	.word	0
b:
	.word	1
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-8
	sw	ra,0(sp)
	la	a0,t0
	lw	t4,0(a0)
	lw	t3,4(sp)
	addi	t3,t4,-1
	la	t4,t1
	sw	t3,0(t4)
	la	t3,t1
	lw	t3,0(t3)
	la	t4,a
	sw	t3,0(t4)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	inc_a
	.type	inc_a, @function
inc_a:
	addi	sp,sp,-12
	sw	ra,0(sp)
	la	t3,a
	lw	t3,0(t3)
	sw	t3,4(sp)
	lw	t4,4(sp)
	lw	t3,8(sp)
	addi	t3,t4,1
	sw	t3,8(sp)
	lw	t3,8(sp)
	sw	t3,4(sp)
	lw	t3,4(sp)
	la	t4,a
	sw	t3,0(t4)
	la	a0,a
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-84
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,5
	sw	t3,4(sp)
.L0:
	lw	t4,4(sp)
	li	t5,0
	slt	t3,t4,t5
	xori	t3,t3,1
	sw	t3,8(sp)
	lw	a0,8(sp)
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L14
.L1:
	call	inc_a
	sw	a0,12(sp)
	lw	t4,12(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,16(sp)
	lw	a0,16(sp)
	bne	a0,zero,.L2
	li	a0,1
	bne	a0,zero,.L5
.L2:
	call	inc_a
	sw	a0,20(sp)
	lw	t4,20(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,24(sp)
	lw	a0,24(sp)
	bne	a0,zero,.L3
	li	a0,1
	bne	a0,zero,.L4
.L3:
	call	inc_a
	sw	a0,28(sp)
	lw	t4,20(sp)
	snez	t4,t4
	lw	t5,28(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,24(sp)
.L4:
	lw	t4,12(sp)
	snez	t4,t4
	lw	t5,24(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,16(sp)
.L5:
	lw	a0,16(sp)
	bne	a0,zero,.L6
	li	a0,1
	bne	a0,zero,.L7
.L6:
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
	li	a0,1
	bne	a0,zero,.L7
.L7:
	call	inc_a
	sw	a0,32(sp)
	lw	t4,32(sp)
	li	t5,14
	slt	t3,t4,t5
	sw	t3,36(sp)
	lw	t4,36(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,40(sp)
	lw	a0,40(sp)
	bne	a0,zero,.L10
	call	inc_a
	sw	a0,44(sp)
	lw	t4,44(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,48(sp)
	lw	a0,48(sp)
	bne	a0,zero,.L8
	li	a0,1
	bne	a0,zero,.L9
.L8:
	call	inc_a
	sw	a0,52(sp)
	call	inc_a
	sw	a0,56(sp)
	lw	t4,52(sp)
	lw	t5,56(sp)
	lw	t3,60(sp)
	sub	t3,t4,t5
	sw	t3,60(sp)
	lw	t4,60(sp)
	lw	t3,64(sp)
	addi	t3,t4,1
	sw	t3,64(sp)
	lw	t4,44(sp)
	snez	t4,t4
	lw	t5,64(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,48(sp)
.L9:
	lw	t4,36(sp)
	snez	t4,t4
	lw	t5,48(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,40(sp)
.L10:
	lw	a0,40(sp)
	bne	a0,zero,.L11
	li	a0,1
	bne	a0,zero,.L12
.L11:
	la	a0,a
	lw	a0,0(a0)
	call	putint
	li	a0,10
	call	putch
	lw	t3,68(sp)
	li	t3,2
	sw	t3,68(sp)
	la	t4,b
	lw	t4,0(t4)
	lw	t5,68(sp)
	lw	t3,72(sp)
	mul	t3,t4,t5
	sw	t3,72(sp)
	lw	t3,72(sp)
	la	t4,b
	sw	t3,0(t4)
	li	a0,1
	bne	a0,zero,.L13
.L12:
	call	inc_a
	sw	a0,76(sp)
.L13:
	lw	t4,4(sp)
	lw	t3,80(sp)
	addi	t3,t4,-1
	sw	t3,80(sp)
	lw	t3,80(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L0
.L14:
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
	la	a0,a
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,84
	jr	ra
