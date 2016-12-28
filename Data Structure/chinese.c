# include <stdio.h>
int main(void)
{
	char str[11];

	for (int i = 0; i < 10; ++i){
		if(i % 4 == 0)
			str[i] = 0xc4;
		else if(i % 4 == 1)
			str[i] = 0xdd;
		else if(i % 4 == 2)
			str[i] = 0xbf;
		else if(i % 4 == 3)
			str[i] = 0xc9;
	}
	str[10] = '\0';
	printf("%s\n", str);
	
	return 0;
}