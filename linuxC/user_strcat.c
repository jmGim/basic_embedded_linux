#if 1 
#include <stdio.h>
#include <string.h>

char* my_strcat(char* str1, char* str2);
char* user_strcpy (char* str1, const char* str2);

int main() {
	char str1[20] = "straw";
	char str2[20] = "berry";
	char fruit[80] = "straw";

	user_strcpy(fruit, "banana");
	my_strcat(str1, str2);

	return 0;
}

char* my_strcat(char* str1, char* str2) {
	int str1_len = strlen(str1);
	int i = 0;

	//while(str2[i] != '\0'){
	//	str1[str1_len + i] = str2[i];
	//	i++;
	//}

	char* temp = str1;
	while (*(str2+i) != '\0') {
		*(str1+ str1_len + i) = *(str2+i);
		//str1++; str2++;
		i++;
	}

	printf("합쳐진 문자열 : %s \n", str1);
	*(str1 + str1_len + i)= '\0';
	return str1;
}

char* user_strcpy(char* str1, const char* str2) {
	char* temp = str1;
	while (*str2 != '\0') {
		*str1 = *str2;
		str1++; str2++;
	}
	*str1 = '\0';
//	printf("복사한 문자열 : %s\n", temp);
	return temp;
}

#endif
