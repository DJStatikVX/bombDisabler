.386
.model flat, C

.code

; Forma un número que tenga los 12 bits de más peso del parámetro 1 
; seguido de los 20 bits más bajos del parámetro 2

IsValidAssembly PROC

; Prólogo
push ebp
mov ebp, esp

; Salvaguarda de registros
push ebx
push ecx
push edx

; Acceso a parámetros
mov eax, [ebp + 8]
mov ebx, [ebp + 12]
mov ecx, [ebp + 16]

; Cuerpo del procedimiento
mov edx, 0FFF00000h; máscara del primer parámetro
and eax, edx

not edx; máscara del segundo parámetro
and ebx, edx

add eax, ebx; se forma el número

mov edx, 00002000h; máscara del número formado
and eax, edx

mov edx, 00020000h; máscara del tercer parámetro
and ecx, edx

; Desplazamientos
shr eax, 13
shr ecx, 17

cmp eax, ecx; se comparan
je consecuente
xor eax, eax; si no son iguales, eax vale 0
jmp siguiente

consecuente:
mov eax, 1; si se cumple que son iguales, eax vale 1

; Epílogo
siguiente:

pop edx
pop ecx
pop ebx
pop ebp

ret

IsValidAssembly ENDP

END