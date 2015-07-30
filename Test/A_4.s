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
	li $t0, 0
	addi $sp, $sp, -4
	sw $t0, -56($fp)
label0 :
	lw $t0, -52($fp)
	li $t1, 10
	blt $t0, $t1, label1
	j label2
label1 :
	lw $t0, -52($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -60($fp)
	li $t0, 12
	lw $t1, -60($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -64($fp)
	lw $t0, -52($fp)
	lw $t1, -64($fp)
	add $t1, $t1, $fp
	sw $t0, ($t1)
	lw $t0, -52($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -68($fp)
	lw $t0, -68($fp)
	sw $t0, -52($fp)
	j label0
label2 :
	li $t0, 0
	sw $t0, -52($fp)
label3 :
	lw $t0, -52($fp)
	li $t1, 10
	blt $t0, $t1, label4
	j label5
label4 :
	lw $t0, -52($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -72($fp)
	li $t0, 12
	lw $t1, -72($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -76($fp)
	lw $t0, -52($fp)
	li $t1, 4
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -80($fp)
	li $t0, 12
	lw $t1, -80($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -84($fp)
	lw $t0, -76($fp)
	add $t0, $t0, $fp
	lw $t0, ($t0)
	lw $t1, -84($fp)
	add $t1, $t1, $fp
	lw $t1, ($t1)
	mul $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -88($fp)
	lw $t0, -56($fp)
	lw $t1, -88($fp)
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -92($fp)
	lw $t0, -92($fp)
	sw $t0, -56($fp)
	lw $t0, -52($fp)
	li $t1, 1
	add $t2, $t0, $t1
	addi $sp, $sp, -4
	sw $t2, -96($fp)
	lw $t0, -96($fp)
	sw $t0, -52($fp)
	j label3
label5 :
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
