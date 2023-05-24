	.file	"39_op_priority5.c"
	.text
	.globl	a
	.data
	.align 4
a:
	.long	1
	.globl	b
	.bss
	.align 4
b:
	.space 4
	.globl	c
	.data
	.align 4
c:
	.long	1
	.globl	d
	.align 4
d:
	.long	2
	.globl	e
	.align 4
e:
	.long	4
	.def	__main;	.scl	2;	.type	32;	.endef
	.text
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
	movl	a(%rip), %edx
	movl	b(%rip), %eax
	imull	%edx, %eax
	movl	c(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%eax, %ecx
	movl	e(%rip), %edx
	movl	d(%rip), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	jne	.L2
	movl	a(%rip), %edx
	movl	b(%rip), %eax
	addl	%eax, %edx
	movl	a(%rip), %eax
	imull	%edx, %eax
	movl	c(%rip), %edx
	addl	%eax, %edx
	movl	d(%rip), %ecx
	movl	e(%rip), %eax
	addl	%ecx, %eax
	cmpl	%eax, %edx
	jle	.L3
.L2:
	movl	a(%rip), %edx
	movl	b(%rip), %ecx
	movl	c(%rip), %eax
	imull	%ecx, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	d(%rip), %r8d
	movl	a(%rip), %eax
	movl	c(%rip), %r9d
	cltd
	idivl	%r9d
	subl	%eax, %r8d
	movl	%r8d, %eax
	cmpl	%eax, %ecx
	jne	.L4
.L3:
	movl	$1, -4(%rbp)
.L4:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
