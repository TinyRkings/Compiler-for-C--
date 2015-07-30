.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
	li $v0, 4
	la $a0, _prompt
	syscall
	li $v0, 5
	syscall
	jr $ra

write:
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, _ret
	syscall
	move $v0, $0
	jr $ra


print_all:
	sw $ra, -4($sp)
	sw $sp, -8($sp)
	addi $sp, $sp, -8
	lw $fp, 0($sp)
	addi $sp, $sp, -4
	sw $a0, 0($sp)
	addi $sp, $sp, -4
	sw $a1, 0($sp)
	addi $sp, $sp, -4
	sw $a2, 0($sp)
	addi $sp, $sp, -4
	sw $a3, 0($sp)
	addi $sp, $sp, -4
	lw $t0, 0($fp)
	sw $t0, 0($sp)
	addi $sp, $sp, -4
	lw $t0, 4($fp)
	sw $t0, 0($sp)
	lw $a0, -12($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $a0, -16($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $a0, -20($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $a0, -24($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $a0, -28($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $a0, -32($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $sp, $fp
	li $v0, 0
	jr $ra

main:
	sw $ra, -4($sp)
	sw $sp, -8($sp)
	addi $sp, $sp, -8
	lw $fp, 0($sp)
	li $t0, 1
	addi $sp, $sp, -4
	sw $t0, -12($fp)
	li $t0, 2
	addi $sp, $sp, -4
	sw $t0, -16($fp)
	li $t0, 3
	addi $sp, $sp, -4
	sw $t0, -20($fp)
	li $t0, 4
	addi $sp, $sp, -4
	sw $t0, -24($fp)
	li $t0, 5
	addi $sp, $sp, -4
	sw $t0, -28($fp)
	li $t0, 6
	addi $sp, $sp, -4
	sw $t0, -32($fp)
	addi $sp, $fp, -1000
	sw $t0, 0($sp)
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	sw $t3, 12($sp)
	sw $t4, 16($sp)
	sw $t5, 20($sp)
	sw $t6, 24($sp)
	sw $t7, 28($sp)
	sw $t8, 32($sp)
	sw $t9, 36($sp)
	sw $s0, 40($sp)
	sw $s1, 44($sp)
	sw $s2, 48($sp)
	sw $s3, 52($sp)
	sw $s4, 56($sp)
	sw $s5, 60($sp)
	sw $s6, 64($sp)
	sw $s7, 68($sp)
	addi $sp, $sp, -8
	lw $a0, -12($fp)
	lw $a1, -16($fp)
	lw $a2, -20($fp)
	lw $a3, -24($fp)
	lw $t0, -28($fp)
	sw $t0, 0($sp)
	lw $t0, -32($fp)
	sw $t0, 4($sp)
	jal print_all
	addi $sp, $sp, 8
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	lw $t3, 12($sp)
	lw $t4, 16($sp)
	lw $t5, 20($sp)
	lw $t6, 24($sp)
	lw $t7, 28($sp)
	lw $t8, 32($sp)
	lw $t9, 36($sp)
	lw $s0, 40($sp)
	lw $s1, 44($sp)
	lw $s2, 48($sp)
	lw $s3, 52($sp)
	lw $s4, 56($sp)
	lw $s5, 60($sp)
	lw $s6, 64($sp)
	lw $s7, 68($sp)
	addi $sp, $sp, 1000
	lw $fp, -8($sp)
	addi $sp, $fp, -32
	lw $ra, -4($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	sw $t0, -36($fp)
	move $sp, $fp
	li $v0, 0
	jr $ra
