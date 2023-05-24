	.file	"51_short_circuit3.c"
	.text
	.comm	a, 4, 2
	.comm	b, 4, 2
	.comm	d, 4, 2
	.globl	set_a
	.def	set_a;	.scl	2;	.type	32;	.endef
	.seh_proc	set_a
set_a:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	leaq	a(%rip), %rax
	movl	16(%rbp), %edx
	movl	%edx, (%rax)
	leaq	a(%rip), %rax
	movl	(%rax), %eax
	popq	%rbp
	ret
	.seh_endproc
	.globl	set_b
	.def	set_b;	.scl	2;	.type	32;	.endef
	.seh_proc	set_b
set_b:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	leaq	b(%rip), %rax
	movl	16(%rbp), %edx
	movl	%edx, (%rax)
	leaq	b(%rip), %rax
	movl	(%rax), %eax
	popq	%rbp
	ret
	.seh_endproc
	.globl	set_d
	.def	set_d;	.scl	2;	.type	32;	.endef
	.seh_proc	set_d
set_d:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	leaq	d(%rip), %rax
	movl	16(%rbp), %edx
	movl	%edx, (%rax)
	leaq	d(%rip), %rax
	movl	(%rax), %eax
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
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	call	__main
	leaq	a(%rip), %rax
	movl	$2, (%rax)
	leaq	b(%rip), %rax
	movl	$3, (%rax)
	movl	$0, %ecx
	call	set_a
	testl	%eax, %eax
	je	.L8
	movl	$1, %ecx
	call	set_b
.L8:
	leaq	a(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putint
	movl	$32, %ecx
	call	putch
	leaq	b(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putint
	movl	$32, %ecx
	call	putch
	leaq	a(%rip), %rax
	movl	$2, (%rax)
	leaq	b(%rip), %rax
	movl	$3, (%rax)
	movl	$0, %ecx
	call	set_a
	testl	%eax, %eax
	je	.L9
	movl	$1, %ecx
	call	set_b
.L9:
	leaq	a(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putint
	movl	$32, %ecx
	call	putch
	leaq	b(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putint
	movl	$10, %ecx
	call	putch
	movl	$1, -4(%rbp)
	leaq	d(%rip), %rax
	movl	$2, (%rax)
	cmpl	$0, -4(%rbp)
	jle	.L10
	movl	$3, %ecx
	call	set_d
.L10:
	leaq	d(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putint
	movl	$32, %ecx
	call	putch
	cmpl	$1, -4(%rbp)
	jle	.L11
	movl	$4, %ecx
	call	set_d
.L11:
	leaq	d(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putint
	movl	$10, %ecx
	call	putch
	movl	$65, %ecx
	call	putch
	movl	$68, %ecx
	call	putch
	movl	$70, %ecx
	call	putch
	movl	$10, %ecx
	call	putch
	movl	$0, -8(%rbp)
	movl	$1, -12(%rbp)
	movl	$2, -16(%rbp)
	movl	$3, -20(%rbp)
	movl	$4, -24(%rbp)
	jmp	.L12
.L14:
	movl	$32, %ecx
	call	putch
.L12:
	cmpl	$0, -8(%rbp)
	je	.L13
	cmpl	$0, -12(%rbp)
	jne	.L14
.L13:
	cmpl	$0, -8(%rbp)
	jne	.L15
	cmpl	$0, -12(%rbp)
	je	.L16
.L15:
	movl	$67, %ecx
	call	putch
.L16:
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	.L17
	movl	-12(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jg	.L18
.L17:
	movl	$72, %ecx
	call	putch
.L18:
	movl	-16(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jl	.L22
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	je	.L22
	movl	$73, %ecx
	call	putch
.L22:
	movl	$74, %ecx
	call	putch
	cmpl	$0, -12(%rbp)
	sete	%al
	movzbl	%al, %eax
	cmpl	%eax, -8(%rbp)
	jne	.L20
	movl	$75, %ecx
	call	putch
.L20:
	movl	$10, %ecx
	call	putch
	movl	$0, %eax
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putint;	.scl	2;	.type	32;	.endef
	.def	putch;	.scl	2;	.type	32;	.endef
