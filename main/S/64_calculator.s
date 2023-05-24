	.file	"64_calculator.c"
	.text
	.comm	ints, 40000, 5
	.comm	intt, 4, 2
	.comm	chas, 40000, 5
	.comm	chat, 4, 2
	.globl	i
	.bss
	.align 4
i:
	.space 4
	.globl	ii
	.data
	.align 4
ii:
	.long	1
	.comm	c, 4, 2
	.comm	get, 40000, 5
	.comm	get2, 40000, 5
	.text
	.globl	isdigit
	.def	isdigit;	.scl	2;	.type	32;	.endef
	.seh_proc	isdigit
isdigit:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cmpl	$47, 16(%rbp)
	jle	.L2
	cmpl	$57, 16(%rbp)
	jg	.L2
	movl	$1, %eax
	jmp	.L3
.L2:
	movl	$0, %eax
.L3:
	popq	%rbp
	ret
	.seh_endproc
	.globl	power
	.def	power;	.scl	2;	.type	32;	.endef
	.seh_proc	power
power:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L5
.L6:
	movl	-4(%rbp), %eax
	imull	16(%rbp), %eax
	movl	%eax, -4(%rbp)
	subl	$1, 24(%rbp)
.L5:
	cmpl	$0, 24(%rbp)
	jne	.L6
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	getstr
	.def	getstr;	.scl	2;	.type	32;	.endef
	.seh_proc	getstr
getstr:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	call	getch
	movl	%eax, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L9
.L11:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	-4(%rbp), %edx
	movl	%edx, (%rax)
	addl	$1, -8(%rbp)
	call	getch
	movl	%eax, -4(%rbp)
.L9:
	cmpl	$13, -4(%rbp)
	je	.L10
	cmpl	$10, -4(%rbp)
	jne	.L11
