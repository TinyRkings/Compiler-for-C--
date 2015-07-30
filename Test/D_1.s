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
	li $t0, 11
	addi $sp, $sp, -4
	sw $t0, -16($fp)
	lw $t0, -12($fp)
	lw $t1, -16($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -20($fp)
	lw $t0, -20($fp)
	addi $sp, $sp, -4
	sw $t0, -24($fp)
	li $t0, 3
	addi $sp, $sp, -4
	sw $t0, -28($fp)
	lw $t0, -28($fp)
	addi $sp, $sp, -4
	sw $t0, -32($fp)
	li $t0, 7
	addi $sp, $sp, -4
	sw $t0, -36($fp)
	li $t0, 30
	addi $sp, $sp, -4
	sw $t0, -40($fp)
	lw $t0, -40($fp)
	li $t1, 3
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -44($fp)
	lw $t0, -36($fp)
	lw $t1, -44($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -48($fp)
	lw $t0, -48($fp)
	li $t1, 4
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -52($fp)
	lw $t0, -52($fp)
	addi $sp, $sp, -4
	sw $t0, -56($fp)
	lw $t0, -24($fp)
	lw $t1, -32($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -60($fp)
	lw $t0, -60($fp)
	lw $t1, -56($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -64($fp)
	lw $t0, -64($fp)
	addi $sp, $sp, -4
	sw $t0, -68($fp)
	lw $t0, -24($fp)
	lw $t1, -32($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -72($fp)
	lw $t0, -56($fp)
	li $t1, 2
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -76($fp)
	lw $t0, -72($fp)
	lw $t1, -76($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -80($fp)
	lw $t0, -80($fp)
	addi $sp, $sp, -4
	sw $t0, -84($fp)
	lw $t0, -24($fp)
	lw $t1, -32($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -88($fp)
	lw $t0, -88($fp)
	lw $t1, -56($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -92($fp)
	lw $t0, -92($fp)
	addi $sp, $sp, -4
	sw $t0, -96($fp)
	li $t0, 42
	addi $sp, $sp, -4
	sw $t0, -100($fp)
	li $t0, 0
	addi $sp, $sp, -4
	sw $t0, -104($fp)
	lw $t0, -24($fp)
	lw $t1, -32($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -108($fp)
	lw $t0, -108($fp)
	lw $t1, -56($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -112($fp)
	lw $t0, -112($fp)
	lw $t1, -68($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -116($fp)
	lw $t0, -116($fp)
	lw $t1, -84($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -120($fp)
	lw $t0, -120($fp)
	lw $t1, -96($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -124($fp)
	lw $t0, -124($fp)
	sw $t0, -96($fp)
label0 :
	lw $t0, -32($fp)
	lw $t1, -24($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -128($fp)
	lw $t0, -128($fp)
	lw $t1, -96($fp)
	blt $t0, $t1, label1
	j label2
label1 :
	lw $t0, -104($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -132($fp)
	lw $t0, -100($fp)
	lw $t1, -132($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -136($fp)
	lw $t0, -136($fp)
	li $t1, 3
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -140($fp)
	lw $t0, -140($fp)
	li $t1, 4
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -144($fp)
	lw $t0, -144($fp)
	li $t1, 5
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -148($fp)
	lw $t0, -148($fp)
	sw $t0, -100($fp)
	lw $t0, -96($fp)
	lw $t1, -32($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -152($fp)
	lw $t0, -24($fp)
	li $t1, 2
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -156($fp)
	lw $t0, -152($fp)
	lw $t1, -156($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -160($fp)
	lw $t0, -56($fp)
	lw $t1, -68($fp)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -164($fp)
	lw $t0, -160($fp)
	lw $t1, -164($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -168($fp)
	lw $t0, -168($fp)
	lw $t1, -96($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -172($fp)
	lw $t0, -172($fp)
	addi $sp, $sp, -4
	sw $t0, -176($fp)
	lw $t0, -104($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -180($fp)
	lw $t0, -180($fp)
	li $t1, 0
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -184($fp)
	lw $t0, -184($fp)
	sw $t0, -104($fp)
	lw $t0, -104($fp)
	li $t1, 3
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -188($fp)
	lw $t0, -188($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -192($fp)
	lw $t0, -192($fp)
	sw $t0, -104($fp)
	lw $t0, -104($fp)
	li $t1, 2
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -196($fp)
	lw $t0, -196($fp)
	li $t1, 2
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -200($fp)
	lw $t0, -200($fp)
	sw $t0, -104($fp)
	lw $t0, -104($fp)
	li $t1, 3
	div $t0, $t1
	mflo $t2
	addi $sp, $sp, -4
	sw $t2, -204($fp)
	lw $t0, -204($fp)
	li $t1, 3
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -208($fp)
	lw $t0, -104($fp)
	lw $t1, -208($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -212($fp)
	lw $t0, -24($fp)
	lw $t1, -24($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -216($fp)
	lw $t0, -216($fp)
	lw $t1, -32($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -220($fp)
	lw $t0, -220($fp)
	lw $t1, -32($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -224($fp)
	lw $t0, -224($fp)
	lw $t1, -56($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -228($fp)
	lw $t0, -228($fp)
	lw $t1, -56($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -232($fp)
	lw $t0, -212($fp)
	lw $t1, -232($fp)
	beq $t0, $t1, label3
	j label4
label3 :
	lw $t0, -96($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -236($fp)
	lw $t0, -236($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -240($fp)
	lw $t0, -240($fp)
	sw $t0, -96($fp)
label4 :
	lw $t0, -96($fp)
	li $t1, 2
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -244($fp)
	lw $t0, -244($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -248($fp)
	lw $t0, -248($fp)
	sw $t0, -96($fp)
	j label0
label2 :
	lw $t0, -100($fp)
	li $t1, 2
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -252($fp)
	lw $t0, -252($fp)
	li $t1, 3
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -256($fp)
	lw $t0, -256($fp)
	addi $sp, $sp, -4
	sw $t0, -260($fp)
	lw $a0, -260($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $t0, -100($fp)
	sw $t0, -104($fp)
label5 :
	li $t0, 1222
	addi $sp, $sp, -4
	sw $t0, -264($fp)
	lw $t0, -100($fp)
	lw $t1, -264($fp)
	bge $t0, $t1, label6
	j label7
label6 :
	lw $t0, -100($fp)
	li $t1, 1024
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -268($fp)
	lw $t0, -268($fp)
	sw $t0, -104($fp)
	lw $t0, -100($fp)
	li $t1, 1
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -272($fp)
	lw $t0, -272($fp)
	sw $t0, -100($fp)
	lw $t0, -100($fp)
	sw $t0, -104($fp)
	j label5
label7 :
	lw $a0, -100($fp)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	addi $sp, $sp, -4
	sw $fp, 0($sp)
	jal write
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $t0, -24($fp)
	lw $t1, -32($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -276($fp)
	lw $t0, -276($fp)
	sw $t0, -24($fp)
	lw $t0, -24($fp)
	lw $t1, -32($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -280($fp)
	lw $t0, -280($fp)
	sw $t0, -32($fp)
	lw $t0, -24($fp)
	lw $t1, -32($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -284($fp)
	lw $t0, -284($fp)
	sw $t0, -56($fp)
	lw $a0, -56($fp)
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
