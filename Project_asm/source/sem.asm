%include "io64.inc"
%include "create_node.inc"
%include "insert.inc"
%include "macro.inc"
%include "parse.inc"
%include "print_list.inc"
section .data
    BUF_MAX equ 256
    null_ptr equ 0
    null equ 0
    printf1_str db "%s col-vo: %d ", 10, 0
section .bss
    struc node
        next resq 1
        prev resq 1
        word_ptr resq 1
        repeat_count resq 1
    endstruc
section .text
%macro ALIGN_STACK 0
    enter 0, 0
    and rsp, -16
%endmacro

%macro UNALIGN_STACK 0
    leave
%endmacro

extern malloc
extern strcpy
extern strlen
extern strcmp
extern printf
global main  

main:
    enter 16, 0
    ALIGN_STACK
    call parse
    UNALIGN_STACK
    mov [rbp - 8], rax;  node** heads
    mov qword[rbp - 16], 1; i
.for:
    mov rcx, [rbp - 16]
    cmp rcx, 9
    jge .end_for
    mov rdi, [rbp - 8]; heads
    mov rdi, [rdi + 8 * rcx]; heads[i]
    call print_list
    inc qword[rbp - 16]
    jmp .for
.end_for:
    leave
    ret