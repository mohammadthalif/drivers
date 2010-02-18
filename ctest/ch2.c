#include <stdio.h>

int stlen(const char st[])
{
	int i = 0;
	do {
		printf("%c\n",*st);
		i++;
	} while(*(st++) != '\0') ;
	return i;
}
int main ( )
{
	enum bool { yes, no};
	printf("%s\n", "welcome\n");
	printf("%d \n",stlen("mohamed"));

	printf("%d , %d\n", yes, no);
	yes = 1;
	return 0;
}
