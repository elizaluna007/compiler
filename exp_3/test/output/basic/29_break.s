	.data
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-24
	sw	ra,0(sp)
	lw	ra,0(sp)
	jr	ra
	.global	main
	.type	main, @function
main:
	sw	ra,0(sp)
	call	global
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
	li	t3,50
	sw	t3,12(sp)
	lw	t4,8(sp)
	lw	t5,4(sp)
	lw	t3,16(sp)
	add	t3,t4,t5
	sw	t3,16(sp)
	lw	t3,16(sp)
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t3,20(sp)
	addi	t3,t4,1
	sw	t3,20(sp)
	lw	t3,20(sp)
	sw	t3,4(sp)
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,24
	jr	ra
