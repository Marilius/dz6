section .data
    const1 dq 0.5
    const2 dq 1.0
    const3 dq 3.0
    const4 dq 2.5
    const5 dq 9.5
    const6 dq 5.0
    
;    fr db "%d", 0; для чтения
;    fout db "%lf", 0;  для вывода
    
;    n dq 0
SECTION .text
;GLOBAL CMAIN
;CMAIN:
;    mov ebp, esp; for correct debugging 
;    push ebp
;    mov ebp, esp
;    
;    finit
;    
;    lea eax, [eax]
;    
;    and esp, ~15
;    sub esp, 16
;    
;    mov dword[esp+4], n
;    mov dword[esp], fout
;    call scanf
;    
;    mov eax, dword[n+4]
;    mov dword[esp], eax
;    call f3
;    
;    fstp qword[n]
;    
;    mov dword[esp], fout
    ;fist dword[esp+4]
;    mov eax, dword[n]
;    mov dword[esp+4], eax 
;    mov eax, dword[n+4]
;    mov dword[esp+8], eax
;    call printf
    
;    leave
;    xor eax, eax
;    ret

; 3 * (0.5 / (x + 1) + 1)
f1:
    push ebp
    mov ebp, esp
    fld qword [const1]
    fld qword [ebp + 8]
    fld qword [const2]
    faddp
    fdivp
    fld qword [const2]
    faddp
    fld qword [const3]
    fmulp
    pop ebp
    ret

; 2.5 * x − 9.5
f2:
    push ebp
    mov ebp, esp
    fld qword [ebp + 8]
    fld qword [const4]
    fmulp
    fld qword [const5]
    fsubp
    pop ebp
    ret

; 5 / x
f3:
    push ebp
    mov ebp, esp
    fld qword [const6]
    fld qword[ebp + 8]
    fdivp
    pop ebp
    ret