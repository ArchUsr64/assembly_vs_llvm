.intel_mnemonic
.intel_syntax
.text
.globl search
.type search, @function
search:
    ; Input Parameters:
        ; rdi -> pointer to search data
        ; rsi -> length of the data
        ; dl -> key

    ; Setup for scasb:
        ; al -> key value
        ; rdi -> buffer pointer
        ; rcx -> counter
        ; clear direction flag to auto-increment rdi
    cld
    mov %al, %dl
    mov %rcx, %rsi
    repne scasb
    ; r8 = (rsi - 1) - rcx
    mov %r8, %rsi
    sub %r8, %rcx
    dec %r8
    ; Success if rcx is not zero
    and %rcx, %rcx
    jnz test_success
    cmp %dl, BYTE PTR [%rdi - 1]
    jpe test_success
    ; key not found
    mov %rax, -1
    ret
test_success:
    ; Expects r8 to have the index of the key
    mov %rax, %r8
    ret

