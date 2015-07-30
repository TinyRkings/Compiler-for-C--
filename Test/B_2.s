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
	li $t0, 2
	addi $sp, $sp, -4
	sw $t0, -12($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal read
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	addi $sp, $sp, -4
	sw $v0, -16($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	addi $sp, $sp, -4
	sw $t0, -24($fp)
label0 :
	lw $t0, -12($fp)
	lw $t1, -24($fp)
	blt $t0, $t1, label1
	j label2
label1 :
	li $t0, 2
	addi $sp, $sp, -4
	sw $t0, -28($fp)
	li $t0, 1
	addi $sp, $sp, -4
	sw $t0, -32($fp)
label3 :
	lw $t0, -28($fp)
	lw $t1, -12($fp)
	blt $t0, $t1, label6
	j label5
label6 :
	lw $t0, -32($fp)
	li $t1, 1
	beq $t0, $t1, label4
	j label5
label4 :
	lw $t0, -12($fp)
	lw $t1, -28($fp)
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -36($fp)
	lw $t0, -36($fp)
	lw $t1, -28($fp)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -40($fp)
	lw $t0, -40($fp)
	lw $t1, -12($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -44($fp)
	lw $t0, -44($fp)
	li $t1, 0
	beq $t0, $t1, label7
	j label8
label7 :
	li $t0, 0
	sw $t0, -32($fp)
label8 :
	lw $t0, -28($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -48($fp)
	lw $t0, -48($fp)
	sw $t0, -28($fp)
	j label3
label5 :
	lw $t0, -32($fp)
	li $t1, 1
	beq $t0, $t1, label9
	j label10
label9 :
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
label10 :
	lw $t0, -12($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -52($fp)
	lw $t0, -52($fp)
	sw $t0, -12($fp)
	j label0
label2 :
	move $sp, $fp
	li $v0, 0
	jr $ra
