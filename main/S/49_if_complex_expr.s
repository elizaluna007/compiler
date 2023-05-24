	.file	"49_if_complex_expr.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	call	__main
	movl	$5, -4(%rbp)
	movl	$5, -8(%rbp)
	movl	$1, -12(%rbp)
	movl	$-2, -16(%rbp)
	movl	$2, -20(%rbp)
	cmpl	$-1, -16(%rbp)
	jl	.L2
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	je	.L3
	movl	-12(%rbp), %eax
	addl	$3, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L3
.L2:
	movl	-20(%rbp), %eax
	movl	%eax, %ecx
	call	putint
.L3:
	movl	-16(%rbp), %edx
	movl	%edx, %eax
	sarl	$31, %eax
	shrl	$31, %eax
	addl	%eax, %edx
	andl	$1, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	cmpl	$-67, %eax
	jl	.L4
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	je	.L5
	movl	-12(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L5
.L4:
	movl	$4, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %ecx
	call	putint
.L5:
	movl	$0, %eax
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putint;	.scl	2;	.type	32;	.endef
