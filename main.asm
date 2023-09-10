.intel_mnemonic
.intel_syntax
.text

.globl search
.type search, @function

.global str_cmp
.type str_cmp, @function

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
    je test_success
    ; key not found
    mov %rax, -1
    ret
test_success:
    ; Expects r8 to have the index of the key
    mov %rax, %r8
    ret

str_cmp:
    ; Input Parameters:
        ; rdi -> pointer to s1
        ; rsi -> pointer to s2
        ; rdx -> length to search for

    ; Returns 0 if both strings are equal, 1 else

    ; Setup for cmpsb:
        ; rsi -> s1
        ; rdi -> s2
        ; rcx -> counter
        ; clear direction flag to auto-increment rdi and rsi

    cld
    mov %rcx, %rdx
    repe cmpsb
    ; Check if rcx is 0
    and %rcx, %rcx
    jz equal
    mov %rax, 1
    ret
equal:
    mov %rax, 0
    ret
