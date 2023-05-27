	.data
t0:
	.word	0
t1:
	.word	0
N:
	.word	0
t3:
	.word	2
t4:
	.word	4
t6:
	.word	0
t7:
	.word	99
t8:
	.word	99
t10:
	.word	0
arr:
	.word	0,0,0,0,0,0,0
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-36
	sw	ra,0(sp)
	la	a0,t0
	lw	t4,0(a0)
	lw	t3,4(sp)
	addi	t3,t4,-1
	la	t4,t1
	sw	t3,0(t4)
	la	t3,t1
	lw	t3,0(t3)
	la	t4,N
	sw	t3,0(t4)
	lw	t3,8(sp)
	li	t3,1
	sw	t3,8(sp)
	la	t4,t3
	lw	t4,0(t4)
	la	t5,t4
	lw	t5,0(t5)
	lw	t3,12(sp)
	mul	t3,t4,t5
	sw	t3,12(sp)
	la	t4,N
	lw	t4,0(t4)
	lw	t5,12(sp)
	lw	t3,16(sp)
	add	t3,t4,t5
	la	t4,t6
	sw	t3,0(t4)
	la	t4,t7
	lw	t4,0(t4)
	la	t5,t8
	lw	t5,0(t5)
	lw	t3,20(sp)
	div	t3,t4,t5
	sw	t3,20(sp)
	la	t4,t6
	lw	t4,0(t4)
	lw	t5,20(sp)
	lw	t3,24(sp)
	sub	t3,t4,t5
	la	t4,t10
	sw	t3,0(t4)
	lw	t4,8(sp)
	la	t5,t10
	lw	t5,0(t5)
	lw	t3,28(sp)
	mul	t3,t4,t5
	sw	t3,28(sp)
	sw	t3,32(sp)
	li	t4,0
	li	t3,0
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,1
	li	t3,0
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,2
	li	t3,0
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,3
	li	t3,0
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,4
	li	t3,0
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,5
	li	t3,0
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,0
	li	t3,1
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,1
	li	t3,2
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,2
	li	t3,33
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,3
	li	t3,4
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,4
	li	t3,5
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	li	t4,5
	li	t3,6
	la	t5,arr
	slli	t4,t4,2
	add	t4,t4,t5
	sw	t3,0(t4)
	lw	ra,0(sp)
	addi	sp,sp,36
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-28
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
.L0:
	lw	t4,4(sp)
	li	t5,6
	slt	t3,t4,t5
	sw	t3,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L2
.L1:
	lw	t4,4(sp)
	la	t3,arr
	slli	t4,t4,2
	add	t4,t4,t3
	lw	t4,0(t4)
	sw	t4,16(sp)
	lw	t4,8(sp)
	lw	t5,16(sp)
	lw	t3,20(sp)
	add	t3,t4,t5
	sw	t3,20(sp)
	lw	t3,20(sp)
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t3,24(sp)
	addi	t3,t4,1
	sw	t3,24(sp)
	lw	t3,24(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L0
.L2:
	lw	a0,8(sp)
	lw	ra,0(sp)
	addi	sp,sp,28
	jr	ra
