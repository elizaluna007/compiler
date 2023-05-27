	.data
a:
	.word	7
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
	addi	sp,sp,-20
	sw	ra,0(sp)
	la	t3,a
	lw	t3,0(t3)
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,1
	sw	t3,8(sp)
	lw	t4,8(sp)
	lw	t5,4(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L0
	li	a0,1
	bne	a0,zero,.L1
.L0:
	lw	t4,8(sp)
	lw	t3,16(sp)
	addi	t3,t4,1
	sw	t3,16(sp)
	lw	t3,16(sp)
	sw	t3,8(sp)
	li	a0,1
	lw	ra,0(sp)
	addi	sp,sp,20
	jr	ra
	li	a0,1
	bne	a0,zero,
.L1:
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,20
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-40
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
.L2:
	lw	t4,8(sp)
	li	t5,100
	slt	t3,t4,t5
	sw	t3,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L3
	li	a0,1
	bne	a0,zero,.L6
.L3:
	call	func
	sw	a0,16(sp)
	lw	t3,20(sp)
	li	t3,1
	sw	t3,20(sp)
	lw	t4,16(sp)
	lw	t5,20(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,24(sp)
	lw	a0,24(sp)
	bne	a0,zero,.L4
	li	a0,1
	bne	a0,zero,.L5
.L4:
	lw	t4,4(sp)
	lw	t3,28(sp)
	addi	t3,t4,1
	sw	t3,28(sp)
	lw	t3,28(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L5
.L5:
	lw	t4,8(sp)
	lw	t3,32(sp)
	addi	t3,t4,1
	sw	t3,32(sp)
	lw	t3,32(sp)
	sw	t3,8(sp)
	li	a0,1
	bne	a0,zero,.L2
.L6:
	lw	t4,4(sp)
	li	t5,100
	slt	t3,t4,t5
	sw	t3,36(sp)
	lw	a0,36(sp)
	bne	a0,zero,.L7
	li	a0,1
	bne	a0,zero,.L8
.L7:
	li	a0,1
	call	putint
	li	a0,1
	bne	a0,zero,.L9
.L8:
	li	a0,0
	call	putint
.L9:
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,40
	jr	ra
