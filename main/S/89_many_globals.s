	.file	"89_many_globals.c"
	.text
	.comm	a0, 4, 2
	.comm	a1, 4, 2
	.comm	a2, 4, 2
	.comm	a3, 4, 2
	.comm	a4, 4, 2
	.comm	a5, 4, 2
	.comm	a6, 4, 2
	.comm	a7, 4, 2
	.comm	a8, 4, 2
	.comm	a9, 4, 2
	.comm	a10, 4, 2
	.comm	a11, 4, 2
	.comm	a12, 4, 2
	.comm	a13, 4, 2
	.comm	a14, 4, 2
	.comm	a15, 4, 2
	.comm	a16, 4, 2
	.comm	a17, 4, 2
	.comm	a18, 4, 2
	.comm	a19, 4, 2
	.comm	a20, 4, 2
	.comm	a21, 4, 2
	.comm	a22, 4, 2
	.comm	a23, 4, 2
	.comm	a24, 4, 2
	.comm	a25, 4, 2
	.comm	a26, 4, 2
	.comm	a27, 4, 2
	.comm	a28, 4, 2
	.comm	a29, 4, 2
	.comm	a30, 4, 2
	.comm	a31, 4, 2
	.comm	a32, 4, 2
	.comm	a33, 4, 2
	.comm	a34, 4, 2
	.comm	a35, 4, 2
	.comm	a36, 4, 2
	.comm	a37, 4, 2
	.comm	a38, 4, 2
	.comm	a39, 4, 2
	.globl	testParam8
	.def	testParam8;	.scl	2;	.type	32;	.endef
	.seh_proc	testParam8
