#include<stdio.h>

int b=0,c =0;

static int a = 3;

void fun();
void pintu();


int main(){

static int a = 1;
fun();
a += 1;
fun();
printf("\n %d %d ",a,b);


pintu();

}


void fun()
{
static int a = 2;
int b = 1;
a += ++b;

printf("\n %d %d ",a,b);

}

void pintu(){
printf(" \n %d",a);
}
