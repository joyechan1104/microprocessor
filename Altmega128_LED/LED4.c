//반도체전자과 2614110179 조예찬
//실습4 LED비트 0,4만 동시에 1초간격으로 5번 깜빡이고 비트 2,6만 동시에 0.5초 간격으로 5번 깜빡이기 반복


#include <io.h>
#include <delay.h>

int i = 0; // 폴문을 돌릴 변수를 생성하고 초기화 
int variable = 0x11; // variable의 시작은 17 즉 00010001로 설정
int sec = 1000; // 딜레이에 넣을 시간 변수 초기값을 1초로 한다.

void main()
{
    DDRA = 0xFF; // PORTA를 전부 출력단으로 설정
    while(1) // 무한반복
    {   

        for(i = 0; i<5; i++)  // 램프 깜빡임을 5번씩 반복 시킨다
        {
           PORTA = variable; // PORTA에 variable 변수의 숫자를 대입
           delay_ms(sec);    // sec초 변수만큼 대기  
           PORTA = 0x00;     // LED전부 끄기
           delay_ms(sec);    // sec초 변수만큼 대기 5번 반복하면 탈출!
        }
            
        if(variable == 0x11)  // for문을 탈출했을때 variable의 변수가 17이라면
        {
            variable = variable << 2;// variable의 비트를 앞으로 2칸 움직이게한다
            sec = sec/2;             // 딜레이 시간을 0.5초로
        }
        else                  // for문을 탈출했을때 variable의 변수가 17이 아니라면 (68이라면)
        {
            variable = variable >> 2; // variable의 비트를 뒤로 2칸 움직이게해서 원상복귀 시킨다.
            sec = sec*2;              // 딜레이 시간을 1초로
        }
        // 00010001 초기값(우측으로 2번 쉬프트래서 원상복구) 17
        // 01000100 좌측으로 2번 쉬프트 시킨 결과 68
    }
}