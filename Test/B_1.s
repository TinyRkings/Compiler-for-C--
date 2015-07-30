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
	sw $v0, -12($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	addi $sp, $sp, -4
	sw $t0, -20($fp)
	lw $t0, -20($fp)
	li $t1, 0
	ble $t0, $t1, label0
	j label1
label0 :
	li $t0, 0
	addi $t1, $t0, -1
	addi $sp, $sp, -4
	sw $t1, -24($fp)
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
	move $sp, $fp
	li $v0, 0
	jr $ra
	j label2
label1 :
	lw $t0, -20($fp)
	li $t1, 4
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -28($fp)
	lw $t0, -28($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -32($fp)
	lw $t0, -20($fp)
	lw $t1, -32($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -36($fp)
	lw $t0, -36($fp)
	addi $sp, $sp, -4
	sw $t0, -40($fp)
	lw $t0, -20($fp)
	li $t1, 100
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -44($fp)
	lw $t0, -44($fp)
	li $t1, 100
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -48($fp)
	lw $t0, -20($fp)
	lw $t1, -48($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -52($fp)
	lw $t0, -52($fp)
	addi $sp, $sp, -4
	sw $t0, -56($fp)
	lw $t0, -20($fp)
	li $t1, 400
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -60($fp)
	lw $t0, -60($fp)
	li $t1, 400
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -64($fp)
	lw $t0, -20($fp)
	lw $t1, -64($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -68($fp)
	lw $t0, -68($fp)
	addi $sp, $sp, -4
	sw $t0, -72($fp)
	lw $t0, -40($fp)
	li $t1, 0
	bne $t0, $t1, label3
	j label4
label3 :
	li $t0, 0
	addi $sp, $sp, -4
	sw $t0, -76($fp)
	j label5
label4 :
	lw $t0, -72($fp)
	li $t1, 0
	beq $t0, $t1, label6
	j label7
label6 :
	li $t0, 1
	sw $t0, -76($fp)
	j label8
label7 :
	lw $t0, -56($fp)
	li $t1, 0
	beq $t0, $t1, label9
	j label10
label9 :
	li $t0, 0
	sw $t0, -76($fp)
	j label11
label10 :
	li $t0, 1
	sw $t0, -76($fp)
label11 :
label8 :
label5 :
label2 :
	lw $t0, -76($fp)
	li $t1, 0
	beq $t0, $t1, label12
	j label13
label12 :
	li $a0, 365
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	j label14
label13 :
	li $a0, 366
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
label14 :
	move $sp, $fp
	li $v0, 0
	jr $ra
