.386
.model flat, C

.code

; Forma un n�mero que tenga los 12 bits de m�s peso del par�metro 1 
; seguido de los 20 bits m�s bajos del par�metro 2

IsValidAssembly PROC

; Pr�logo
push ebp
mov ebp, esp

; Salvaguarda de registros
push ebx
push ecx
push edx

; Acceso a par�metros
mov eax, [ebp + 8]
mov ebx, [ebp + 12]
mov ecx, [ebp + 16]

; Cuerpo del procedimiento
mov edx, 0FFF00000h; m�scara del primer par�metro
and eax, edx

not edx; m�scara del segundo par�metro
and ebx, edx

add eax, ebx; se forma el n�mero

mov edx, 00002000h; m�scara del n�mero formado
and eax, edx

mov edx, 00020000h; m�scara del tercer par�metro
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

; Ep�logo
siguiente:

pop edx
pop ecx
pop ebx
pop ebp

ret

IsValidAssembly ENDP

END