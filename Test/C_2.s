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


mod:
	sw $ra, -4($sp)
	sw $sp, -8($sp)
	addi $sp, $sp, -8
	lw $fp, 0($sp)
	addi $sp, $sp, -4
	sw $a0, 0($sp)
	addi $sp, $sp, -4
	sw $a1, 0($sp)
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
	lw $t0, -12($fp)
	lw $t1, -24($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -28($fp)
	move $sp, $fp
	lw $v0, -28($fp)
	jr $ra

printHexDigit:
	sw $ra, -4($sp)
	sw $sp, -8($sp)
	addi $sp, $sp, -8
	lw $fp, 0($sp)
	addi $sp, $sp, -4
	sw $a0, 0($sp)
	lw $t0, -12($fp)
	li $t1, 10
	blt $t0, $t1, label0
	j label1
label0 :
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
	j label2
label1 :
	li $t0, 0
	lw $t1, -12($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -16($fp)
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
label2 :
	move $sp, $fp
	li $v0, 0
	jr $ra

printHex:
	sw $ra, -4($sp)
	sw $sp, -8($sp)
	addi $sp, $sp, -8
	lw $fp, 0($sp)
	addi $sp, $sp, -4
	sw $a0, 0($sp)
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	li $t0, 0
	addi $sp, $sp, -4
	sw $t0, -28($fp)
label3 :
	lw $t0, -28($fp)
	li $t1, 3
	blt $t0, $t1, label4
	j label5
label4 :
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
	lw $a0, -12($fp)
	li $a1, 16
	jal mod
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
	addi $sp, $fp, -28
	lw $ra, -4($fp)
	lw $a0, -12($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	sw $t0, -32($fp)
	lw $t0, -28($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -36($fp)
	li $t0, 16
	lw $t1, -36($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -40($fp)
	lw $t0, -32($fp)
	lw $t1, -40($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	lw $t0, -12($fp)
	li $t1, 16
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -44($fp)
	lw $t0, -44($fp)
	sw $t0, -12($fp)
	lw $t0, -28($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -48($fp)
	lw $t0, -48($fp)
	sw $t0, -28($fp)
	j label3
label5 :
	li $t0, 2
	sw $t0, -28($fp)
label6 :
	lw $t0, -28($fp)
	li $t1, 0
	bge $t0, $t1, label7
	j label8
label7 :
	lw $t0, -28($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -52($fp)
	li $t0, 16
	lw $t1, -52($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -56($fp)
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
	lw $t1, -56($fp)
	add $t1, $t1, $fp
	lw $a0, ($t1)
	jal printHexDigit
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
	addi $sp, $fp, -56
	lw $ra, -4($fp)
	lw $a0, -12($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	sw $t0, -60($fp)
	lw $t0, -28($fp)
	li $t1, 1
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -64($fp)
	lw $t0, -64($fp)
	sw $t0, -28($fp)
	j label6
label8 :
	move $sp, $fp
	li $v0, 0
	jr $ra

perfect_num:
	sw $ra, -4($sp)
	sw $sp, -8($sp)
	addi $sp, $sp, -8
	lw $fp, 0($sp)
	li $t0, 490
	addi $sp, $sp, -4
	sw $t0, -12($fp)
label9 :
	lw $t0, -12($fp)
	li $t1, 500
	blt $t0, $t1, label10
	j label11
label10 :
	li $t0, 0
	addi $sp, $sp, -4
	sw $t0, -16($fp)
	li $t0, 1
	addi $sp, $sp, -4
	sw $t0, -20($fp)
label12 :
	lw $t0, -12($fp)
	li $t1, 2
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -24($fp)
	lw $t0, -20($fp)
	lw $t1, -24($fp)
	ble $t0, $t1, label13
	j label14
label13 :
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
	lw $a0, -12($fp)
	lw $a1, -20($fp)
	jal mod
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
	addi $sp, $fp, -24
	lw $ra, -4($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	sw $t0, -28($fp)
	lw $t0, -28($fp)
	li $t1, 0
	beq $t0, $t1, label15
	j label16
label15 :
	lw $t0, -16($fp)
	lw $t1, -20($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -32($fp)
	lw $t0, -32($fp)
	sw $t0, -16($fp)
label16 :
	lw $t0, -20($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -36($fp)
	lw $t0, -36($fp)
	sw $t0, -20($fp)
	j label12
label14 :
	lw $t0, -16($fp)
	lw $t1, -12($fp)
	beq $t0, $t1, label17
	j label18
label17 :
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
	lw $a0, -12($fp)
	jal printHex
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
	addi $sp, $fp, -36
	lw $ra, -4($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	sw $t0, -40($fp)
label18 :
	lw $t0, -12($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -44($fp)
	lw $t0, -44($fp)
	sw $t0, -12($fp)
	j label9
label11 :
	move $sp, $fp
	li $v0, 0
	jr $ra

main:
	sw $ra, -4($sp)
	sw $sp, -8($sp)
	addi $sp, $sp, -8
	lw $fp, 0($sp)
	jal perfect_num
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $sp, $fp
	li $v0, 0
	jr $ra
