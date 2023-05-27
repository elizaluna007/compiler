	.data
g:
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
	.global	func
	.type	func, @function
func:
	addi	sp,sp,-12
	sw	ra,0(sp)
	sw	a0,4(sp)
	la	t4,g
	lw	t4,0(t4)
	lw	t5,4(sp)
	lw	t3,8(sp)
	add	t3,t4,t5
	sw	t3,8(sp)
	lw	t3,8(sp)
	la	t4,g
	sw	t3,0(t4)
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
	addi	sp,sp,-88
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	call	getint
	sw	a0,8(sp)
	lw	t3,8(sp)
	sw	t3,4(sp)
	lw	t4,4(sp)
	li	t5,10
	slt	t3,t5,t4
	sw	t3,12(sp)
	lw	t4,12(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,16(sp)
	lw	a0,16(sp)
	bne	a0,zero,.L0
	li	a0,1
	bne	a0,zero,.L1
.L0:
	lw	a0,4(sp)
	call	func
	sw	a0,20(sp)
	lw	t4,12(sp)
	snez	t4,t4
	lw	t5,20(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,16(sp)
.L1:
	lw	a0,16(sp)
	bne	a0,zero,.L2
	li	a0,1
	bne	a0,zero,.L3
.L2:
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L4
.L3:
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
.L4:
	call	getint
	sw	a0,24(sp)
	lw	t3,24(sp)
	sw	t3,4(sp)
	lw	t4,4(sp)
	li	t5,11
	slt	t3,t5,t4
	sw	t3,28(sp)
	lw	t4,28(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,32(sp)
	lw	a0,32(sp)
	bne	a0,zero,.L5
	li	a0,1
	bne	a0,zero,.L6
.L5:
	lw	a0,4(sp)
	call	func
	sw	a0,36(sp)
	lw	t4,28(sp)
	snez	t4,t4
	lw	t5,36(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,32(sp)
.L6:
	lw	a0,32(sp)
	bne	a0,zero,.L7
	li	a0,1
	bne	a0,zero,.L8
.L7:
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L9
.L8:
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
.L9:
	call	getint
	sw	a0,40(sp)
	lw	t3,40(sp)
	sw	t3,4(sp)
	lw	t4,4(sp)
	li	t5,99
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
	bne	a0,zero,.L10
	lw	a0,4(sp)
	call	func
	sw	a0,52(sp)
	lw	t4,44(sp)
	snez	t4,t4
	lw	t5,52(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,48(sp)
.L10:
	lw	a0,48(sp)
	bne	a0,zero,.L11
	li	a0,1
	bne	a0,zero,.L12
.L11:
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L13
.L12:
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
.L13:
	call	getint
	sw	a0,56(sp)
	lw	t3,56(sp)
	sw	t3,4(sp)
	lw	t4,4(sp)
	li	t5,100
	slt	t0,t4,t5
	sub	t1,t4,t5
	seqz	t1,t1
	or	t3,t0,t1
	sw	t3,60(sp)
	lw	t4,60(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,64(sp)
	lw	a0,64(sp)
	bne	a0,zero,.L14
	lw	a0,4(sp)
	call	func
	sw	a0,68(sp)
	lw	t4,60(sp)
	snez	t4,t4
	lw	t5,68(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,64(sp)
.L14:
	lw	a0,64(sp)
	bne	a0,zero,.L15
	li	a0,1
	bne	a0,zero,.L16
.L15:
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L17
.L16:
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
.L17:
	li	a0,99
	call	func
	sw	a0,72(sp)
	lw	t4,72(sp)
	seqz	t4,t4
	sw	t4,76(sp)
	lw	t4,76(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,80(sp)
	lw	a0,80(sp)
	bne	a0,zero,.L18
	li	a0,1
	bne	a0,zero,.L19
.L18:
	li	a0,100
	call	func
	sw	a0,84(sp)
	lw	t4,76(sp)
	snez	t4,t4
	lw	t5,84(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,80(sp)
.L19:
	lw	a0,80(sp)
	bne	a0,zero,.L20
	li	a0,1
	bne	a0,zero,.L21
.L20:
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L22
.L21:
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
.L22:
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,88
	jr	ra
