	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,0(sp)
	call	global
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
	li	t3,0
	sw	t3,20(sp)
	lw	t3,24(sp)
	li	t3,0
	sw	t3,24(sp)
	lw	t3,28(sp)
	li	t3,0
	sw	t3,28(sp)
	call	putint
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,32
	jr	ra
