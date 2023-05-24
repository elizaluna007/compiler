	.text
	.global	global
	.type	global, @function
global:
	jr	ra
	.global	defn
	.type	defn, @function
defn:
	addi	sp,sp,-8
	sw	ra,0(sp)
	lw	a0,4(sp)
	li	a0,4
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	defn
	la	a0,a
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
