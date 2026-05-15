#include <stdio.h>

char *getname() {

	char name[128];
	printf("Input Name : ");
	scanf("%s", name);
	return name;
}


int main(){
	char *str;
	str = getname();
	printf("I like you \n");
	printf("%s\n", str);

	return 0;

}
