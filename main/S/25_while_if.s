	.file	"25_while_if.c"
	.text
	.globl	get_one
	.def	get_one;	.scl	2;	.type	32;	.endef
	.seh_proc	get_one
get_one:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	$1, %eax
	popq	%rbp
	ret
	.seh_endproc
	.globl	deepWhileBr
	.def	deepWhileBr;	.scl	2;	.type	32;	.endef
	.seh_proc	deepWhileBr
deepWhileBr:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	16(%rbp), %edx
	movl	24(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	jmp	.L4
.L5:
	movl	$42, -8(%rbp)
	cmpl	$99, -4(%rbp)
	jg	.L4
	movl	-8(%rbp), %eax
	addl	%eax, -4(%rbp)
	cmpl	$99, -4(%rbp)
	jle	.L4
	movl	-8(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, -12(%rbp)
	movl	$0, %ecx
	call	get_one
	cmpl	$1, %eax
	jne	.L4
	movl	-12(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, -4(%rbp)
.L4:
	cmpl	$74, -4(%rbp)
	jle	.L5
	movl	-4(%rbp), %eax
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
	movl	$2, -4(%rbp)
	movl	-4(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	call	deepWhileBr
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	call	putint
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putint;	.scl	2;	.type	32;	.endef
