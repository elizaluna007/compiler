	.file	"50_short_circuit.c"
	.text
	.globl	g
	.bss
	.align 4
g:
	.space 4
	.text
	.globl	func
	.def	func;	.scl	2;	.type	32;	.endef
	.seh_proc	func
func:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	g(%rip), %edx
	movl	16(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, g(%rip)
	movl	g(%rip), %eax
	movl	%eax, %ecx
	call	putint
	movl	g(%rip), %eax
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
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	call	getint
	movl	%eax, -4(%rbp)
	cmpl	$10, -4(%rbp)
	jle	.L4
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	call	func
	testl	%eax, %eax
	je	.L4
	movl	$1, -4(%rbp)
	jmp	.L5
.L4:
	movl	$0, -4(%rbp)
.L5:
	call	getint
	movl	%eax, -4(%rbp)
	cmpl	$11, -4(%rbp)
	jle	.L6
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	call	func
	testl	%eax, %eax
	je	.L6
	movl	$1, -4(%rbp)
	jmp	.L7
.L6:
	movl	$0, -4(%rbp)
.L7:
	call	getint
	movl	%eax, -4(%rbp)
	cmpl	$99, -4(%rbp)
	jle	.L8
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	call	func
	testl	%eax, %eax
	je	.L9
.L8:
	movl	$1, -4(%rbp)
	jmp	.L10
.L9:
	movl	$0, -4(%rbp)
.L10:
	call	getint
	movl	%eax, -4(%rbp)
	cmpl	$100, -4(%rbp)
	jle	.L11
	movl	-4(%rbp), %eax
	movl	%eax, %ecx
	call	func
	testl	%eax, %eax
	je	.L12
.L11:
	movl	$1, -4(%rbp)
	jmp	.L13
.L12:
	movl	$0, -4(%rbp)
.L13:
	movl	$99, %ecx
	call	func
	testl	%eax, %eax
	jne	.L14
	movl	$100, %ecx
	call	func
	testl	%eax, %eax
	je	.L14
	movl	$1, -4(%rbp)
	jmp	.L15
.L14:
	movl	$0, -4(%rbp)
.L15:
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putint;	.scl	2;	.type	32;	.endef
	.def	getint;	.scl	2;	.type	32;	.endef
