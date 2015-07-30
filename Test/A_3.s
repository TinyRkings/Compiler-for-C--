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
	li $t0, 12
	addi $sp, $sp, -4
	sw $t0, -12($fp)
	li $t0, 1
	addi $sp, $sp, -4
	sw $t0, -16($fp)
label0 :
	lw $t0, -16($fp)
	lw $t1, -12($fp)
	blt $t0, $t1, label1
	j label2
label1 :
	lw $t0, -12($fp)
	lw $t1, -16($fp)
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -20($fp)
	lw $t0, -20($fp)
	lw $t1, -16($fp)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -24($fp)
	lw $t0, -24($fp)
	lw $t1, -12($fp)
	beq $t0, $t1, label3
	j label4
label3 :
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
label4 :
	lw $t0, -16($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -28($fp)
	lw $t0, -28($fp)
	sw $t0, -16($fp)
	j label0
label2 :
	move $sp, $fp
	li $v0, 0
	jr $ra
