	.file	"66_exgcd.c"
	.text
	.globl	exgcd
	.def	exgcd;	.scl	2;	.type	32;	.endef
	.seh_proc	exgcd
exgcd:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movq	%r9, 40(%rbp)
	cmpl	$0, 24(%rbp)
	jne	.L2
	movq	32(%rbp), %rax
	movl	$1, (%rax)
	movq	40(%rbp), %rax
	movl	$0, (%rax)
	movl	16(%rbp), %eax
	jmp	.L3
.L2:
	movl	16(%rbp), %eax
	cltd
	idivl	24(%rbp)
	movl	%edx, %r10d
	movq	40(%rbp), %rcx
	movq	32(%rbp), %rdx
	movl	24(%rbp), %eax
	movq	%rcx, %r9
	movq	%rdx, %r8
	movl	%r10d, %edx
	movl	%eax, %ecx
	call	exgcd
	movl	%eax, -4(%rbp)
	movq	32(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -8(%rbp)
	movq	40(%rbp), %rax
	movl	(%rax), %edx
	movq	32(%rbp), %rax
	movl	%edx, (%rax)
	movl	16(%rbp), %eax
	cltd
	idivl	24(%rbp)
	movl	%eax, %edx
	movq	40(%rbp), %rax
	movl	(%rax), %eax
	imull	%edx, %eax
	movl	-8(%rbp), %edx
	subl	%eax, %edx
	movq	40(%rbp), %rax
	movl	%edx, (%rax)
	movl	-4(%rbp), %eax
.L3:
	addq	$48, %rsp
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
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	movl	$7, -4(%rbp)
	movl	$15, -8(%rbp)
	movl	$1, -12(%rbp)
	movl	$1, -16(%rbp)
	leaq	-16(%rbp), %r8
	leaq	-12(%rbp), %rcx
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movq	%r8, %r9
	movq	%rcx, %r8
	movl	%eax, %ecx
	call	exgcd
	movl	-12(%rbp), %eax
	cltd
	idivl	-8(%rbp)
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	cltd
	idivl	-8(%rbp)
	movl	%edx, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %ecx
	call	putint
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putint;	.scl	2;	.type	32;	.endef
