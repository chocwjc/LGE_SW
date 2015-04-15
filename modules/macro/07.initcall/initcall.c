/* 특정 section 에 위치한 함수 포인터 */
/* 자동으로 unique id 를 붙여주기 위해 __LINE__ 또는 __COUNTER__ 사용 */
#include  <stdio.h>

typedef void (*func_ptr)(void);

/* 언제 macro 단계를 증가시켜야 하는가? 
	 # 나 ## 뒤에는 macro 가 들어갈수 없다. 이 경우 단계를 증가시킨다 */

/* original
#define set_func_section(fptr, secname) \
	func_ptr new_function_pointer_ ## __LINE__ used \
	__attribute__((__section__("."secname))) = fptr
	*/

#define __set_func_section(fptr, secname, id) \
	func_ptr new_function_pointer##id __attribute__((__section__("." secname))) = fptr

#define _set_func_section(fptr, secname, id) __set_func_section(fptr, secname, id) 

#define set_func_section(fptr, secname) _set_func_section(fptr, secname, __LINE__)


void hello(void)
{
	printf("Hello?\n");
}

void world(void)
{
	printf("World?\n");
}

set_func_section(hello, "hello_section");
set_func_section(world, "world_section");

/* 호출은 어떻게? 즉, 섹션의 주소를 어떻게 가져 오는가? */

int main()
{
	return 0;
}
