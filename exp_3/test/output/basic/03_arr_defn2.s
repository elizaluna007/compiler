	.data
t1:
	.word	10
t3:
	.word	10
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-16
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,10
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,10
	sw	t3,12(sp)
	lw	ra,0(sp)
	addi	sp,sp,16
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
