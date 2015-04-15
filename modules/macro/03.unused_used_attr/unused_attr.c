#include <stdio.h>

/* unused attribute 를 가진 변수는 사용하지 않더라도 경고가 없다 */
/* __used 지시자를붙인 변수는 사용하지 않더라도 컴파일러가 자동으로 삭제하지 않는다 */
/* 보통 같이 사용한다  */

int main()
{
	int __used __attribute__((unused)) nowarning;
	int warning;
	return 0;
}
