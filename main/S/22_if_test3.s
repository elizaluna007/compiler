	.file	"22_if_test3.c"
	.text
	.globl	ififElse
	.def	ififElse;	.scl	2;	.type	32;	.endef
	.seh_proc	ififElse
ififElse:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	$5, -4(%rbp)
	movl	$10, -8(%rbp)
	cmpl	$5, -4(%rbp)
	jne	.L2
	cmpl	$10, -8(%rbp)
	jne	.L3
	movl	$25, -4(%rbp)
	jmp	.L2
.L3:
	addl	$15, -4(%rbp)
.L2:
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
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	call	ififElse
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
