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
insert: ;void insert(node**head, char* word)
    enter 24, 0
    mov [rbp - 8], rdi; node ** head
    mov [rbp - 16], rsi; char* word
    mov rdi, [rdi]
    cmp qword[rdi], null_ptr
    je .rebase_head
    jmp .dont_rebase
.rebase_head:
    mov rdi, [rbp - 16]; word
    mov rsi, null_ptr
    mov rdx, null_ptr
    call create_node
    mov rdi, [rbp - 8]
    mov rdi, [rdi]
    mov [rdi], rax
    jmp .exit
.dont_rebase:
    mov rdi, [rbp - 8]; node** head
    mov rdi, [rdi]; node** head
    mov rdi, [rdi]; node* head
    mov [rbp - 24], rdi; tmp = *head
.while:
    mov rdi, [rbp - 24]
    cmp qword[rdi + next],  null_ptr
    je .end_while
    mov rdi, [rbp - 24]; tmp
    mov rdi, [rdi + word_ptr]; tmp -> word
    mov rsi, [rbp - 16]; word
    ALIGN_STACK
    call strcmp
    UNALIGN_STACK
    cmp eax, 0
    jl .if
    jmp .else
.if:
    mov rdi, [rbp - 24]; tmp
    mov rdi, [rdi + next]; tmp->next
    mov [rbp - 24], rdi
    jmp .while
.else:
    jmp .end_while 
.end_while:
    mov rsi, [rbp - 24]; tmp
    mov rdi, [rsi + word_ptr]
    mov rsi, [rbp - 16]; word
    ALIGN_STACK
    call strcmp
    UNALIGN_STACK
    cmp eax, 0; 
    jg .rebase_head2; tmp->word > word
    je .change_amound; tmp->word == word
    jmp .not_rebase2; tmp->word < word
.rebase_head2:
    mov rsi, [rbp - 24]
    cmp qword[rsi + prev], null_ptr
    je .before_head
    jmp .between
.before_head:
    mov rdi, [rbp - 16]; word
    mov rsi, null_ptr
    mov rdx, [rbp - 24]; tmp
    call create_node
    mov rdi, [rbp - 8]; head
    mov rdi, [rdi]
    mov [rdi], rax
    mov rdi, [rbp - 24]; tmp 
    mov [rdi + prev], rax
    jmp .exit
.between:
    mov rdi, [rbp - 24]; tmp
    mov rsi, [rdi + prev]; tmp -> prev
    mov r9, [rsi + word_ptr]
    mov rdi, [rbp - 16]; word
    mov rdx, [rbp - 24]; tmp
    call create_node
    mov rdi, [rbp - 24]; tmp
    mov rdi, [rdi + prev]
    mov [rdi + next], rax
    mov rdi, [rbp - 24]
    mov [rdi + prev], rax
    jmp .exit
.not_rebase2:
    mov rdi, [rbp - 16]; word
    mov rsi, [rbp - 24]; tmp
    mov rdx, null_ptr
    call create_node
    mov rdi, [rbp - 24]
    mov [rdi + next], rax
    jmp .exit
.change_amound:
    mov rdi, [rbp - 24]; tmp
    inc qword[rdi + repeat_count]
.exit:
    leave
    ret