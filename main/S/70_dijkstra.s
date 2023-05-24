	.file	"70_dijkstra.c"
	.text
	.globl	INF
	.section .rdata,"dr"
	.align 4
INF:
	.long	65535
	.comm	e, 1024, 5
	.comm	book, 64, 5
	.comm	dis, 64, 5
	.comm	n, 4, 2
	.comm	m, 4, 2
	.comm	v1, 4, 2
	.comm	v2, 4, 2
	.comm	w, 4, 2
	.text
	.globl	Dijkstra
	.def	Dijkstra;	.scl	2;	.type	32;	.endef
	.seh_proc	Dijkstra
Dijkstra:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	$1, -4(%rbp)
	jmp	.L2
.L3:
	leaq	e(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	addq	$16, %rdx
	movl	(%rax,%rdx,4), %ecx
	leaq	dis(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	leaq	book(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	$0, (%rax,%rdx,4)
	addl	$1, -4(%rbp)
.L2:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jle	.L3
	leaq	book(%rip), %rax
	movl	$1, 4(%rax)
	movl	$1, -4(%rbp)
	jmp	.L4
.L11:
	movl	$65535, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	$1, -16(%rbp)
	jmp	.L5
.L7:
	leaq	dis(%rip), %rax
	movl	-16(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	%eax, -8(%rbp)
	jle	.L6
	leaq	book(%rip), %rax
	movl	-16(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	testl	%eax, %eax
	jne	.L6
	leaq	dis(%rip), %rax
	movl	-16(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, -8(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, -12(%rbp)
.L6:
	addl	$1, -16(%rbp)
.L5:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -16(%rbp)
	jle	.L7
	leaq	book(%rip), %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	movl	$1, (%rax,%rdx,4)
	movl	$1, -20(%rbp)
	jmp	.L8
.L10:
	leaq	e(%rip), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	-12(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$4, %rcx
	addq	%rcx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	$65535, %edx
	cmpl	%edx, %eax
	jge	.L9
	leaq	dis(%rip), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %r8d
	leaq	dis(%rip), %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %r9d
	leaq	e(%rip), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	-12(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$4, %rcx
	addq	%rcx, %rdx
	movl	(%rax,%rdx,4), %eax
	addl	%r9d, %eax
	cmpl	%eax, %r8d
	jle	.L9
	leaq	dis(%rip), %rax
	movl	-12(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %r8d
	leaq	e(%rip), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	-12(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$4, %rcx
	addq	%rcx, %rdx
	movl	(%rax,%rdx,4), %eax
	leal	(%r8,%rax), %ecx
	leaq	dis(%rip), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
.L9:
	addl	$1, -20(%rbp)
.L8:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jle	.L10
	addl	$1, -4(%rbp)
.L4:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L11
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
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	call	getint
	movl	%eax, %edx
	leaq	n(%rip), %rax
	movl	%edx, (%rax)
	call	getint
	movl	%eax, %edx
	leaq	m(%rip), %rax
	movl	%edx, (%rax)
	movl	$1, -4(%rbp)
	jmp	.L13
.L18:
	movl	$1, -8(%rbp)
	jmp	.L14
.L17:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jne	.L15
	leaq	e(%rip), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$4, %rcx
	addq	%rcx, %rdx
	movl	$0, (%rax,%rdx,4)
	jmp	.L16
.L15:
	movl	$65535, %r8d
	leaq	e(%rip), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	movl	-4(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$4, %rcx
	addq	%rcx, %rdx
	movl	%r8d, (%rax,%rdx,4)
.L16:
	addl	$1, -8(%rbp)
.L14:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jle	.L17
	addl	$1, -4(%rbp)
.L13:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jle	.L18
	movl	$1, -4(%rbp)
	jmp	.L19
.L20:
	call	getint
	movl	%eax, -12(%rbp)
	call	getint
	movl	%eax, -16(%rbp)
	call	getint
	movl	%eax, %r8d
	leaq	e(%rip), %rax
	movl	-16(%rbp), %edx
	movslq	%edx, %rdx
	movl	-12(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$4, %rcx
	addq	%rcx, %rdx
	movl	%r8d, (%rax,%rdx,4)
	addl	$1, -4(%rbp)
.L19:
	leaq	m(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jle	.L20
	call	Dijkstra
	movl	$1, -4(%rbp)
	jmp	.L21
.L22:
	leaq	dis(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, %ecx
	call	putint
	movl	$32, %ecx
	call	putch
	addl	$1, -4(%rbp)
.L21:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jle	.L22
	movl	$10, %ecx
	call	putch
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	getint;	.scl	2;	.type	32;	.endef
	.def	putint;	.scl	2;	.type	32;	.endef
	.def	putch;	.scl	2;	.type	32;	.endef
