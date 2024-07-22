section .data
    BUF_MAX equ 256
    null_ptr equ 0
    null equ 0
section .bss
    struc node
        next resq 1
        prev resq 1
        word_ptr resq 1
        repeat_count resq 1
    endstruc
section .text
parse: ;node** parse()
    enter 56, 0
    mov rdi, BUF_MAX
    ALIGN_STACK
    call malloc
    UNALIGN_STACK
    mov [rbp - 16], rax; char* word
    mov qword[rbp - 24], 0; int i = 0
    mov qword[rbp - 32], null_ptr; head = NULL

    mov rdi, 72
    ALIGN_STACK
    call malloc
    UNALIGN_STACK
    mov [rbp - 40], rax; node** heads
    
.for:
    mov rcx, [rbp - 24]
    cmp rcx, 9
    jge .end_for
    mov rdi, [rbp - 40]
    mov qword[rdi + 8 * rcx], null_ptr
    inc qword[rbp - 24]
    jmp .for
.end_for:
    mov qword[rbp - 24], 0
.while:
    xor rax, rax
    GET_CHAR al
    mov [rbp - 8], al
    cmp byte[rbp - 8], '.'
    je .end_while
    cmp byte[rbp - 8], ','
    je .if
    jmp .else
.if:
    mov rdi, [rbp - 16]; word
    mov rcx, [rbp - 24]; i
    mov byte[rdi + rcx], `\0`
    mov rdi, [rbp - 16]; word
    ALIGN_STACK
    call strlen
    UNALIGN_STACK
    mov rdi, rax
    inc rdi
    ALIGN_STACK
    call malloc
    UNALIGN_STACK

    mov [rbp - 48], rax; char* tmp
    mov rdi, [rbp - 48]; tmp
    mov rsi, [rbp - 16]; word
    ALIGN_STACK
    call strcpy
    UNALIGN_STACK
    mov rdi, [rbp - 16]; word
    ALIGN_STACK
    call strlen
    UNALIGN_STACK
    mov rdi, [rbp - 40]; heads
    lea rdi, [rdi + 8 * rax]
    mov [rbp - 56], rdi
    lea rdi, [rbp - 56]; &heads[strlen(word)]
    mov rsi, [rbp - 48]
    call insert
    mov qword[rbp - 24], 0; i = 0
    jmp .while
.else:
    mov rdi, [rbp - 16]; word
    mov rcx, [rbp - 24]; i
    mov al, byte[rbp - 8]
    mov byte[rdi + rcx], al
    inc qword[rbp - 24]
    jmp .while
.end_while:
    mov rdi, [rbp - 16]; word
    mov rcx, [rbp - 24]; i
    mov byte[rdi + rcx], `\0`
    mov rdi, [rbp - 16]
    ALIGN_STACK
    call strlen
    UNALIGN_STACK
    mov rdi, [rbp - 40]; heads
    lea rdi, [rdi + 8 * rax]
    mov [rbp - 56], rdi
    lea rdi, [rbp - 56]; &heads[strlen(word)]
    mov rsi, [rbp - 16]; word
    call insert
    mov rax, [rbp - 40]
    leave
    ret