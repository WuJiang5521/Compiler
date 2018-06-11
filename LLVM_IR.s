	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.file	"main"
	.text
	.p2align	2               # -- Begin function main
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.ent	main
main:                                   # @main
	.cfi_startproc
	.frame	$sp,24,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -24
	.cfi_def_cfa_offset 24
	sw	$ra, 20($sp)            # 4-byte Folded Spill
	sw	$16, 16($sp)            # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 16, -8
	lui	$16, %hi(k)
	sw	$zero, %lo(k)($16)
	addiu	$4, $16, %lo(k)
	jal	go
	addiu	$5, $zero, 5
	move	$5, $2
	lui	$1, %hi(f)
	sw	$2, %lo(f)($1)
	lui	$1, %hi($.str)
	jal	printf
	addiu	$4, $1, %lo($.str)
	lui	$1, %hi($.str.1)
	lw	$5, %lo(k)($16)
	jal	printf
	addiu	$4, $1, %lo($.str.1)
	lw	$16, 16($sp)            # 4-byte Folded Reload
	lw	$ra, 20($sp)            # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end0:
	.size	main, ($func_end0)-main
	.cfi_endproc
                                        # -- End function
	.p2align	2               # -- Begin function go
	.type	go,@function
	.set	nomicromips
	.set	nomips16
	.ent	go
go:                                     # @go
	.cfi_startproc
	.frame	$sp,48,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
# %bb.0:                                # %entry
	addiu	$sp, $sp, -48
	.cfi_def_cfa_offset 48
	sw	$ra, 44($sp)            # 4-byte Folded Spill
	sw	$16, 40($sp)            # 4-byte Folded Spill
	.cfi_offset 31, -4
	.cfi_offset 16, -8
	sw	$5, 32($sp)
	blez	$5, $BB1_2
	sw	$4, 36($sp)
# %bb.1:                                # %thenStmt
	lw	$4, 36($sp)
	lw	$16, 32($sp)
	jal	go
	addiu	$5, $16, -1
	mul	$1, $16, $2
	j	$BB1_3
	sw	$1, 28($sp)
$BB1_2:                                 # %elseStmt
	addiu	$1, $zero, 1
	sw	$1, 28($sp)
$BB1_3:                                 # %mergeStmt
	lw	$1, 36($sp)
	lw	$2, 0($1)
	lw	$3, 28($sp)
	addu	$2, $2, $3
	sw	$2, 0($1)
	lui	$1, %hi(k)
	lw	$3, %lo(k)($1)
	lw	$2, 28($sp)
	addu	$3, $3, $2
	sw	$3, %lo(k)($1)
	lw	$16, 40($sp)            # 4-byte Folded Reload
	lw	$ra, 44($sp)            # 4-byte Folded Reload
	jr	$ra
	addiu	$sp, $sp, 48
	.set	at
	.set	macro
	.set	reorder
	.end	go
$func_end1:
	.size	go, ($func_end1)-go
	.cfi_endproc
                                        # -- End function
	.type	f,@object               # @f
	.bss
	.globl	f
	.p2align	2
f:
	.4byte	0                       # 0x0
	.size	f, 4

	.type	k,@object               # @k
	.globl	k
	.p2align	2
k:
	.4byte	0                       # 0x0
	.size	k, 4

	.type	$.str,@object           # @.str
	.section	.rodata,"a",@progbits
	.p2align	2
$.str:
	.asciz	"%d\n"
	.size	$.str, 4

	.type	$.str.1,@object         # @.str.1
	.p2align	2
$.str.1:
	.asciz	"%d\n"
	.size	$.str.1, 4


	.section	".note.GNU-stack","",@progbits
	.text
