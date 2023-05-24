	.file	"43_logi_assign.c"
	.text
	.comm	a, 4, 2
	.comm	b, 4, 2
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
	leaq	a(%rip), %rax
	movl	$4, (%rax)
	leaq	b(%rip), %rax
	movl	$4, (%rax)
	leaq	a(%rip), %rax
	movl	(%rax), %edx
	leaq	b(%rip), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L2
	leaq	a(%rip), %rax
	movl	(%rax), %eax
	cmpl	$3, %eax
	je	.L2
	movl	$1, -4(%rbp)
	jmp	.L3
.L2:
	movl	$0, -4(%rbp)
.L3:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
