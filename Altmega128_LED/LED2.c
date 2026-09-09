// 반도체전자과 2614110179 조예찬
// 실습2 LED한개를 1초간격으로 온오프 시키기 

#include <io.h>
#include <delay.h>

void main()
{
    DDRA = 0xFF; // PORTA를 전부 출력단으로 설정
    while(1) // 무한반복
    {   
        PORTA = 0x01;    // 최하위 비트 1개만 켜기
        delay_ms(1000);  // 1초대기
        PORTA = 0x00;    // 모든 LED오프
        delay_ms(1000);  // 1초대기
    }
}
