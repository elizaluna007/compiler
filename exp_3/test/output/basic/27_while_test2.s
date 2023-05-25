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
	addi	sp,sp,-36
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,0
	sw	t3,16(sp)
	lw	t3,20(sp)
	li	t3,7
	sw	t3,20(sp)
	lw	t4,8(sp)
	lw	t5,16(sp)
	add	t3,t4,t5
	sw	t3,24(sp)
	lw	t4,4(sp)
	lw	t5,24(sp)
	add	t3,t4,t5
	sw	t3,28(sp)
	lw	t4,28(sp)
	lw	t5,12(sp)
	add	t3,t4,t5
	sw	t3,32(sp)
	lw	a0,32(sp)
	lw	ra,0(sp)
	addi	sp,sp,36
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	FourWhile
	la	a0,t15
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
