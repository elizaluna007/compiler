	.file	"27_while_test2.c"
	.text
	.globl	FourWhile
	.def	FourWhile;	.scl	2;	.type	32;	.endef
	.seh_proc	FourWhile
FourWhile:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	$5, -4(%rbp)
	movl	$6, -8(%rbp)
	movl	$7, -12(%rbp)
	movl	$10, -16(%rbp)
	jmp	.L2
.L9:
	addl	$3, -4(%rbp)
	jmp	.L3
.L8:
	addl	$1, -8(%rbp)
	jmp	.L4
.L7:
	subl	$1, -12(%rbp)
	jmp	.L5
.L6:
	addl	$3, -16(%rbp)
.L5:
	cmpl	$19, -16(%rbp)
	jle	.L6
	subl	$1, -16(%rbp)
.L4:
	cmpl	$7, -12(%rbp)
	je	.L7
	addl	$1, -12(%rbp)
.L3:
	cmpl	$9, -8(%rbp)
	jle	.L8
	subl	$2, -8(%rbp)
.L2:
	cmpl	$19, -4(%rbp)
	jle	.L9
	movl	-8(%rbp), %edx
	movl	-16(%rbp), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	addq	$16, %rsp
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
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	call	FourWhile
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
