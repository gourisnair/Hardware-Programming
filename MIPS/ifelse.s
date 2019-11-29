.text
.globl main
main: li $t3, 12
li $t4, 0

beq $t3, $zero, y1
beq $t3, $t0, y2
li, $t4, 100
j exit

y1: 
addi $t4, $t4, 1
j exit

y2: j exit

exit: move $a0, $t4
li $v0, 1
syscall
jr $ra
