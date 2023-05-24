	.file	"95_float.c"
	.text
	.globl	RADIUS
	.section .rdata,"dr"
	.align 4
RADIUS:
	.long	1085276160
	.globl	PI
	.align 4
PI:
	.long	1078530011
	.globl	EPS
	.align 4
EPS:
	.long	897988541
	.globl	PI_HEX
	.align 4
PI_HEX:
	.long	1078530011
	.globl	HEX2
	.align 4
HEX2:
	.long	1033895936
	.globl	FACT
	.align 4
FACT:
	.long	-956241920
	.globl	EVAL1
	.align 4
EVAL1:
	.long	1119752446
	.globl	EVAL2
	.align 4
EVAL2:
	.long	1107966695
	.globl	EVAL3
	.align 4
EVAL3:
	.long	1107966695
	.globl	CONV1
	.align 4
CONV1:
	.long	1130954752
	.globl	CONV2
	.align 4
CONV2:
	.long	1166012416
	.globl	MAX
	.align 4
MAX:
	.long	1000000000
	.globl	TWO
	.align 4
TWO:
	.long	2
	.globl	THREE
	.align 4
THREE:
	.long	3
	.globl	FIVE
	.align 4
FIVE:
	.long	5
	.text
	.globl	float_abs
	.def	float_abs;	.scl	2;	.type	32;	.endef
	.seh_proc	float_abs
float_abs:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movss	%xmm0, 16(%rbp)
	pxor	%xmm0, %xmm0
	comiss	16(%rbp), %xmm0
	jbe	.L6
	movss	16(%rbp), %xmm0
	movss	.LC1(%rip), %xmm1
	xorps	%xmm1, %xmm0
	jmp	.L4
.L6:
	movss	16(%rbp), %xmm0
.L4:
	popq	%rbp
	ret
	.seh_endproc
	.globl	circle_area
	.def	circle_area;	.scl	2;	.type	32;	.endef
	.seh_proc	circle_area
circle_area:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cvtsi2ss	16(%rbp), %xmm1
	movss	.LC2(%rip), %xmm0
	mulss	%xmm0, %xmm1
	cvtsi2ss	16(%rbp), %xmm0
	mulss	%xmm0, %xmm1
	movl	16(%rbp), %eax
	imull	16(%rbp), %eax
	cvtsi2ss	%eax, %xmm2
	movss	.LC2(%rip), %xmm0
	mulss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	movss	.LC3(%rip), %xmm1
	divss	%xmm1, %xmm0
	popq	%rbp
	ret
	.seh_endproc
	.globl	float_eq
	.def	float_eq;	.scl	2;	.type	32;	.endef
	.seh_proc	float_eq
float_eq:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movss	%xmm0, 16(%rbp)
	movss	%xmm1, 24(%rbp)
	movss	16(%rbp), %xmm0
	subss	24(%rbp), %xmm0
	call	float_abs
	movaps	%xmm0, %xmm1
	movss	.LC4(%rip), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L14
	movl	$1, %eax
	jmp	.L12
.L14:
	movl	$0, %eax
.L12:
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	error
	.def	error;	.scl	2;	.type	32;	.endef
	.seh_proc	error
error:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	$101, %ecx
	call	putch
	movl	$114, %ecx
	call	putch
	movl	$114, %ecx
	call	putch
	movl	$111, %ecx
	call	putch
	movl	$114, %ecx
	call	putch
	movl	$10, %ecx
	call	putch
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	ok
	.def	ok;	.scl	2;	.type	32;	.endef
	.seh_proc	ok
ok:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	$111, %ecx
	call	putch
	movl	$107, %ecx
	call	putch
	movl	$10, %ecx
	call	putch
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	assert
	.def	assert;	.scl	2;	.type	32;	.endef
	.seh_proc	assert
assert:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cmpl	$0, 16(%rbp)
	jne	.L18
	call	error
	jmp	.L20
.L18:
	call	ok
.L20:
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	assert_not
	.def	assert_not;	.scl	2;	.type	32;	.endef
	.seh_proc	assert_not
assert_not:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cmpl	$0, 16(%rbp)
	je	.L22
	call	error
	jmp	.L24
.L22:
	call	ok
