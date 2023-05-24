	.file	"26_while_test1.c"
	.text
	.globl	doubleWhile
	.def	doubleWhile;	.scl	2;	.type	32;	.endef
	.seh_proc	doubleWhile
doubleWhile:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	$5, -4(%rbp)
	movl	$7, -8(%rbp)
	jmp	.L2
.L5:
	addl	$30, -4(%rbp)
	jmp	.L3
.L4:
	addl	$6, -8(%rbp)
.L3:
	cmpl	$99, -8(%rbp)
	jle	.L4
	subl	$100, -8(%rbp)
.L2:
	cmpl	$99, -4(%rbp)
	jle	.L5
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
	call	doubleWhile
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
