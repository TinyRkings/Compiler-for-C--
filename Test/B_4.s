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
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	li $t0, 0
	addi $sp, $sp, -4
	sw $t0, -52($fp)
label0 :
	lw $t0, -52($fp)
	li $t1, 10
	blt $t0, $t1, label1
	j label2
label1 :
	li $t0, 10
	lw $t1, -52($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -56($fp)
	lw $t0, -56($fp)
	li $t1, 2
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -60($fp)
	lw $t0, -52($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -64($fp)
	li $t0, 12
	lw $t1, -64($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -68($fp)
	lw $t0, -60($fp)
	lw $t1, -68($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	lw $t0, -52($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -72($fp)
	lw $t0, -72($fp)
	sw $t0, -52($fp)
	j label0
label2 :
	li $t0, 12
	li $t1, 8
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -76($fp)
	li $t0, 5
	lw $t1, -76($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 12
	li $t1, 28
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -80($fp)
	li $t0, 16
	lw $t1, -80($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 12
	li $t1, 36
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -84($fp)
	li $t0, 15
	lw $t1, -84($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 1
	addi $sp, $sp, -4
	sw $t0, -88($fp)
label3 :
	lw $t0, -88($fp)
	li $t1, 10
	blt $t0, $t1, label4
	j label5
label4 :
	lw $t0, -88($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -92($fp)
	li $t0, 12
	lw $t1, -92($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -96($fp)
	lw $t0, -96($fp)
	add $t0, $t0, $fp
	lw $t0, ($t0)
	addi $sp, $sp, -4
	sw $t0, -100($fp)
	lw $t0, -88($fp)
	li $t1, 1
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -104($fp)
	lw $t0, -104($fp)
	addi $sp, $sp, -4
	sw $t0, -108($fp)
label6 :
	li $t0, 0
	addi $sp, $sp, -4
	sw $t0, -112($fp)
	lw $t0, -108($fp)
	li $t1, 0
	bge $t0, $t1, label10
	j label11
label10 :
	li $t0, 1
	sw $t0, -112($fp)
label11 :
	lw $t0, -112($fp)
	li $t1, 0
	bne $t0, $t1, label9
	j label8
label9 :
	li $t0, 0
	addi $sp, $sp, -4
	sw $t0, -116($fp)
	lw $t0, -108($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -120($fp)
	li $t0, 12
	lw $t1, -120($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -124($fp)
	lw $t5, -124($fp)
	add $t5, $t5, $fp
	lw $t0, ($t5)
	lw $t1, -100($fp)
	bgt $t0, $t1, label12
	j label13
label12 :
	li $t0, 1
	sw $t0, -116($fp)
label13 :
	lw $t0, -116($fp)
	li $t1, 0
	bne $t0, $t1, label7
	j label8
label7 :
	lw $t0, -108($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -128($fp)
	li $t0, 12
	lw $t1, -128($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -132($fp)
	lw $t0, -108($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -136($fp)
	lw $t0, -136($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -140($fp)
	li $t0, 12
	lw $t1, -140($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -144($fp)
	lw $t0, -132($fp)
	add $t0, $t0, $fp
	lw $t0, ($t0)
	lw $t1, -144($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	lw $t0, -108($fp)
	li $t1, 1
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -148($fp)
	lw $t0, -148($fp)
	sw $t0, -108($fp)
	j label6
label8 :
	lw $t0, -88($fp)
	li $t1, 1
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -152($fp)
	lw $t0, -108($fp)
	lw $t1, -152($fp)
	bne $t0, $t1, label14
	j label15
label14 :
	lw $t0, -108($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -156($fp)
	lw $t0, -156($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -160($fp)
	li $t0, 12
	lw $t1, -160($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -164($fp)
	lw $t0, -100($fp)
	lw $t1, -164($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
label15 :
	lw $t0, -88($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -168($fp)
	lw $t0, -168($fp)
	sw $t0, -88($fp)
	j label3
label5 :
	li $t0, 0
	sw $t0, -88($fp)
label16 :
	lw $t0, -88($fp)
	li $t1, 10
	blt $t0, $t1, label17
	j label18
label17 :
	lw $t0, -88($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -172($fp)
	li $t0, 12
	lw $t1, -172($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -176($fp)
	lw $t1, -176($fp)
	add $t1, $t1, $fp
	lw $a0, ($t1)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $t0, -88($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -180($fp)
	lw $t0, -180($fp)
	sw $t0, -88($fp)
	j label16
label18 :
	move $sp, $fp
	li $v0, 0
	jr $ra
