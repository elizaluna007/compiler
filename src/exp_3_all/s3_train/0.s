	.file	"0.c"
	.text
	.comm	a0,4,4
	.comm	a1,4,4
	.comm	a2,4,4
	.comm	a3,4,4
	.comm	a4,4,4
	.comm	a5,4,4
	.comm	a6,4,4
	.comm	a7,4,4
	.comm	a8,4,4
	.comm	a9,4,4
	.comm	a10,4,4
	.comm	a11,4,4
	.comm	a12,4,4
	.comm	a13,4,4
	.comm	a14,4,4
	.comm	a15,4,4
	.comm	a16,4,4
	.comm	a17,4,4
	.comm	a18,4,4
	.comm	a19,4,4
	.comm	a20,4,4
	.comm	a21,4,4
	.comm	a22,4,4
	.comm	a23,4,4
	.comm	a24,4,4
	.comm	a25,4,4
	.comm	a26,4,4
	.comm	a27,4,4
	.comm	a28,4,4
	.comm	a29,4,4
	.comm	a30,4,4
	.comm	a31,4,4
	.comm	a32,4,4
	.comm	a33,4,4
	.comm	a34,4,4
	.comm	a35,4,4
	.comm	a36,4,4
	.comm	a37,4,4
	.comm	a38,4,4
	.comm	a39,4,4
	.globl	testParam8
	.type	testParam8, @function
