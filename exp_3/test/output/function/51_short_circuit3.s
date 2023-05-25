	.data
a:
	.word	0
b:
	.word	0
d:
	.word	0
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-16
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	lw	ra,0(sp)
	addi	sp,sp,16
	jr	ra
	.global	set_a
	.type	set_a, @function
set_a:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,a
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	set_b
	.type	set_b, @function
set_b:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,b
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	set_d
	.type	set_d, @function
set_d:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,d
	lw	a0,0(a0)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-68
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
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	call	set_d
	call	putint
	call	putch
	call	set_d
	call	putint
	call	putch
	call	putch
	lw	t3,8(sp)
	li	t3,6
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,3
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,36
	sw	t3,16(sp)
	lw	t3,20(sp)
	li	t3,18
	sw	t3,20(sp)
	call	putch
	lw	t3,24(sp)
	li	t3,7
	sw	t3,24(sp)
	lw	t3,28(sp)
	li	t3,2
	sw	t3,28(sp)
	call	putch
	lw	t3,32(sp)
	li	t3,0
	sw	t3,32(sp)
	call	putch
	lw	t3,36(sp)
	li	t3,1
	sw	t3,36(sp)
	call	putch
	lw	t3,40(sp)
	li	t3,0
	sw	t3,40(sp)
	lw	t3,44(sp)
	li	t3,-1
	sw	t3,44(sp)
	call	putch
	call	putch
	lw	t3,48(sp)
	li	t3,0
	sw	t3,48(sp)
	lw	t3,52(sp)
	li	t3,1
	sw	t3,52(sp)
	lw	t3,56(sp)
	li	t3,2
	sw	t3,56(sp)
	lw	t3,60(sp)
	li	t3,3
	sw	t3,60(sp)
	lw	t3,64(sp)
	li	t3,4
	sw	t3,64(sp)
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	call	putch
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,68
	jr	ra
