	.data
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-36
	sw	ra,0(sp)
	lw	ra,0(sp)
	jr	ra
	.global	whileIf
	.type	whileIf, @function
whileIf:
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
	lw	t3,12(sp)
	li	t3,5
	sw	t3,12(sp)
	lw	t3,8(sp)
	li	t3,25
	sw	t3,8(sp)
	lw	t3,16(sp)
	li	t3,10
	sw	t3,16(sp)
	lw	t3,8(sp)
	li	t3,42
	sw	t3,8(sp)
	lw	t3,20(sp)
	li	t3,2
	sw	t3,20(sp)
	lw	t4,4(sp)
	lw	t5,20(sp)
	lw	t3,24(sp)
	mul	t3,t4,t5
	sw	t3,24(sp)
	lw	t3,24(sp)
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t3,28(sp)
	addi	t3,t4,1
	sw	t3,28(sp)
	lw	t3,28(sp)
	sw	t3,4(sp)
	lw	a0,8(sp)
	lw	ra,0(sp)
	jr	ra
	.global	main
	.type	main, @function
main:
	sw	ra,0(sp)
	call	global
	call	whileIf
	sw	a0,32(sp)
	lw	a0,32(sp)
	lw	ra,0(sp)
	addi	sp,sp,36
	jr	ra
