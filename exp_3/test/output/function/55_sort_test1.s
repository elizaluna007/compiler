	.data
n:
	.word	0
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-8
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,8
	jr	ra
	.global	bubblesort
	.type	bubblesort, @function
bubblesort:
	addi	sp,sp,-16
	sw	ra,0(sp)
	lw	t3,4(sp)
	li	t3,0
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,0
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,16
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-60
	sw	ra,0(sp)
	call	global
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	lw	t3,8(sp)
	li	t3,10
	sw	t3,8(sp)
	lw	t3,12(sp)
	li	t3,0
	sw	t3,12(sp)
	lw	t3,16(sp)
	li	t3,1
	sw	t3,16(sp)
	lw	t3,20(sp)
	li	t3,2
	sw	t3,20(sp)
	lw	t3,24(sp)
	li	t3,3
	sw	t3,24(sp)
	lw	t3,28(sp)
	li	t3,4
	sw	t3,28(sp)
	lw	t3,32(sp)
	li	t3,5
	sw	t3,32(sp)
	lw	t3,36(sp)
	li	t3,6
	sw	t3,36(sp)
	lw	t3,40(sp)
	li	t3,7
	sw	t3,40(sp)
	lw	t3,44(sp)
	li	t3,8
	sw	t3,44(sp)
	lw	t3,48(sp)
	li	t3,9
	sw	t3,48(sp)
	lw	t3,52(sp)
	li	t3,0
	sw	t3,52(sp)
	call	bubblesort
	lw	t3,56(sp)
	li	t3,0
	sw	t3,56(sp)
	call	putint
	call	putch
	li	a0,0
	lw	ra,0(sp)
	addi	sp,sp,60
	jr	ra
