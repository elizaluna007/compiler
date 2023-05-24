	.file	"28_while_test3.c"
	.text
	.comm	g, 4, 2
	.comm	h, 4, 2
	.comm	f, 4, 2
	.comm	e, 4, 2
	.globl	EightWhile
	.def	EightWhile;	.scl	2;	.type	32;	.endef
	.seh_proc	EightWhile
EightWhile:
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
.L17:
	addl	$3, -4(%rbp)
	jmp	.L3
.L16:
	addl	$1, -8(%rbp)
	jmp	.L4
.L15:
	subl	$1, -12(%rbp)
	jmp	.L5
.L14:
	addl	$3, -16(%rbp)
	jmp	.L6
.L13:
	leaq	e(%rip), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	leaq	e(%rip), %rax
	movl	%edx, (%rax)
	jmp	.L7
.L12:
	leaq	f(%rip), %rax
	movl	(%rax), %eax
	leal	-2(%rax), %edx
	leaq	f(%rip), %rax
	movl	%edx, (%rax)
	jmp	.L8
.L11:
	leaq	g(%rip), %rax
	movl	(%rax), %eax
	leal	10(%rax), %edx
	leaq	g(%rip), %rax
	movl	%edx, (%rax)
	jmp	.L9
.L10:
	leaq	h(%rip), %rax
	movl	(%rax), %eax
	leal	8(%rax), %edx
	leaq	h(%rip), %rax
	movl	%edx, (%rax)
.L9:
	leaq	h(%rip), %rax
	movl	(%rax), %eax
	cmpl	$9, %eax
	jle	.L10
	leaq	h(%rip), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	leaq	h(%rip), %rax
	movl	%edx, (%rax)
.L8:
	leaq	g(%rip), %rax
	movl	(%rax), %eax
	cmpl	$2, %eax
	jle	.L11
	leaq	g(%rip), %rax
	movl	(%rax), %eax
	leal	-8(%rax), %edx
	leaq	g(%rip), %rax
	movl	%edx, (%rax)
.L7:
	leaq	f(%rip), %rax
	movl	(%rax), %eax
	cmpl	$2, %eax
	jg	.L12
	leaq	f(%rip), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	leaq	f(%rip), %rax
	movl	%edx, (%rax)
.L6:
	leaq	e(%rip), %rax
	movl	(%rax), %eax
	cmpl	$1, %eax
	jg	.L13
	leaq	e(%rip), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	leaq	e(%rip), %rax
	movl	%edx, (%rax)
.L5:
	cmpl	$19, -16(%rbp)
	jle	.L14
	subl	$1, -16(%rbp)
.L4:
	cmpl	$7, -12(%rbp)
	je	.L15
	addl	$1, -12(%rbp)
.L3:
	cmpl	$9, -8(%rbp)
	jle	.L16
	subl	$2, -8(%rbp)
.L2:
	cmpl	$19, -4(%rbp)
	jle	.L17
	movl	-8(%rbp), %edx
	movl	-16(%rbp), %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%eax, %edx
	leaq	e(%rip), %rax
	movl	(%rax), %ecx
	movl	-16(%rbp), %eax
	addl	%eax, %ecx
	leaq	g(%rip), %rax
	movl	(%rax), %eax
	subl	%eax, %ecx
	leaq	h(%rip), %rax
	movl	(%rax), %eax
	addl	%ecx, %eax
	subl	%eax, %edx
	movl	%edx, %eax
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
	leaq	g(%rip), %rax
	movl	$1, (%rax)
	leaq	h(%rip), %rax
	movl	$2, (%rax)
	leaq	e(%rip), %rax
	movl	$4, (%rax)
	leaq	f(%rip), %rax
	movl	$6, (%rax)
	call	EightWhile
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
