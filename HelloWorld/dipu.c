#include<stdio.h>

int v(char *p);

int main(){

char *str = "Gate2015";

if(1){
printf("This will never get printed !");
}

printf("%d",v(str));
return 0;
}

int v(char *p){

char *p2 = p;
while(*++p){
	printf("%d\n",*p);	

}
return (p-p2);

}
