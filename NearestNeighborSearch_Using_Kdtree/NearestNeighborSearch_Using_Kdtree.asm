########################################
################ UmBum #################
########################################

	.data
	.align	2
kdtree:
	.space	8200
	.align	2
visited:
	.space 1025
	
current_best_distance:
	.word	134217727
	.align	2
nearest:
	.space	8

####### File IO Variable #######
fname: 		
	.asciiz "input.txt"
buffer:		
	.space	1024
readbytestr:	
	.asciiz " bytes were read from input.txt\n"
ninput:
	.word	0
inputarray:
	.space 208

comma:		.asciiz ","
space:		.asciiz " "
leftp:		.asciiz "("
rightp:		.asciiz ")"
kdtreestr:  .asciiz "k-d tree array : "	
neareststr: .asciiz "\nNearest Neighbor : "
promptx:	.asciiz "input query point x value : "
prompty:	.asciiz "input query point y value : "
CRLF:		.asciiz "\n"


	.text
	.align	2
	.globl	initialize
initialize:
	.frame	$fp,32,$31		# vars= 16, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	sw	$fp,28($sp)
	move	$fp,$sp
	sw	$0,8($fp)
	movz	$31,$31,$0
	sw	$0,12($fp)
	sw	$0,16($fp)
	b	$L82
	nop

$L88:
	sw	$0,12($fp)
	sw	$0,16($fp)
	nop
$L83:
	lw	$2,8($fp)
	nop
	addiu	$3,$2,1
	sw	$3,8($fp)
	la	$3,buffer
	nop
	addu	$2,$3,$2
	lb	$3,0($2)
	li	$2,40			# 0x28
	bne	$3,$2,$L83
	nop

$L84:
	lw	$2,12($fp)
	nop
	sll	$2,$2,1
	sll	$3,$2,2
	addu	$2,$2,$3
	sw	$2,12($fp)
	la	$3,buffer
	lw	$2,8($fp)
	nop
	addu	$2,$3,$2
	lb	$2,0($2)
	nop
	addiu	$2,$2,-48
	lw	$3,12($fp)
	nop
	addu	$2,$3,$2
	sw	$2,12($fp)
	lw	$2,8($fp)
	nop
	addiu	$2,$2,1
	sw	$2,8($fp)
	la	$3,buffer
	lw	$2,8($fp)
	nop
	addu	$2,$3,$2
	lb	$3,0($2)
	li	$2,44			# 0x2c
	bne	$3,$2,$L84
	nop

$L85:
	lw	$2,8($fp)
	nop
	addiu	$2,$2,1
	sw	$2,8($fp)
	la	$3,buffer
	lw	$2,8($fp)
	nop
	addu	$2,$3,$2
	lb	$3,0($2)
	li	$2,32			# 0x20
	beq	$3,$2,$L85
	nop

$L86:
	lw	$2,16($fp)
	nop
	sll	$2,$2,1
	sll	$3,$2,2
	addu	$2,$2,$3
	sw	$2,16($fp)
	la	$3,buffer
	lw	$2,8($fp)
	nop
	addu	$2,$3,$2
	lb	$2,0($2)
	nop
	addiu	$2,$2,-48
	lw	$3,16($fp)
	nop
	addu	$2,$3,$2
	sw	$2,16($fp)
	lw	$2,8($fp)
	nop
	addiu	$2,$2,1
	sw	$2,8($fp)
	la	$3,buffer
	lw	$2,8($fp)
	nop
	addu	$2,$3,$2
	lb	$3,0($2)
	li	$2,41			# 0x29
	bne	$3,$2,$L86
	nop

	la	$2,ninput
	nop
	lw	$2,0($2)
	la	$3,inputarray
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,12($fp)
	nop
	sw	$3,0($2)
	la	$2,ninput
	nop
	lw	$2,0($2)
	la	$3,inputarray
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,16($fp)
	nop
	sw	$3,4($2)
	la	$2,ninput
	nop
	lw	$2,0($2)
	nop
	addiu	$3,$2,1
	la	$2,ninput
	nop
	sw	$3,0($2)
	lw	$2,8($fp)
	nop
	addiu	$2,$2,1
	sw	$2,8($fp)
