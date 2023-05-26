	.data
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-56
	sw	ra,0(sp)
	lw	ra,0(sp)
	jr	ra
	.global	ifElseIf
	.type	ifElseIf, @function
ifElseIf:
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
	lw	t3,8(sp)
	li	t3,10
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,6
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,0
	sw	t3,16(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	jr	ra
	lw	t3,20(sp)
	li	t3,10
	sw	t3,20(sp)
	lw	t3,24(sp)
	li	t3,1
	sw	t3,24(sp)
	lw	t3,4(sp)
	li	t3,25
	sw	t3,4(sp)
	lw	t3,28(sp)
	li	t3,10
	sw	t3,28(sp)
	lw	t3,32(sp)
	li	t3,0
	sw	t3,32(sp)
	lw	t4,32(sp)
	lw	t3,36(sp)
	addi	t3,t4,-5
	sw	t3,36(sp)
	lw	t4,4(sp)
	lw	t3,40(sp)
	addi	t3,t4,15
	sw	t3,40(sp)
	lw	t3,40(sp)
	sw	t3,4(sp)
	lw	t3,44(sp)
	li	t3,0
	sw	t3,44(sp)
	lw	t4,44(sp)
	lw	t5,4(sp)
	lw	t3,48(sp)
	sub	t3,t4,t5
	sw	t3,48(sp)
	lw	t3,48(sp)
	sw	t3,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	jr	ra
	.global	main
	.type	main, @function
main:
	sw	ra,0(sp)
	call	global
	call	ifElseIf
	sw	a0,52(sp)
	lw	a0,52(sp)
	call	putint
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,56
	jr	ra
