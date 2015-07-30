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

main:
	sw $ra, -4($sp)
	sw $sp, -8($sp)
	addi $sp, $sp, -8
	lw $fp, 0($sp)
	li $t0, 0
	addi $t1, $t0, -10
	sw $t1, -12($fp)
	lw $t0, -12($fp)
	sw $t0, -16($fp)
	li $t0, 30
	sw $t0, -20($fp)
	li $t0, 20
	sw $t0, -24($fp)
	lw $t0, -16($fp)
	lw $t1, -16($fp)
	mul $t2, $t0, $t1
	sw $t2, -28($fp)
	li $t0, 4
	lw $t1, -20($fp)
	mul $t2, $t0, $t1
	sw $t2, -32($fp)
	lw $t0, -32($fp)
	lw $t1, -24($fp)
	mul $t2, $t0, $t1
	sw $t2, -36($fp)
	lw $t0, -28($fp)
	lw $t1, -36($fp)
	sub $t2, $t0, $t1
	sw $t2, -40($fp)
	lw $t0, -40($fp)
	sw $t0, -44($fp)
	lw $a0, -44($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	li $t0, 2
	lw $t1, -16($fp)
	mul $t2, $t1, $t0
	sw $t2, -48($fp)
	lw $t0, -48($fp)
	sw $t0, -20($fp)
	lw $a0, -20($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	li $v0, 0
	jr $ra
