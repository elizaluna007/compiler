	.text
	.global	global
	.type	global, @function
global:
	jr	ra
	.global	get_one
	.type	get_one, @function
get_one:
	addi	sp,sp,-8
	sw	ra,0(sp)
	lw	a0,4(sp)
	li	a0,1
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	deepWhileBr
	.type	deepWhileBr, @function
deepWhileBr:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	get_one
	la	a0,c
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	deepWhileBr
	call	putint
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
