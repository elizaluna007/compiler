	.text
	.comm	zero,4,4
	.comm	fzero,4,4
	.comm	one,4,4
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-24
	sw	ra,0(sp)
	call	global
	li	a0,10
	sw	a0,4(sp)
	li	a0,30
	sw	a0,8(sp)
	lw	t4,4(sp)
	addi	t3,t4,5
	sw	t3,12(sp)
	lw	t4,12(sp)
	lw	t5,8(sp)
	add	t3,t4,t5
	sw	t3,16(sp)
	lw	t4,16(sp)
	addi	t3,t4,-5
	sw	t3,20(sp)
	lw	a0,20(sp)
	lw	ra,0(sp)
	addi	sp,sp,24
	jr	ra
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	li	a0,0
	la	a1,zero
	sw	a0,0(a1)
	la	a0,FLOAT0
	flw	fa0,0(a0)
	la	a1,fzero
	fsw	fa0,0(a1)
	li	a0,1
	la	a1,one
	sw	a0,0(a1)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
FLOAT0:
	.word	0
