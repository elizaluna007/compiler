	.file	"21_if_test2.c"
	.text
	.globl	ifElseIf
	.def	ifElseIf;	.scl	2;	.type	32;	.endef
	.seh_proc	ifElseIf
ifElseIf:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	$5, -4(%rbp)
	movl	$10, -8(%rbp)
	cmpl	$6, -4(%rbp)
	je	.L2
	cmpl	$11, -8(%rbp)
	jne	.L3
.L2:
	movl	-4(%rbp), %eax
	jmp	.L4
.L3:
	cmpl	$10, -8(%rbp)
	jne	.L5
	cmpl	$1, -4(%rbp)
	jne	.L5
	movl	$25, -4(%rbp)
	jmp	.L6
.L5:
	cmpl	$10, -8(%rbp)
	jne	.L7
	cmpl	$-5, -4(%rbp)
	jne	.L7
	addl	$15, -4(%rbp)
	jmp	.L6
.L7:
	negl	-4(%rbp)
.L6:
	movl	-4(%rbp), %eax
.L4:
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
	call	ifElseIf
	movl	%eax, %ecx
	call	putint
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putint;	.scl	2;	.type	32;	.endef
