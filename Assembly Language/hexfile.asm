.386
data segment use16
_offset 	db 4 dup(0)
_offset_temp db 4 dup(0)
i_16	db 0
xx 		db 0
s 		db "00000000:            |           |           |                             "
pattern db "00000000:            |           |           |                             "
t 		db "0123456789ABCDEF"
prompt1 db "Please input filename:", 0Dh, 0Ah, '$'
prompt2 db "Cannot open file!", 0Dh, 0Ah, '$'

filename 	db 100, 0, 100 dup(0)
bytes_in_buf 	db 2 dup(0)
buf 		db 256 dup(0)
handle 		db 2 dup(0)
file_size 	db 4 dup(0)
key 	db 2 dup(0)
buf_offset 	db 0
bytes_on_row 	db 2 dup(0)
s_offset 	db 0

_PageUp 	dw 4900h
_PageDown 	dw 5100h
_Home 		dw 4700h
_End 		dw 4F00h
_Esc 		dw 011Bh
data ends

code segment use16
assume ds:data, cs:code

char2hex:
	push bx
	push di
	push ax
	push ax
	push ax
	mov bx, offset t
	mov al, s_offset
	cbw
	mov di, ax
	pop ax;
	shr al, 4
	and al, 0Fh
	xlat
	mov s[di], al
	pop ax
	and al, 0Fh
	xlat
	mov s[di + 1], al
	pop ax
	pop di
	pop bx
	ret

long2hex:
	push bx
	push cx
	push eax
	and cx, 0
	mov eax, dword ptr _offset
	add eax, i_16
	mov dword ptr _offset_temp, eax
loop_long2hex:
	cmp cx, 4
	je long2hex_done
	mov eax, dword ptr _offset_temp
	rol eax, 8
	mov dword ptr _offset_temp, eax
	and eax, 0FFh ;al = xx
	push ax
	mov al, cl
	shl al, 1
	mov s_offset, al
	pop ax
	inc cx
	call char2hex
	jmp loop_long2hex
long2hex_done:
	pop eax
	pop cx
	pop bx
	ret

show_this_row:
	push ax
	push bx
	push cx
	push dx
	push si
	push di
	push es
;strcpy(s, pattern);
	mov si, offset pattern
	mov ax, data
	mov es, ax
	mov di, offset s
	mov cx, 74
	cld
	rep movsb
;long2hex(offset, s);
	call long2hex
;for(i=0; i<bytes_on_row; i++)
	mov bp, i_16
	mov di, 0
loop1_show_this_row:
	cmp di, word ptr bytes_on_row
	je loop1_show_this_row_done
	;char2hex(buf[i], s+10+i*3);
	mov ax, di
	;and ax, 00FFh
	mov bx, 3
	mul bx
	add al, 10
	mov s_offset, al
	mov al, buf[bp + di]
	call char2hex
	inc di
	jmp loop1_show_this_row
loop1_show_this_row_done:
;for(i=0; i<bytes_on_row; i++)
	mov di, 0
loop2_show_this_row:
	cmp di, word ptr bytes_on_row
	je loop2_show_this_row_done
	;s[59+i] = buf[i];
	mov al, buf[bp + di]
	mov s[di + 59], al
	inc di
	jmp loop2_show_this_row
loop2_show_this_row_done:
;vp = vp + row*80*2;
	mov ax, 0B800h
	mov es, ax
	mov cx, 0
	mov cl, i_16
	mov ax, cx
	mov bl, 10
	mul bl
	mov dx, ax
;for(i=0; i<sizeof(s)-1; i++)
	mov di, 0
	mov bp, di
	add bp, dx
loop3_show_this_row:
	cmp di, 73
	je loop3_show_this_row_done
	mov al, s[di]
	mov es:[bp + di], al
	cmp di, 59
	jae white
	cmp s[di], '|'
	jne white
highlight_white:
	mov es:[bp + di + 1], byte ptr 0Fh
	jmp color_done
white:
	mov es:[bp + di + 1], byte ptr 07h
color_done:
	inc di
	mov bp, di
	add bp, dx
	jmp loop3_show_this_row
loop3_show_this_row_done:
	pop es
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	ret

clear_this_page:
	push ax
	push es
	push di
	push cx
	mov ax, 0B800h
	mov es, ax
	mov di, 0
	mov cx, 1280h
	mov ax, 0020h
	rep stosw
	pop cx
	pop di
	pop es
	pop ax
	ret

show_this_page:
	push ax
	push bx
	push cx
	push dx
	call clear_this_page
