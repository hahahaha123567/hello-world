# include <stdio.h>
int main(void)
{
	char str[11];

	for (int i = 0; i < 10; ++i){
		switch (i % 4){
			case 0:
				str[i] = 0xc4;
				break;
			case 1:
				str[i] = 0xdd;
				break;
			case 2:
				str[i] = 0xbf;
				break;
			case 3:
				str[i] = 0xc9;
				break;
		}
	}
	str[10] = '\0';
	printf("%s\n", str);
	
	return 0;
}