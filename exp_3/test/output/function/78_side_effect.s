	.data
t0:
	.word	0
b:
	.word	1
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-12
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,1
	sw	t3,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	inc_a
	.type	inc_a, @function
inc_a:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,a
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-12
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,5
	sw	t3,4(sp)
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
	lw	t3,8(sp)
	li	t3,2
	sw	t3,8(sp)
	call	inc_a
	call	putint
	call	putch
	call	putint
	call	putch
	la	a0,a
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
