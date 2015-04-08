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
		int len;

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
						plus(buf);
		} else if (operation == '-') {
						printf("operation is MINUS\n");
						minus(buf);
		} else if (operation == '*') {
						printf("operation is MULTIPLE\n");
						multiple(buf);
		} else if (operation == '/') {
						printf("operation is DIVISION\n");
						division(buf);
		}


		// Parsing operand
		//parsing_ops(buf);



				
		return 0;
}

void plus(char *buf)
{
				int carry = 0;
				int l, s, i, j, d;
				char temp[4096], *lo, *so;

				memset(temp, 0 ,4096);

				if (op1.mag_len > op2.mag_len) {
								lo = op1.mag;
								l  = op1.mag_len;
								so = op2.mag;
								s  = op2.mag_len;
				} else {
								lo = op2.mag;
								l  = op2.mag_len;
								so = op1.mag;
								s  = op2.mag_len;
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
				
				while (j >= 0) printf("%c", temp[j--]);
				printf("\n");

				if (buf) {
					strcpy(buf, temp);
					reverse(buf);
				}

}

void minus(char *buf)
{
				int borrow = 0;
				int l, s, i, j, d;
				char temp[4096];

				memset(temp, 0 ,4096);

				d = op1.mag_len - op2.mag_len;

				if (d > 0) {
								// A > B
								l = op1.mag_len;
								s = op2.mag_len;

								for (i = l, j = 0; i > d; i--, j++) {
												int t;

												if (op1.mag[i-1] < op2.mag[i-d-1]){
																borrow = 10;
																op1.mag[i-2]--;
												}
												t = op1.mag[i-1]  -  op2.mag[i-d-1]  + borrow;
												temp[j] = t % 10 + '0'; 
								}
								for (i = d; i > 0; i--, j++) {
												int t;
												if (op1.mag[i-1] < '0'){
																borrow = 10;
																op1.mag[i-2]--;
												}
												t = op1.mag[i - 1] - '0' + borrow;
												temp[j] = t % 10 + '0';
								}
								temp[j] = 0;
								while (j >= 0) printf("%c", temp[j--]);
								printf("\n");

								if (buf) {
									strcpy(buf, temp);
									reverse(buf);
								}

				} else if (d < 0)  {
								// A < B
								l = op2.mag_len;
								s = op1.mag_len;
								d = - d;

								for (i = l, j = 0; i > d; i--, j++) {
												int t;

												if (op2.mag[i-1] < op1.mag[i-d-1]){
																borrow = 10;
																op2.mag[i-2]--;
												}
												t = op2.mag[i-1]  -  op1.mag[i-d-1]  + borrow;
												temp[j] = t % 10 + '0'; 
								}
								for (i = d; i > 0; i--, j++) {
												int t;
												if (op2.mag[i-1] < '0'){
																borrow = 10;
																op2.mag[i-2]--;
												}
												t = op2.mag[i - 1] - '0' + borrow;
												temp[j] = t % 10 + '0';
								}
								temp[j] = 0;
								printf("-");
								while (j >= 0) printf("%c", temp[j--]);
								printf("\n");

								if (buf) {
									strcpy(buf, temp);
									reverse(buf);
								}

				} else {
								// equal !!

								int k =0;
								for (k = op1.mag_len - 1; k >= 0; k--)
								{
												if (op1.mag[k] > op2.mag[k]) {
																l = op1.mag_len;
																int zerocount = 0;

																for (i = l, j = 0; i > 0; i--, j++) {
																				int t;

																				if (op1.mag[i-1] < op2.mag[i-1]){
																								borrow = 10;
																								op1.mag[i-2]--;
																				}
																				t = op1.mag[i-1]  -  op2.mag[i-d-1]  + borrow;
																				temp[j] = t % 10 + '0'; 
																}
																temp[j] = 0;
																while (j >= 0) {
																				if (temp[j] == '0') {
																								zerocount++;
																								continue;
																				}
																				printf("%c", temp[j--]);
																}
																printf("\n");
																if (buf) {
																				strncpy(buf, temp, strlen(temp)-zerocount);
																				reverse(buf);
																}
																break;
												}
												if (op1.mag[k] < op2.mag[k]) {
																l = op1.mag_len;
																int zerocount = 0;

																for (i = l, j = 0; i > 0; i--, j++) {
																				int t;

																				if (op2.mag[i-1] < op1.mag[i-1]){
																								borrow = 10;
																								op2.mag[i-2]--;
																				}
																				t = op2.mag[i-1]  -  op1.mag[i-d-1]  + borrow;
																				temp[j] = t % 10 + '0'; 
																}
																temp[j] = 0;
																printf("-");
																while (j >= 0) {
																				if (temp[j] == '0')
																				{
																								zerocount++;
																								continue;
																				}
																				printf("%c", temp[j--]);
																}
																printf("\n");
																if (buf) {
																				strncpy(buf, temp, strlen(temp)-zerocount);
																				reverse(buf);
																}
																break;
												}
												if (k == 0)
																printf("0\n");
								}
				}
}

void multiple(char *buf)
{
}
void division(char *buf)
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
