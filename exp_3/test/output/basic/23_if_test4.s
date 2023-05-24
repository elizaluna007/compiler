	.text
	.global	global
	.type	global, @function
global:
	jr	ra
	.global	if_ifElse_
	.type	if_ifElse_, @function
if_ifElse_:
	addi	sp,sp,-4
	sw	ra,0(sp)
	la	a0,a
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
	.global	main
	.type	main, @function
main:
	addi	sp,sp,-4
	sw	ra,0(sp)
	call	global
	call	if_ifElse_
	la	a0,t5
	lw	a0,0(a0)
	addi	sp,sp,4
	jr	ra
