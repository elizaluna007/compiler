	.data
a:
	.word	0,0,0,0,0
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-16
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,5
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	lw	t3,12(sp)
	mul	t3,t4,t5
	sw	t3,12(sp)
	li	t4,0
	li	t3,0
	la	t5,a
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,1
	li	t3,0
	la	t5,a
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,2
	li	t3,0
	la	t5,a
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,3
	li	t3,0
	la	t5,a
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,4
	li	t3,0
	la	t5,a
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,0
	li	t3,0
	la	t5,a
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,1
	li	t3,1
	la	t5,a
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,2
	li	t3,2
	la	t5,a
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,3
	li	t3,3
	la	t5,a
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,4
	li	t3,4
	la	t5,a
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	lw	ra,0(sp)
	addi	sp,sp,16
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-12
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,4
	sw	t3,4(sp)
	lw	t4,4(sp)
	la	t3,a
	slli	t4,t4,2
	add	t4,t4,t3
	lw	t4,0(t4)
	sw	t4,8(sp)
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,12
	jr	ra