.L24:
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	addq	$-128, %rsp
	.seh_stackalloc	128
	movaps	%xmm6, -16(%rbp)
	.seh_savexmm	%xmm6, 112
	.seh_endprologue
	call	__main
	movss	.LC5(%rip), %xmm0
	movss	%xmm0, -28(%rbp)
	movss	.LC6(%rip), %xmm0
	movl	.LC7(%rip), %eax
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	float_eq
	movl	%eax, %ecx
	call	assert_not
	movss	.LC8(%rip), %xmm0
	movl	.LC9(%rip), %eax
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	float_eq
	movl	%eax, %ecx
	call	assert_not
	movss	.LC8(%rip), %xmm0
	movl	.LC8(%rip), %eax
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	float_eq
	movl	%eax, %ecx
	call	assert
	movl	$5, %eax
	movl	%eax, %ecx
	call	circle_area
	movaps	%xmm0, %xmm6
	movss	.LC10(%rip), %xmm0
	cvttss2si	%xmm0, %eax
	movl	%eax, %ecx
	call	circle_area
	movaps	%xmm6, %xmm1
	call	float_eq
	movl	%eax, %ecx
	call	assert
	movss	.LC11(%rip), %xmm0
	movl	.LC12(%rip), %eax
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	float_eq
	movl	%eax, %ecx
	call	assert_not
	call	ok
	call	ok
	call	ok
	movl	$1, -20(%rbp)
	movl	$0, -24(%rbp)
	movq	$0, -96(%rbp)
	movq	$0, -88(%rbp)
	movq	$0, -80(%rbp)
	movq	$0, -72(%rbp)
	movq	$0, -64(%rbp)
	movss	.LC13(%rip), %xmm0
	movss	%xmm0, -96(%rbp)
	movss	.LC3(%rip), %xmm0
	movss	%xmm0, -92(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	getfarray
	movl	%eax, -32(%rbp)
	jmp	.L26
.L27:
	call	getfloat
	cvtsi2ss	%eax, %xmm0
	movss	%xmm0, -36(%rbp)
	movss	.LC2(%rip), %xmm0
	mulss	-36(%rbp), %xmm0
	movss	-36(%rbp), %xmm1
	mulss	%xmm1, %xmm0
	movss	%xmm0, -40(%rbp)
	movss	-36(%rbp), %xmm0
	cvttss2si	%xmm0, %eax
	movl	%eax, %ecx
	call	circle_area
	movd	%xmm0, %eax
	movl	%eax, -44(%rbp)
	movl	-24(%rbp), %eax
	cltq
	movss	-96(%rbp,%rax,4), %xmm0
	addss	-36(%rbp), %xmm0
	movl	-24(%rbp), %eax
	cltq
	movss	%xmm0, -96(%rbp,%rax,4)
	cvtss2sd	-40(%rbp), %xmm0
	call	putfloat
	movl	$32, %ecx
	call	putch
	cvtss2sd	-44(%rbp), %xmm0
	call	putint
	movl	$10, %ecx
	call	putch
	movl	-20(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -20(%rbp)
	addl	$1, -24(%rbp)
.L26:
	movl	$1000000000, %eax
	cmpl	%eax, -20(%rbp)
	jl	.L27
	leaq	-96(%rbp), %rax
	movl	-32(%rbp), %ecx
	movq	%rax, %rdx
	call	putfarray
	movl	$0, %eax
	movaps	-16(%rbp), %xmm6
	subq	$-128, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 16
.LC1:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.align 4
.LC2:
	.long	1078530011
	.align 4
.LC3:
	.long	1073741824
	.align 4
.LC4:
	.long	897988541
	.align 4
.LC5:
	.long	-1110651699
	.align 4
.LC6:
	.long	-956241920
	.align 4
.LC7:
	.long	1033895936
	.align 4
.LC8:
	.long	1107966695
	.align 4
.LC9:
	.long	1119752446
	.align 4
.LC10:
	.long	1085276160
	.align 4
.LC11:
	.long	1166012416
	.align 4
.LC12:
	.long	1130954752
	.align 4
.LC13:
	.long	1065353216
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putch;	.scl	2;	.type	32;	.endef
	.def	getfarray;	.scl	2;	.type	32;	.endef
	.def	getfloat;	.scl	2;	.type	32;	.endef
	.def	putfloat;	.scl	2;	.type	32;	.endef
	.def	putint;	.scl	2;	.type	32;	.endef
	.def	putfarray;	.scl	2;	.type	32;	.endef
