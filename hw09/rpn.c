#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define STACK_INIT_SIZE 200
#define STACKINCREMENT 100

typedef double Elemtype;
typedef struct {
	Elemtype *base;
	Elemtype *top;
	int stackSize;
}sqStack;

void InitStack (sqStack *s) {
	s->base =(Elemtype *)malloc (STACK_INIT_SIZE * sizeof(Elemtype));
	s->top =s->base ;
	s->stackSize =STACK_INIT_SIZE;
}

void Push (sqStack *s, Elemtype e) {
	if(s->top -s->base  >=s->stackSize )  {
		s->base = (Elemtype *)realloc (s->base ,(s->stackSize +STACKINCREMENT* sizeof(Elemtype)));
	}
	
	*(s->top )=e;
	s->top ++;
	
}

void Pop(sqStack *s,Elemtype *e) {
	if(s->top ==s->base ) return ;
	*e= *--(s->top );
	
}

int StackLen (sqStack s) {
	return (s.top - s.base );
	
}

int main() {
	sqStack s;
	char c;
	double a,b;
	char str[STACKINCREMENT];
	int i=0;
	
 	InitStack (&s);
	scanf("%c",&c);
	while( ) {
		while(isdigit(c) || c=='.') {
			str[i++]=c;
			str[i]='\0';
			
			scanf("%c",&c);
			if(c==' ') {
				a=atof(str);
				Push(&s,a);
				i=0;
				break;
			}
		} 
		switch (c) {
			case '+':
   				    Pop(&s,&b);
					Pop(&s,&a);
					Push(&s,a+b);
					break;
			case'-':
				    Pop(&s,&b);
				    Pop(&s,&a);
				    Push(&s,a-b);
				    break;
            case'*':
					Pop(&s,&b);
					Pop(&s,&a);
					Push(&s,a*b);
					break;
           	case'/':
					Pop(&s,&b);
					Pop(&s,&a);
					if(b!=0) {
						Push(&s,a/b);
					}
					else {
						printf("You can't divide by 0!\n");
						return -1;
					}
					break;	 
		}
		scanf("%c",&c);
	}

	Pop(&s,&a);
	
	printf("%f\n",a);
}
