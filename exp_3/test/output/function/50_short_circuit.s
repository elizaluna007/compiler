	.text
	.comm	g,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-8
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	func
	.type	func, @function
func:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	putint
	la	a0,g
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
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
	call	getint
	call	func
	call	getint
	call	func
	call	getint
	call	func
	call	getint
	call	func
	call	func
	call	func
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
