	.text
	.comm	c,4,4
	.comm	chas,40000,4
	.comm	chat,4,4
	.comm	get,40000,4
	.comm	get2,40000,4
	.comm	i,4,4
	.comm	ii,4,4
	.comm	ints,40000,4
	.comm	intt,4,4
	.comm	t1,4,4
	.comm	t10004,4,4
	.comm	t20007,4,4
	.comm	t30010,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	isdigit
	.type	isdigit, @function
isdigit:
	addi	sp,sp,-12
	sw	ra,0(sp)
	lw	a0,4(sp)
	li	a0,1
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,0
	jr	ra
	lw	a0,8(sp)
	li	a0,0
	sw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	power
	.type	power, @function
power:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,result
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	getstr
	.type	getstr, @function
getstr:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	getch
	call	getch
	la	a0,length
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	intpush
	.type	intpush, @function
intpush:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	chapush
	.type	chapush, @function
chapush:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	intpop
	.type	intpop, @function
intpop:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,t40031
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	chapop
	.type	chapop, @function
chapop:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,t40034
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	intadd
	.type	intadd, @function
intadd:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	find
	.type	find, @function
find:
	addi	sp,sp,-12
	sw	ra,0(sp)
	call	chapop
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,0
	jr	ra
	lw	a0,8(sp)
	li	a0,1
	sw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	getstr
	call	isdigit
	call	chapush
	call	chapush
	call	chapop
	call	chapop
	call	find
	call	chapush
	call	find
	call	chapush
	call	find
	call	chapush
	call	find
	call	chapush
	call	find
	call	chapush
	call	chapop
	call	intpop
	call	intpop
	call	power
	call	intpush
	call	intpush
	call	intadd
	call	putint
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
