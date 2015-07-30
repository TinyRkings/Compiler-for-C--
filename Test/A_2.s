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
	sw $v0, -24($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	addi $sp, $sp, -4
	sw $t0, -32($fp)
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
	sw $v0, -36($fp)
	addi $sp, $sp, -4
	move $t0, $v0
	addi $sp, $sp, -4
	sw $t0, -44($fp)
	lw $t0, -20($fp)
	lw $t1, -32($fp)
	bgt $t0, $t1, label0
	j label1
label0 :
	lw $t0, -20($fp)
	lw $t1, -32($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -48($fp)
	lw $t0, -48($fp)
	sw $t0, -20($fp)
	lw $t0, -20($fp)
	lw $t1, -32($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -52($fp)
	lw $t0, -52($fp)
	sw $t0, -32($fp)
	lw $t0, -20($fp)
	lw $t1, -32($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -56($fp)
	lw $t0, -56($fp)
	sw $t0, -20($fp)
label1 :
	lw $t0, -44($fp)
	lw $t1, -20($fp)
	blt $t0, $t1, label2
	j label3
label2 :
	lw $t0, -32($fp)
	addi $sp, $sp, -4
	sw $t0, -60($fp)
	lw $t0, -20($fp)
	sw $t0, -32($fp)
	lw $t0, -44($fp)
	sw $t0, -20($fp)
	lw $t0, -60($fp)
	sw $t0, -44($fp)
	j label4
label3 :
	lw $t0, -44($fp)
	lw $t1, -32($fp)
	blt $t0, $t1, label5
	j label6
label5 :
	lw $t0, -32($fp)
	lw $t1, -44($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -64($fp)
	lw $t0, -64($fp)
	sw $t0, -32($fp)
	lw $t0, -32($fp)
	lw $t1, -44($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -68($fp)
	lw $t0, -68($fp)
	sw $t0, -44($fp)
	lw $t0, -32($fp)
	lw $t1, -44($fp)
	sub $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -72($fp)
	lw $t0, -72($fp)
	sw $t0, -32($fp)
label6 :
label4 :
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
	move $sp, $fp
	li $v0, 0
	jr $ra
