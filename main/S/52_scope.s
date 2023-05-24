	.file	"52_scope.c"
	.text
	.globl	a
	.data
	.align 4
a:
	.long	7
	.text
	.globl	func
	.def	func;	.scl	2;	.type	32;	.endef
	.seh_proc	func
func:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	a(%rip), %eax
	movl	%eax, -4(%rbp)
	movl	$1, -8(%rbp)
	movl	-8(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jne	.L2
	addl	$1, -8(%rbp)
	movl	$1, %eax
	jmp	.L3
.L2:
	movl	$0, %eax
.L3:
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
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L5
.L7:
	call	func
	cmpl	$1, %eax
	jne	.L6
	addl	$1, -4(%rbp)
.L6:
	addl	$1, -8(%rbp)
.L5:
	cmpl	$99, -8(%rbp)
	jle	.L7
	cmpl	$99, -4(%rbp)
	jg	.L8
	movl	$1, %ecx
	call	putint
	jmp	.L9
.L8:
	movl	$0, %ecx
	call	putint
.L9:
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putint;	.scl	2;	.type	32;	.endef
