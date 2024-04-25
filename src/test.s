	.file	"test.c"
	.text
	.section	.rodata
.LC0:
	.string	"R"
.LC1:
	.string	"B"
.LC2:
	.string	"%d(%s) "
	.text
	.globl	printTree2
	.type	printTree2, @function
printTree2:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -32(%rbp)
	je	.L7
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -32(%rbp)
	je	.L7
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L5
	leaq	.LC0(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L6
.L5:
	leaq	.LC1(%rip), %rax
	movq	%rax, -8(%rbp)
.L6:
	movq	-32(%rbp), %rax
	movl	4(%rax), %eax
	movq	-8(%rbp), %rdx
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-32(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	printTree2
	movq	-32(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	printTree2
	jmp	.L1
.L7:
	nop
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	printTree2, .-printTree2
	.section	.rodata
.LC3:
	.string	"    "
.LC4:
	.string	" \\_ "
.LC5:
	.string	" /\342\216\272 "
.LC6:
	.string	"\033[31m%d\033[0m\n"
.LC7:
	.string	"%d\n"
	.text
	.globl	printTree
	.type	printTree, @function
printTree:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	%ecx, -40(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -32(%rbp)
	je	.L18
	movl	-36(%rbp), %eax
	leal	1(%rax), %edx
	movq	-32(%rbp), %rax
	movq	24(%rax), %rsi
	movq	-24(%rbp), %rax
	movl	$0, %ecx
	movq	%rax, %rdi
	call	printTree
	movl	$0, -4(%rbp)
	jmp	.L11
.L12:
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
.L11:
	movl	-36(%rbp), %eax
	subl	$1, %eax
	cmpl	%eax, -4(%rbp)
	jl	.L12
	cmpl	$0, -36(%rbp)
	jle	.L13
	cmpl	$0, -40(%rbp)
	je	.L14
	leaq	.LC4(%rip), %rax
	jmp	.L15
.L14:
	leaq	.LC5(%rip), %rax
.L15:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L13:
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L16
	movq	-32(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, %esi
	leaq	.LC6(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L17
.L16:
	movq	-32(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, %esi
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L17:
	movl	-36(%rbp), %eax
	leal	1(%rax), %edx
	movq	-32(%rbp), %rax
	movq	16(%rax), %rsi
	movq	-24(%rbp), %rax
	movl	$1, %ecx
	movq	%rax, %rdi
	call	printTree
	jmp	.L8
.L18:
	nop
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	printTree, .-printTree
	.section	.rodata
	.align 8
.LC8:
	.string	"-------------------------------------"
	.align 8
.LC9:
	.string	"Please input your choice(1/2/3/4/5/0)"
.LC10:
	.string	"1: rbtree insert"
.LC11:
	.string	"2: rbtree find"
.LC12:
	.string	"3: rbtree_erase"
.LC13:
	.string	"4: rbtree min"
.LC14:
	.string	"5: rbtree max"
.LC15:
	.string	"0: Quit;"
.LC16:
	.string	": "
.LC17:
	.string	"%d"
.LC18:
	.string	"\352\260\222\354\235\204 \354\236\205\353\240\245\355\225\230\354\204\270\354\232\224:"
.LC19:
	.string	"The resulting tree is: "
.LC20:
	.string	"\353\213\244\354\213\234 \354\236\205\353\240\245\355\225\230\354\204\270\354\232\224"
	.align 8
.LC21:
	.string	"\354\260\276\354\235\204 \352\260\222\354\235\204 \354\236\205\353\240\245\355\225\230\354\204\270\354\232\224:"
.LC22:
	.string	"The resulting node is: "
.LC23:
	.string	"(RED)"
.LC24:
	.string	"(BLACK)"
.LC25:
	.string	"\354\260\276\354\235\204 \354\210\230 \354\227\206\354\212\265\353\213\210\353\213\244."
	.align 8
.LC26:
	.string	"\354\247\200\354\232\270 \352\260\222\354\235\204 \354\236\205\353\240\245\355\225\230\354\204\270\354\232\224:"
.LC27:
	.string	"The erased node is: "
.LC28:
	.string	"(R)"
.LC29:
	.string	"(B)"
.LC30:
	.string	"Minimum is %d\n"
	.align 8
.LC31:
	.string	"\354\265\234\354\206\214\352\260\222\354\235\204 \354\260\276\354\235\204 \354\210\230 \354\227\206\354\212\265\353\213\210\353\213\244."
.LC32:
	.string	"Maximum is %d\n"
	.align 8
.LC33:
	.string	"\354\265\234\353\214\200\352\260\222\354\235\204 \354\260\276\354\235\204 \354\210\230 \354\227\206\354\212\265\353\213\210\353\213\244."
.LC34:
	.string	"Choice unknown;"
.LC35:
	.string	"%c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -28(%rbp)
	call	new_rbtree@PLT
	movq	%rax, -24(%rbp)
	movl	$1, -36(%rbp)
	jmp	.L20
.L47:
	leaq	.LC8(%rip), %rdi
	call	puts@PLT
	leaq	.LC9(%rip), %rdi
	call	puts@PLT
	leaq	.LC8(%rip), %rdi
	call	puts@PLT
	leaq	.LC10(%rip), %rdi
	call	puts@PLT
	leaq	.LC11(%rip), %rdi
	call	puts@PLT
	leaq	.LC12(%rip), %rdi
	call	puts@PLT
	leaq	.LC13(%rip), %rdi
	call	puts@PLT
	leaq	.LC14(%rip), %rdi
	call	puts@PLT
	leaq	.LC15(%rip), %rdi
	call	puts@PLT
	leaq	.LC16(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-36(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC17(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	testl	%eax, %eax
	jle	.L21
	movl	-36(%rbp), %eax
	cmpl	$5, %eax
	ja	.L22
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L24(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L24(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L24:
	.long	.L50-.L24
	.long	.L25-.L24
	.long	.L26-.L24
	.long	.L27-.L24
	.long	.L28-.L24
	.long	.L29-.L24
	.text
.L25:
	leaq	.LC18(%rip), %rdi
	call	puts@PLT
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC17(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$1, %eax
	jne	.L30
	movl	-32(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	rbtree_insert@PLT
	leaq	.LC19(%rip), %rdi
	call	puts@PLT
	movq	-24(%rbp), %rax
	movq	(%rax), %rsi
	movl	-28(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	$0, %ecx
	movq	%rax, %rdi
	call	printTree
	movl	$10, %edi
	call	putchar@PLT
	addl	$1, -28(%rbp)
	jmp	.L20
.L30:
	leaq	.LC20(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L20
.L26:
	leaq	.LC21(%rip), %rdi
	call	puts@PLT
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC17(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$1, %eax
	jne	.L33
	movl	-32(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	rbtree_find@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	je	.L34
	leaq	.LC22(%rip), %rdi
	call	puts@PLT
	movq	-16(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, %esi
	leaq	.LC17(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L35
	leaq	.LC23(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L36
.L35:
	leaq	.LC24(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L36:
	movl	$10, %edi
	call	putchar@PLT
	jmp	.L20
.L34:
	leaq	.LC25(%rip), %rdi
	call	puts@PLT
	jmp	.L20
.L33:
	leaq	.LC20(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L20
.L27:
	leaq	.LC26(%rip), %rdi
	call	puts@PLT
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC17(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	cmpl	$1, %eax
	jne	.L39
	movl	-32(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	rbtree_find@PLT
	movq	%rax, -16(%rbp)
	leaq	.LC27(%rip), %rdi
	call	puts@PLT
	movq	-16(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, %esi
	leaq	.LC17(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L40
	leaq	.LC28(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L41
.L40:
	leaq	.LC29(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L41:
	movl	$10, %edi
	call	putchar@PLT
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	rbtree_erase@PLT
	leaq	.LC19(%rip), %rdi
	call	puts@PLT
	movq	-24(%rbp), %rax
	movq	(%rax), %rsi
	movl	-28(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	$0, %ecx
	movq	%rax, %rdi
	call	printTree
	movl	$10, %edi
	call	putchar@PLT
	subl	$1, -28(%rbp)
	jmp	.L20
.L39:
	leaq	.LC20(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L20
.L28:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	rbtree_min@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	je	.L43
	movq	-16(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, %esi
	leaq	.LC30(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L20
.L43:
	leaq	.LC31(%rip), %rdi
	call	puts@PLT
	jmp	.L20
.L29:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	rbtree_max@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	je	.L45
	movq	-16(%rbp), %rax
	movl	4(%rax), %eax
	movl	%eax, %esi
	leaq	.LC32(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L20
.L45:
	leaq	.LC33(%rip), %rdi
	call	puts@PLT
	jmp	.L20
.L22:
	leaq	.LC34(%rip), %rdi
	call	puts@PLT
	jmp	.L20
.L50:
	nop
	jmp	.L20
.L21:
	leaq	-37(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC35(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
.L20:
	movl	-36(%rbp), %eax
	testl	%eax, %eax
	jne	.L47
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L49
	call	__stack_chk_fail@PLT
.L49:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
