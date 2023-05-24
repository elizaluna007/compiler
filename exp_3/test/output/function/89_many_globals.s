	.text
	.comm	a0,4,4
	.comm	a1,4,4
	.comm	a10,4,4
	.comm	a11,4,4
	.comm	a12,4,4
	.comm	a13,4,4
	.comm	a14,4,4
	.comm	a15,4,4
	.comm	a16,4,4
	.comm	a17,4,4
	.comm	a18,4,4
	.comm	a19,4,4
	.comm	a2,4,4
	.comm	a20,4,4
	.comm	a21,4,4
	.comm	a22,4,4
	.comm	a23,4,4
	.comm	a24,4,4
	.comm	a25,4,4
	.comm	a26,4,4
	.comm	a27,4,4
	.comm	a28,4,4
	.comm	a29,4,4
	.comm	a3,4,4
	.comm	a30,4,4
	.comm	a31,4,4
	.comm	a32,4,4
	.comm	a33,4,4
	.comm	a34,4,4
	.comm	a35,4,4
	.comm	a36,4,4
	.comm	a37,4,4
	.comm	a38,4,4
	.comm	a39,4,4
	.comm	a4,4,4
	.comm	a5,4,4
	.comm	a6,4,4
	.comm	a7,4,4
	.comm	a8,4,4
	.comm	a9,4,4
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-4
	sw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	testParam8
	.type	testParam8, @function
testParam8:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,t6
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	testParam16
	.type	testParam16, @function
testParam16:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,t21
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	testParam32
	.type	testParam32, @function
testParam32:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,t52
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	call	testParam8
	call	putint
	call	testParam16
	call	putint
	call	testParam32
	call	putint
	lw	a0,4(sp)
	li	a0,0
	sw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
