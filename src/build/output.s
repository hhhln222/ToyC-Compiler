.global main
factorial:
addi sp, sp, -24
sw ra, 20(sp)
sw s0, 16(sp)
addi s0, sp, 24
li a6, 1
slt a5, a6, a7
xori a5, a5, 1
sw a5, 0(sp)
lw a5, 0(sp)
bnez a5, 0
li a6, 1
mv a0, a6
j 1
0:
1:
li a6, 1
sub a7, a5, a6
sw a7, -4(sp)
addi sp, sp, -16
sw a0, 0(sp)
sw a1, 4(sp)
sw a2, 8(sp)
sw a7, 12(sp)
mv a0, a7
call factorial
lw a7, 12(sp)
lw a2, 8(sp)
lw a1, 4(sp)
lw a0, 0(sp)
addi sp, sp, 16
mv a7, a0
sw a7, -8(sp)
lw a5, -8(sp)
.option rvc
.option arch, +m
mul a4, a7, a5
.option rvc
.option arch, -m
sw a4, -12(sp)
lw a4, -12(sp)
mv a0, a4
lw s0, 16(sp)
lw ra, 20(sp)
addi sp, sp, 24
ret
main:
addi sp, sp, -20
sw ra, 16(sp)
sw s0, 12(sp)
addi s0, sp, 20
li a4, 5
mv a5, a4
addi sp, sp, -16
sw a0, 0(sp)
sw a1, 4(sp)
sw a2, 8(sp)
sw a7, 12(sp)
mv a0, a5
call factorial
lw a7, 12(sp)
lw a2, 8(sp)
lw a1, 4(sp)
lw a0, 0(sp)
addi sp, sp, 16
mv a5, a0
sw a5, -16(sp)
lw a5, -16(sp)
mv a7, a5
mv a0, a7
lw s0, 12(sp)
lw ra, 16(sp)
addi sp, sp, 20
ret
