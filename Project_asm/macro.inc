extern printf

%macro PRINTF 1-*

    mov rdi, %1

    %if %0 > 1
        mov rsi, %2
    %endif
    %if %0 > 2
        mov rdx, %3
    %endif
    %if %0 > 3
        mov rcx, %4
    %endif
    %if %0 > 4
        mov r8, %5
    %endif
    %if %0 > 5
        mov r9, %6
    %endif 
 
    ALIGN_STACK
    call printf
    UNALIGN_STACK
%endmacro

%macro SAVE 0
    push rdi
    push rsi
    push rdx
    push rcx
    push r8
    push r9
%endmacro

%macro RESTORE 0
    pop r9
    pop r8
    pop rcx
    pop rdx
    pop rsi
    pop rdi
%endmacro