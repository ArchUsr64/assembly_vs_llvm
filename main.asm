.intel_syntax
.text
.globl func
.type func, @function
func:
    xord %eax, %eax
    movw %ax, %si
    mulw %di
    ret

