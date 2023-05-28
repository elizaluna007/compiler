	.file	"95.c"
	.option pic
	.text
	.globl	RADIUS
	.section	.rodata
	.align	2
	.type	RADIUS, @object
	.size	RADIUS, 4
RADIUS:
	.word	1085276160
	.globl	PI
	.align	2
	.type	PI, @object
	.size	PI, 4
PI:
	.word	1078530011
	.globl	EPS
	.align	2
	.type	EPS, @object
	.size	EPS, 4
EPS:
	.word	897988541
	.globl	PI_HEX
	.align	2
	.type	PI_HEX, @object
	.size	PI_HEX, 4
PI_HEX:
	.word	1078530011
	.globl	HEX2
	.align	2
	.type	HEX2, @object
	.size	HEX2, 4
HEX2:
	.word	1033895936
	.globl	FACT
	.align	2
	.type	FACT, @object
	.size	FACT, 4
FACT:
	.word	-956241920
	.globl	EVAL1
	.align	2
	.type	EVAL1, @object
	.size	EVAL1, 4
EVAL1:
	.word	1119752446
	.globl	EVAL2
	.align	2
	.type	EVAL2, @object
	.size	EVAL2, 4
EVAL2:
	.word	1107966695
	.globl	EVAL3
	.align	2
	.type	EVAL3, @object
	.size	EVAL3, 4
EVAL3:
	.word	1107966695
	.globl	CONV1
	.align	2
	.type	CONV1, @object
	.size	CONV1, 4
CONV1:
	.word	1130954752
	.globl	CONV2
	.align	2
	.type	CONV2, @object
	.size	CONV2, 4
CONV2:
	.word	1166012416
	.globl	MAX
	.align	2
	.type	MAX, @object
	.size	MAX, 4
MAX:
	.word	1000000000
	.globl	TWO
	.align	2
	.type	TWO, @object
	.size	TWO, 4
TWO:
	.word	2
	.globl	THREE
	.align	2
	.type	THREE, @object
	.size	THREE, 4
THREE:
	.word	3
	.globl	FIVE
	.align	2
	.type	FIVE, @object
	.size	FIVE, 4
FIVE:
	.word	5
	.text
	.align	1
	.globl	float_abs
	.type	float_abs, @function
float_abs:
	addi	sp,sp,-32
	sd	s0,24(sp)
	addi	s0,sp,32
	fsw	fa0,-20(s0)
	flw	fa5,-20(s0)
	fmv.w.x	fa4,zero
	flt.s	a5,fa5,fa4
	beq	a5,zero,.L6
	flw	fa5,-20(s0)
	fneg.s	fa5,fa5
	j	.L4
.L6:
	flw	fa5,-20(s0)
.L4:
	fmv.s	fa0,fa5
	ld	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	float_abs, .-float_abs
	.align	1
	.globl	circle_area
	.type	circle_area, @function
circle_area:
	addi	sp,sp,-32
	sd	s0,24(sp)
	addi	s0,sp,32
	mv	a5,a0
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	fcvt.s.w	fa4,a5
	lla	a5,.LC0
	flw	fa5,0(a5)
	fmul.s	fa4,fa4,fa5
	lw	a5,-20(s0)
	fcvt.s.w	fa5,a5
	fmul.s	fa4,fa4,fa5
	lw	a5,-20(s0)
	mulw	a5,a5,a5
	sext.w	a5,a5
	fcvt.s.w	fa3,a5
	lla	a5,.LC0
	flw	fa5,0(a5)
	fmul.s	fa5,fa3,fa5
	fadd.s	fa4,fa4,fa5
	lla	a5,.LC1
	flw	fa5,0(a5)
	fdiv.s	fa5,fa4,fa5
	fmv.s	fa0,fa5
	ld	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	circle_area, .-circle_area
	.align	1
	.globl	float_eq
	.type	float_eq, @function
float_eq:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	fsw	fa0,-20(s0)
	fsw	fa1,-24(s0)
	flw	fa4,-20(s0)
	flw	fa5,-24(s0)
	fsub.s	fa5,fa4,fa5
	fmv.s	fa0,fa5
	call	float_abs
	fmv.s	fa4,fa0
	lla	a5,.LC2
	flw	fa5,0(a5)
	flt.s	a5,fa4,fa5
	beq	a5,zero,.L14
	li	a5,1
	j	.L12
.L14:
	li	a5,0
.L12:
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	float_eq, .-float_eq
	.align	1
	.globl	error
	.type	error, @function
error:
	addi	sp,sp,-16
	sd	s0,8(sp)
	addi	s0,sp,16
	nop
	ld	s0,8(sp)
	addi	sp,sp,16
	jr	ra
	.size	error, .-error
	.align	1
	.globl	ok
	.type	ok, @function
ok:
	addi	sp,sp,-16
	sd	s0,8(sp)
	addi	s0,sp,16
	nop
	ld	s0,8(sp)
	addi	sp,sp,16
	jr	ra
	.size	ok, .-ok
	.align	1
	.globl	assert
	.type	assert, @function
assert:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	mv	a5,a0
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	sext.w	a5,a5
	bne	a5,zero,.L18
	call	error
	j	.L20
.L18:
	call	ok
.L20:
	nop
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	assert, .-assert
	.align	1
	.globl	assert_not
	.type	assert_not, @function
assert_not:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	mv	a5,a0
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	sext.w	a5,a5
	beq	a5,zero,.L22
	call	error
	j	.L24
