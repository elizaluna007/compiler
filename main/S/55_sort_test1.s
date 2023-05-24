	.file	"55_sort_test1.c"
	.text
	.comm	n, 4, 2
	.globl	bubblesort
	.def	bubblesort;	.scl	2;	.type	32;	.endef
	.seh_proc	bubblesort
bubblesort:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L6:
	movl	$0, -8(%rbp)
	jmp	.L3
.L5:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rcx
	movq	16(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jle	.L4
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rax, %rdx
	movl	-8(%rbp), %eax
	cltq
	addq	$1, %rax
	leaq	0(,%rax,4), %rcx
	movq	16(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rdx), %edx
	movl	%edx, (%rax)
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	-12(%rbp), %edx
	movl	%edx, (%rax)
.L4:
	addl	$1, -8(%rbp)
.L3:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	subl	-4(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -8(%rbp)
	jl	.L5
	addl	$1, -4(%rbp)
.L2:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	subl	$1, %eax
	cmpl	%eax, -4(%rbp)
	jl	.L6
	movl	$0, %eax
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
	subq	$80, %rsp
	.seh_stackalloc	80
	.seh_endprologue
	call	__main
	leaq	n(%rip), %rax
	movl	$10, (%rax)
	movl	$4, -48(%rbp)
	movl	$3, -44(%rbp)
	movl	$9, -40(%rbp)
	movl	$2, -36(%rbp)
	movl	$0, -32(%rbp)
	movl	$1, -28(%rbp)
	movl	$6, -24(%rbp)
	movl	$5, -20(%rbp)
	movl	$7, -16(%rbp)
	movl	$8, -12(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rcx
	call	bubblesort
	movl	%eax, -4(%rbp)
	jmp	.L9
.L10:
	movl	-4(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, %ecx
	call	putint
	movl	$10, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, %ecx
	call	putch
	addl	$1, -4(%rbp)
.L9:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L10
	movl	$0, %eax
	addq	$80, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putint;	.scl	2;	.type	32;	.endef
	.def	putch;	.scl	2;	.type	32;	.endef
