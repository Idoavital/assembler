
;file.as

    .entry LIST
    .extern fn1
MAIN: add r3, LIST
.string "abc ,, abs"
jsr fn1
LOOP: prn #48
lea STR, r6
inc r6
STR: .string "abcd"
mov r6, L3
sub r1, r4
cmp r3, #-6
.string "asd   df" 
bne END
add r7, r6
sub L3, L3
    .entry MAIN
.string "abc , d, "
    .extern fn1
jmp LOOP
END: stop

LIST: .data 6, -9
    .data -100
K: .data 31
    .extern L3
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
