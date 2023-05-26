	.data
a:
	.word	0
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	func
	.type	func, @function
func:
	addi	sp,sp,-12
	sw	ra,0(sp)
	sw	a0,4(sp)
	lw	t4,4(sp)
	lw	t3,8(sp)
	addi	t3,t4,-1
	sw	t3,8(sp)
	lw	t3,8(sp)
	sw	t3,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-12
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	li	t4,10
	la	t3,a
	sw	t4,0(t3)
	lw	a0,a
	call	func
	sw	a0,8(sp)
	lw	t3,8(sp)
	sw	t3,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
