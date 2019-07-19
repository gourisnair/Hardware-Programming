.data
arr:	.word 1, 2, 3, 4, 5, 6, 7, 0
msg:	.asciiz "Length of the array is = "


.text
.globl main
main:	la $a1, arr
		
loop:	lw $a2, 0($a1)
		beq $a2, 0, endloop
		addi $t0, $t0, 1
		addi $a1, $a1, 4
		j loop
		
endloop:li $v0, 4
		la $a0, msg
		syscall
		
		li $v0, 1
		move $a0, $t0
		syscall
		
		li $v0, 10
		syscall
