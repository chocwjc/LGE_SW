#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) > (y) ? (y) : (x))

struct bigint {
				int sign;
				int mag_len;
				char *mag;
};

struct bigint op1, op2;
char operation;


void parsing_ops(char *buf);
void set_operation(char op);
void reverse(char *buf);
void plus();
void minus();
void multiple();
void division();

int main()
{
		char *buf, *buf1, *buf2;
		int len, sign;

		/* Initilize and get buffer string */
		buf = (char*)malloc(4096);
		buf1 = (char*)malloc(4096);
		buf2 = (char*)malloc(4096);
		memset(buf, 0, 4096);
		memset(buf1, 0, 4096);
		memset(buf2, 0, 4096);

		scanf("%s %c %s", buf1, &operation, buf2);
		op1.mag = (char*)malloc(strlen(buf1) + 2);
		op2.mag = (char*)malloc(strlen(buf2) + 2);
		op1.mag_len = strlen(buf1);
		op2.mag_len = strlen(buf2);
		strcpy(op1.mag, buf1);
		strcpy(op2.mag, buf2);
		free(buf1);
		free(buf2);

		printf("operand1: %s\n", op1.mag);
		printf("operand2: %s\n", op2.mag);

		if (operation == '+')  {
						printf("operation is PLUS\n");
						plus(op1.mag, op1.mag_len, op2.mag, op2.mag_len, buf);
						printf("%s\n", buf);
		} else if (operation == '-') {
						printf("operation is MINUS\n");
						minus(op1.mag, op1.mag_len, op2.mag, op2.mag_len, buf,  &sign);
						printf("%c%s\n", sign == 1 ? '-' : ' ', buf);
		} else if (operation == '*') {
						printf("operation is MULTIPLE\n");
						multiple(op1.mag, op1.mag_len, op2.mag, op2.mag_len, buf);
						printf("%s\n", buf);
		} else if (operation == '/') {
						printf("operation is DIVISION\n");
						division(op1.mag, op1.mag_len, op2.mag, op2.mag_len, buf);
						printf("%s\n", buf);
		}

		free(buf);
		free(op1.mag);
		free(op2.mag);

		return 0;
}

void plus(char *a, int al, char *b, int bl, char *buf)
{
				int carry = 0;
				int l, s, i, j, d;
				char temp[4096], *lo, *so;

				memset(temp, 0 ,4096);

				if (op1.mag_len > op2.mag_len) {
								lo = a;
								l  = al;
								so = b;
								s  = bl;
				} else {
								lo = b;
								l  = bl;
								so = a;
								s  = al;
				}
				d = l - s;

				for (i = l, j = 0; i > d; i--, j++) {
								int t;
								t = lo[i-1] - '0'  + so[i - d -1] - '0' + carry;
								temp[j] = t % 10 + '0'; 
								carry = t / 10;
				}

				for (i = d; i > 0; i--, j++) {
								int t;
								t = lo[i - 1] - '0' + carry;
								temp[j] = t % 10 + '0';
								carry = t / 10;
				}
	
				if (carry) temp[j++] = '1';
				temp[j] = 0;
				

				if (buf) {
					strcpy(buf, temp);
					reverse(buf);
				}

}

