STR: .string "abcd"
.string "asd   df" 
.string "abc ,, abs"
.string "abc , d, "
.string "fff" fff
.string "fff"ff"
.string ggg"
.string "ggg
;file.as

    .entry LIST
    .extern fn1
MAIN: add r3, LIST
jsr fn1
LOOP: prn #48
lea STR, r6
inc r6
mov r6, L3
sub r1, r4
cmp r3, #-6
bne END
add r7, r6
clr K
sub L3, L3
    .entry MAIN
    .extern fn1
jmp LOOP
END: stop
STR: .string "abcd"
LIST: .data 6, -9
    .data -100
K: .data 31
    .extern L3