.L10:
	movl	-8(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	intpush
	.def	intpush;	.scl	2;	.type	32;	.endef
	.seh_proc	intpush
intpush:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	leaq	intt(%rip), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	leaq	intt(%rip), %rax
	movl	%edx, (%rax)
	leaq	intt(%rip), %rax
	movl	(%rax), %edx
	leaq	ints(%rip), %rax
	movslq	%edx, %rdx
	movl	16(%rbp), %ecx
	movl	%ecx, (%rax,%rdx,4)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	chapush
	.def	chapush;	.scl	2;	.type	32;	.endef
	.seh_proc	chapush
chapush:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	leaq	chat(%rip), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	leaq	chat(%rip), %rax
	movl	%edx, (%rax)
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	16(%rbp), %ecx
	movl	%ecx, (%rax,%rdx,4)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	intpop
	.def	intpop;	.scl	2;	.type	32;	.endef
	.seh_proc	intpop
intpop:
	.seh_endprologue
	leaq	intt(%rip), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	leaq	intt(%rip), %rax
	movl	%edx, (%rax)
	leaq	intt(%rip), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	leaq	ints(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	ret
	.seh_endproc
	.globl	chapop
	.def	chapop;	.scl	2;	.type	32;	.endef
	.seh_proc	chapop
chapop:
	.seh_endprologue
	leaq	chat(%rip), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	leaq	chat(%rip), %rax
	movl	%edx, (%rax)
	leaq	chat(%rip), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	ret
	.seh_endproc
	.globl	intadd
	.def	intadd;	.scl	2;	.type	32;	.endef
	.seh_proc	intadd
intadd:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	leaq	intt(%rip), %rax
	movl	(%rax), %edx
	leaq	ints(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %edx
	leaq	intt(%rip), %rax
	movl	(%rax), %ecx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, %r8d
	leaq	ints(%rip), %rax
	movslq	%ecx, %rdx
	movl	%r8d, (%rax,%rdx,4)
	leaq	intt(%rip), %rax
	movl	(%rax), %edx
	leaq	ints(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %ecx
	leaq	intt(%rip), %rax
	movl	(%rax), %edx
	movl	16(%rbp), %eax
	addl	%eax, %ecx
	leaq	ints(%rip), %rax
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	find
	.def	find;	.scl	2;	.type	32;	.endef
	.seh_proc	find
find:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	chapop
	movl	%eax, %edx
	leaq	c(%rip), %rax
	movl	%edx, (%rax)
	movl	ii(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	$32, (%rax,%rdx,4)
	movl	ii(%rip), %eax
	leal	1(%rax), %edx
	leaq	c(%rip), %rax
	movl	(%rax), %ecx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	movl	ii(%rip), %eax
	addl	$2, %eax
	movl	%eax, ii(%rip)
	leaq	chat(%rip), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L21
	movl	$0, %eax
	jmp	.L22
.L21:
	movl	$1, %eax
.L22:
	addq	$32, %rsp
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
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	call	__main
	leaq	intt(%rip), %rax
	movl	$0, (%rax)
	leaq	chat(%rip), %rax
	movl	$0, (%rax)
	leaq	get(%rip), %rax
	movq	%rax, %rcx
	call	getstr
	movl	%eax, -8(%rbp)
	jmp	.L24
.L52:
	movl	i(%rip), %edx
	leaq	get(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	subl	$48, %eax
	cmpl	$9, %eax
	ja	.L25
	movl	i(%rip), %edx
	movl	ii(%rip), %r8d
	leaq	get(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %ecx
	leaq	get2(%rip), %rax
	movslq	%r8d, %rdx
	movl	%ecx, (%rax,%rdx,4)
	movl	ii(%rip), %eax
	addl	$1, %eax
	movl	%eax, ii(%rip)
	jmp	.L26
.L25:
	movl	i(%rip), %edx
	leaq	get(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$40, %eax
	jne	.L27
	movl	$40, %ecx
	call	chapush
.L27:
	movl	i(%rip), %edx
	leaq	get(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$94, %eax
	jne	.L28
	movl	$94, %ecx
	call	chapush
.L28:
	movl	i(%rip), %edx
	leaq	get(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$41, %eax
	jne	.L29
	call	chapop
	movl	%eax, %edx
	leaq	c(%rip), %rax
	movl	%edx, (%rax)
	jmp	.L30
.L31:
	movl	ii(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	$32, (%rax,%rdx,4)
	movl	ii(%rip), %eax
	leal	1(%rax), %edx
	leaq	c(%rip), %rax
	movl	(%rax), %ecx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	movl	ii(%rip), %eax
	addl	$2, %eax
	movl	%eax, ii(%rip)
	call	chapop
	movl	%eax, %edx
	leaq	c(%rip), %rax
	movl	%edx, (%rax)
.L30:
	leaq	c(%rip), %rax
	movl	(%rax), %eax
	cmpl	$40, %eax
	jne	.L31
.L29:
	movl	i(%rip), %edx
	leaq	get(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$43, %eax
	jne	.L32
	jmp	.L33
.L35:
	call	find
	testl	%eax, %eax
	je	.L69
.L33:
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$43, %eax
	je	.L35
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$45, %eax
	je	.L35
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$42, %eax
	je	.L35
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$47, %eax
	je	.L35
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$37, %eax
	je	.L35
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$94, %eax
	je	.L35
	jmp	.L34
.L69:
	nop
.L34:
	movl	$43, %ecx
	call	chapush
.L32:
	movl	i(%rip), %edx
	leaq	get(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$45, %eax
	jne	.L36
	jmp	.L37
.L39:
	call	find
	testl	%eax, %eax
	je	.L70
.L37:
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$43, %eax
	je	.L39
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$45, %eax
	je	.L39
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$42, %eax
	je	.L39
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$47, %eax
	je	.L39
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$37, %eax
	je	.L39
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$94, %eax
	je	.L39
	jmp	.L38
.L70:
	nop
.L38:
	movl	$45, %ecx
	call	chapush
.L36:
	movl	i(%rip), %edx
	leaq	get(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$42, %eax
	jne	.L40
	jmp	.L41
.L43:
	call	find
	testl	%eax, %eax
	je	.L71
.L41:
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$42, %eax
	je	.L43
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$47, %eax
	je	.L43
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$37, %eax
	je	.L43
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$94, %eax
	je	.L43
	jmp	.L42
.L71:
	nop
.L42:
	movl	$42, %ecx
	call	chapush
.L40:
	movl	i(%rip), %edx
	leaq	get(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$47, %eax
	jne	.L44
	jmp	.L45
.L47:
	call	find
	testl	%eax, %eax
	je	.L72
.L45:
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$42, %eax
	je	.L47
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$47, %eax
	je	.L47
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$37, %eax
	je	.L47
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$94, %eax
	je	.L47
	jmp	.L46
.L72:
	nop
.L46:
	movl	$47, %ecx
	call	chapush
.L44:
	movl	i(%rip), %edx
	leaq	get(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$37, %eax
	jne	.L48
	jmp	.L49
.L51:
	call	find
	testl	%eax, %eax
	je	.L73
.L49:
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$42, %eax
	je	.L51
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$47, %eax
	je	.L51
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$37, %eax
	je	.L51
	leaq	chat(%rip), %rax
	movl	(%rax), %edx
	leaq	chas(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$94, %eax
	je	.L51
	jmp	.L50
.L73:
	nop
.L50:
	movl	$37, %ecx
	call	chapush
.L48:
	movl	ii(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	$32, (%rax,%rdx,4)
	movl	ii(%rip), %eax
	addl	$1, %eax
	movl	%eax, ii(%rip)
.L26:
	movl	i(%rip), %eax
	addl	$1, %eax
	movl	%eax, i(%rip)
.L24:
	movl	i(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jg	.L52
	jmp	.L53
.L54:
	call	chapop
	movl	%eax, -12(%rbp)
	movl	ii(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	$32, (%rax,%rdx,4)
	movl	ii(%rip), %eax
	leal	1(%rax), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	-12(%rbp), %ecx
	movl	%ecx, (%rax,%rdx,4)
	movl	ii(%rip), %eax
	addl	$2, %eax
	movl	%eax, ii(%rip)
.L53:
	leaq	chat(%rip), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jg	.L54
	movl	ii(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	$64, (%rax,%rdx,4)
	movl	$1, i(%rip)
	jmp	.L55
.L67:
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$43, %eax
	je	.L56
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$45, %eax
	je	.L56
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$42, %eax
	je	.L56
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$47, %eax
	je	.L56
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$37, %eax
	je	.L56
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$94, %eax
	jne	.L57
.L56:
	call	intpop
	movl	%eax, -16(%rbp)
	call	intpop
	movl	%eax, -20(%rbp)
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$43, %eax
	jne	.L58
	movl	-16(%rbp), %edx
	movl	-20(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
.L58:
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$45, %eax
	jne	.L59
	movl	-20(%rbp), %eax
	subl	-16(%rbp), %eax
	movl	%eax, -4(%rbp)
.L59:
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$42, %eax
	jne	.L60
	movl	-16(%rbp), %eax
	imull	-20(%rbp), %eax
	movl	%eax, -4(%rbp)
.L60:
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$47, %eax
	jne	.L61
	movl	-20(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%eax, -4(%rbp)
.L61:
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$37, %eax
	jne	.L62
	movl	-20(%rbp), %eax
	cltd
	idivl	-16(%rbp)
	movl	%edx, -4(%rbp)
.L62:
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$94, %eax
	jne	.L63
	movl	-16(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %ecx
	call	power
	movl	%eax, -4(%rbp)
.L63:
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	call	intpush
	jmp	.L64
.L57:
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$32, %eax
	je	.L64
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	subl	$48, %eax
	movl	%eax, %ecx
	call	intpush
	movl	$1, ii(%rip)
	jmp	.L65
.L66:
	movl	i(%rip), %edx
	movl	ii(%rip), %eax
	addl	%eax, %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	subl	$48, %eax
	movl	%eax, %ecx
	call	intadd
	movl	ii(%rip), %eax
	addl	$1, %eax
	movl	%eax, ii(%rip)
.L65:
	movl	i(%rip), %edx
	movl	ii(%rip), %eax
	addl	%eax, %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$32, %eax
	jne	.L66
	movl	i(%rip), %edx
	movl	ii(%rip), %eax
	addl	%edx, %eax
	subl	$1, %eax
	movl	%eax, i(%rip)
.L64:
	movl	i(%rip), %eax
	addl	$1, %eax
	movl	%eax, i(%rip)
.L55:
	movl	i(%rip), %edx
	leaq	get2(%rip), %rax
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$64, %eax
	jne	.L67
	leaq	ints(%rip), %rax
	movl	4(%rax), %eax
	movl	%eax, %ecx
	call	putint
	movl	$0, %eax
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	getch;	.scl	2;	.type	32;	.endef
	.def	putint;	.scl	2;	.type	32;	.endef
