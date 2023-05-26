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
	.global	FourWhile
	.type	FourWhile, @function
FourWhile:
	addi	sp,sp,-80
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
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	lw	t3,8(sp)
	li	t3,6
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,7
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,0
	sw	t3,16(sp)
	lw	t3,16(sp)
	li	t3,10
	sw	t3,16(sp)
.L0:
	lw	t4,4(sp)
	li	t5,20
	slt	t3,t4,t5
	sw	t3,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L11
.L1:
	lw	t4,4(sp)
	lw	t3,24(sp)
	addi	t3,t4,3
	sw	t3,24(sp)
	lw	t3,24(sp)
	sw	t3,4(sp)
.L2:
	lw	t4,8(sp)
	li	t5,10
	slt	t3,t4,t5
	sw	t3,28(sp)
	lw	a0,28(sp)
	bne	a0,zero,.L3
	li	a0,1
	bne	a0,zero,.L10
.L3:
	lw	t4,8(sp)
	lw	t3,32(sp)
	addi	t3,t4,1
	sw	t3,32(sp)
	lw	t3,32(sp)
	sw	t3,8(sp)
.L4:
	lw	t3,36(sp)
	li	t3,7
	sw	t3,36(sp)
	lw	t4,12(sp)
	lw	t5,36(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,40(sp)
	lw	a0,40(sp)
	bne	a0,zero,.L5
	li	a0,1
	bne	a0,zero,.L9
.L5:
	lw	t4,12(sp)
	lw	t3,44(sp)
	addi	t3,t4,-1
	sw	t3,44(sp)
	lw	t3,44(sp)
	sw	t3,12(sp)
.L6:
	lw	t4,16(sp)
	li	t5,20
	slt	t3,t4,t5
	sw	t3,48(sp)
	lw	a0,48(sp)
	bne	a0,zero,.L7
	li	a0,1
	bne	a0,zero,.L8
.L7:
	lw	t4,16(sp)
	lw	t3,52(sp)
	addi	t3,t4,3
	sw	t3,52(sp)
	lw	t3,52(sp)
	sw	t3,16(sp)
	li	a0,1
	bne	a0,zero,.L6
.L8:
	lw	t4,16(sp)
	lw	t3,56(sp)
	addi	t3,t4,-1
	sw	t3,56(sp)
	lw	t3,56(sp)
	sw	t3,16(sp)
	li	a0,1
	bne	a0,zero,.L4
.L9:
	lw	t4,12(sp)
	lw	t3,60(sp)
	addi	t3,t4,1
	sw	t3,60(sp)
	lw	t3,60(sp)
	sw	t3,12(sp)
	li	a0,1
	bne	a0,zero,.L2
.L10:
	lw	t4,8(sp)
	lw	t3,64(sp)
	addi	t3,t4,-2
	sw	t3,64(sp)
	lw	t3,64(sp)
	sw	t3,8(sp)
	li	a0,1
	bne	a0,zero,.L0
.L11:
	lw	t4,8(sp)
	lw	t5,16(sp)
	lw	t3,68(sp)
	add	t3,t4,t5
	sw	t3,68(sp)
	lw	t4,4(sp)
	lw	t5,68(sp)
	lw	t3,72(sp)
	add	t3,t4,t5
	sw	t3,72(sp)
	lw	t4,72(sp)
	lw	t5,12(sp)
	lw	t3,76(sp)
	add	t3,t4,t5
	sw	t3,76(sp)
	lw	a0,76(sp)
	lw	ra,0(sp)
	addi	sp,sp,80
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	FourWhile
	sw	a0,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
