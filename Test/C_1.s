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


max:
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
	bgt $t0, $t1, label0
	j label1
label0 :
	move $sp, $fp
	lw $v0, -12($fp)
	jr $ra
label1 :
	move $sp, $fp
	lw $v0, -16($fp)
	jr $ra

min:
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
	blt $t0, $t1, label2
	j label3
label2 :
	move $sp, $fp
	lw $v0, -12($fp)
	jr $ra
label3 :
	move $sp, $fp
	lw $v0, -16($fp)
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
	li $t0, 12
	li $t1, 0
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -52($fp)
	li $t0, 2
	lw $t1, -52($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 0
	addi $t1, $t0, -1
	addi $sp, $sp, -4
	sw $t1, -56($fp)
	li $t0, 12
	li $t1, 4
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -60($fp)
	lw $t0, -56($fp)
	lw $t1, -60($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 12
	li $t1, 8
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -64($fp)
	li $t0, 1
	lw $t1, -64($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 12
	li $t1, 12
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -68($fp)
	li $t0, 0
	lw $t1, -68($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 12
	li $t1, 16
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -72($fp)
	li $t0, 2
	lw $t1, -72($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 0
	addi $t1, $t0, -10
	addi $sp, $sp, -4
	sw $t1, -76($fp)
	li $t0, 12
	li $t1, 20
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -80($fp)
	lw $t0, -76($fp)
	lw $t1, -80($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 12
	li $t1, 24
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -84($fp)
	li $t0, 4
	lw $t1, -84($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 0
	addi $t1, $t0, -2
	addi $sp, $sp, -4
	sw $t1, -88($fp)
	li $t0, 12
	li $t1, 28
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -92($fp)
	lw $t0, -88($fp)
	lw $t1, -92($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 0
	addi $t1, $t0, -1
	addi $sp, $sp, -4
	sw $t1, -96($fp)
	li $t0, 12
	li $t1, 32
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -100($fp)
	lw $t0, -96($fp)
	lw $t1, -100($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 12
	li $t1, 36
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -104($fp)
	li $t0, 4
	lw $t1, -104($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	li $t0, 12
	li $t1, 0
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -108($fp)
	lw $t0, -108($fp)
	add $t0, $t0, $fp
	lw $t0, ($t0)
	addi $sp, $sp, -4
	sw $t0, -112($fp)
	li $t0, 12
	li $t1, 0
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -116($fp)
	lw $t0, -116($fp)
	add $t0, $t0, $fp
	lw $t0, ($t0)
	addi $sp, $sp, -4
	sw $t0, -120($fp)
	li $t0, 12
	li $t1, 0
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -124($fp)
	lw $t0, -124($fp)
	add $t0, $t0, $fp
	lw $t0, ($t0)
	addi $sp, $sp, -4
	sw $t0, -128($fp)
	li $t0, 1
	addi $sp, $sp, -4
	sw $t0, -132($fp)
label4 :
	lw $t0, -132($fp)
	li $t1, 10
	blt $t0, $t1, label5
	j label6
label5 :
	lw $t0, -120($fp)
	addi $sp, $sp, -4
	sw $t0, -136($fp)
	lw $t0, -132($fp)
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
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -148($fp)
	li $t0, 12
	lw $t1, -148($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -152($fp)
	lw $t0, -152($fp)
	add $t0, $t0, $fp
	lw $t0, ($t0)
	lw $t1, -120($fp)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -156($fp)
	lw $t0, -132($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -160($fp)
	li $t0, 12
	lw $t1, -160($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -164($fp)
	lw $t0, -164($fp)
	add $t0, $t0, $fp
	lw $t0, ($t0)
	lw $t1, -128($fp)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -168($fp)
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
	lw $a0, -156($fp)
	lw $a1, -168($fp)
	jal max
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
	addi $sp, $fp, -168
	lw $ra, -4($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	sw $t0, -172($fp)
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
	lw $t1, -144($fp)
	add $t1, $t1, $fp
	lw $a0, ($t1)
	lw $a1, -172($fp)
	jal max
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
	addi $sp, $fp, -172
	lw $ra, -4($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	sw $t0, -176($fp)
	lw $t0, -176($fp)
	sw $t0, -120($fp)
	lw $t0, -132($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -180($fp)
	li $t0, 12
	lw $t1, -180($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -184($fp)
	lw $t0, -132($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -188($fp)
	li $t0, 12
	lw $t1, -188($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -192($fp)
	lw $t0, -192($fp)
	add $t0, $t0, $fp
	lw $t0, ($t0)
	lw $t1, -136($fp)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -196($fp)
	lw $t0, -132($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -200($fp)
	li $t0, 12
	lw $t1, -200($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -204($fp)
	lw $t0, -204($fp)
	add $t0, $t0, $fp
	lw $t0, ($t0)
	lw $t1, -128($fp)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -208($fp)
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
	lw $a0, -196($fp)
	lw $a1, -208($fp)
	jal min
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
	addi $sp, $fp, -208
	lw $ra, -4($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	sw $t0, -212($fp)
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
	lw $t1, -184($fp)
	add $t1, $t1, $fp
	lw $a0, ($t1)
	lw $a1, -212($fp)
	jal min
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
	addi $sp, $fp, -212
	lw $ra, -4($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	sw $t0, -216($fp)
	lw $t0, -216($fp)
	sw $t0, -128($fp)
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
	lw $a0, -112($fp)
	lw $a1, -120($fp)
	jal max
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
	addi $sp, $fp, -216
	lw $ra, -4($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	sw $t0, -220($fp)
	lw $t0, -220($fp)
	sw $t0, -112($fp)
	lw $t0, -132($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -224($fp)
	lw $t0, -224($fp)
	sw $t0, -132($fp)
	j label4
label6 :
	lw $a0, -112($fp)
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
