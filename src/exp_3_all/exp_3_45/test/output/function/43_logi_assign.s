	.data
a:
	.word	0
b:
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
	addi	sp,sp,-24
	sw	ra,0(sp)
	call	global
	li	t4,4
	la	t3,a
	sw	t4,0(t3)
	li	t4,4
	la	t3,b
	sw	t4,0(t3)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	la	a0,a
	lw	t4,0(a0)
	la	a0,b
	lw	t5,0(a0)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,8(sp)
	lw	t4,8(sp)
	snez	t4,t4
	li	t5,1
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,12(sp)
	lw	a0,12(sp)
	bne	a0,zero,.L0
	li	a0,1
	bne	a0,zero,.L1
.L0:
	lw	t3,16(sp)
	li	t3,3
	sw	t3,16(sp)
	la	a0,a
	lw	t4,0(a0)
	lw	t5,16(sp)
	sub	t3,t4,t5
	snez	t3,t3
	sw	t3,20(sp)
	lw	t4,8(sp)
	snez	t4,t4
	lw	t5,20(sp)
	snez	t5,t5
	and	t3,t4,t5
	sw	t3,12(sp)
.L1:
	lw	a0,12(sp)
	bne	a0,zero,.L2
	li	a0,1
	bne	a0,zero,.L3
.L2:
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L4
.L3:
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
.L4:
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,24
	jr	ra
