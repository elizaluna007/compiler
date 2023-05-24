	.file	"32_while_if_test2.c"
	.text
	.globl	ifWhile
	.def	ifWhile;	.scl	2;	.type	32;	.endef
	.seh_proc	ifWhile
ifWhile:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	$0, -4(%rbp)
	movl	$3, -8(%rbp)
	cmpl	$5, -4(%rbp)
	jne	.L6
	jmp	.L3
.L4:
	addl	$2, -8(%rbp)
.L3:
	cmpl	$2, -8(%rbp)
	je	.L4
	addl	$25, -8(%rbp)
	jmp	.L5
.L7:
	sall	-8(%rbp)
	addl	$1, -4(%rbp)
.L6:
	cmpl	$4, -4(%rbp)
	jle	.L7
.L5:
	movl	-8(%rbp), %eax
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
	call	ifWhile
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
