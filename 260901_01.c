# include <stdio.h>

int main()
{
	char a = 0; // 8bit
	short b = 0; // 16bit
	int c = 0; // 32bit
	float d = 0.0; // 32bit
	double e = 0.0; // 64bit

	a = 7; // 00000111
	b = 12; // 00000000 00001100
	c = 16; // 00000000 00000000 00000000 00010000
	printf("%d \n", !a); // 7이 있으니 참으로 인식 not연산이므로 거짓으로 출력
	printf("%d \n", ~a); // 11111000 MLB가 마이너스 상태

	b = a << 2; // 00000000 000011100
	printf("%d \n", b); 
	
	// 통신ex. x=7 ,y=9, z=2, t=3 한꺼번에 보내기 위해서 bit and, bit or 연산을 사용한다.

	short x = 2, y = 6, z = 5, t = 3; 
	short result = 0;
	// x = 00000000 00000010 (2) -> 00000000 00000010
	// y = 00000000 00000110 (6) -> 00000000 00110000
	// z = 00000000 00000101 (5) -> 00000001 01000000
	// t = 00000000 00000011 (3) -> 00000110 00000000
	//						  bit or_________________ // bit and 연산시 0이 나온다.
	//                    result == 00000111 01110010 (1906)
	//								    tttz zzyyyxxx
	result = x | (y << 3) | (z << 6) | (t << 9); // bit or 연산 
	printf("%d \n", result);

	short x22 = 0, y2 = 0, z2 = 0, t2 = 0;
	short result2 = result;
	x22 = result2 & 0x7; //00000111 01110010	00000000 11101110
	//	15 = 0xF		   00000000 00000111	00000000 00000111
	//		   	  bit and  _________________	_________________
	//					   00000000 00000010	00000000 00000110
	y2 = (result >> 3) & 0x7; // 하위비트 3자리를 날리고 해야지 보낸신호 그대로 6이 나온다 안밀어내면 큰수 나옴
	z2 = (result >> 6) & 0x7; // 6자리 날리고 왜냐하면 전줄에서 3자리 날린거 저장되는게 아님
	t2 = (result >> 9) & 0x7; // 9자리 날리고
	printf("x %d=%d, y %d=%d, z %d=%d, t %d=%d \n", x, x22, y, y2, z, z2, t, t2);
	
	char grade = 0; // 등급저장
	int x1 = 90, x2 = 88, x3 = 76; // 성적저장
	int sum = 0; // 3개 결과값 합산
	float avr = 0.0; // 3개값의 평균값 저장
	
	sum = x1 + x2 + x3; // 합
	avr = sum / 3.0; // 합한거 나누기

	if (avr >= 90)
		grade = 'A'; // 아스키 코드 값이 들어간다 
	else if (avr >= 80)
		grade = 'B';
	else if (avr >= 70)
		grade = 'C';
	else if (avr >= 60)
		grade = 'D';
	else
		grade = 'F';

	printf("sum = %d, avr = %.2f, grade = %c, %d(ask11 cord Desimal) \n", sum, avr, grade, grade);
	// %.2f 소수점 2번째 까지만 출력하라!

	int score[3] = { 90, 88, 76}; // int형 자료형 방을 3개 만들어라
	printf("Where is Address %p %p %p \n", &score[0], &score[1], &score[2]); // 랜덤방 생성 하지만 위치는 쪼르륵

	int newsum = 0;
	for (int i = 0; i <= 2; i++) // i를 2씩증가하고싶으면 i = i+2
	{
		newsum += score[i];
	}
	printf("%d \n", newsum);
	
	int hap = 0;
	for (int a = 1; a <= 100; ++a)
	{
		hap += a;
	}
	printf("1 to 100 hap is %d \n", hap);
	
	int even = 0;
	for (int a = 1; a <= 100; ++a)
	{
		if (a % 2 == 0)
		{
			even += a;
		}
	}
	printf("1 to 100 even number hap is %d \n", even);

	int odd = 0;
	for (int a = 1; a <= 100; ++a)
	{
		if (a % 2 == 1)
		{
			odd += a;
		}
	}
	printf("1 to 100 odd number hap is %d \n\n", odd);

	int c1 = 1;
	while (c1 <= 3)
	{
		for (int d1 = 1; d1 <= c1; d1++)
		{
			printf("*");
		}
		printf("\n");
		c1++;
	}
	int a1 = 4;
	while (a1 >= 1)
	{
		for (int b1 = 1; b1 <= a1; b1++)
		{
			printf("*");
		}
		printf("\n");
		a1--;
	}

	return 0;
}