void minus(char *a, int al, char *b, int bl, char *buf, int *sign)
{
				int borrow = 0;
				int l, s, i, j, d;
				char temp[4096];

				memset(temp, 0 ,4096);

				d = al - bl;

				if (d > 0) {
								// A > B
								int zerocount = 0;
								l = al;
								s = bl;

								for (i = l, j = 0; i > d; i--, j++) {
												int t;

												if (a[i-1] < b[i-d-1]){
																borrow = 10;
																a[i-2]--;
												}
												t = a[i-1]  -  b[i-d-1]  + borrow;
												temp[j] = t % 10 + '0'; 
								}
								for (i = d; i > 0; i--, j++) {
												int t;
												if (a[i-1] < '0'){
																borrow = 10;
																a[i-2]--;
												}
												t = a[i - 1] - '0' + borrow;
												temp[j] = t % 10 + '0';
								}
								temp[j] = 0;
								while (j >= 0) {
												if (temp[j-1] == '0')
																zerocount++;
												else
																break;
												j--;
								}

								if (buf) {
									strncpy(buf, temp, strlen(temp)-zerocount);
									reverse(buf);
									*sign = 0;
								}

				} else if (d < 0)  {
								// A < B
								int zerocount = 0;
								l = bl;
								s = al;
								d = - d;

								for (i = l, j = 0; i > d; i--, j++) {
												int t;

												if (b[i-1] < a[i-d-1]){
																borrow = 10;
																b[i-2]--;
												}
												t = b[i-1]  -  a[i-d-1]  + borrow;
												temp[j] = t % 10 + '0'; 
								}
								for (i = d; i > 0; i--, j++) {
												int t;
												if (b[i-1] < '0'){
																borrow = 10;
																b[i-2]--;
												}
												t = b[i - 1] - '0' + borrow;
												temp[j] = t % 10 + '0';
								}
								temp[j] = 0;

								while (j >= 0) {
												if (temp[j-1] == '0')
																zerocount++;
												else
																break;
												j--;
								}
								if (buf) {
									strncpy(buf, temp, strlen(temp)-zerocount);
									reverse(buf);
									*sign = 1;
								}

				} else {
								// equal !!

								int k =0;
								for (k = al - 1; k >= 0; k--)
								{
												if (a[k] > b[k]) {
																l = al;
																int zerocount = 0;

																for (i = l, j = 0; i > 0; i--, j++) {
																				int t;

																				if (a[i-1] < b[i-1]){
																								borrow = 10;
																								a[i-2]--;
																				}
																				t = a[i-1]  -  b[i-d-1]  + borrow;
																				temp[j] = t % 10 + '0'; 
																}
																temp[j] = 0;
																while (j >= 0) {
																				if (temp[j-1] == '0') 
																								zerocount++;
																				else
																								break;
																				j--;
	//																			printf("%c", temp[j--]);
																}
	//															printf("\n");
																if (buf) {
																				strncpy(buf, temp, strlen(temp)-zerocount);
																				reverse(buf);
																				*sign = 0;
																}
																break;
												}
												if (a[k] < b[k]) {
																l = al;
																int zerocount = 0;

																for (i = l, j = 0; i > 0; i--, j++) {
																				int t;

																				if (b[i-1] < a[i-1]){
																								borrow = 10;
																								b[i-2]--;
																				}
																				t = b[i-1]  -  a[i-d-1]  + borrow;
																				temp[j] = t % 10 + '0'; 
																}
																temp[j] = 0;
//																printf("-");
																while (j >= 0) {
																				if (temp[j-1] == '0')
																								zerocount++;
																				else
																								break;
																				j--;
//																				printf("%c", temp[j--]);
																}
//																printf("\n");
																if (buf) {
																				strncpy(buf, temp, strlen(temp)-zerocount);
																				reverse(buf);
																				*sign = 1;
																}
																break;
												}
												if (k == 0) {
//																printf("0\n");
																if (buf) {
																				buf[0] = '0';
																				buf[1] = 0;
																				*sign = 2; // special case
																}
												}

								}
				}
}

void multiple(char *a, int al,  char *b, int bl, char *buf)
{

	int zerofound = 0, i = 0;;
	char dum[2];
	char tozero1[4096], pad[1000], tozero2[4096];

	dum[0] = '1';
	dum[1] = 0;
	buf[0] = '0';
	buf[1] = 0;

	memset(tozero1, 0, 4096);
	memset(tozero2, 0, 4096);

	minus(b,  bl,  dum,  1, tozero1, &zerofound);
	while (zerofound != 1)
	{
					//plus(a, al, buf, strlen(buf), buf);

					//p
					dum[0] = '1';
					dum[1] = 0;

					if (i%2 == 0) {
									minus(tozero1,  strlen (tozero1),  dum,  1, tozero2, &zerofound);
									printf("%d %s\n", zerofound, tozero2);
					}	else {
									minus(tozero2,  strlen (tozero2),  dum,  1, tozero1, &zerofound);
									printf("%d %s\n", zerofound, tozero1);
					}
					i++;
					usleep(100000);
	}
}
void division(char *a, char *b, char *buf)
{
}
void reverse(char *buf)
{
				char t;
				int i, j;
				for (i = strlen(buf) - 1, j  = 0; i>j; i--, j++) {
								t = buf[i];
								buf[i] = buf[j];
								buf[j] = t;
				}
}


			


# if 0

void parsing_ops(char *buf)
{
	int j = 0, i = 0, delim_off = 0;

	printf("%s\n", buf);

	// skip operand 1
	while (*buf != ' ' && *buf) {
					printf("%c\n", *buf++);
					delim_off++;
					buf++;
	}

	op1.mag = (char*)malloc((delim_off+1) * sizeof (char));
	memset(op1.mag, 0, (delim_off + 1) * sizeof (char));

	// copy operand 1
	while (i < delim_off) {
					op1.mag[i] = buf[i];
					i++;
	}
	printf("operand 1 is %s\n",op1.mag);

	// skip blank
	while (*buf == ' ' && *buf) {
					delim_off++;
					buf++;
	}

	if (*buf == '+') {
					op = PLUS;
					printf("operand is PLUS\n");
	} else if (*buf == '-') {
					op = MINUS;
					printf("operand is MINUS\n");
	} else if (*buf == '*') {
					op = MUL;
					printf("operand is MULTIPLE\n");
	} else if (*buf == '/') {
					op = DIV;
					printf("operand is DIVISION\n");
	} else {
					printf("FATAL: operation error\n");
					exit(1);
	}

	// skip blank
	while (*buf == ' ' && *buf) {
					buf++;
					delim_off++;
	}

	i = delim_off;

	// skip operand 2
	while (*buf != ' ' && *buf) {
					buf++;
					delim_off++;
	}
	
	op2.mag = (char*)malloc((delim_off - i +1) * sizeof (char));
	memset(op1.mag, 0, (delim_off - i + 1) * sizeof (char));

	// copy operand 2
	while (i < delim_off) {
					op2.mag[j++] = buf[i++];
	}
}
				





#endif
