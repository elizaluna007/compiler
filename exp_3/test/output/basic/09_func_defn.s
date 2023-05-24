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
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,p
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	func
	la	a0,b
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
