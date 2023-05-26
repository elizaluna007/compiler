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
	addi	sp,sp,-4
	sw	ra,0(sp)
	lw	ra,0(sp)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-68
	sw	ra,0(sp)
	call	global
	li	t4,0
	la	t3,a
	sw	t4,0(t3)
	li	t4,1
	la	t3,b
	sw	t4,0(t3)
	li	t4,1
	la	t3,c
	sw	t4,0(t3)
	li	t4,1
	la	t3,d
	sw	t4,0(t3)
	li	t4,1
	la	t3,e
	sw	t4,0(t3)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t4,b
	lw	t5,c
	lw	t3,8(sp)
	mul	t3,t4,t5
	sw	t3,8(sp)
	lw	t4,a
	lw	t5,8(sp)
	lw	t3,12(sp)
	sub	t3,t4,t5
	sw	t3,12(sp)
	lw	t4,a
	lw	t5,c
	lw	t3,16(sp)
	div	t3,t4,t5
	sw	t3,16(sp)
	lw	t4,d
	lw	t5,16(sp)
	lw	t3,20(sp)
	sub	t3,t4,t5
	sw	t3,20(sp)
	lw	t4,12(sp)
	lw	t5,20(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,24(sp)
	lw	t4,24(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,28(sp)
	lw	a0,28(sp)
	bne	a0,zero,.L1
	lw	t4,a
	lw	t5,b
	lw	t3,32(sp)
	mul	t3,t4,t5
	sw	t3,32(sp)
	lw	t4,32(sp)
	lw	t5,c
	lw	t3,36(sp)
	div	t3,t4,t5
	sw	t3,36(sp)
	lw	t4,e
	lw	t5,d
	lw	t3,40(sp)
	add	t3,t4,t5
	sw	t3,40(sp)
	lw	t4,36(sp)
	lw	t5,40(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,44(sp)
	lw	t4,44(sp)
	snez	t4,t4
	li	t5,0
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,48(sp)
	lw	a0,48(sp)
	bne	a0,zero,.L0
	lw	t4,a
	lw	t5,b
	lw	t3,52(sp)
	add	t3,t4,t5
	sw	t3,52(sp)
	lw	t4,52(sp)
	lw	t5,c
	lw	t3,56(sp)
	add	t3,t4,t5
	sw	t3,56(sp)
	lw	t4,d
	lw	t5,e
	lw	t3,60(sp)
	add	t3,t4,t5
	sw	t3,60(sp)
	lw	t4,56(sp)
	lw	t5,60(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,64(sp)
	lw	t4,44(sp)
	snez	t4,t4
	lw	t5,64(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,48(sp)
.L0:
	lw	t4,24(sp)
	snez	t4,t4
	lw	t5,48(sp)
	snez	t5,t5
	or	t3,t4,t5
	sw	t3,28(sp)
.L1:
	lw	a0,28(sp)
	bne	a0,zero,.L2
	li	a0,1
	bne	a0,zero,.L3
.L2:
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L3
.L3:
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,68
	jr	ra
