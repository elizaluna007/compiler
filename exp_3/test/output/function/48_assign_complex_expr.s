	.data
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-136
	sw	ra,0(sp)
	lw	ra,0(sp)
	jr	ra
	.global	main
	.type	main, @function
main:
	sw	ra,0(sp)
	call	global
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
	lw	t3,4(sp)
	li	t3,5
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,5
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,1
	sw	t3,12(sp)
	lw	t3,24(sp)
	li	t3,0
	sw	t3,24(sp)
	lw	t4,24(sp)
	lw	t3,28(sp)
	addi	t3,t4,-2
	sw	t3,28(sp)
	lw	t3,28(sp)
	sw	t3,16(sp)
	lw	t3,32(sp)
	li	t3,1
	sw	t3,32(sp)
	lw	t4,16(sp)
	lw	t5,32(sp)
	lw	t3,36(sp)
	mul	t3,t4,t5
	sw	t3,36(sp)
	lw	t3,40(sp)
	li	t3,2
	sw	t3,40(sp)
	lw	t4,36(sp)
	lw	t5,40(sp)
	lw	t3,44(sp)
	div	t3,t4,t5
	sw	t3,44(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	lw	t3,48(sp)
	sub	t3,t4,t5
	sw	t3,48(sp)
	lw	t4,44(sp)
	lw	t5,48(sp)
	lw	t3,52(sp)
	add	t3,t4,t5
	sw	t3,52(sp)
	lw	t4,12(sp)
	lw	t3,56(sp)
	addi	t3,t4,3
	sw	t3,56(sp)
	lw	t3,60(sp)
	li	t3,0
	sw	t3,60(sp)
	lw	t4,60(sp)
	lw	t5,56(sp)
	lw	t3,64(sp)
	sub	t3,t4,t5
	sw	t3,64(sp)
	lw	t3,68(sp)
	li	t3,2
	sw	t3,68(sp)
	lw	t4,64(sp)
	lw	t5,68(sp)
	lw	t3,72(sp)
	rem	t3,t4,t5
	sw	t3,72(sp)
	lw	t4,52(sp)
	lw	t5,72(sp)
	lw	t3,76(sp)
	sub	t3,t4,t5
	sw	t3,76(sp)
	lw	t3,76(sp)
	sw	t3,20(sp)
	lw	a0,20(sp)
	call	putint
	lw	t3,80(sp)
	li	t3,2
	sw	t3,80(sp)
	lw	t4,16(sp)
	lw	t5,80(sp)
	lw	t3,84(sp)
	rem	t3,t4,t5
	sw	t3,84(sp)
	lw	t4,84(sp)
	lw	t3,88(sp)
	addi	t3,t4,67
	sw	t3,88(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	lw	t3,92(sp)
	sub	t3,t4,t5
	sw	t3,92(sp)
	lw	t3,96(sp)
	li	t3,0
	sw	t3,96(sp)
	lw	t4,96(sp)
	lw	t5,92(sp)
	lw	t3,100(sp)
	sub	t3,t4,t5
	sw	t3,100(sp)
	lw	t4,88(sp)
	lw	t5,100(sp)
	lw	t3,104(sp)
	add	t3,t4,t5
	sw	t3,104(sp)
	lw	t4,12(sp)
	lw	t3,108(sp)
	addi	t3,t4,2
	sw	t3,108(sp)
	lw	t3,112(sp)
	li	t3,2
	sw	t3,112(sp)
	lw	t4,108(sp)
	lw	t5,112(sp)
	lw	t3,116(sp)
	rem	t3,t4,t5
	sw	t3,116(sp)
	lw	t3,120(sp)
	li	t3,0
	sw	t3,120(sp)
	lw	t4,120(sp)
	lw	t5,116(sp)
	lw	t3,124(sp)
	sub	t3,t4,t5
	sw	t3,124(sp)
	lw	t4,104(sp)
	lw	t5,124(sp)
	lw	t3,128(sp)
	sub	t3,t4,t5
	sw	t3,128(sp)
	lw	t3,128(sp)
	sw	t3,20(sp)
	lw	t4,20(sp)
	lw	t3,132(sp)
	addi	t3,t4,3
	sw	t3,132(sp)
	lw	t3,132(sp)
	sw	t3,20(sp)
	lw	a0,20(sp)
	call	putint
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,136
	jr	ra
