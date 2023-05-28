	.file	"89.c"
	.option pic
	.text
	.globl	a0
	.bss
	.align	2
	.type	a0, @object
	.size	a0, 4
a0:
	.zero	4
	.globl	a1
	.align	2
	.type	a1, @object
	.size	a1, 4
a1:
	.zero	4
	.globl	a2
	.align	2
	.type	a2, @object
	.size	a2, 4
a2:
	.zero	4
	.globl	a3
	.align	2
	.type	a3, @object
	.size	a3, 4
a3:
	.zero	4
	.globl	a4
	.align	2
	.type	a4, @object
	.size	a4, 4
a4:
	.zero	4
	.globl	a5
	.align	2
	.type	a5, @object
	.size	a5, 4
a5:
	.zero	4
	.globl	a6
	.align	2
	.type	a6, @object
	.size	a6, 4
a6:
	.zero	4
	.globl	a7
	.align	2
	.type	a7, @object
	.size	a7, 4
a7:
	.zero	4
	.globl	a8
	.align	2
	.type	a8, @object
	.size	a8, 4
a8:
	.zero	4
	.globl	a9
	.align	2
	.type	a9, @object
	.size	a9, 4
a9:
	.zero	4
	.globl	a10
	.align	2
	.type	a10, @object
	.size	a10, 4
a10:
	.zero	4
	.globl	a11
	.align	2
	.type	a11, @object
	.size	a11, 4
a11:
	.zero	4
	.globl	a12
	.align	2
	.type	a12, @object
	.size	a12, 4
a12:
	.zero	4
	.globl	a13
	.align	2
	.type	a13, @object
	.size	a13, 4
a13:
	.zero	4
	.globl	a14
	.align	2
	.type	a14, @object
	.size	a14, 4
a14:
	.zero	4
	.globl	a15
	.align	2
	.type	a15, @object
	.size	a15, 4
a15:
	.zero	4
	.globl	a16
	.align	2
	.type	a16, @object
	.size	a16, 4
a16:
	.zero	4
	.globl	a17
	.align	2
	.type	a17, @object
	.size	a17, 4
a17:
	.zero	4
	.globl	a18
	.align	2
	.type	a18, @object
	.size	a18, 4
a18:
	.zero	4
	.globl	a19
	.align	2
	.type	a19, @object
	.size	a19, 4
a19:
	.zero	4
	.globl	a20
	.align	2
	.type	a20, @object
	.size	a20, 4
a20:
	.zero	4
	.globl	a21
	.align	2
	.type	a21, @object
	.size	a21, 4
a21:
	.zero	4
	.globl	a22
	.align	2
	.type	a22, @object
	.size	a22, 4
a22:
	.zero	4
	.globl	a23
	.align	2
	.type	a23, @object
	.size	a23, 4
a23:
	.zero	4
	.globl	a24
	.align	2
	.type	a24, @object
	.size	a24, 4
a24:
	.zero	4
	.globl	a25
	.align	2
	.type	a25, @object
	.size	a25, 4
a25:
	.zero	4
	.globl	a26
	.align	2
	.type	a26, @object
	.size	a26, 4
a26:
	.zero	4
	.globl	a27
	.align	2
	.type	a27, @object
	.size	a27, 4
a27:
	.zero	4
	.globl	a28
	.align	2
	.type	a28, @object
	.size	a28, 4
a28:
	.zero	4
	.globl	a29
	.align	2
	.type	a29, @object
	.size	a29, 4
a29:
	.zero	4
	.globl	a30
	.align	2
	.type	a30, @object
	.size	a30, 4
a30:
	.zero	4
	.globl	a31
	.align	2
	.type	a31, @object
	.size	a31, 4
a31:
	.zero	4
	.globl	a32
	.align	2
	.type	a32, @object
	.size	a32, 4
a32:
	.zero	4
	.globl	a33
	.align	2
	.type	a33, @object
	.size	a33, 4
a33:
	.zero	4
	.globl	a34
	.align	2
	.type	a34, @object
	.size	a34, 4
a34:
	.zero	4
	.globl	a35
	.align	2
	.type	a35, @object
	.size	a35, 4
a35:
	.zero	4
	.globl	a36
	.align	2
	.type	a36, @object
	.size	a36, 4
a36:
	.zero	4
	.globl	a37
	.align	2
	.type	a37, @object
	.size	a37, 4
a37:
	.zero	4
	.globl	a38
	.align	2
	.type	a38, @object
	.size	a38, 4
a38:
	.zero	4
	.globl	a39
	.align	2
	.type	a39, @object
	.size	a39, 4
