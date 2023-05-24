	.text
	.comm	a,4,4
	.comm	b,4,4
	.comm	t0,4,4
	.comm	t1,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	inc_a
	.type	inc_a, @function
inc_a:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,a
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	inc_a
	call	inc_a
	call	inc_a
	call	putint
	call	putch
	call	putint
	call	putch
	call	inc_a
	call	inc_a
	call	inc_a
	call	inc_a
	call	putint
	call	putch
	call	inc_a
	call	putint
	call	putch
	call	putint
	call	putch
	la	a0,a
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
