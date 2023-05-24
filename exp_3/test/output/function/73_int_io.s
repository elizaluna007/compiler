	.text
	.comm	ascii_0,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	my_getint
	.type	my_getint, @function
my_getint:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	getch
	call	getch
	la	a0,sum
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	my_putint
	.type	my_putint, @function
my_putint:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	putch
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	my_getint
	call	my_getint
	call	my_putint
	call	putch
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
