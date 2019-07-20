.data
char: 	.byte 'b'
vowels: .asciiz "asdfcvbnmk"
msg1:	.asciiz "Character found"
msg2:	.asciiz "Charcter not found"

.text 
.globl main 
main:	la $a1, vowels
		lb $t0, char

loop:	lb $a2, 0($a1)
		seq $t1, $a2, $t0
		beq $t1, 1, endloop
		addi $a1, $a1, 1
		beq $a2, 0, exit
		j loop
		
endloop:li $v0, 4
		la $a0, msg1
		syscall
		
		li $v0, 10
		syscall


exit:	li $v0, 4
		la $a0, msg2
		syscall

		li $v0, 10
		syscall
