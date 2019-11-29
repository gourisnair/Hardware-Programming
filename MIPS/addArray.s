.data
arr: .word 1, 2, 3, 4, 5
msg: .asciiz "Sum of the elements = "

.text
.globl main
main: la $t0, arr
li $t2, 5

loop: lw $t4, 0($t0)
add $t1, $t1, $t4
addi $t0, $t0, 4
addi $t2, $t2, -1
beq $t2, $zero, exit
j loop

exit: li $v0, 4
la $a0, msg
syscall

move $a0, $t1
li $v0, 1
syscall


jr $ra
