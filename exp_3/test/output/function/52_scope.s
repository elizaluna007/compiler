	.data
a:
	.word	7
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-8
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,7
	sw	t3,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	func
	.type	func, @function
func:
	addi	sp,sp,-8
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	li	a0,1
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-16
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	call	func
	lw	t3,12(sp)
	li	t3,1
	sw	t3,12(sp)
	call	putint
	call	putint
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,16
	jr	ra
