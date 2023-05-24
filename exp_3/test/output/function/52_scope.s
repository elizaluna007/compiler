	.text
	.comm	a,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	func
	.type	func, @function
func:
	addi	sp,sp,-12
	sw	ra,0(sp)
	lw	a0,4(sp)
	li	a0,1
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,0
	jr	ra
	lw	a0,8(sp)
	li	a0,0
	sw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	func
	call	putint
	call	putint
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
