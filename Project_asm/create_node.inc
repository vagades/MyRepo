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
create_node: ;node* create_node(char* word, node* prev, node* next)
    enter 24, 0
    mov [rbp - 8], rdi; word
    mov [rbp - 16], rsi; prev
    mov [rbp - 24], rdx; next

    mov rdi, node_size
    ALIGN_STACK
    call malloc
    UNALIGN_STACK
    mov rdi, [rbp - 8]
    mov qword[rax + word_ptr], rdi
    mov rsi, [rbp - 16]
    mov [rax + prev], rsi
    mov rdx, [rbp - 24]
    mov [rax + next], rdx
    mov qword[rax + repeat_count], 1

    leave
    ret
