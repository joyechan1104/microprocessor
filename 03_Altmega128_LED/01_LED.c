//반도체전자과 2614110179 조예찬 
//실습1-1 0.3초마다 전체 온오프

#include <io.h>
#include <delay.h>

void main()
{
    DDRA = 0xFF; // PORTA를 전부 출력단으로 설정
    while(1) // 무한반복
    {   
        PORTA = 0xFF;    // LED를 전부 high로
        delay_ms(300);   // 0.3초 대기
        PORTA = 0x00;    // LED를 전부 Low로
        delay_ms(300);   // 0.3초 대기
    }
}

//실습1-2 0.5초마다 전체 온오프

#include <io.h>
#include <delay.h>

void main()
{
    DDRA = 0xFF; // PORTA를 전부 출력단으로 설정
    while(1) // 무한반복
    {   
        PORTA = 0xFF;    // LED를 전부 high로
        delay_ms(500);   // 0.5초 대기
        PORTA = 0x00;    // LED를 전부 Low로
        delay_ms(500);   // 0.5초 대기
     }
}

//실습1-3 2초마다 전체 온오프

#include <io.h>
#include <delay.h>

void main()
{
    DDRA = 0xFF; // PORTA를 전부 출력단으로 설정
    while(1) // 무한반복
    {   
        PORTA = 0xFF;    // LED를 전부 high로
        delay_ms(2000);  // 2초 대기
        PORTA = 0x00;    // LED를 전부 Low로
        delay_ms(2000);  // 2초 대기
    }
}

//실습1-4 5초마다 전체 온오프

#include <io.h>
#include <delay.h>

void main()
{
    DDRA = 0xFF; // PORTA를 전부 출력단으로 설정
    while(1) // 무한반복
    {   
        PORTA = 0xFF;    // LED를 전부 high로
        delay_ms(5000);  // 5초 대기
        PORTA = 0x00;    // LED를 전부 Low로
        delay_ms(5000);  // 5초 대기
    }
}

//실습1-5 오프시간 2초, 온시간 0.5초 반복

#include <io.h>
#include <delay.h>

void main()
{
    DDRA = 0xFF; // PORTA를 전부 출력단으로 설정
    while(1) // 무한반복
    {   
        PORTA = 0x00;    // LED를 전부 Low로
        delay_ms(2000);  // 2초 대기  
        PORTA = 0xFF;    // LED를 전부 high로
        delay_ms(500);   // 0.5초 대기
    }
} 

//실습1-6 오프시간 5초 온시간 0.5초 반복 
 
#include <io.h>
#include <delay.h>

void main()
{
    DDRA = 0xFF; // PORTA를 전부 출력단으로 설정
    while(1) // 무한반복
    {   
        PORTA = 0x00;    // LED를 전부 Low로
        delay_ms(5000);  // 5초 대기   
        PORTA = 0xFF;    // LED를 전부 high로
        delay_ms(500);   // 0.5초 대기
    }
}











