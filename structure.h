#include<stdlib.h>
#include <stdio.h>
typedef struct
{
	char uname[20];
	char pwd[10];
        int len;
}LOGIN;
/*typedef struct
{
	char bname[10];
	char aname[10];
	int aval;
	float cost;
	char cat[20];
	int len;
}BOOK;
*/
typedef struct
{
	char color[10];
	char type[20];
        char size[20];
	char material[20];
	float cost;
	int len;
}dress;
typedef struct
{
	char color[20];
	char type[20];
        char make[20];
	float cost;
        int len;
}watch;

typedef struct
{
	char type[20];
	int discount;
	float pr1;
	float pr2;
	int len;
}ofr;


typedef struct
{
	char type[20];
	int discount;
	float pr1;
	float pr2;
	int len;
}ofr1;

typedef struct
{
	int code;
	int code1;
	char type[50];
	char msg[50];
	char msg1[50];
	LOGIN l;
	dress d;
	watch w;
	ofr o;
	ofr1 o1;
	int len;
}APP;


