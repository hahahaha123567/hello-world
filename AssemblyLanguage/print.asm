code segment
assume cs:code
main:
	;set the segment address of graphics card
	mov ax, 0B800h
	mov es, ax
	;clear screen
	mov ax, 0003h
	int 10h
	;initialize the parameters
	mov bp, 0	;bp controls the x position
	mov si, 0	;si controls the y position
	mov al, 0	;the character
loop_row:
loop_column:
	;print the character
	mov byte ptr es:[bp + si], al
	mov byte ptr es:[bp + si + 1], 0Ch
	;print the hex number
	call hex1	;the first hex number is stored in ah
	mov byte ptr es:[bp + si + 2], ah
	mov byte ptr es:[bp + si + 3], 0Ah
	call hex2	;the second hex number is stored in ah
	mov byte ptr es:[bp + si + 4], ah
	mov byte ptr es:[bp + si + 5], 0Ah
	add al, 1
	;judge if the program should end
	cmp al, 00h
	je  done
	;judge if this colume should end
	add si, 160
	cmp si, 4000
	jne loop_column
	;adjust the x position and y position
	add bp, 14
	mov si, 0
	jmp loop_row
done:
	mov ah, 1
	int 21h
	mov ah, 4Ch
	int 21h

hex1:
	mov cl, al
	rol cl, 1
	rol cl, 1
	rol cl, 1
	rol cl, 1
	and cl, 0Fh
	cmp cl, 10
	jb  smaller_than_10_1
	add cl, 'A'
	sub cl, 10
	sub cl, '0'
smaller_than_10_1:
	add cl, '0'
	mov ah, cl
	ret

hex2:
	mov cl, al
	and cl, 0Fh
	cmp cl, 10
	jb  smaller_than_10_2
	add cl, 'A'
	sub cl, 10
	sub cl, '0'
smaller_than_10_2:
	add cl, '0'
	mov ah, cl
	ret
code ends
end main