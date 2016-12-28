# include <stdio.h>

__declspec(naked) char niconiconi(int index)
{
	__asm{
		push ebp
		mov ebp, esp

		mov eax, [ebp + 8]
		and eax, 3
		cmp eax, 0
		je n
		cmp eax, 1
		je i
		cmp eax, 2
		je c
		cmp eax, 3
		je o
		jmp done

		n:
		mov eax, 'n'
		jmp done

		i:
		mov eax, 'i'
		jmp done

		c:
		mov eax, 'c'
		jmp done

		o:
		mov eax, 'o'
		jmp done

		done:
		mov esp, ebp
		pop ebp
		ret
	}
}

__declspec(naked) char NICONICONI(int index)
{
	__asm{
		push ebp
		mov ebp, esp

		mov eax, [ebp + 8]
		and eax, 3
		cmp eax, 0
		je n
		cmp eax, 1
		je i
		cmp eax, 2
		je k
		cmp eax, 3
		je e

		n:
		mov eax, 0xc4
		jmp done

		i:
		mov eax, 0xdd
		jmp done

		k:
		mov eax, 0xbf
		jmp done

		e:
		mov eax, 0xc9
		jmp done

		done:
		mov esp, ebp
		pop ebp
		ret
	}
}

int main(void)
{
	char s[11];

	for(int i = 0; i < 10; i++)
		s[i] = niconiconi(i);
	s[10] = '\0';
	printf("%s\n", s);

	for(int i = 0; i < 10; i++)
		s[i] = NICONICONI(i);
	s[10] = '\0';
	printf("%s\n", s);

	return 0;
}