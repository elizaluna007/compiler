	.file	"36_op_priority2.c"
	.text
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
	movl	$10, -4(%rbp)
	movl	$4, -8(%rbp)
	movl	$2, -12(%rbp)
	movl	$2, -16(%rbp)
	movl	-12(%rbp), %edx
	movl	-4(%rbp), %eax
	addl	%eax, %edx
	movl	-8(%rbp), %eax
	subl	-16(%rbp), %eax
	imull	%edx, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
