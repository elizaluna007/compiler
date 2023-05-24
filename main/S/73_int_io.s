	.file	"73_int_io.c"
	.text
	.globl	ascii_0
	.section .rdata,"dr"
	.align 4
ascii_0:
	.long	48
	.text
	.globl	my_getint
	.def	my_getint;	.scl	2;	.type	32;	.endef
	.seh_proc	my_getint
my_getint:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	$0, -4(%rbp)
.L4:
	call	getch
	movl	$48, %edx
	subl	%edx, %eax
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	js	.L4
	cmpl	$9, -8(%rbp)
	jle	.L3
	jmp	.L4
.L3:
	movl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
.L6:
	call	getch
	movl	$48, %edx
	subl	%edx, %eax
	movl	%eax, -8(%rbp)
	cmpl	$0, -8(%rbp)
	js	.L5
	cmpl	$9, -8(%rbp)
	jg	.L5
	movl	-4(%rbp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	jmp	.L6
.L5:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	my_putint
	.def	my_putint;	.scl	2;	.type	32;	.endef
	.seh_proc	my_putint
my_putint:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$112, %rsp
	.seh_stackalloc	112
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L9
.L10:
	movl	16(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movl	$48, %eax
	addl	%eax, %edx
	movl	-4(%rbp), %eax
	cltq
	movl	%edx, -80(%rbp,%rax,4)
	movl	16(%rbp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, 16(%rbp)
	addl	$1, -4(%rbp)
.L9:
	cmpl	$0, 16(%rbp)
	jg	.L10
	jmp	.L11
.L12:
	subl	$1, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %eax
	movl	%eax, %ecx
	call	putch
.L11:
	cmpl	$0, -4(%rbp)
	jg	.L12
	nop
	addq	$112, %rsp
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
	call	my_getint
	movl	%eax, -4(%rbp)
	jmp	.L14
.L15:
	call	my_getint
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, %ecx
	call	my_putint
	movl	$10, %ecx
	call	putch
	subl	$1, -4(%rbp)
.L14:
	cmpl	$0, -4(%rbp)
	jg	.L15
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	getch;	.scl	2;	.type	32;	.endef
	.def	putch;	.scl	2;	.type	32;	.endef
