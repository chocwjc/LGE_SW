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
int compare(char *a, int al, char *b, int bl);

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
						printf("%c%s\n", sign == -1 ? '-' : ' ', buf);
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

int compare(char *a, int al, char *b, int bl)
{
				int i, j;

				if (al > bl)
								return 1;
				if (al < bl)
								return -1;
				if (al == bl) {
								for (i = al-1; i >= 0; i--) {
												if (a[i] > b[i])
																return 1;
												if (a[i] < b[i])
																return-1;
								}
								return 0;
				}
				
}

void plus(char *a, int al, char *b, int bl, char *buf)
{
				int carry = 0;
				int l, s, i, j, d, t;
				char temp[4096], op1[4096], op2[4096], *lo, *so;

				memset(temp, 0 ,4096);
				memset(op1, 0 ,4096);
				memset(op2, 0 ,4096);

				strcpy(op1, a);
				strcpy(op2, b);
				reverse(op1);
				reverse(op2);

				if (al > bl) {
								lo = op1;
								l  = al;
								so = op2;
								s  = bl;
				} else {
								lo = op2;
								l  = bl;
								so = op1;
								s  = al;
				}
				d = l - s;

				carry = 0;
				for (i=0; i<s; i++) {
								t = lo[i] - '0' + so[i]  - '0' + carry ;
								if (t > 9) {
												carry = 1;
												t-=10;
								} else
												carry =  0;
								temp[i] = t + '0';
				}
				for (; i<l; i++) {
								t = lo[i] - '0' + carry ;
								if (t > 9) {
												carry = 1;
												t-=10;
								} else
												carry = 0;
								temp[i] = t + '0';
				}
				if (carry)
								temp[i++] = '1';
				temp[i] = 0;

				strcpy(buf, temp);
				reverse(buf);

}

void minus(char *a, int al, char *b, int bl, char *buf, int *sign)
{
				int borrow = 0;
				int i, j, d, t;
				char op1[4096], op2[4096];
				char temp[4096];

				if (compare(a, al, b, bl) < 0) {
								*sign = -1;
								minus(b, bl, a, al, buf, sign);
								return;
				}
				if (compare(a, al, b, bl) == 0) {

								*sign = 0;
								buf[0] = '0';
								buf[1] = 0;
								return;
				}

				// base setup
				memset(op1, 0 ,4096);
				memset(op2, 0 ,4096);
				memset(temp, 0 ,4096);

				strcpy(op1, a);
				strcpy(op2, b);
				reverse(op1);
				reverse(op2);

				d = al - bl;


				borrow = 0;
				for  (i=0; i<=bl-1; i++) {

								t = op1[i] - op2[i] - borrow;

								if (t < 0) {
												borrow = 1;
												t += 10;
								} else
												borrow = 0;

								temp[i] = t + '0';;

				}

				for (; i<al; i++) {
								t = op1[i] - borrow - '0';

								if (t < 0) {
												borrow = 1;
												t += 10;
								} else
												borrow = 0;

								temp[i] = t + '0';
				}

				temp[i] = 0;

				// trim zero
				for (i=i-1; i>=0; i--) {
								if (temp[i] == '0')
												temp[i] = 0;
								else
												break;
				}

				strcpy(buf, temp);
				reverse(buf);

				if (*sign != -1)
								*sign = 1;
}

void multiple(char *a, int al,  char *b, int bl, char *buf)
{

	int i, j, k, d, t, carry;
	char temp1[4096], temp2[4096], temp3[4096];;

	memset(temp1, 0, 4096);
	memset(temp2, 0, 4096);
	memset(temp3, 0, 4096);
	strcpy(temp1, a);
	strcpy(temp2, b);
	reverse(temp1);
	reverse(temp2);

	buf[0] = '0';
	buf[1] = 0;

	carry = 0;
	for (i = 0; i < bl; i++) {
		
		for (j = 0; j < i; j++) {
			temp3[j] = '0';
		}
		temp3[j] = 0;

		carry = 0;
		for (j = 0; j < al; j++) {
			t = (temp2[i]-'0') * (temp1[j]-'0') + carry;

			if (t > 9) {
				carry = t / 10;
				t = t % 10;
			} else {
				carry = 0;
			}
			temp3[i+j] = t + '0';

		}
		if (carry) {
			temp3[i+j] = carry  + '0';
		}
		temp3[i+j+1] = 0;
		reverse(temp3);

		plus(temp3, strlen(temp3), buf, strlen(buf), buf);
	}
}

void division(char *a, int al, char *b, int bl, char *buf)
{
	int i, j, k, d, t, zerofound;
	char ca[4096], ta[4096], mb[4096], pt[4096], one[2], tm[4096], cb[4096];

	memset(ca, 0, 4096);
	memset(ta, 0, 4096);
	memset(mb, 0, 4096);
	strcpy(ca, a);

	buf[0] = '0';
	buf[1] = 0;
	one[0] = '1';
	one[1] = 0;

	d = al - bl;

	for (i = d; i>=0; i--) {

		// make power of ten
		pt[0] = '1';
		for (j = 1; j <= i; j++) {
			pt[j] = '0';
		}
		pt[j] = 0;

		// multiple divident * 1000...
		multiple(b, bl, pt, strlen(pt), mb);

		// multiple one * 1000...
		multiple(one, strlen(one), pt, strlen(pt), tm);

		strcpy(ta, ca);

		// try and sub
		zerofound = 0;
		minus(ta, strlen(ta), mb, strlen(mb), ta, &zerofound);
		while (zerofound != -1) {
			minus(ca, strlen(ca), mb, strlen(mb), ca, &zerofound);
			strcpy(cb, buf);
			plus(cb, strlen(cb), tm, strlen(tm), buf);
			minus(ta, strlen(ta), mb, strlen(mb), ta, &zerofound);
		}
	}
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
