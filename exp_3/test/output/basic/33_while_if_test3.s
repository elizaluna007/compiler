	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	deepWhileBr
	.type	deepWhileBr, @function
deepWhileBr:
	addi	sp,sp,-32
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
	li	t3,2
	sw	t3,16(sp)
	lw	t3,20(sp)
	li	t3,1
	sw	t3,20(sp)
	lw	t3,24(sp)
	li	t3,1
	sw	t3,24(sp)
	lw	t3,28(sp)
	li	t3,2
	sw	t3,28(sp)
	la	a0,c
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,32
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	call	deepWhileBr
	la	a0,t12
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
