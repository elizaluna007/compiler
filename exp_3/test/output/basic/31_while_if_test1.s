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
	.global	whileIf
	.type	whileIf, @function
whileIf:
	addi	sp,sp,-44
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
.L0:
	lw	t4,4(sp)
	li	t5,100
	slt	t3,t4,t5
	sw	t3,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L7
.L1:
	lw	t3,16(sp)
	li	t3,5
	sw	t3,16(sp)
	lw	t4,4(sp)
	lw	t5,16(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L2
	li	a0,1
	bne	a0,zero,.L3
.L2:
	lw	t3,8(sp)
	li	t3,25
	sw	t3,8(sp)
	li	a0,1
	bne	a0,zero,.L6
.L3:
	lw	t3,24(sp)
	li	t3,10
	sw	t3,24(sp)
	lw	t4,4(sp)
	lw	t5,24(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,28(sp)
	lw	a0,28(sp)
	bne	a0,zero,.L4
	li	a0,1
	bne	a0,zero,.L5
.L4:
	lw	t3,8(sp)
	li	t3,42
	sw	t3,8(sp)
	li	a0,1
	bne	a0,zero,.L6
.L5:
	lw	t3,32(sp)
	li	t3,2
	sw	t3,32(sp)
	lw	t4,4(sp)
	lw	t5,32(sp)
	lw	t3,36(sp)
	mul	t3,t4,t5
	sw	t3,36(sp)
	lw	t3,36(sp)
	sw	t3,8(sp)
.L6:
	lw	t4,4(sp)
	lw	t3,40(sp)
	addi	t3,t4,1
	sw	t3,40(sp)
	lw	t3,40(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L0
.L7:
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,44
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	whileIf
	sw	a0,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
