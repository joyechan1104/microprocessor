#include<stdio.h>

int main()
{
	/*
	int kor; 
	kor = 90; 
	printf("%d", kor);

	int math = 0;
	math = kor + 50;
	printf("%d", math);

	int a, b, c;									
	float x, y = 3.3, z = -7.7;	
	printf("input to integers: ");
	scanf("%d%d", &b, &c);
	// 변수에 숫자를 대입하기 전까지는 쓰레기값이 들어가 있다.	
	// 변수선언 자료형은 int 10^-32~10^32-1 운영체제가 방사이즈 알아서 32bit로 메모리에 만든다.
	// 실수방이니까 3을 적으면 뒤에 알아서 소수점을 붙인다. 3.0
	// x는 쓰레기값이 들어간다. 선언과 동시에 초기화를 진행 할 수 있다.
	// "" 가 있으면 화면에 모두 인쇄되어 나온다.
	*/

	int a = 0, b = 10, c = 20;
	float x = 1.5, y = 3.3, z = -7.7;

	a = b + c;
	x = y * z;

	printf("%d \n%f \n", a, x); // 실수출력은 %f , \n 줄바꿈 역슬러쉬 엔
	// 주석처리하고 다 바꿨으니 솔루션정리를 한뒤에 빌드를 해주는게 좋다.
	printf("%d = %d  %d \n", a, b, c);
	printf("%.2f = %.2f x %.2f \n", x, y, z); // 소수점 2자리만 출력해라! 
	
	// 도구 옵션 언어 멤버 언어 목록 자동 표시 지우기

	return 0;
}
