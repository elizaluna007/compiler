	.data
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-44
	sw	ra,0(sp)
	lw	ra,0(sp)
	jr	ra
	.global	ifWhile
	.type	ifWhile, @function
ifWhile:
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
	li	t3,3
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,5
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,2
	sw	t3,16(sp)
	lw	t4,8(sp)
	lw	t3,20(sp)
	addi	t3,t4,2
	sw	t3,20(sp)
	lw	t3,20(sp)
	sw	t3,8(sp)
	lw	t4,8(sp)
	lw	t3,24(sp)
	addi	t3,t4,25
	sw	t3,24(sp)
	lw	t3,24(sp)
	sw	t3,8(sp)
	lw	t3,28(sp)
	li	t3,2
	sw	t3,28(sp)
	lw	t4,8(sp)
	lw	t5,28(sp)
	lw	t3,32(sp)
	mul	t3,t4,t5
	sw	t3,32(sp)
	lw	t3,32(sp)
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t3,36(sp)
	addi	t3,t4,1
	sw	t3,36(sp)
	lw	t3,36(sp)
	sw	t3,4(sp)
	lw	a0,8(sp)
	lw	ra,0(sp)
	jr	ra
	.global	main
	.type	main, @function
main:
	sw	ra,0(sp)
	call	global
	call	ifWhile
	sw	a0,40(sp)
	lw	a0,40(sp)
	lw	ra,0(sp)
	addi	sp,sp,44
	jr	ra
