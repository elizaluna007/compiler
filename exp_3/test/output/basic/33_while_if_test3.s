	.data
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-64
	sw	ra,0(sp)
	lw	ra,0(sp)
	jr	ra
	.global	deepWhileBr
	.type	deepWhileBr, @function
deepWhileBr:
	sw	ra,0(sp)
	sw	a0,4(sp)
	sw	a1,8(sp)
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	lw	t4,4(sp)
	lw	t5,8(sp)
	lw	t3,16(sp)
	add	t3,t4,t5
	sw	t3,16(sp)
	lw	t3,16(sp)
	sw	t3,12(sp)
	lw	t3,20(sp)
	li	t3,0
	sw	t3,20(sp)
	lw	t3,20(sp)
	li	t3,42
	sw	t3,20(sp)
	lw	t4,12(sp)
	lw	t5,20(sp)
	lw	t3,24(sp)
	add	t3,t4,t5
	sw	t3,24(sp)
	lw	t3,24(sp)
	sw	t3,12(sp)
	lw	t3,28(sp)
	li	t3,0
	sw	t3,28(sp)
	lw	t3,32(sp)
	li	t3,2
	sw	t3,32(sp)
	lw	t4,20(sp)
	lw	t5,32(sp)
	lw	t3,36(sp)
	mul	t3,t4,t5
	sw	t3,36(sp)
	lw	t3,36(sp)
	sw	t3,28(sp)
	lw	t3,40(sp)
	li	t3,1
	sw	t3,40(sp)
	lw	t3,44(sp)
	li	t3,1
	sw	t3,44(sp)
	lw	t3,48(sp)
	li	t3,2
	sw	t3,48(sp)
	lw	t4,28(sp)
	lw	t5,48(sp)
	lw	t3,52(sp)
	mul	t3,t4,t5
	sw	t3,52(sp)
	lw	t3,52(sp)
	sw	t3,12(sp)
	lw	a0,12(sp)
	lw	ra,0(sp)
	jr	ra
	.global	main
	.type	main, @function
main:
	sw	ra,0(sp)
	call	global
	lw	t3,56(sp)
	li	t3,0
	sw	t3,56(sp)
	lw	t3,56(sp)
	li	t3,2
	sw	t3,56(sp)
	lw	a0,56(sp)
	lw	a1,56(sp)
	call	deepWhileBr
	sw	a0,60(sp)
	lw	a0,60(sp)
	lw	ra,0(sp)
	addi	sp,sp,64
	jr	ra
