	.data
a:
	.word	0
b:
	.word	0
c:
	.word	0
d:
	.word	0
e:
	.word	0
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-24
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
	lw	t3,16(sp)
	li	t3,0
	sw	t3,16(sp)
	lw	t3,20(sp)
	li	t3,0
	sw	t3,20(sp)
	lw	ra,0(sp)
	addi	sp,sp,24
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-24
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	la	t4,e
	lw	t4,0(t4)
	la	t5,d
	lw	t5,0(t5)
	add	t3,t4,t5
	sw	t3,8(sp)
	la	t4,a
	lw	t4,0(t4)
	la	t5,b
	lw	t5,0(t5)
	add	t3,t4,t5
	sw	t3,12(sp)
	lw	t4,12(sp)
	la	t5,c
	lw	t5,0(t5)
	add	t3,t4,t5
	sw	t3,16(sp)
	la	t4,d
	lw	t4,0(t4)
	la	t5,e
	lw	t5,0(t5)
	add	t3,t4,t5
	sw	t3,20(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,24
	jr	ra
