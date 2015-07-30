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
	addi $sp, $sp, -4
	sw $t1, -12($fp)
	lw $t0, -12($fp)
	addi $sp, $sp, -4
	sw $t0, -16($fp)
	li $t0, 30
	addi $sp, $sp, -4
	sw $t0, -20($fp)
	li $t0, 20
	addi $sp, $sp, -4
	sw $t0, -24($fp)
	lw $t0, -16($fp)
	lw $t1, -16($fp)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -28($fp)
	li $t0, 4
	lw $t1, -20($fp)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -32($fp)
	lw $t0, -32($fp)
	lw $t1, -24($fp)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -36($fp)
	lw $t0, -28($fp)
	lw $t1, -36($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -40($fp)
	lw $t0, -40($fp)
	addi $sp, $sp, -4
	sw $t0, -44($fp)
	lw $a0, -44($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $t0, -16($fp)
	lw $t1, -24($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -48($fp)
	lw $t0, -48($fp)
	sw $t0, -16($fp)
	lw $t0, -16($fp)
	lw $t1, -24($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -52($fp)
	lw $t0, -52($fp)
	sw $t0, -24($fp)
	lw $t0, -16($fp)
	lw $t1, -24($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -56($fp)
	lw $t0, -56($fp)
	sw $t0, -16($fp)
	lw $t0, -16($fp)
	li $t1, 2
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -60($fp)
	lw $t0, -24($fp)
	li $t1, 3
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -64($fp)
	lw $t0, -60($fp)
	lw $t1, -64($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -68($fp)
	lw $t0, -16($fp)
	lw $t1, -20($fp)
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -72($fp)
	lw $t0, -72($fp)
	li $t1, 2
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -76($fp)
	lw $t0, -68($fp)
	lw $t1, -76($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -80($fp)
	lw $t0, -44($fp)
	lw $t1, -24($fp)
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -84($fp)
	lw $t0, -84($fp)
	li $t1, 2
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -88($fp)
	lw $t0, -80($fp)
	lw $t1, -88($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -92($fp)
	lw $t0, -92($fp)
	sw $t0, -20($fp)
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
	move $sp, $fp
	li $v0, 0
	jr $ra
