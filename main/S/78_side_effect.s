	.file	"78_side_effect.c"
	.text
	.globl	a
	.data
	.align 4
a:
	.long	-1
	.globl	b
	.align 4
b:
	.long	1
	.text
	.globl	inc_a
	.def	inc_a;	.scl	2;	.type	32;	.endef
	.seh_proc	inc_a
inc_a:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	a(%rip), %eax
	movl	%eax, -4(%rbp)
	addl	$1, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, a(%rip)
	movl	a(%rip), %eax
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
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	call	__main
	movl	$5, -84(%rbp)
	jmp	.L4
.L9:
	call	inc_a
	testl	%eax, %eax
	je	.L5
	call	inc_a
	testl	%eax, %eax
	je	.L5
	call	inc_a
	testl	%eax, %eax
	je	.L5
	movl	a(%rip), %eax
	movl	%eax, %ecx
	call	putint
	movl	$32, %ecx
	call	putch
	movl	b(%rip), %eax
	movl	%eax, %ecx
	call	putint
	movl	$10, %ecx
	call	putch
.L5:
	call	inc_a
	cmpl	$13, %eax
	jle	.L6
	call	inc_a
	testl	%eax, %eax
	je	.L7
	call	inc_a
	movl	%eax, %ebx
	call	inc_a
	subl	%eax, %ebx
	movl	%ebx, %eax
	cmpl	$-1, %eax
	je	.L7
.L6:
	movl	a(%rip), %eax
	movl	%eax, %ecx
	call	putint
	movl	$10, %ecx
	call	putch
	movl	b(%rip), %eax
	addl	%eax, %eax
	movl	%eax, b(%rip)
	jmp	.L8
.L7:
	call	inc_a
.L8:
	subl	$1, -84(%rbp)
.L4:
	cmpl	$0, -84(%rbp)
	jns	.L9
	movl	a(%rip), %eax
	movl	%eax, %ecx
	call	putint
	movl	$32, %ecx
	call	putch
	movl	b(%rip), %eax
	movl	%eax, %ecx
	call	putint
	movl	$10, %ecx
	call	putch
	movl	a(%rip), %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putint;	.scl	2;	.type	32;	.endef
	.def	putch;	.scl	2;	.type	32;	.endef