.L22:
	call	ok
.L24:
	nop
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	assert_not, .-assert_not
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-112
	sd	ra,104(sp)
	sd	s0,96(sp)
	sd	s1,88(sp)
	addi	s0,sp,112
	la	a5,__stack_chk_guard
	ld	a4, 0(a5)
	sd	a4, -40(s0)
	li	a4, 0
	lla	a5,.LC3
	flw	fa5,0(a5)
	fsw	fa5,-96(s0)
	lla	a5,.LC4
	flw	fa5,0(a5)
	lla	a5,.LC5
	flw	fa4,0(a5)
	fmv.s	fa1,fa4
	fmv.s	fa0,fa5
	call	float_eq
	mv	a5,a0
	mv	a0,a5
	call	assert_not
	lla	a5,.LC6
	flw	fa5,0(a5)
	lla	a5,.LC7
	flw	fa4,0(a5)
	fmv.s	fa1,fa4
	fmv.s	fa0,fa5
	call	float_eq
	mv	a5,a0
	mv	a0,a5
	call	assert_not
	lla	a5,.LC7
	flw	fa5,0(a5)
	lla	a5,.LC7
	flw	fa4,0(a5)
	fmv.s	fa1,fa4
	fmv.s	fa0,fa5
	call	float_eq
	mv	a5,a0
	mv	a0,a5
	call	assert
	lla	a5,.LC8
	flw	fa5,0(a5)
	fcvt.w.s a5,fa5,rtz
	sext.w	a5,a5
	mv	a0,a5
	call	circle_area
	fmv.x.w	s1,fa0
	li	a5,5
	mv	a0,a5
	call	circle_area
	fmv.x.w	a5,fa0
	fmv.w.x	fa1,a5
	fmv.w.x	fa0,s1
	call	float_eq
	mv	a5,a0
	mv	a0,a5
	call	assert
	lla	a5,.LC9
	flw	fa5,0(a5)
	lla	a5,.LC10
	flw	fa4,0(a5)
	fmv.s	fa1,fa4
	fmv.s	fa0,fa5
	call	float_eq
	mv	a5,a0
	mv	a0,a5
	call	assert_not
	call	ok
	call	ok
	call	ok
	li	a5,1
	sw	a5,-104(s0)
	sw	zero,-100(s0)
	sd	zero,-80(s0)
	sd	zero,-72(s0)
	sd	zero,-64(s0)
	sd	zero,-56(s0)
	sd	zero,-48(s0)
	lla	a5,.LC11
	flw	fa5,0(a5)
	fsw	fa5,-80(s0)
	lla	a5,.LC1
	flw	fa5,0(a5)
	fsw	fa5,-76(s0)
	j	.L26
.L27:
	lla	a5,.LC12
	flw	fa5,0(a5)
	fsw	fa5,-92(s0)
	lla	a5,.LC0
	flw	fa4,0(a5)
	flw	fa5,-92(s0)
	fmul.s	fa5,fa4,fa5
	flw	fa4,-92(s0)
	fmul.s	fa5,fa4,fa5
	fsw	fa5,-88(s0)
	flw	fa5,-92(s0)
	fcvt.w.s a5,fa5,rtz
	sext.w	a5,a5
	mv	a0,a5
	call	circle_area
	fsw	fa0,-84(s0)
	lw	a5,-100(s0)
	slli	a5,a5,2
	addi	a5,a5,-32
	add	a5,a5,s0
	flw	fa4,-48(a5)
	flw	fa5,-92(s0)
	fadd.s	fa5,fa4,fa5
	lw	a5,-100(s0)
	slli	a5,a5,2
	addi	a5,a5,-32
	add	a5,a5,s0
	fsw	fa5,-48(a5)
	lw	a5,-104(s0)
	mv	a4,a5
	mv	a5,a4
	slliw	a5,a5,2
	addw	a5,a5,a4
	slliw	a5,a5,1
	sw	a5,-104(s0)
	lw	a5,-100(s0)
	addiw	a5,a5,1
	sw	a5,-100(s0)
.L26:
	li	a5,1000001536
	addi	a4,a5,-1536
	lw	a5,-104(s0)
	sext.w	a5,a5
	blt	a5,a4,.L27
	li	a5,0
	mv	a4,a5
	la	a5,__stack_chk_guard
	ld	a3, -40(s0)
	ld	a5, 0(a5)
	xor	a5, a3, a5
	li	a3, 0
	beq	a5,zero,.L29
	call	__stack_chk_fail@plt
.L29:
	mv	a0,a4
	ld	ra,104(sp)
	ld	s0,96(sp)
	ld	s1,88(sp)
	addi	sp,sp,112
	jr	ra
	.size	main, .-main
	.section	.rodata
	.align	2
.LC0:
	.word	1078530011
	.align	2
.LC1:
	.word	1073741824
	.align	2
.LC2:
	.word	897988541
	.align	2
.LC3:
	.word	-1110651699
	.align	2
.LC4:
	.word	1033895936
	.align	2
.LC5:
	.word	-956241920
	.align	2
.LC6:
	.word	1119752446
	.align	2
.LC7:
	.word	1107966695
	.align	2
.LC8:
	.word	1085276160
	.align	2
.LC9:
	.word	1130954752
	.align	2
.LC10:
	.word	1166012416
	.align	2
.LC11:
	.word	1065353216
	.align	2
.LC12:
	.word	1079194419
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
