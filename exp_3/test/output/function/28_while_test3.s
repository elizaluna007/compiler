	.data
g:
	.word	0
h:
	.word	0
f:
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
	.global	EightWhile
	.type	EightWhile, @function
EightWhile:
	addi	sp,sp,-144
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,4(sp)
	li	t3,5
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	lw	t3,8(sp)
	li	t3,6
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,7
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,0
	sw	t3,16(sp)
	lw	t3,16(sp)
	li	t3,10
	sw	t3,16(sp)
.L0:
	lw	t4,4(sp)
	li	t5,20
	slt	t3,t4,t5
	sw	t3,20(sp)
	lw	a0,20(sp)
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L23
.L1:
	lw	t4,4(sp)
	lw	t3,24(sp)
	addi	t3,t4,3
	sw	t3,24(sp)
	lw	t3,24(sp)
	sw	t3,4(sp)
.L2:
	lw	t4,8(sp)
	li	t5,10
	slt	t3,t4,t5
	sw	t3,28(sp)
	lw	a0,28(sp)
	bne	a0,zero,.L3
	li	a0,1
	bne	a0,zero,.L22
.L3:
	lw	t4,8(sp)
	lw	t3,32(sp)
	addi	t3,t4,1
	sw	t3,32(sp)
	lw	t3,32(sp)
	sw	t3,8(sp)
.L4:
	lw	t3,36(sp)
	li	t3,7
	sw	t3,36(sp)
	lw	t4,12(sp)
	lw	t5,36(sp)
	sub	t3,t4,t5
	seqz	t3,t3
	sw	t3,40(sp)
	lw	a0,40(sp)
	bne	a0,zero,.L5
	li	a0,1
	bne	a0,zero,.L21
.L5:
	lw	t4,12(sp)
	lw	t3,44(sp)
	addi	t3,t4,-1
	sw	t3,44(sp)
	lw	t3,44(sp)
	sw	t3,12(sp)
.L6:
	lw	t4,16(sp)
	li	t5,20
	slt	t3,t4,t5
	sw	t3,48(sp)
	lw	a0,48(sp)
	bne	a0,zero,.L7
	li	a0,1
	bne	a0,zero,.L20
.L7:
	lw	t4,16(sp)
	lw	t3,52(sp)
	addi	t3,t4,3
	sw	t3,52(sp)
	lw	t3,52(sp)
	sw	t3,16(sp)
.L8:
	la	a0,e
	lw	t4,0(a0)
	li	t5,1
	slt	t3,t5,t4
	sw	t3,56(sp)
	lw	a0,56(sp)
	bne	a0,zero,.L9
	li	a0,1
	bne	a0,zero,.L19
.L9:
	la	a0,e
	lw	t4,0(a0)
	lw	t3,60(sp)
	addi	t3,t4,-1
	sw	t3,60(sp)
	lw	t3,60(sp)
	la	t4,e
	sw	t3,0(t4)
.L10:
	la	a0,f
	lw	t4,0(a0)
	li	t5,2
	slt	t3,t5,t4
	sw	t3,64(sp)
	lw	a0,64(sp)
	bne	a0,zero,.L11
	li	a0,1
	bne	a0,zero,.L18
.L11:
	la	a0,f
	lw	t4,0(a0)
	lw	t3,68(sp)
	addi	t3,t4,-2
	sw	t3,68(sp)
	lw	t3,68(sp)
	la	t4,f
	sw	t3,0(t4)
.L12:
	la	a0,g
	lw	t4,0(a0)
	li	t5,3
	slt	t3,t4,t5
	sw	t3,72(sp)
	lw	a0,72(sp)
	bne	a0,zero,.L13
	li	a0,1
	bne	a0,zero,.L17
.L13:
	la	a0,g
	lw	t4,0(a0)
	lw	t3,76(sp)
	addi	t3,t4,10
	sw	t3,76(sp)
	lw	t3,76(sp)
	la	t4,g
	sw	t3,0(t4)
.L14:
	la	a0,h
	lw	t4,0(a0)
	li	t5,10
	slt	t3,t4,t5
	sw	t3,80(sp)
	lw	a0,80(sp)
	bne	a0,zero,.L15
	li	a0,1
	bne	a0,zero,.L16
