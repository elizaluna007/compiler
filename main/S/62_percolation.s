	.file	"62_percolation.c"
	.text
	.comm	array, 440, 5
	.comm	n, 4, 2
	.globl	init
	.def	init;	.scl	2;	.type	32;	.endef
	.seh_proc	init
init:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L2
.L3:
	leaq	array(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	$-1, (%rax,%rdx,4)
	addl	$1, -4(%rbp)
.L2:
	movl	16(%rbp), %eax
	imull	16(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, -4(%rbp)
	jle	.L3
	nop
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	findfa
	.def	findfa;	.scl	2;	.type	32;	.endef
	.seh_proc	findfa
findfa:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	leaq	array(%rip), %rax
	movl	16(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	%eax, 16(%rbp)
	jne	.L5
	movl	16(%rbp), %eax
	jmp	.L6
.L5:
	leaq	array(%rip), %rax
	movl	16(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	movl	%eax, %ecx
	call	findfa
	movl	%eax, %ecx
	leaq	array(%rip), %rax
	movl	16(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	leaq	array(%rip), %rax
	movl	16(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
.L6:
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	mmerge
	.def	mmerge;	.scl	2;	.type	32;	.endef
	.seh_proc	mmerge
mmerge:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	16(%rbp), %ecx
	call	findfa
	movl	%eax, -4(%rbp)
	movl	24(%rbp), %eax
	movl	%eax, %ecx
	call	findfa
	movl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	je	.L9
	leaq	array(%rip), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movl	-8(%rbp), %ecx
	movl	%ecx, (%rax,%rdx,4)
.L9:
	nop
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
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$88, %rsp
	.seh_stackalloc	88
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	call	__main
	movl	$1, -52(%rbp)
	jmp	.L11
.L21:
	subl	$1, -52(%rbp)
	leaq	n(%rip), %rax
	movl	$4, (%rax)
	movl	$10, -64(%rbp)
	movl	$0, -56(%rbp)
	movl	$0, -60(%rbp)
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	init
	leaq	n(%rip), %rax
	movl	(%rax), %edx
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	imull	%edx, %eax
	addl	$1, %eax
	movl	%eax, -68(%rbp)
	jmp	.L12
.L20:
	call	getint
	movl	%eax, -72(%rbp)
	call	getint
	movl	%eax, -76(%rbp)
	cmpl	$0, -60(%rbp)
	jne	.L13
	movl	-72(%rbp), %eax
	leal	-1(%rax), %edx
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	imull	%edx, %eax
	movl	-76(%rbp), %edx
	addl	%edx, %eax
	movl	%eax, -80(%rbp)
	leaq	array(%rip), %rax
	movl	-80(%rbp), %edx
	movslq	%edx, %rdx
	movl	-80(%rbp), %ecx
	movl	%ecx, (%rax,%rdx,4)
	cmpl	$1, -72(%rbp)
	jne	.L14
	leaq	array(%rip), %rax
	movl	$0, (%rax)
	movl	-80(%rbp), %eax
	movl	$0, %edx
	movl	%eax, %ecx
	call	mmerge
.L14:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -72(%rbp)
	jne	.L15
	leaq	array(%rip), %rax
	movl	-68(%rbp), %edx
	movslq	%edx, %rdx
	movl	-68(%rbp), %ecx
	movl	%ecx, (%rax,%rdx,4)
	movl	-68(%rbp), %edx
	movl	-80(%rbp), %eax
	movl	%eax, %ecx
	call	mmerge
.L15:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -76(%rbp)
	jge	.L16
	movl	-80(%rbp), %eax
	leal	1(%rax), %edx
	leaq	array(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$-1, %eax
	je	.L16
	movl	-80(%rbp), %eax
	leal	1(%rax), %edx
	movl	-80(%rbp), %eax
	movl	%eax, %ecx
	call	mmerge
.L16:
	cmpl	$1, -76(%rbp)
	jle	.L17
	movl	-80(%rbp), %eax
	leal	-1(%rax), %edx
	leaq	array(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$-1, %eax
	je	.L17
	movl	-80(%rbp), %eax
	leal	-1(%rax), %edx
	movl	-80(%rbp), %eax
	movl	%eax, %ecx
	call	mmerge
.L17:
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, -72(%rbp)
	jge	.L18
	leaq	n(%rip), %rax
	movl	(%rax), %edx
	movl	-80(%rbp), %eax
	addl	%eax, %edx
	leaq	array(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$-1, %eax
	je	.L18
	leaq	n(%rip), %rax
	movl	(%rax), %edx
	movl	-80(%rbp), %eax
	addl	%eax, %edx
	movl	-80(%rbp), %eax
	movl	%eax, %ecx
	call	mmerge
.L18:
	cmpl	$1, -72(%rbp)
	jle	.L19
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	movl	-80(%rbp), %edx
	subl	%eax, %edx
	leaq	array(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$-1, %eax
	je	.L19
	leaq	n(%rip), %rax
	movl	(%rax), %eax
	movl	-80(%rbp), %edx
	subl	%eax, %edx
	movl	-80(%rbp), %eax
	movl	%eax, %ecx
	call	mmerge
.L19:
	leaq	array(%rip), %rax
	movl	(%rax), %eax
	cmpl	$-1, %eax
	je	.L13
	leaq	array(%rip), %rax
	movl	-68(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$-1, %eax
	je	.L13
	movl	$0, %ecx
	call	findfa
	movl	%eax, %ebx
	movl	-68(%rbp), %eax
	movl	%eax, %ecx
	call	findfa
	cmpl	%eax, %ebx
	jne	.L13
	movl	$1, -60(%rbp)
	movl	-56(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -84(%rbp)
	movl	-84(%rbp), %eax
	movl	%eax, %ecx
	call	putint
	movl	$10, %ecx
	call	putch
.L13:
	addl	$1, -56(%rbp)
.L12:
	movl	-56(%rbp), %eax
	cmpl	-64(%rbp), %eax
	jl	.L20
	cmpl	$0, -60(%rbp)
	jne	.L11
	movl	$-1, %ecx
	call	putint
	movl	$10, %ecx
	call	putch
.L11:
	cmpl	$0, -52(%rbp)
	jne	.L21
	movl	$0, %eax
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	getint;	.scl	2;	.type	32;	.endef
	.def	putint;	.scl	2;	.type	32;	.endef
	.def	putch;	.scl	2;	.type	32;	.endef
