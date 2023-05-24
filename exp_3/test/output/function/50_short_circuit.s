	.text
	.comm	g,4,4
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
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	putint
	la	a0,g
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
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
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
