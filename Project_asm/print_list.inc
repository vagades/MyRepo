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
print_list: ;void print_list(node* head)
    enter 16, 0
    mov [rbp - 8], rdi; head
    mov [rbp - 16] , rdi; tmp
.while:
    mov rdi, [rbp - 16]
    cmp rdi, null_ptr
    je .end_while
    mov rdx, [rdi + repeat_count]
    lea rdi, [printf1_str]
    mov rsi, [rbp - 16]
    mov rsi, [rsi + word_ptr]
    mov rax, 2
    ALIGN_STACK
    call printf
    UNALIGN_STACK
    mov rdi, [rbp - 16]
    mov rdi, [rdi + next]
    mov [rbp - 16], rdi
    jmp .while
.end_while:
    leave
    ret