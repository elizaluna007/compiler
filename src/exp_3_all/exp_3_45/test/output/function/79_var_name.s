	.data
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
	addi	sp,sp,-156
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,2
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,20
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,1
	sw	t3,12(sp)
	lw	t4,12(sp)
	lw	t5,8(sp)
	lw	t3,16(sp)
	mul	t3,t4,t5
	sw	t3,16(sp)
	sw	t3,20(sp)
	lw	t3,24(sp)
	li	t3,0
	sw	t3,24(sp)
	lw	t3,28(sp)
	li	t3,0
	sw	t3,28(sp)
	lw	t3,32(sp)
	li	t3,0
	sw	t3,32(sp)
	lw	t3,36(sp)
	li	t3,0
	sw	t3,36(sp)
	lw	t3,40(sp)
	li	t3,0
	sw	t3,40(sp)
	lw	t3,44(sp)
	li	t3,0
	sw	t3,44(sp)
	lw	t3,48(sp)
	li	t3,0
	sw	t3,48(sp)
	lw	t3,52(sp)
	li	t3,0
	sw	t3,52(sp)
	lw	t3,56(sp)
	li	t3,0
	sw	t3,56(sp)
	lw	t3,60(sp)
	li	t3,0
	sw	t3,60(sp)
	lw	t3,64(sp)
	li	t3,0
	sw	t3,64(sp)
	lw	t3,68(sp)
	li	t3,0
	sw	t3,68(sp)
	lw	t3,72(sp)
	li	t3,0
	sw	t3,72(sp)
	lw	t3,76(sp)
	li	t3,0
	sw	t3,76(sp)
	lw	t3,80(sp)
	li	t3,0
	sw	t3,80(sp)
	lw	t3,84(sp)
	li	t3,0
	sw	t3,84(sp)
	lw	t3,88(sp)
	li	t3,0
	sw	t3,88(sp)
	lw	t3,92(sp)
	li	t3,0
	sw	t3,92(sp)
	lw	t3,96(sp)
	li	t3,0
	sw	t3,96(sp)
	lw	t3,100(sp)
	li	t3,0
	sw	t3,100(sp)
	lw	t3,24(sp)
	li	t3,1
	sw	t3,24(sp)
	lw	t3,28(sp)
	li	t3,2
	sw	t3,28(sp)
	lw	t3,104(sp)
	li	t3,0
	sw	t3,104(sp)
.L0:
	lw	t4,4(sp)
	lw	t5,8(sp)
	slt	t3,t4,t5
	sw	t3,108(sp)
	lw	a0,108(sp)
	bne	a0,zero,.L1
	li	a0,1
	bne	a0,zero,.L2
.L1:
	lw	t4,4(sp)
	lw	t3,112(sp)
	lw	t3,32(sp)
	sw	t3,112(sp)
	lw	t4,4(sp)
	lw	t3,116(sp)
	addi	t3,t4,-1
	sw	t3,116(sp)
	lw	t4,116(sp)
	lw	t3,120(sp)
	lw	t3,28(sp)
	sw	t3,120(sp)
	lw	t4,112(sp)
	lw	t5,120(sp)
	lw	t3,124(sp)
	add	t3,t4,t5
	sw	t3,124(sp)
	lw	t4,4(sp)
	lw	t3,128(sp)
	addi	t3,t4,-2
	sw	t3,128(sp)
	lw	t4,128(sp)
	lw	t3,132(sp)
	lw	t3,24(sp)
	sw	t3,132(sp)
	lw	t4,124(sp)
	lw	t5,132(sp)
	lw	t3,136(sp)
	add	t3,t4,t5
	sw	t3,136(sp)
	li	t3,0
	lw	t3,136(sp)
	sw	t3,32(sp)
	lw	t4,4(sp)
	lw	t3,140(sp)
	lw	t3,32(sp)
	sw	t3,140(sp)
	lw	t4,104(sp)
	lw	t5,140(sp)
	lw	t3,144(sp)
	add	t3,t4,t5
	sw	t3,144(sp)
	lw	t3,144(sp)
	sw	t3,104(sp)
	lw	t4,4(sp)
	lw	t3,148(sp)
	lw	t3,32(sp)
	sw	t3,148(sp)
	lw	a0,148(sp)
	call	putint
	li	a0,10
	call	putch
	lw	t4,4(sp)
	lw	t3,152(sp)
	addi	t3,t4,1
	sw	t3,152(sp)
	lw	t3,152(sp)
	sw	t3,4(sp)
	li	a0,1
	bne	a0,zero,.L0
.L2:
	lw	a0,104(sp)
	lw	ra,0(sp)
	addi	sp,sp,156
	jr	ra