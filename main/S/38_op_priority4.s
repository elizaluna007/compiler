	.file	"38_op_priority4.c"
	.text
	.comm	a, 4, 2
	.comm	b, 4, 2
	.comm	c, 4, 2
	.comm	d, 4, 2
	.comm	e, 4, 2
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
	leaq	a(%rip), %rax
	movl	$0, (%rax)
	leaq	b(%rip), %rax
	movl	$1, (%rax)
	leaq	c(%rip), %rax
	movl	$1, (%rax)
	leaq	d(%rip), %rax
	movl	$1, (%rax)
	leaq	e(%rip), %rax
	movl	$1, (%rax)
	movl	$0, -4(%rbp)
	leaq	a(%rip), %rax
	movl	(%rax), %edx
	leaq	b(%rip), %rax
	movl	(%rax), %ecx
	leaq	c(%rip), %rax
	movl	(%rax), %eax
	imull	%ecx, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	leaq	d(%rip), %rax
	movl	(%rax), %r8d
	leaq	a(%rip), %rax
	movl	(%rax), %edx
	leaq	c(%rip), %rax
	movl	(%rax), %r9d
	movl	%edx, %eax
	cltd
	idivl	%r9d
	subl	%eax, %r8d
	movl	%r8d, %eax
	cmpl	%eax, %ecx
	jne	.L2
	leaq	a(%rip), %rax
	movl	(%rax), %edx
	leaq	b(%rip), %rax
	movl	(%rax), %eax
	imull	%edx, %eax
	leaq	c(%rip), %rdx
	movl	(%rdx), %ecx
	cltd
	idivl	%ecx
	movl	%eax, %ecx
	leaq	e(%rip), %rax
	movl	(%rax), %edx
	leaq	d(%rip), %rax
	movl	(%rax), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	je	.L2
	leaq	a(%rip), %rax
	movl	(%rax), %edx
	leaq	b(%rip), %rax
	movl	(%rax), %eax
	addl	%eax, %edx
	leaq	c(%rip), %rax
	movl	(%rax), %eax
	addl	%eax, %edx
	leaq	d(%rip), %rax
	movl	(%rax), %ecx
	leaq	e(%rip), %rax
	movl	(%rax), %eax
	addl	%ecx, %eax
	cmpl	%eax, %edx
	jne	.L3
.L2:
	movl	$1, -4(%rbp)
.L3:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
