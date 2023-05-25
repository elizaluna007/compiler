	.text
	.comm	ascii_0,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-8
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,48
	sw	t3,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	my_getint
	.type	my_getint, @function
my_getint:
	addi	sp,sp,-16
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	call	getch
	call	getch
	lw	t3,12(sp)
	li	t3,10
	sw	t3,12(sp)
	la	a0,sum
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,16
	jr	ra
	.global	my_putint
	.type	my_putint, @function
my_putint:
	addi	sp,sp,-24
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,16
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,10
	sw	t3,16(sp)
	lw	t3,20(sp)
	li	t3,10
	sw	t3,20(sp)
	call	putch
	lw	ra,0(sp)
	addi	sp,sp,24
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	my_getint
	la	a0,t43
	lw	a0,0(a0)
	call	my_getint
	la	a0,t45
	lw	a0,0(a0)
	call	my_putint
	call	putch
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
