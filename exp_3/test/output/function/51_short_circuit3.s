	.text
	.comm	a,4,4
	.comm	b,4,4
	.comm	d,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	set_a
	.type	set_a, @function
set_a:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,a
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	set_b
	.type	set_b, @function
set_b:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,b
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	set_d
	.type	set_d, @function
set_d:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,d
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	set_a
	call	set_b
	call	putint
	call	putch
	call	putint
	call	putch
	call	set_a
	call	set_b
	call	putint
	call	putch
	call	putint
	call	putch
	call	set_d
	call	putint
	call	putch
	call	set_d
	call	putint
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
