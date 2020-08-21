.entry x
.extern p
sub r1, p
jmp &next
list: cmp r1, r2
.string "abc"
x: .data 3,5,-9
main: add #4, r5
next: mov x,r1 
A: jsr x
jmp &list