$L82:
	la	$3,buffer
	lw	$2,8($fp)
	nop
	addu	$2,$3,$2
	lb	$2,0($2)
	nop
	beq	$2,$0,$L89
	nop

	lw	$2,8($fp)
	nop
	addiu	$2,$2,1
	la	$3,buffer
	nop
	addu	$2,$3,$2
	lb	$2,0($2)
	nop
	bne	$2,$0,$L88
	nop

$L89:
	nop
	move	$sp,$fp
	lw	$fp,28($sp)
	addiu	$sp,$sp,32
	j	$31
	nop
	
	.align	2
	.globl	insertSegment
insertSegment:
	.frame	$fp,40,$31		# vars= 24, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-40
	sw	$fp,36($sp)
	move	$fp,$sp
	sw	$0,16($fp)
	movz	$31,$31,$0
	b	$L2
	nop

$L11:
	la	$3,inputarray
	lw	$2,16($fp)
	nop
	sll	$2,$2,3				# idx * 8 ( entry size is 8 )
	addu	$2,$3,$2
	lw	$2,0($2)
	nop
	sw	$2,20($fp)
	la	$3,inputarray
	lw	$2,16($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$2,4($2)
	nop
	sw	$2,24($fp)
	li	$2,1			# 0x1
	sw	$2,8($fp)
	sw	$0,12($fp)
	b	$L3
	nop

$L10:
	lw	$2,12($fp)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$L4
	nop

	lw	$2,12($fp)
	nop
	addiu	$2,$2,1
	sw	$2,12($fp)
	la	$3,kdtree
	lw	$2,8($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,20($fp)
	nop
	slt	$2,$3,$2
	bne	$2,$0,$L5
	nop

	lw	$2,8($fp)
	nop
	sll	$2,$2,1
	sw	$2,8($fp)
	b	$L3
	nop

$L5:
	la	$3,kdtree
	lw	$2,8($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,20($fp)
	nop
	slt	$2,$3,$2
	beq	$2,$0,$L3
	nop

	lw	$2,8($fp)
	nop
	sll	$2,$2,1
	addiu	$2,$2,1
	sw	$2,8($fp)
	b	$L3
	nop

$L4:
	lw	$3,12($fp)
	li	$2,-2147483648			# 0xffffffff80000000
	ori	$2,$2,0x1
	and	$2,$3,$2
	bgez	$2,$L7
	nop

	addiu	$2,$2,-1
	li	$3,-2			# 0xfffffffffffffffe
	or	$2,$2,$3
	addiu	$2,$2,1
$L7:
	move	$3,$2
	li	$2,1			# 0x1
	bne	$3,$2,$L3
	nop

	lw	$2,12($fp)
	nop
	addiu	$2,$2,1
	sw	$2,12($fp)
	la	$3,kdtree
	lw	$2,8($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,4($2)
	lw	$2,24($fp)
	nop
	slt	$2,$3,$2
	bne	$2,$0,$L8
	nop

	lw	$2,8($fp)
	nop
	sll	$2,$2,1
	sw	$2,8($fp)
	b	$L3
	nop

$L8:
	la	$3,kdtree
	lw	$2,8($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,4($2)
	lw	$2,24($fp)
	nop
	slt	$2,$3,$2
	beq	$2,$0,$L3
	nop

	lw	$2,8($fp)
	nop
	sll	$2,$2,1
	addiu	$2,$2,1
	sw	$2,8($fp)
$L3:
	la	$3,kdtree
	lw	$2,8($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$2,0($2)
	nop
	beq	$2,$0,$L9
	nop

	la	$3,kdtree
	lw	$2,8($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$2,4($2)
	nop
	bne	$2,$0,$L10
	nop

$L9:
	la	$3,kdtree
	lw	$2,8($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,20($fp)
	nop
	sw	$3,0($2)
	la	$3,kdtree
	lw	$2,8($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,24($fp)
	nop
	sw	$3,4($2)
	lw	$2,16($fp)
	nop
	addiu	$2,$2,1
	sw	$2,16($fp)
$L2:			
	la	$2,ninput		# for (int i = 0; i < ninput; i ++)
	nop					
	lw	$2,0($2)		# $2 is ninput
	lw	$3,16($fp)		# $3 is i
	nop
	slt	$2,$3,$2		# set on less than. ninput < i
	bne	$2,$0,$L11		# if ninput < i, branch to $L11
	nop

	nop
	move	$sp,$fp
	lw	$fp,36($sp)
	addiu	$sp,$sp,40
	j	$31
	nop

	.align 2
	.globl printTreeArray
printTreeArray:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	nop
	
	###### print kdtree array
	li $v0, 4		# print_str syscall number
	la $a0, kdtreestr
	syscall
	addu $t5, $0, $0
	la $t0, kdtree
	addiu $t1, $t0, 8  # kdtree[0].x is 0($t1)
$L99:
	li $v0, 4		# print_str syscall number
	la $a0, leftp	# print '('
	syscall
	li $v0, 1		# print_int syscall number
	lw $a0,0($t1)	# print kdtree[i].x
	syscall
	li $v0, 4		# print_str syscall number
	la $a0, comma   # print ','
	syscall
	li $v0, 1
	lw $a0,4($t1)	# print kdtree[i].y
	syscall
	li $v0, 4		# print_str syscall number
	la $a0, rightp # print ','
	syscall
	addiu $t1, $t1, 8		# kdtree's next entry
	addiu $t5, $t5, 1		# i++
	slt $t6, $t5, 1024		# if i < 1024
	bne $t6, $0, $L99	# loop
	###### print kdtree array end
	
	move	$sp,$fp
	movz	$31,$31,$0
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	j	$31
	nop
	
	.align 2
	.globl query
query:
	.frame	$fp,96,$31		# vars= 64, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-96
	sw	$31,92($sp)
	sw	$fp,88($sp)
	move	$fp,$sp
	movz	$31,$31,$0
	sw	$4,96($fp)
	sw	$5,100($fp)
	sw	$6,104($fp)
	sw	$7,108($fp)
	lw	$2,104($fp)
	nop
	sw	$2,24($fp)
	sw	$0,44($fp)
	sw	$0,48($fp)
	sw	$0,52($fp)
	sw	$0,56($fp)
	sw	$0,60($fp)
	sw	$0,64($fp)
	sw	$0,68($fp)
	sw	$0,72($fp)
	sw	$0,76($fp)
	sw	$0,80($fp)
	sw	$0,28($fp)
	b	$L22
	nop

$L29:
	la	$3,visited
	lw	$2,24($fp)
	nop
	addu	$2,$3,$2
	li	$3,1			# 0x1
	sb	$3,0($2)
	lw	$2,28($fp)
	nop
	addiu	$3,$2,1
	sw	$3,28($fp)
	sll	$2,$2,2
	addiu	$3,$fp,24
	addu	$2,$3,$2
	lw	$3,24($fp)
	nop
	sw	$3,20($2)
	lw	$2,108($fp)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$L23
	nop

	lw	$2,108($fp)
	nop
	addiu	$2,$2,1
	sw	$2,108($fp)
	la	$3,kdtree
	lw	$2,24($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,96($fp)
	nop
	slt	$2,$3,$2
	bne	$2,$0,$L24
	nop

	lw	$2,24($fp)
	nop
	sll	$2,$2,1
	sw	$2,24($fp)
	b	$L22
	nop

$L24:
	la	$3,kdtree
	lw	$2,24($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,0($2)
	lw	$2,96($fp)
	nop
	slt	$2,$3,$2
	beq	$2,$0,$L22
	nop

	lw	$2,24($fp)
	nop
	sll	$2,$2,1
	addiu	$2,$2,1
	sw	$2,24($fp)
	b	$L22
	nop

$L23:
	lw	$3,108($fp)
	li	$2,-2147483648			# 0xffffffff80000000
	ori	$2,$2,0x1
	and	$2,$3,$2
	bgez	$2,$L26
	nop

	addiu	$2,$2,-1
	li	$3,-2			# 0xfffffffffffffffe
	or	$2,$2,$3
	addiu	$2,$2,1
$L26:
	move	$3,$2
	li	$2,1			# 0x1
	bne	$3,$2,$L22
	nop

	lw	$2,108($fp)
	nop
	addiu	$2,$2,1
	sw	$2,108($fp)
	la	$3,kdtree
	lw	$2,24($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,4($2)
	lw	$2,100($fp)
	nop
	slt	$2,$3,$2
	bne	$2,$0,$L27
	nop

	lw	$2,24($fp)
	nop
	sll	$2,$2,1
	sw	$2,24($fp)
	b	$L22
	nop

$L27:
	la	$3,kdtree
	lw	$2,24($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,4($2)
	lw	$2,100($fp)
	nop
	slt	$2,$3,$2
	beq	$2,$0,$L22
	nop

	lw	$2,24($fp)
	nop
	sll	$2,$2,1
	addiu	$2,$2,1
	sw	$2,24($fp)
$L22:
	la	$3,kdtree
	lw	$2,24($fp)		# get local var : idx
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$2,0($2)		# if kdtree[idx].x == 0 branch L19  ( short circuit evaluation )
	nop
	beq	$2,$0,$L28
	nop

	la	$3,kdtree
	lw	$2,24($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$2,4($2)		# if kdtree[idx].y != 0 goto L29
	nop
	bne	$2,$0,$L29
	nop

$L28:
	lw	$2,108($fp)
	nop
	addiu	$2,$2,-1
	sw	$2,108($fp)
	b	$L30
	nop

$L36:
	lw	$2,28($fp)
	nop
	addiu	$2,$2,-1
	sw	$2,28($fp)
	lw	$2,28($fp)
	nop
	sll	$2,$2,2
	addiu	$3,$fp,24
	addu	$2,$3,$2
	lw	$2,20($2)
	nop
	sw	$2,24($fp)
	la	$3,kdtree
	lw	$2,24($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$2,0($2)
	lw	$3,96($fp)
	nop
	subu	$3,$3,$2
	la	$4,kdtree
	lw	$2,24($fp)
	nop
	sll	$2,$2,3
	addu	$2,$4,$2
	lw	$2,0($2)
	lw	$4,96($fp)
	nop
	subu	$2,$4,$2
	mult	$3,$2
	mflo	$3
	la	$4,kdtree
	lw	$2,24($fp)
	nop
	sll	$2,$2,3
	addu	$2,$4,$2
	lw	$2,4($2)
	lw	$4,100($fp)
	nop
	subu	$4,$4,$2
	la	$5,kdtree
	lw	$2,24($fp)
	nop
	sll	$2,$2,3
	addu	$2,$5,$2
	lw	$2,4($2)
	lw	$5,100($fp)
	nop
	subu	$2,$5,$2
	mult	$4,$2
	mflo	$2
	addu	$2,$3,$2
	sw	$2,40($fp)
	la	$2,current_best_distance
	nop
	lw	$2,0($2)
	lw	$3,40($fp)			# get local var : distance
	nop
	slt	$2,$3,$2			# if current_best_distance < distance
	beq	$2,$0,$L31
	nop

	la	$2,current_best_distance
	lw	$3,40($fp)			# get local var : distance
	nop
	sw	$3,0($2)			# assign : distance = current_best_distance 
	la	$3,kdtree
	lw	$2,24($fp)			# get local var : idx
	nop
	sll	$2,$2,3				# idx * 8
	addu	$2,$3,$2
	lw	$3,0($2)			# $3 = kdtree[idx].x
	la	$2,nearest
	nop
	sw	$3,0($2)
	la	$3,kdtree
	lw	$2,24($fp)
	nop
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$3,4($2)
	la	$2,nearest
	nop
	sw	$3,4($2)
$L31:
	lw	$2,108($fp)			# get local var : level
	nop
	addiu	$2,$2,-1		# level--;
	andi	$2,$2,0x1
	bne	$2,$0,$L32
	nop

	lw	$2,24($fp)
	nop
	srl	$3,$2,31
	addu	$2,$3,$2
	sra	$2,$2,1
	la	$3,kdtree
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$2,0($2)
	lw	$3,96($fp)
	nop
	subu	$3,$3,$2
	lw	$2,24($fp)
	nop
	srl	$4,$2,31
	addu	$2,$4,$2
	sra	$2,$2,1
	la	$4,kdtree
	sll	$2,$2,3
	addu	$2,$4,$2
	lw	$2,0($2)
	lw	$4,96($fp)
	nop
	subu	$2,$4,$2
	mult	$3,$2
	mflo	$2
	sw	$2,32($fp)
	b	$L33
	nop

$L32:
	lw	$2,24($fp)
	nop
	srl	$3,$2,31
	addu	$2,$3,$2
	sra	$2,$2,1
	la	$3,kdtree
	sll	$2,$2,3
	addu	$2,$3,$2
	lw	$2,4($2)
	lw	$3,100($fp)
	nop
	subu	$3,$3,$2
	lw	$2,24($fp)
	nop
	srl	$4,$2,31
	addu	$2,$4,$2
	sra	$2,$2,1
	la	$4,kdtree
	sll	$2,$2,3
	addu	$2,$4,$2
	lw	$2,4($2)
	lw	$4,100($fp)
	nop
	subu	$2,$4,$2
	mult	$3,$2
	mflo	$2
	sw	$2,32($fp)
$L33:
	lw	$3,32($fp)
	lw	$2,40($fp)
	nop
	slt	$2,$3,$2
	beq	$2,$0,$L30
	nop

	lw	$2,24($fp)
	nop
	andi	$2,$2,0x1
	bne	$2,$0,$L34
	nop

	lw	$2,24($fp)
	nop
	addiu	$2,$2,1
	sw	$2,36($fp)
	b	$L35
	nop

$L34:
	lw	$2,24($fp)
	nop
	addiu	$2,$2,-1
	sw	$2,36($fp)
$L35:
	la	$3,visited
	lw	$2,36($fp)
	nop
	addu	$2,$3,$2
	lb	$2,0($2)
	nop
	bne	$2,$0,$L30
	nop

	lw	$7,108($fp)
	lw	$6,36($fp)
	lw	$5,100($fp)
	lw	$4,96($fp)
	jalr	query
	nop

	lw	$28,16($fp)
$L30:
	lw	$2,28($fp)
	nop
	bgtz	$2,$L36
	nop

	nop
	move	$sp,$fp
	lw	$31,92($sp)
	lw	$fp,88($sp)
	addiu	$sp,$sp,96
	j	$31
	nop
	
	
	.align	2
	.globl	main
main:
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32     # Expand stack to save $fp & $ra($31)
	sw	$31,28($sp)			# save $ra
	sw	$fp,24($sp)			# save $fp
	move	$fp,$sp

	####################################################
	# 1. initlialize() & file input    #################
	####################################################
	### File Open
	li $v0, 13				# File Open syscall number
	la $a0, fname			# a0 is file name
	li $a1, 0				# a1 is access flag. Read = 0 Write = 0
	li $a2, 0				# a2 is file mode. 0
	syscall
	move $s0, $v0			# save fd

	### File Read
	li $v0, 14				
	move $a0, $s0			# $a0 is file descriptor
	la $a1, buffer			# $a1 is buffer starting address
	li $a2, 1024			# $a2 is number of bytes to read
	syscall
	# $v0 is number of bytes actually read from file (-1 = error, 0 = end of file)
	
	move $a0, $v0
	li $v0, 1		# print_int syscall number
	syscall
	li $v0, 4		# print_str syscall number
	la $a0, readbytestr
	syscall
	
	### File Close
	li $v0, 16
	move $a0, $s0
	syscall
	
	movz	$31,$31,$0
	jalr	initialize
	nop
	
	####################################################
	# 2. insertSegment()    ############################
	####################################################
	jalr	insertSegment
	nop
	
	#jalr printTreeArray       # correctlly operate, but slow
	#nop
	li $v0, 4
	la $a0, CRLF
	syscall
	
	####################################################
	# 3. input query point  ############################
	####################################################
	
	li $v0, 4
	la $a0, promptx
	syscall
	li $v0, 5
	syscall
	move $t0, $v0
	
	li $v0, 4
	la $a0, prompty
	syscall
	li $v0, 5
	syscall
	move $t1, $v0
	
	####################################################
	# 4. query()    ####################################
	####################################################
	
	#li		$a0, 7		# query_point.x test
	#li		$a1, 13		# query_point.y test
	move	$a0, $t0		# query_point.x
	move	$a1, $t1		# query_point.y
	li		$a2, 1		# start_idx
	jalr	query
	nop
	
	####################################################
	# 5. print result   #################################
	####################################################
	
	li $v0, 4		# print_str syscall number
	la $a0, neareststr
	syscall
	li $v0, 4		# print_str syscall number
	la $a0, leftp	# print '('
	syscall
	li $v0, 1		# print_int syscall number
	lw $a0,nearest	# print nearest.x
	syscall
	li $v0, 4		# print_str syscall number
	la $a0, comma   # print ','
	syscall
	li $v0, 1
	la $t0,nearest
	lw $a0,4($t0)	# print nearest.y
	syscall
	li $v0, 4		# print_str syscall number
	la $a0, rightp # print ','
	syscall
	
	lw	$28,16($fp)
	move	$2,$0
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	nop
