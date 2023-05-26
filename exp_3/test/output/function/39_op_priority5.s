	.data
a:
	.word	1
b:
	.word	0
c:
	.word	1
d:
	.word	2
e:
	.word	4
	.bss
	.text
	.global	global
	.type	global, @function
global:
	addi	sp,sp,-52
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
	lw	t4,a
	lw	t5,b
	lw	t3,8(sp)
	mul	t3,t4,t5
	sw	t3,8(sp)
	lw	t4,8(sp)
	lw	t5,c
	lw	t3,12(sp)
	div	t3,t4,t5
	sw	t3,12(sp)
	lw	t4,e
	lw	t5,d
	lw	t3,16(sp)
	add	t3,t4,t5
	sw	t3,16(sp)
	lw	t4,a
	lw	t5,b
	lw	t3,20(sp)
	add	t3,t4,t5
	sw	t3,20(sp)
	lw	t4,a
	lw	t5,20(sp)
	lw	t3,24(sp)
	mul	t3,t4,t5
	sw	t3,24(sp)
	lw	t4,24(sp)
	lw	t5,c
	lw	t3,28(sp)
	add	t3,t4,t5
	sw	t3,28(sp)
	lw	t4,d
	lw	t5,e
	lw	t3,32(sp)
	add	t3,t4,t5
	sw	t3,32(sp)
	lw	t4,b
	lw	t5,c
	lw	t3,36(sp)
	mul	t3,t4,t5
	sw	t3,36(sp)
	lw	t4,a
	lw	t5,36(sp)
	lw	t3,40(sp)
	sub	t3,t4,t5
	sw	t3,40(sp)
	lw	t4,a
	lw	t5,c
	lw	t3,44(sp)
	div	t3,t4,t5
	sw	t3,44(sp)
	lw	t4,d
	lw	t5,44(sp)
	lw	t3,48(sp)
	sub	t3,t4,t5
	sw	t3,48(sp)
	lw	t3,4(sp)
	li	t3,1
	sw	t3,4(sp)
	lw	a0,4(sp)
	lw	ra,0(sp)
	addi	sp,sp,52
	jr	ra
