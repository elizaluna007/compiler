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
	addi	sp,sp,-208
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,4
	sw	t3,8(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	lw	t3,12(sp)
	mul	t3,t4,t5
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,2
	sw	t3,16(sp)
	lw	t4,12(sp)
	lw	t5,16(sp)
	lw	t3,20(sp)
	mul	t3,t4,t5
	sw	t3,20(sp)
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
	li	t3,1
	sw	t3,60(sp)
	lw	t3,64(sp)
	li	t3,4
	sw	t3,64(sp)
	lw	t4,60(sp)
	lw	t5,64(sp)
	lw	t3,68(sp)
	mul	t3,t4,t5
	sw	t3,68(sp)
	lw	t3,72(sp)
	li	t3,2
	sw	t3,72(sp)
	lw	t4,68(sp)
	lw	t5,72(sp)
	lw	t3,76(sp)
	mul	t3,t4,t5
	sw	t3,76(sp)
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
	lw	t3,104(sp)
	li	t3,0
	sw	t3,104(sp)
	lw	t3,108(sp)
	li	t3,0
	sw	t3,108(sp)
	lw	t3,112(sp)
	li	t3,0
	sw	t3,112(sp)
	lw	t3,84(sp)
	li	t3,1
	sw	t3,84(sp)
	lw	t3,88(sp)
	li	t3,2
	sw	t3,88(sp)
	lw	t3,92(sp)
	li	t3,3
	sw	t3,92(sp)
	lw	t3,96(sp)
	li	t3,4
	sw	t3,96(sp)
	lw	t3,100(sp)
	li	t3,5
	sw	t3,100(sp)
	lw	t3,104(sp)
	li	t3,6
	sw	t3,104(sp)
	lw	t3,108(sp)
	li	t3,7
	sw	t3,108(sp)
	lw	t3,112(sp)
	li	t3,8
	sw	t3,112(sp)
	lw	t3,116(sp)
	li	t3,3
	sw	t3,116(sp)
	lw	t3,120(sp)
	li	t3,1
	sw	t3,120(sp)
	lw	t4,72(sp)
	lw	t5,116(sp)
	lw	t3,124(sp)
	mul	t3,t4,t5
	sw	t3,124(sp)
	lw	t4,124(sp)
	lw	t5,120(sp)
	lw	t3,128(sp)
	add	t3,t4,t5
	sw	t3,128(sp)
	lw	t4,128(sp)
	lw	t3,132(sp)
	lw	t3,112(sp)
	sw	t3,132(sp)
	lw	t3,136(sp)
	li	t3,0
	sw	t3,136(sp)
	lw	t3,140(sp)
	li	t3,0
	sw	t3,140(sp)
	lw	t4,72(sp)
	lw	t5,136(sp)
	lw	t3,144(sp)
	mul	t3,t4,t5
	sw	t3,144(sp)
	lw	t4,144(sp)
	lw	t5,140(sp)
	lw	t3,148(sp)
	add	t3,t4,t5
	sw	t3,148(sp)
	lw	t4,148(sp)
	lw	t3,152(sp)
	lw	t3,84(sp)
	sw	t3,152(sp)
	lw	t4,132(sp)
	lw	t5,152(sp)
	lw	t3,156(sp)
	add	t3,t4,t5
	sw	t3,156(sp)
	lw	t3,160(sp)
	li	t3,0
	sw	t3,160(sp)
	lw	t3,164(sp)
	li	t3,1
	sw	t3,164(sp)
	lw	t4,72(sp)
	lw	t5,160(sp)
	lw	t3,168(sp)
	mul	t3,t4,t5
	sw	t3,168(sp)
	lw	t4,168(sp)
	lw	t5,164(sp)
	lw	t3,172(sp)
	add	t3,t4,t5
	sw	t3,172(sp)
	lw	t4,172(sp)
	lw	t3,176(sp)
	lw	t3,88(sp)
	sw	t3,176(sp)
	lw	t4,156(sp)
	lw	t5,176(sp)
	lw	t3,180(sp)
	add	t3,t4,t5
	sw	t3,180(sp)
	lw	t3,184(sp)
	li	t3,2
	sw	t3,184(sp)
	lw	t3,188(sp)
	li	t3,0
	sw	t3,188(sp)
	lw	t4,72(sp)
	lw	t5,184(sp)
	lw	t3,192(sp)
	mul	t3,t4,t5
	sw	t3,192(sp)
	lw	t4,192(sp)
	lw	t5,188(sp)
	lw	t3,196(sp)
	add	t3,t4,t5
	sw	t3,196(sp)
	lw	t4,196(sp)
	lw	t3,200(sp)
	lw	t3,100(sp)
	sw	t3,200(sp)
	lw	t4,180(sp)
	lw	t5,200(sp)
	lw	t3,204(sp)
	add	t3,t4,t5
	sw	t3,204(sp)
	lw	a0,204(sp)
	lw	ra,0(sp)
	addi	sp,sp,208
	jr	ra