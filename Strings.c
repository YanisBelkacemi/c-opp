#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
	char* string;
	size_t len;
	size_t capacity;
}String;

String append_string(String a, char* b , int space);

String create_string(char* S){
	String new_s ;
	new_s.len = strlen(S),
	new_s.capacity = strlen(S)+1,

	new_s.string = malloc(new_s.capacity);

	strcpy(new_s.string , S);

	return new_s;
}

String append_string(String a, char* b ,int space){ 
	if (space == 1){
		int newcapacity = a.len + 2;
		a.string = realloc(a.string , newcapacity);
		a.capacity = newcapacity;
	 	strcpy(a.string + a.len ," ");
	 	a.len += 1;
	}


	if ((a.len + strlen(b) + 1 ) > a.capacity){

		int new_capacity = a.len + strlen(b) + 1 ;	
		a.string = realloc(a.string , new_capacity);
		a.capacity = new_capacity;
		printf(" a : %s \n", a.string);
		strcpy(a.string + a.len , b);
		a.len += strlen(b);
		return a;
	}
	strcpy(a.string + a.len , b);
	a.len += strlen(b); 
	return a;
}

void string_free(String s){
	free(s.string);

}

void string_clear(String s){
	s.len = 0;

}

String change_text(String S , char* new_text){
	string_clear(S);
	if (strlen(new_text) + 1 > S.capacity){
		
		size_t new_capacity = strlen(new_text) + 1;
		S.string = realloc(S.string , new_capacity);
		S.capacity = new_capacity ;

		S.string = strcpy(S.string , new_text);
		S.len = strlen(new_text);
		return S;
	}
	strcpy(S.string , new_text);
	S.len = strlen(new_text);
	
	return S;
}
void main(){
	String S = create_string("Hello");
	printf("after appending : %s\n" , append_string(S , "World" ,1 ).string);
	;

	printf("after changing : %s", change_text(S , "This is changed").string);
	string_free(S);
	return ;

}