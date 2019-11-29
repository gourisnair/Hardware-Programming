.data
arr: .word 1, 2, 0
msg: .asciiz "Sum = "

.text
.globl main
main: 

la $t0, arr
lw $t1, 0($t0)
lw $t2, 4($t0)
add $t3, $t1, $t2
li $v0, 4
la $a0, msg
syscall
move $a0 $t3
li $v0, 1
syscall
jr $ra