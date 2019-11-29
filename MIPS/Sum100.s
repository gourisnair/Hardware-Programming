.data
msg: .asciiz "Sum of first 100 natural numbers : "

.text
.globl main
main: li $t0, 100

loop: 
addi $t1, $t1, 1
add $t2, $t2, $t1
addi $t0, $t0, -1
beq $t0, $zero, exit
j loop

exit: li $v0, 4
la $a0, msg
syscall

move $a0, $t2
li $v0, 1
syscall
jr $ra
