/* __attribute__  ((section(".section-name"))) 로 선언된 데이터는 지정한section 으로들어감  */
static const char a[] __attribute__((section(".abcde"))) = "aaaaaaa";
static const char b[] __attribute__((section(".abcde"))) = "bbbbbbb";
static const char c[] __attribute__((section(".abcde"))) = "ccccccc";


int main()
{
	return 0;
}
