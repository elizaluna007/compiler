	.data
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
	.global	doubleWhile
	.type	doubleWhile, @function
doubleWhile:
	addi	sp,sp,-32
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,4(sp)
	li	t3,5
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,8(sp)
	li	t3,7
	sw	t3,8(sp)
.L0:
	lw	t4,4(sp)
	li	t5,100
	slt	t3,t4,t5
	sw	t3,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L5
.L1:
	lw	t4,4(sp)
	lw	t3,16(sp)
	addi	t3,t4,30
	sw	t3,16(sp)
	lw	t3,16(sp)
	sw	t3,4(sp)
.L2:
	lw	t4,8(sp)
	li	t5,100
	slt	t3,t4,t5
	sw	t3,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L3
	li	a0,1
	bne	a0,zero,.L4
.L3:
	lw	t4,8(sp)
	lw	t3,24(sp)
	addi	t3,t4,6
	sw	t3,24(sp)
	lw	t3,24(sp)
	sw	t3,8(sp)
	li	a0,1
	bne	a0,zero,.L2
.L4:
	lw	t4,8(sp)
	lw	t3,28(sp)
	addi	t3,t4,-100
	sw	t3,28(sp)
	lw	t3,28(sp)
	sw	t3,8(sp)
	li	a0,1
	bne	a0,zero,.L0
.L5:
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,32
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	doubleWhile
	sw	a0,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