;rows = (bytes_in_buf + 15) / 16;
	mov ax, word ptr bytes_in_buf
	add ax, 15	
	shr ax, 4	;al = rows
	mov ah, al
	dec ah 		;ah = rows - 1
	mov cl, 0	;cl = i
loop_show_this_page:
	cmp cl, al
	je show_this_page_done
;bytes_on_row = (i == rows-1) ? (bytes_in_buf - i*16) : 16;
	cmp cl, ah
	jne bytes_on_row_16
		mov bx, word ptr bytes_in_buf
		push cx
		shl cl, 4
		and cx, 00FFh
		sub bx, cx
		pop cx
		jmp bytes_on_row_done
	bytes_on_row_16:
		mov bx, 16
bytes_on_row_done:
	mov word ptr bytes_on_row, bx
;show_this_row(i, offset+i*16, &buf[i*16], bytes_on_row); 
	push cx
	shl cl, 4
	mov i_16, cl
	pop cx
	call show_this_row	;cx = i, bx = bytes_on_row
	inc cx
	jmp loop_show_this_page
show_this_page_done:
	pop dx
	pop cx
	pop bx
	pop ax
	ret

main:
	mov ax, data
	mov ds, ax
;puts("Please input filename:");
	mov ah, 9
	mov dx, offset prompt1
	int 21h
;gets(filename);
	mov ah, 0Ah
	mov dx, offset filename
	int 21h
	lea di, filename
	mov al, [di+1]
	cbw
	add di, 2
	add di, ax
	mov byte ptr [di], 0
;handle = _open(filename, 0);
	mov ah, 3Dh
	mov al, 0
	mov dx, offset filename + 2
	int 21h
	mov word ptr handle, ax
;if(handle == -1)
	jc file_open_error
;file_size = lseek(handle, 0, 2);
	mov ah, 42h
	mov al, 2
	mov bx, word ptr handle
	mov cx, 0
	mov dx, 0;
	int 21h
	mov word ptr file_size[2], dx
	mov word ptr file_size[0], ax
;offset = 0;
	mov dword ptr _offset, 0
;n = file_size - offset;
Show:
	mov eax, dword ptr file_size
	sub eax, dword ptr _offset
	cmp eax, 256
	jb bytes_in_buf_n
	bytes_in_buf_256:
		mov byte ptr bytes_in_buf[0], 0
		mov byte ptr bytes_in_buf[1], 1
	jmp bytes_in_buf_done
	bytes_in_buf_n:
		mov bytes_in_buf[0], al
		mov bytes_in_buf[1], 0
	bytes_in_buf_done:
;lseek(handle, offset, 0);
	mov ah, 42h
	mov al, 0
	mov bx, word ptr handle
	mov cx, word ptr _offset[2]; \cx:dx合一起构成
	mov dx, word ptr _offset[0]; /32位值=offset
	int 21h
;_read(handle, buf, bytes_in_buf);
	mov ah, 3Fh
	mov bx, word ptr handle
	mov cx, word ptr bytes_in_buf
	mov dx, data
	mov ds, dx
	mov dx, offset buf
	int 21h
;show_this_page(buf, offset, bytes_in_buf);
	call show_this_page
;key = bioskey(0);
	mov ah, 0
    int 16h
	cmp ax, _Esc
	je over
	cmp ax, _PageUp
	je PageUp_
	cmp ax, _PageDown
	je PageDown_
	cmp ax, _Home
	je Home_
	cmp ax, _End
	je End_
	jmp Show

PageUp_:
	push eax
	mov eax, dword ptr _offset
	cmp eax, 256
	jb offset_0
	sub eax, 256
	mov dword ptr _offset, eax
	pop eax
	jmp Show
	offset_0:
	mov dword ptr _offset, 0
	pop eax
	jmp Show

PageDown_:
	push eax
	mov eax, dword ptr _offset
	add eax, 256
	cmp eax, dword ptr file_size
	jae PageDown_done
	mov dword ptr _offset, eax
	PageDown_done:
	pop eax
	jmp Show

Home_:
	mov dword ptr _offset, 0
	jmp Show

End_:
	push eax
	mov eax, dword ptr file_size
	and eax, 0FFFFFF00h
	cmp eax, dword ptr file_size
	jne End_done
	sub eax, 256
	End_done:
	mov dword ptr _offset, eax
	pop eax
	jmp Show

;puts("Cannot open file!");
file_open_error:
	mov ah, 9
	mov dx, offset prompt2
	int 21h
	jmp over_
;exit(0);
over:
	call clear_this_page
	mov ah, 3Eh
	mov bx, handle
	int 21h
over_:
	mov ah, 4Ch
	mov al, 0
	int 21h
code ends
end main