	.text
	.comm	INF,4,4
	.comm	book,64,4
	.comm	dis,64,4
	.comm	e,1024,4
	.comm	m,4,4
	.comm	n,4,4
	.comm	t1,4,4
	.comm	t262,4,4
	.comm	t281,4,4
	.comm	t3,4,4
	.comm	v1,4,4
	.comm	v2,4,4
	.comm	w,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	Dijkstra
	.type	Dijkstra, @function
Dijkstra:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	getint
	call	getint
	call	getint
	call	getint
	call	getint
	call	Dijkstra
	call	putint
	call	putch
	call	putch
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
