	.file	"31_while_if_test1.c"
	.text
	.globl	whileIf
	.def	whileIf;	.scl	2;	.type	32;	.endef
	.seh_proc	whileIf
whileIf:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L2
.L6:
	cmpl	$5, -4(%rbp)
	jne	.L3
	movl	$25, -8(%rbp)
	jmp	.L4
.L3:
	cmpl	$10, -4(%rbp)
	jne	.L5
	movl	$42, -8(%rbp)
	jmp	.L4
.L5:
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, -8(%rbp)
.L4:
	addl	$1, -4(%rbp)
.L2:
	cmpl	$99, -4(%rbp)
	jle	.L6
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
	call	whileIf
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
