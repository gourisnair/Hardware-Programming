.data
msg: .asciiz "The sum is: "


.text
.globl main
main: li $t1, 2
li $t2, 3
add $t0, $t1, $t2

li $v0, 4
la $a0, msg
syscall

move $a0, $t0

li $v0, 1
syscall

li $v0, 10
syscall