a39:
	.zero	4
	.text
	.align	1
	.globl	testParam8
	.type	testParam8, @function
testParam8:
	addi	sp,sp,-48
	sd	s0,40(sp)
	addi	s0,sp,48
	mv	t4,a0
	mv	t3,a1
	mv	t1,a2
	mv	a0,a3
	mv	a1,a4
	mv	a2,a5
	mv	a3,a6
	mv	a4,a7
	mv	a5,t4
	sw	a5,-20(s0)
	mv	a5,t3
	sw	a5,-24(s0)
	mv	a5,t1
	sw	a5,-28(s0)
	mv	a5,a0
	sw	a5,-32(s0)
	mv	a5,a1
	sw	a5,-36(s0)
	mv	a5,a2
	sw	a5,-40(s0)
	mv	a5,a3
	sw	a5,-44(s0)
	mv	a5,a4
	sw	a5,-48(s0)
	lw	a5,-20(s0)
	mv	a4,a5
	lw	a5,-24(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-28(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-32(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-36(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-40(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-44(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-48(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	mv	a0,a5
	ld	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	testParam8, .-testParam8
	.align	1
	.globl	testParam16
	.type	testParam16, @function
testParam16:
	addi	sp,sp,-48
	sd	s0,40(sp)
	addi	s0,sp,48
	mv	t4,a0
	mv	t3,a1
	mv	t1,a2
	mv	a0,a3
	mv	a1,a4
	mv	a2,a5
	mv	a3,a6
	mv	a4,a7
	mv	a5,t4
	sw	a5,-20(s0)
	mv	a5,t3
	sw	a5,-24(s0)
	mv	a5,t1
	sw	a5,-28(s0)
	mv	a5,a0
	sw	a5,-32(s0)
	mv	a5,a1
	sw	a5,-36(s0)
	mv	a5,a2
	sw	a5,-40(s0)
	mv	a5,a3
	sw	a5,-44(s0)
	mv	a5,a4
	sw	a5,-48(s0)
	lw	a5,-20(s0)
	mv	a4,a5
	lw	a5,-24(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-28(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-32(s0)
	subw	a5,a5,a4
	sext.w	a5,a5
	lw	a4,-36(s0)
	subw	a5,a5,a4
	sext.w	a5,a5
	lw	a4,-40(s0)
	subw	a5,a5,a4
	sext.w	a5,a5
	lw	a4,-44(s0)
	subw	a5,a5,a4
	sext.w	a5,a5
	lw	a4,-48(s0)
	subw	a5,a5,a4
	sext.w	a5,a5
	lw	a4,0(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,8(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,16(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,24(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,32(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,40(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,48(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,56(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	mv	a0,a5
	ld	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	testParam16, .-testParam16
	.align	1
	.globl	testParam32
	.type	testParam32, @function
testParam32:
	addi	sp,sp,-48
	sd	s0,40(sp)
	addi	s0,sp,48
	mv	t4,a0
	mv	t3,a1
	mv	t1,a2
	mv	a0,a3
	mv	a1,a4
	mv	a2,a5
	mv	a3,a6
	mv	a4,a7
	mv	a5,t4
	sw	a5,-20(s0)
	mv	a5,t3
	sw	a5,-24(s0)
	mv	a5,t1
	sw	a5,-28(s0)
	mv	a5,a0
	sw	a5,-32(s0)
	mv	a5,a1
	sw	a5,-36(s0)
	mv	a5,a2
	sw	a5,-40(s0)
	mv	a5,a3
	sw	a5,-44(s0)
	mv	a5,a4
	sw	a5,-48(s0)
	lw	a5,-20(s0)
	mv	a4,a5
	lw	a5,-24(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-28(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-32(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-36(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-40(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-44(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-48(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,0(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,8(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,16(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,24(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,32(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,40(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,48(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,56(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,64(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,72(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,80(s0)
	subw	a5,a5,a4
	sext.w	a5,a5
	lw	a4,88(s0)
	subw	a5,a5,a4
	sext.w	a5,a5
	lw	a4,96(s0)
	subw	a5,a5,a4
	sext.w	a5,a5
	lw	a4,104(s0)
	subw	a5,a5,a4
	sext.w	a5,a5
	lw	a4,112(s0)
	subw	a5,a5,a4
	sext.w	a5,a5
	lw	a4,120(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,128(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,136(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,144(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,152(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,160(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,168(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,176(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	lw	a4,184(s0)
	addw	a5,a4,a5
	sext.w	a5,a5
	mv	a0,a5
	ld	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	testParam32, .-testParam32
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-352
	sd	ra,344(sp)
	sd	s0,336(sp)
	sd	s1,328(sp)
	sd	s2,320(sp)
	sd	s3,312(sp)
	sd	s4,304(sp)
	sd	s5,296(sp)
	sd	s6,288(sp)
	sd	s7,280(sp)
	sd	s8,272(sp)
	sd	s9,264(sp)
	sd	s10,256(sp)
	sd	s11,248(sp)
	addi	s0,sp,352
	lla	a5,a0
	sw	zero,0(a5)
	lla	a5,a1
	li	a4,1
	sw	a4,0(a5)
	lla	a5,a2
	li	a4,2
	sw	a4,0(a5)
	lla	a5,a3
	li	a4,3
	sw	a4,0(a5)
	lla	a5,a4
	li	a4,4
	sw	a4,0(a5)
	lla	a5,a5
	li	a4,5
	sw	a4,0(a5)
	lla	a5,a6
	li	a4,6
	sw	a4,0(a5)
	lla	a5,a7
	li	a4,7
	sw	a4,0(a5)
	lla	a5,a8
	li	a4,8
	sw	a4,0(a5)
	lla	a5,a9
	li	a4,9
	sw	a4,0(a5)
	lla	a5,a10
	sw	zero,0(a5)
	lla	a5,a11
	li	a4,1
	sw	a4,0(a5)
	lla	a5,a12
	li	a4,2
	sw	a4,0(a5)
	lla	a5,a13
	li	a4,3
	sw	a4,0(a5)
	lla	a5,a14
	li	a4,4
	sw	a4,0(a5)
	lla	a5,a15
	li	a4,5
	sw	a4,0(a5)
	lla	a5,a16
	li	a4,6
	sw	a4,0(a5)
	lla	a5,a17
	li	a4,7
	sw	a4,0(a5)
	lla	a5,a18
	li	a4,8
	sw	a4,0(a5)
	lla	a5,a19
	li	a4,9
	sw	a4,0(a5)
	lla	a5,a20
	sw	zero,0(a5)
	lla	a5,a21
	li	a4,1
	sw	a4,0(a5)
	lla	a5,a22
	li	a4,2
	sw	a4,0(a5)
	lla	a5,a23
	li	a4,3
	sw	a4,0(a5)
	lla	a5,a24
	li	a4,4
	sw	a4,0(a5)
	lla	a5,a25
	li	a4,5
	sw	a4,0(a5)
	lla	a5,a26
	li	a4,6
	sw	a4,0(a5)
	lla	a5,a27
	li	a4,7
	sw	a4,0(a5)
	lla	a5,a28
	li	a4,8
	sw	a4,0(a5)
	lla	a5,a29
	li	a4,9
	sw	a4,0(a5)
	lla	a5,a30
	sw	zero,0(a5)
	lla	a5,a31
	li	a4,1
	sw	a4,0(a5)
	lla	a5,a32
	li	a4,4
	sw	a4,0(a5)
	lla	a5,a33
	li	a4,5
	sw	a4,0(a5)
	lla	a5,a34
	li	a4,6
	sw	a4,0(a5)
	lla	a5,a35
	li	a4,7
	sw	a4,0(a5)
	lla	a5,a36
	li	a4,8
	sw	a4,0(a5)
	lla	a5,a37
	li	a4,9
	sw	a4,0(a5)
	lla	a5,a38
	sw	zero,0(a5)
	lla	a5,a39
	li	a4,1
	sw	a4,0(a5)
	lla	a5,a0
	lw	a0,0(a5)
	lla	a5,a1
	lw	a1,0(a5)
	lla	a5,a2
	lw	a2,0(a5)
	lla	a5,a3
	lw	a3,0(a5)
	lla	a5,a4
	lw	a4,0(a5)
	lla	a5,a5
	lw	t1,0(a5)
	lla	a5,a6
	lw	a6,0(a5)
	lla	a5,a7
	lw	a5,0(a5)
	mv	a7,a5
	mv	a5,t1
	call	testParam8
	mv	a5,a0
	mv	a4,a5
	lla	a5,a0
	sw	a4,0(a5)
	lla	a5,a32
	lw	t1,0(a5)
	lla	a5,a33
	lw	t3,0(a5)
	lla	a5,a34
	lw	t4,0(a5)
	lla	a5,a35
	lw	t5,0(a5)
	lla	a5,a36
	lw	t6,0(a5)
	lla	a5,a37
	lw	t0,0(a5)
	lla	a5,a38
	lw	t2,0(a5)
	lla	a5,a39
	lw	ra,0(a5)
	lla	a5,a8
	lw	a5,0(a5)
	lla	a4,a9
	lw	a4,0(a4)
	lla	a3,a10
	lw	a3,0(a3)
	lla	a2,a11
	lw	a2,0(a2)
	lla	a1,a12
	lw	a1,0(a1)
	lla	a0,a13
	lw	a0,0(a0)
	lla	a6,a14
	lw	a6,0(a6)
	lla	a7,a15
	lw	a7,0(a7)
	sd	a7,56(sp)
	sd	a6,48(sp)
	sd	a0,40(sp)
	sd	a1,32(sp)
	sd	a2,24(sp)
	sd	a3,16(sp)
	sd	a4,8(sp)
	sd	a5,0(sp)
	mv	a7,ra
	mv	a6,t2
	mv	a5,t0
	mv	a4,t6
	mv	a3,t5
	mv	a2,t4
	mv	a1,t3
	mv	a0,t1
	call	testParam16
	mv	a5,a0
	mv	a4,a5
	lla	a5,a0
	sw	a4,0(a5)
	lla	a5,a0
	lw	s9,0(a5)
	lla	a5,a1
	lw	s10,0(a5)
	lla	a5,a2
	lw	s11,0(a5)
	lla	a5,a3
	lw	a5,0(a5)
	sd	a5,-120(s0)
	lla	a5,a4
	lw	a4,0(a5)
	sd	a4,-128(s0)
	lla	a5,a5
	lw	a2,0(a5)
	sd	a2,-136(s0)
	lla	a5,a6
	lw	a1,0(a5)
	sd	a1,-144(s0)
	lla	a5,a7
	lw	a0,0(a5)
	sd	a0,-152(s0)
	lla	a5,a8
	lw	a5,0(a5)
	lla	a4,a9
	lw	a4,0(a4)
	lla	a3,a10
	lw	a3,0(a3)
	lla	a2,a11
	lw	a2,0(a2)
	lla	a1,a12
	lw	a1,0(a1)
	lla	a0,a13
	lw	a0,0(a0)
	lla	a6,a14
	lw	a6,0(a6)
	lla	a7,a15
	lw	a7,0(a7)
	lla	t1,a16
	lw	t1,0(t1)
	lla	t3,a17
	lw	t3,0(t3)
	lla	t4,a18
	lw	t4,0(t4)
	lla	t5,a19
	lw	t5,0(t5)
	lla	t6,a20
	lw	t6,0(t6)
	lla	t0,a21
	lw	t0,0(t0)
	lla	t2,a22
	lw	t2,0(t2)
	lla	ra,a23
	lw	ra,0(ra)
	lla	s1,a24
	lw	s1,0(s1)
	lla	s2,a25
	lw	s2,0(s2)
	lla	s3,a26
	lw	s3,0(s3)
	lla	s4,a27
	lw	s4,0(s4)
	lla	s5,a28
	lw	s5,0(s5)
	lla	s6,a29
	lw	s6,0(s6)
	lla	s7,a30
	lw	s7,0(s7)
	lla	s8,a31
	lw	s8,0(s8)
	sd	s8,184(sp)
	sd	s7,176(sp)
	sd	s6,168(sp)
	sd	s5,160(sp)
	sd	s4,152(sp)
	sd	s3,144(sp)
	sd	s2,136(sp)
	sd	s1,128(sp)
	sd	ra,120(sp)
	sd	t2,112(sp)
	sd	t0,104(sp)
	sd	t6,96(sp)
	sd	t5,88(sp)
	sd	t4,80(sp)
	sd	t3,72(sp)
	sd	t1,64(sp)
	sd	a7,56(sp)
	sd	a6,48(sp)
	sd	a0,40(sp)
	sd	a1,32(sp)
	sd	a2,24(sp)
	sd	a3,16(sp)
	sd	a4,8(sp)
	sd	a5,0(sp)
	ld	a7,-152(s0)
	ld	a6,-144(s0)
	ld	a5,-136(s0)
	ld	a4,-128(s0)
	ld	a3,-120(s0)
	mv	a2,s11
	mv	a1,s10
	mv	a0,s9
	call	testParam32
	mv	a5,a0
	mv	a4,a5
	lla	a5,a0
	sw	a4,0(a5)
	li	a5,0
	mv	a0,a5
	ld	ra,344(sp)
	ld	s0,336(sp)
	ld	s1,328(sp)
	ld	s2,320(sp)
	ld	s3,312(sp)
	ld	s4,304(sp)
	ld	s5,296(sp)
	ld	s6,288(sp)
	ld	s7,280(sp)
	ld	s8,272(sp)
	ld	s9,264(sp)
	ld	s10,256(sp)
	ld	s11,248(sp)
	addi	sp,sp,352
	jr	ra
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