testParam8:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	movl	16(%rbp), %edx
	movl	24(%rbp), %eax
	addl	%eax, %edx
	movl	32(%rbp), %eax
	addl	%eax, %edx
	movl	40(%rbp), %eax
	addl	%eax, %edx
	movl	48(%rbp), %eax
	addl	%eax, %edx
	movl	56(%rbp), %eax
	addl	%eax, %edx
	movl	64(%rbp), %eax
	addl	%eax, %edx
	movl	72(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	ret
	.seh_endproc
	.globl	testParam16
	.def	testParam16;	.scl	2;	.type	32;	.endef
	.seh_proc	testParam16
testParam16:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	movl	16(%rbp), %edx
	movl	24(%rbp), %eax
	addl	%eax, %edx
	movl	32(%rbp), %eax
	addl	%edx, %eax
	subl	40(%rbp), %eax
	subl	48(%rbp), %eax
	subl	56(%rbp), %eax
	subl	64(%rbp), %eax
	subl	72(%rbp), %eax
	movl	80(%rbp), %edx
	addl	%eax, %edx
	movl	88(%rbp), %eax
	addl	%eax, %edx
	movl	96(%rbp), %eax
	addl	%eax, %edx
	movl	104(%rbp), %eax
	addl	%eax, %edx
	movl	112(%rbp), %eax
	addl	%eax, %edx
	movl	120(%rbp), %eax
	addl	%eax, %edx
	movl	128(%rbp), %eax
	addl	%eax, %edx
	movl	136(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	ret
	.seh_endproc
	.globl	testParam32
	.def	testParam32;	.scl	2;	.type	32;	.endef
	.seh_proc	testParam32
testParam32:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movl	%r9d, 40(%rbp)
	movl	16(%rbp), %edx
	movl	24(%rbp), %eax
	addl	%eax, %edx
	movl	32(%rbp), %eax
	addl	%eax, %edx
	movl	40(%rbp), %eax
	addl	%eax, %edx
	movl	48(%rbp), %eax
	addl	%eax, %edx
	movl	56(%rbp), %eax
	addl	%eax, %edx
	movl	64(%rbp), %eax
	addl	%eax, %edx
	movl	72(%rbp), %eax
	addl	%eax, %edx
	movl	80(%rbp), %eax
	addl	%eax, %edx
	movl	88(%rbp), %eax
	addl	%eax, %edx
	movl	96(%rbp), %eax
	addl	%eax, %edx
	movl	104(%rbp), %eax
	addl	%eax, %edx
	movl	112(%rbp), %eax
	addl	%eax, %edx
	movl	120(%rbp), %eax
	addl	%eax, %edx
	movl	128(%rbp), %eax
	addl	%eax, %edx
	movl	136(%rbp), %eax
	addl	%eax, %edx
	movl	144(%rbp), %eax
	addl	%eax, %edx
	movl	152(%rbp), %eax
	addl	%edx, %eax
	subl	160(%rbp), %eax
	subl	168(%rbp), %eax
	subl	176(%rbp), %eax
	subl	184(%rbp), %eax
	subl	192(%rbp), %eax
	movl	200(%rbp), %edx
	addl	%eax, %edx
	movl	208(%rbp), %eax
	addl	%eax, %edx
	movl	216(%rbp), %eax
	addl	%eax, %edx
	movl	224(%rbp), %eax
	addl	%eax, %edx
	movl	232(%rbp), %eax
	addl	%eax, %edx
	movl	240(%rbp), %eax
	addl	%eax, %edx
	movl	248(%rbp), %eax
	addl	%eax, %edx
	movl	256(%rbp), %eax
	addl	%eax, %edx
	movl	264(%rbp), %eax
	addl	%edx, %eax
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
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$344, %rsp
	.seh_stackalloc	344
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	call	__main
	leaq	a0(%rip), %rax
	movl	$0, (%rax)
	leaq	a1(%rip), %rax
	movl	$1, (%rax)
	leaq	a2(%rip), %rax
	movl	$2, (%rax)
	leaq	a3(%rip), %rax
	movl	$3, (%rax)
	leaq	a4(%rip), %rax
	movl	$4, (%rax)
	leaq	a5(%rip), %rax
	movl	$5, (%rax)
	leaq	a6(%rip), %rax
	movl	$6, (%rax)
	leaq	a7(%rip), %rax
	movl	$7, (%rax)
	leaq	a8(%rip), %rax
	movl	$8, (%rax)
	leaq	a9(%rip), %rax
	movl	$9, (%rax)
	leaq	a10(%rip), %rax
	movl	$0, (%rax)
	leaq	a11(%rip), %rax
	movl	$1, (%rax)
	leaq	a12(%rip), %rax
	movl	$2, (%rax)
	leaq	a13(%rip), %rax
	movl	$3, (%rax)
	leaq	a14(%rip), %rax
	movl	$4, (%rax)
	leaq	a15(%rip), %rax
	movl	$5, (%rax)
	leaq	a16(%rip), %rax
	movl	$6, (%rax)
	leaq	a17(%rip), %rax
	movl	$7, (%rax)
	leaq	a18(%rip), %rax
	movl	$8, (%rax)
	leaq	a19(%rip), %rax
	movl	$9, (%rax)
	leaq	a20(%rip), %rax
	movl	$0, (%rax)
	leaq	a21(%rip), %rax
	movl	$1, (%rax)
	leaq	a22(%rip), %rax
	movl	$2, (%rax)
	leaq	a23(%rip), %rax
	movl	$3, (%rax)
	leaq	a24(%rip), %rax
	movl	$4, (%rax)
	leaq	a25(%rip), %rax
	movl	$5, (%rax)
	leaq	a26(%rip), %rax
	movl	$6, (%rax)
	leaq	a27(%rip), %rax
	movl	$7, (%rax)
	leaq	a28(%rip), %rax
	movl	$8, (%rax)
	leaq	a29(%rip), %rax
	movl	$9, (%rax)
	leaq	a30(%rip), %rax
	movl	$0, (%rax)
	leaq	a31(%rip), %rax
	movl	$1, (%rax)
	leaq	a32(%rip), %rax
	movl	$4, (%rax)
	leaq	a33(%rip), %rax
	movl	$5, (%rax)
	leaq	a34(%rip), %rax
	movl	$6, (%rax)
	leaq	a35(%rip), %rax
	movl	$7, (%rax)
	leaq	a36(%rip), %rax
	movl	$8, (%rax)
	leaq	a37(%rip), %rax
	movl	$9, (%rax)
	leaq	a38(%rip), %rax
	movl	$0, (%rax)
	leaq	a39(%rip), %rax
	movl	$1, (%rax)
	leaq	a7(%rip), %rax
	movl	(%rax), %r10d
	leaq	a6(%rip), %rax
	movl	(%rax), %r9d
	leaq	a5(%rip), %rax
	movl	(%rax), %r8d
	leaq	a4(%rip), %rax
	movl	(%rax), %ecx
	leaq	a3(%rip), %rax
	movl	(%rax), %ebx
	leaq	a2(%rip), %rax
	movl	(%rax), %r11d
	leaq	a1(%rip), %rax
	movl	(%rax), %edx
	leaq	a0(%rip), %rax
	movl	(%rax), %eax
	movl	%r10d, 56(%rsp)
	movl	%r9d, 48(%rsp)
	movl	%r8d, 40(%rsp)
	movl	%ecx, 32(%rsp)
	movl	%ebx, %r9d
	movl	%r11d, %r8d
	movl	%eax, %ecx
	call	testParam8
	movl	%eax, %edx
	leaq	a0(%rip), %rax
	movl	%edx, (%rax)
	leaq	a0(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putint
	leaq	a15(%rip), %rax
	movl	(%rax), %ecx
	leaq	a14(%rip), %rax
	movl	(%rax), %r15d
	leaq	a13(%rip), %rax
	movl	(%rax), %r14d
	leaq	a12(%rip), %rax
	movl	(%rax), %r13d
	leaq	a11(%rip), %rax
	movl	(%rax), %r12d
	leaq	a10(%rip), %rax
	movl	(%rax), %edi
	leaq	a9(%rip), %rax
	movl	(%rax), %esi
	leaq	a8(%rip), %rax
	movl	(%rax), %ebx
	leaq	a39(%rip), %rax
	movl	(%rax), %r11d
	leaq	a38(%rip), %rax
	movl	(%rax), %r10d
	leaq	a37(%rip), %rax
	movl	(%rax), %r9d
	leaq	a36(%rip), %rax
	movl	(%rax), %r8d
	leaq	a35(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, 204(%rbp)
	leaq	a34(%rip), %rax
	movl	(%rax), %edx
	movl	%edx, 200(%rbp)
	leaq	a33(%rip), %rax
	movl	(%rax), %edx
	leaq	a32(%rip), %rax
	movl	(%rax), %eax
	movl	%ecx, 120(%rsp)
	movl	%r15d, 112(%rsp)
	movl	%r14d, 104(%rsp)
	movl	%r13d, 96(%rsp)
	movl	%r12d, 88(%rsp)
	movl	%edi, 80(%rsp)
	movl	%esi, 72(%rsp)
	movl	%ebx, 64(%rsp)
	movl	%r11d, 56(%rsp)
	movl	%r10d, 48(%rsp)
	movl	%r9d, 40(%rsp)
	movl	%r8d, 32(%rsp)
	movl	204(%rbp), %r9d
	movl	200(%rbp), %r8d
	movl	%eax, %ecx
	call	testParam16
	movl	%eax, %edx
	leaq	a0(%rip), %rax
	movl	%edx, (%rax)
	leaq	a0(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putint
	leaq	a31(%rip), %rax
	movl	(%rax), %r12d
	leaq	a30(%rip), %rax
	movl	(%rax), %r13d
	leaq	a29(%rip), %rax
	movl	(%rax), %r15d
	leaq	a28(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, 204(%rbp)
	leaq	a27(%rip), %rax
	movl	(%rax), %esi
	movl	%esi, 200(%rbp)
	leaq	a26(%rip), %rax
	movl	(%rax), %edi
	movl	%edi, 196(%rbp)
	leaq	a25(%rip), %rax
	movl	(%rax), %ebx
	movl	%ebx, 192(%rbp)
	leaq	a24(%rip), %rax
	movl	(%rax), %ecx
	movl	%ecx, 188(%rbp)
	leaq	a23(%rip), %rax
	movl	(%rax), %edx
	movl	%edx, 184(%rbp)
	leaq	a22(%rip), %rax
	movl	(%rax), %r14d
	movl	%r14d, 180(%rbp)
	leaq	a21(%rip), %rax
	movl	(%rax), %r10d
	movl	%r10d, 176(%rbp)
	leaq	a20(%rip), %rax
	movl	(%rax), %r11d
	movl	%r11d, 172(%rbp)
	leaq	a19(%rip), %rax
	movl	(%rax), %r8d
	movl	%r8d, 168(%rbp)
	leaq	a18(%rip), %rax
	movl	(%rax), %r9d
	movl	%r9d, 164(%rbp)
	leaq	a17(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, 160(%rbp)
	leaq	a16(%rip), %rax
	movl	(%rax), %esi
	movl	%esi, 156(%rbp)
	leaq	a15(%rip), %rax
	movl	(%rax), %edi
	movl	%edi, 152(%rbp)
	leaq	a14(%rip), %rax
	movl	(%rax), %ebx
	movl	%ebx, 148(%rbp)
	leaq	a13(%rip), %rax
	movl	(%rax), %ecx
	movl	%ecx, 144(%rbp)
	leaq	a12(%rip), %rax
	movl	(%rax), %edx
	movl	%edx, 140(%rbp)
	leaq	a11(%rip), %rax
	movl	(%rax), %r14d
	movl	%r14d, 136(%rbp)
	leaq	a10(%rip), %rax
	movl	(%rax), %r14d
	leaq	a9(%rip), %rax
	movl	(%rax), %edi
	leaq	a8(%rip), %rax
	movl	(%rax), %esi
	leaq	a7(%rip), %rax
	movl	(%rax), %ebx
	leaq	a6(%rip), %rax
	movl	(%rax), %r11d
	leaq	a5(%rip), %rax
	movl	(%rax), %r10d
	leaq	a4(%rip), %rax
	movl	(%rax), %r8d
	leaq	a3(%rip), %rax
	movl	(%rax), %r9d
	leaq	a2(%rip), %rax
	movl	(%rax), %ecx
	leaq	a1(%rip), %rax
	movl	(%rax), %edx
	leaq	a0(%rip), %rax
	movl	(%rax), %eax
	movl	%r12d, 248(%rsp)
	movl	%r13d, 240(%rsp)
	movl	%r15d, 232(%rsp)
	movl	204(%rbp), %r15d
	movl	%r15d, 224(%rsp)
	movl	200(%rbp), %r15d
	movl	%r15d, 216(%rsp)
	movl	196(%rbp), %r15d
	movl	%r15d, 208(%rsp)
	movl	192(%rbp), %r15d
	movl	%r15d, 200(%rsp)
	movl	188(%rbp), %r15d
	movl	%r15d, 192(%rsp)
	movl	184(%rbp), %r15d
	movl	%r15d, 184(%rsp)
	movl	180(%rbp), %r15d
	movl	%r15d, 176(%rsp)
	movl	176(%rbp), %r15d
	movl	%r15d, 168(%rsp)
	movl	172(%rbp), %r15d
	movl	%r15d, 160(%rsp)
	movl	168(%rbp), %r15d
	movl	%r15d, 152(%rsp)
	movl	164(%rbp), %r15d
	movl	%r15d, 144(%rsp)
	movl	160(%rbp), %r15d
	movl	%r15d, 136(%rsp)
	movl	156(%rbp), %r15d
	movl	%r15d, 128(%rsp)
	movl	152(%rbp), %r15d
	movl	%r15d, 120(%rsp)
	movl	148(%rbp), %r15d
	movl	%r15d, 112(%rsp)
	movl	144(%rbp), %r15d
	movl	%r15d, 104(%rsp)
	movl	140(%rbp), %r15d
	movl	%r15d, 96(%rsp)
	movl	136(%rbp), %r15d
	movl	%r15d, 88(%rsp)
	movl	%r14d, 80(%rsp)
	movl	%edi, 72(%rsp)
	movl	%esi, 64(%rsp)
	movl	%ebx, 56(%rsp)
	movl	%r11d, 48(%rsp)
	movl	%r10d, 40(%rsp)
	movl	%r8d, 32(%rsp)
	movl	%ecx, %r8d
	movl	%eax, %ecx
	call	testParam32
	movl	%eax, %edx
	leaq	a0(%rip), %rax
	movl	%edx, (%rax)
	leaq	a0(%rip), %rax
	movl	(%rax), %eax
	movl	%eax, %ecx
	call	putint
	movl	$0, %eax
	addq	$344, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-sjlj-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	putint;	.scl	2;	.type	32;	.endef
