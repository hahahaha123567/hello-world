.386
data segment use16
input_temp		db 6, 0, 6 dup(0)
operand1_str	db 6 dup(0), 0Dh, 0Ah, "$"
operand2_str	db 6 dup(0), 0Dh, 0Ah, "$"
operand1_val	dw 0
operand2_val	dw 0
ans_val			dd 0
ans_dec			db 16 dup(' '), 0Dh, 0Ah, "$"
ans_bin			db 32 dup('0'), 'B', 0Dh, 0Ah, "$"
list 			db "0123456789ABCDEF"
data ends

code segment use16
assume cs:code, ds:data

;parameter:	di = store address of string
;return:	ax = length of string		
input:
	push cx
	push dx
	push si
	push di
	mov ah, 0Ah
	mov dx, offset input_temp
	int 21h
	mov ch, 0      
	mov cl, input_temp[1] ; CX=已输入的字符个数
	push cx        
	lea si, input_temp[2] ; mov si, (offset input_temp) + 2
	input_next:
	   cmp cx, 0
	   je input_done
	   mov al, [si]
	   mov [di], al
	   inc si
	   inc di
	   dec cx
	   jmp input_next
	input_done:
	mov byte ptr [di], 0
	pop ax; AX=CX=字符串长度
	pop di
	pop si
	pop dx
	pop cx
	ret

;parameter:	bp = string address
;return：	eax = number address
dec2val:			
	push si
	push ebx
	push edx
	mov eax, 0; 被乘数
	mov si, 0; 数组的下标
	loop_dec2val:
		cmp byte ptr ds:[bp+si], 0; 判断是否到达数组的结束标志
		je done
		mov ebx, 10
		mul ebx; EDX:EAX=乘积, 其中EDX=0
		mov dl, ds:[bp+si]
		sub dl, '0'
		movzx edx, dl
		add eax, edx
		inc si
		jmp loop_dec2val
	done:
	pop edx
	pop ebx
	pop si
	ret

;parameter:	eax = value to convert
val2dec:
	push ebx
	push ecx
	push edx
	push di
	mov cx, 0; 统计push的次数
	loop_val2dec:
		mov edx, 0; 被除数为EDX:EAX
		mov ebx, 10
		div ebx; EAX=商, EDX=余数
		add dl, '0'
		push dx
		inc cx
		cmp eax, 0
		jne loop_val2dec
		mov di, 0
	pop_again:
		pop dx
		mov ans_dec[di], dl
		inc di
		dec cx
		jnz pop_again
	pop di
	pop edx
	pop ecx
	pop ebx
	ret

;parameter: eax = value
print_hex:
	push ebx
	push edx
	push ecx
	mov bx, offset list
	mov ecx, 8
	loop_val2hex:
		rol eax, 4
		push eax
		and eax, 0Fh
		xlat
		mov ah, 2   
		mov dl, al  
		int 21h     
		pop eax
		sub ecx, 1
		jnz loop_val2hex
	mov ah, 2
	mov dl, 'h'
	int 21h
	mov dl, 0Ah
	int 21h
	pop ecx
	pop edx
	pop ebx
	ret

;parameter:	eax = value
val2bin:
	push ebx
	push edx
	push ecx
	mov bx, 0
	mov cx, 32; 循环次数
	mov edx, ans_val
		next:
		mov eax, edx
		rol eax, 1; 
		mov edx, eax; 
		and eax, 1 
		add ans_bin[bx], al
		add bx, 1
		dec cx
		jnz next
	pop ecx
	pop edx
	pop ebx
	ret

main:
	mov ax, data
	mov ds, ax
	;input operand1
	mov di, offset operand1_str
	call input
	push ax 	;store the length of string1
	mov bp, offset operand1_str
	call dec2val
	mov operand1_val, ax
	mov ah, 2
	mov dl, 0Ah
	int 21h
	;input operand2
	mov di, offset operand2_str
	call input
	mov bp, offset operand2_str
	call dec2val
	mov operand2_val, ax
	mov ah, 2
	mov dl, 0Ah
	int 21h
	;print "operand1 * oprand2 =\n"
	pop bx	;bx = length of string1
	mov di, 0
	print1:
		mov ah, 2
		mov dl, operand1_str[di]
		int 21h
		inc di
		dec bx
		jnz print1
	mov ah, 2
	mov dl, '*'
	int 21h
	mov bl, input_temp[1]
	mov di, 0
	print2:
		mov ah, 2
		mov dl, operand2_str[di]
		int 21h
		inc di
		dec bl
		jnz print2
	mov ah, 2
	mov dl, '='
	int 21h
	mov ah, 2
	mov dl, 0Ah
	int 21h
	;calculate
	mov ax, operand1_val
	mov bx, operand2_val
	mul ebx
	mov ans_val, eax
	;print dec
	mov eax, ans_val
	call val2dec
	mov ah, 9
	mov dx, offset ans_dec
	int 21h
	;print hex
	mov eax, ans_val
	call print_hex
	;print bin
	mov eax, ans_val
	call val2bin
	mov ah, 9
	mov dx, offset ans_bin
	int 21h
	;end
	mov ah, 4Ch
	int 21h
code ends
end main
