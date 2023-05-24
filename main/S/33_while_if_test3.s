	.file	"33_while_if_test3.c"
	.text
	.globl	deepWhileBr
	.def	deepWhileBr;	.scl	2;	.type	32;	.endef
	.seh_proc	deepWhileBr
deepWhileBr:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	16(%rbp), %edx
	movl	24(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	jmp	.L2
.L3:
	movl	$42, -8(%rbp)
	cmpl	$99, -4(%rbp)
	jg	.L2
	movl	-8(%rbp), %eax
	addl	%eax, -4(%rbp)
	cmpl	$99, -4(%rbp)
	jle	.L2
	movl	-8(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, -4(%rbp)
.L2:
	cmpl	$74, -4(%rbp)
	jle	.L3
	movl	-4(%rbp), %eax
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
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	movl	$2, -4(%rbp)
	movl	-4(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	call	deepWhileBr
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