.L15:
	la	a0,h
	lw	t4,0(a0)
	lw	t3,84(sp)
	addi	t3,t4,8
	sw	t3,84(sp)
	lw	t3,84(sp)
	la	t4,h
	sw	t3,0(t4)
	li	a0,1
	bne	a0,zero,.L14
.L16:
	la	a0,h
	lw	t4,0(a0)
	lw	t3,88(sp)
	addi	t3,t4,-1
	sw	t3,88(sp)
	lw	t3,88(sp)
	la	t4,h
	sw	t3,0(t4)
	li	a0,1
	bne	a0,zero,.L12
.L17:
	la	a0,g
	lw	t4,0(a0)
	lw	t3,92(sp)
	addi	t3,t4,-8
	sw	t3,92(sp)
	lw	t3,92(sp)
	la	t4,g
	sw	t3,0(t4)
	li	a0,1
	bne	a0,zero,.L10
.L18:
	la	a0,f
	lw	t4,0(a0)
	lw	t3,96(sp)
	addi	t3,t4,1
	sw	t3,96(sp)
	lw	t3,96(sp)
	la	t4,f
	sw	t3,0(t4)
	li	a0,1
	bne	a0,zero,.L8
.L19:
	la	a0,e
	lw	t4,0(a0)
	lw	t3,100(sp)
	addi	t3,t4,1
	sw	t3,100(sp)
	lw	t3,100(sp)
	la	t4,e
	sw	t3,0(t4)
	li	a0,1
	bne	a0,zero,.L6
.L20:
	lw	t4,16(sp)
	lw	t3,104(sp)
	addi	t3,t4,-1
	sw	t3,104(sp)
	lw	t3,104(sp)
	sw	t3,16(sp)
	li	a0,1
	bne	a0,zero,.L4
.L21:
	lw	t4,12(sp)
	lw	t3,108(sp)
	addi	t3,t4,1
	sw	t3,108(sp)
	lw	t3,108(sp)
	sw	t3,12(sp)
	li	a0,1
	bne	a0,zero,.L2
.L22:
	lw	t4,8(sp)
	lw	t3,112(sp)
	addi	t3,t4,-2
	sw	t3,112(sp)
	lw	t3,112(sp)
	sw	t3,8(sp)
	li	a0,1
	bne	a0,zero,.L0
.L23:
	lw	t4,8(sp)
	lw	t5,16(sp)
	lw	t3,116(sp)
	add	t3,t4,t5
	sw	t3,116(sp)
	lw	t4,4(sp)
	lw	t5,116(sp)
	lw	t3,120(sp)
	add	t3,t4,t5
	sw	t3,120(sp)
	lw	t4,120(sp)
	lw	t5,12(sp)
	lw	t3,124(sp)
	add	t3,t4,t5
	sw	t3,124(sp)
	la	t4,e
	lw	t4,0(t4)
	lw	t5,16(sp)
	lw	t3,128(sp)
	add	t3,t4,t5
	sw	t3,128(sp)
	lw	t4,128(sp)
	la	t5,g
	lw	t5,0(t5)
	lw	t3,132(sp)
	sub	t3,t4,t5
	sw	t3,132(sp)
	lw	t4,132(sp)
	la	t5,h
	lw	t5,0(t5)
	lw	t3,136(sp)
	add	t3,t4,t5
	sw	t3,136(sp)
	lw	t4,124(sp)
	lw	t5,136(sp)
	lw	t3,140(sp)
	sub	t3,t4,t5
	sw	t3,140(sp)
	lw	a0,140(sp)
	lw	ra,0(sp)
	addi	sp,sp,144
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-8
	sw	ra,0(sp)
	call	global
	li	t4,1
	la	t3,g
	sw	t4,0(t3)
	li	t4,2
	la	t3,h
	sw	t4,0(t3)
	li	t4,4
	la	t3,e
	sw	t4,0(t3)
	li	t4,6
	la	t3,f
	sw	t4,0(t3)
	call	EightWhile
	sw	a0,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
