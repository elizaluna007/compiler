	.data
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-28
	sw	ra,0(sp)
	lw	ra,0(sp)
	jr	ra
	.global	ififElse
	.type	ififElse, @function
ififElse:
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
	li	t3,10
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,5
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,10
	sw	t3,16(sp)
	lw	t3,4(sp)
	li	t3,25
	sw	t3,4(sp)
	lw	t4,4(sp)
	lw	t3,20(sp)
	addi	t3,t4,15
	sw	t3,20(sp)
	lw	t3,20(sp)
	sw	t3,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	jr	ra
	.global	main
	.type	main, @function
main:
	sw	ra,0(sp)
	call	global
	call	ififElse
	sw	a0,24(sp)
	lw	a0,24(sp)
	lw	ra,0(sp)
	addi	sp,sp,28
	jr	ra