testParam8:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%eax, %edx
	movl	-16(%rbp), %eax
	addl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%eax, %edx
	movl	-24(%rbp), %eax
	addl	%eax, %edx
	movl	16(%rbp), %eax
	addl	%eax, %edx
	movl	24(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	testParam8, .-testParam8
	.globl	testParam16
	.type	testParam16, @function
testParam16:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	subl	-16(%rbp), %eax
	subl	-20(%rbp), %eax
	subl	-24(%rbp), %eax
	subl	16(%rbp), %eax
	subl	24(%rbp), %eax
	movl	%eax, %edx
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
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	testParam16, .-testParam16
	.globl	testParam32
	.type	testParam32, @function
testParam32:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%eax, %edx
	movl	-16(%rbp), %eax
	addl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%eax, %edx
	movl	-24(%rbp), %eax
	addl	%eax, %edx
	movl	16(%rbp), %eax
	addl	%eax, %edx
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
	addl	%edx, %eax
	subl	112(%rbp), %eax
	subl	120(%rbp), %eax
	subl	128(%rbp), %eax
	subl	136(%rbp), %eax
	subl	144(%rbp), %eax
	movl	%eax, %edx
	movl	152(%rbp), %eax
	addl	%eax, %edx
	movl	160(%rbp), %eax
	addl	%eax, %edx
	movl	168(%rbp), %eax
	addl	%eax, %edx
	movl	176(%rbp), %eax
	addl	%eax, %edx
	movl	184(%rbp), %eax
	addl	%eax, %edx
	movl	192(%rbp), %eax
	addl	%eax, %edx
	movl	200(%rbp), %eax
	addl	%eax, %edx
	movl	208(%rbp), %eax
	addl	%eax, %edx
	movl	216(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	testParam32, .-testParam32
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	$0, a0(%rip)
	movl	$1, a1(%rip)
	movl	$2, a2(%rip)
	movl	$3, a3(%rip)
	movl	$4, a4(%rip)
	movl	$5, a5(%rip)
	movl	$6, a6(%rip)
	movl	$7, a7(%rip)
	movl	$8, a8(%rip)
	movl	$9, a9(%rip)
	movl	$0, a10(%rip)
	movl	$1, a11(%rip)
	movl	$2, a12(%rip)
	movl	$3, a13(%rip)
	movl	$4, a14(%rip)
	movl	$5, a15(%rip)
	movl	$6, a16(%rip)
	movl	$7, a17(%rip)
	movl	$8, a18(%rip)
	movl	$9, a19(%rip)
	movl	$0, a20(%rip)
	movl	$1, a21(%rip)
	movl	$2, a22(%rip)
	movl	$3, a23(%rip)
	movl	$4, a24(%rip)
	movl	$5, a25(%rip)
	movl	$6, a26(%rip)
	movl	$7, a27(%rip)
	movl	$8, a28(%rip)
	movl	$9, a29(%rip)
	movl	$0, a30(%rip)
	movl	$1, a31(%rip)
	movl	$4, a32(%rip)
	movl	$5, a33(%rip)
	movl	$6, a34(%rip)
	movl	$7, a35(%rip)
	movl	$8, a36(%rip)
	movl	$9, a37(%rip)
	movl	$0, a38(%rip)
	movl	$1, a39(%rip)
	movl	a7(%rip), %r8d
	movl	a6(%rip), %edi
	movl	a5(%rip), %r9d
	movl	a4(%rip), %r10d
	movl	a3(%rip), %ecx
	movl	a2(%rip), %edx
	movl	a1(%rip), %esi
	movl	a0(%rip), %eax
	pushq	%r8
	pushq	%rdi
	movl	%r10d, %r8d
	movl	%eax, %edi
	call	testParam8
	addq	$16, %rsp
	movl	%eax, a0(%rip)
	movl	a15(%rip), %edx
	movl	a14(%rip), %r15d
	movl	a13(%rip), %r14d
	movl	a12(%rip), %r13d
	movl	a11(%rip), %r12d
	movl	a10(%rip), %ebx
	movl	a9(%rip), %r11d
	movl	a8(%rip), %r10d
	movl	a39(%rip), %r9d
	movl	a38(%rip), %r8d
	movl	a37(%rip), %eax
	movl	%eax, -44(%rbp)
	movl	a36(%rip), %ecx
	movl	%ecx, -48(%rbp)
	movl	a35(%rip), %ecx
	movl	a34(%rip), %edi
	movl	a33(%rip), %esi
	movl	a32(%rip), %eax
	pushq	%rdx
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	pushq	%r11
	pushq	%r10
	pushq	%r9
	pushq	%r8
	movl	-44(%rbp), %r9d
	movl	-48(%rbp), %r8d
	movl	%edi, %edx
	movl	%eax, %edi
	call	testParam16
	addq	$80, %rsp
	movl	%eax, a0(%rip)
	movl	a31(%rip), %edx
	movl	a30(%rip), %ecx
	movl	a29(%rip), %r8d
	movl	a28(%rip), %r9d
	movl	a27(%rip), %r11d
	movl	a26(%rip), %ebx
	movl	a25(%rip), %r13d
	movl	a24(%rip), %r15d
	movl	a23(%rip), %eax
	movl	%eax, -44(%rbp)
	movl	a22(%rip), %esi
	movl	%esi, -48(%rbp)
	movl	a21(%rip), %edi
	movl	%edi, -52(%rbp)
	movl	a20(%rip), %r14d
	movl	%r14d, -56(%rbp)
	movl	a19(%rip), %r10d
	movl	%r10d, -60(%rbp)
	movl	a18(%rip), %r12d
	movl	%r12d, -64(%rbp)
	movl	a17(%rip), %eax
	movl	%eax, -68(%rbp)
	movl	a16(%rip), %esi
	movl	%esi, -72(%rbp)
	movl	a15(%rip), %edi
	movl	%edi, -76(%rbp)
	movl	a14(%rip), %r14d
	movl	%r14d, -80(%rbp)
	movl	a13(%rip), %r10d
	movl	%r10d, -84(%rbp)
	movl	a12(%rip), %r12d
	movl	%r12d, -88(%rbp)
	movl	a11(%rip), %eax
	movl	%eax, -92(%rbp)
	movl	a10(%rip), %esi
	movl	%esi, -96(%rbp)
	movl	a9(%rip), %edi
	movl	%edi, -100(%rbp)
	movl	a8(%rip), %r14d
	movl	%r14d, -104(%rbp)
	movl	a7(%rip), %r14d
	movl	a6(%rip), %r12d
	movl	a5(%rip), %r10d
	movl	%r10d, -108(%rbp)
	movl	a4(%rip), %eax
	movl	%eax, -112(%rbp)
	movl	a3(%rip), %r10d
	movl	a2(%rip), %edi
	movl	a1(%rip), %esi
	movl	a0(%rip), %eax
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%r11
	pushq	%rbx
	pushq	%r13
	pushq	%r15
	movl	-44(%rbp), %ebx
	pushq	%rbx
	movl	-48(%rbp), %ebx
	pushq	%rbx
	movl	-52(%rbp), %ebx
	pushq	%rbx
	movl	-56(%rbp), %edx
	pushq	%rdx
	movl	-60(%rbp), %ebx
	pushq	%rbx
	movl	-64(%rbp), %edx
	pushq	%rdx
	movl	-68(%rbp), %ecx
	pushq	%rcx
	movl	-72(%rbp), %ebx
	pushq	%rbx
	movl	-76(%rbp), %edx
	pushq	%rdx
	movl	-80(%rbp), %ecx
	pushq	%rcx
	movl	-84(%rbp), %ebx
	pushq	%rbx
	movl	-88(%rbp), %edx
	pushq	%rdx
	movl	-92(%rbp), %ecx
	pushq	%rcx
	movl	-96(%rbp), %ebx
	pushq	%rbx
	movl	-100(%rbp), %edx
	pushq	%rdx
	movl	-104(%rbp), %ecx
	pushq	%rcx
	pushq	%r14
	pushq	%r12
	movl	-108(%rbp), %r9d
	movl	-112(%rbp), %r8d
	movl	%r10d, %ecx
	movl	%edi, %edx
	movl	%eax, %edi
	call	testParam32
	addq	$208, %rsp
	movl	%eax, a0(%rip)
	movl	$0, %eax
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
