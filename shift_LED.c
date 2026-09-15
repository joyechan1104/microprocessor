// 반도체전자과 2614110179 조예찬

// 언사인드 캐릭터는 최상위 비트를 데이터비트로 사용하겠다
//0000 0001
//0000 0010
//0000 0100
//0000 1000
//0001 0000
//0010 0000
//0100 0000
//1000 0000
//언사인드 캐릭터의 1000 0000을 << 시키면 0000 0000이 된다.


//실습1 shift연산자를 활용한 비트 이동방법
#include <io.h>
#include <delay.h>

unsigned char shift= 0x01; // 데이터비트로 8칸을 쓰겠다
int i = 0; // 반복문에 쓸 변수 설정

void main()
{
    DDRA = 0xFF; // 모두 출력으로 쓰겠다
            
    while(1) // 무한반복
    {
        for(i = 0; i < 3; i ++) // 3번씩 반복
        {
            PORTA = shift; // 포트A에 쉬프트를 대입
            delay_ms(200); // 0.2초 대기
            PORTA = 0x00;  // 모두 끄기
            delay_ms(200); // 0.2초 대기 , 3번깜빡이면 탈출
        }
        shift = shift << 1; // 비트를 1칸 왼쪽으로 이동시킨다
        
        if(shift == 0) // 쉬프트 변수가 1000000을 초과해 이동하면 00000000이 되면
        {
            shift = 0x01; // 다시 00000001로 초기화 시킨다.
        }    
    }
}




//실습2
#include <io.h>
#include <delay.h>

unsigned char data = 0x01; 
int i = 0;
int sec = 500;

void main()
{
    DDRA = 0xFF;
    
    while(1)
    {
        for(i = 0; i < 8; i ++) // 8번 반복한다
        {
            PORTA = data; // 포트A에 데이터를 대입시킨다
            delay_ms(sec);
            PORTA = 0x00;
            delay_ms(sec);
            data = ( data << 1 ) | 0x01; // 데이터에 데이터를 왼쪽으로 한칸 옮긴것과 00000001을 OR연산 시킨다.
            // 11111111 << 1 을 하면
            // 11111110 이 되어버린다. 따라서 수정시킬 필요가 있다.
        
            if(data == 0xFF) // 비트가 11111111이 되버리면
            {
                PORTA = data; // 11111111인 상태로 불을 킨다
                delay_ms(sec);
                PORTA = 0x00; // 전부 오프시키고
                delay_ms(sec);
                
                data = 0x01; // 다시 리셋시킨다
            }    
        }
    }
}




// 실습2 버젼2~
#include <io.h>
#include <delay.h>

unsigned char more = 0x02; // 초기변수를 00000010으로 설정
int i = 0;
int sec = 500;

void main()
{
    DDRA = 0xFF;
    
    while(1)
    {
        for(i = 0; i < 8; i ++) // 8번 반복한다
        {
        PORTA = more - 1; // 모얼변수에서 1을 뺀 값을 포트A에 대입시킨다.
        delay_ms(sec);
        more = more << 1; // sec초마다 왼쪽으로 1칸 시프트
        }
        // 탈출 
        more = 0x02; // 원래대로 초기화
        sec = sec/2; // 점점더 빠르게
        
        if(sec < 30)
        {
            sec = 500; // 너무빨라지면 초기화 시키기
        }
    }
}




// 실습3
#include <io.h>
#include <delay.h>

int j = 0, i = 0;
unsigned char data = 0x01; // 00000001로 시작
int sec = 200;

void main()
{
    DDRA = 0xFF;
    
    while(1)
    {
        for(i = 0; i < 8; i++) // 8번 반복
        {
            for(j = 0; j < 3; j++) // 3번 깜빡인다
            {
                PORTA = data;
                delay_ms(sec);
                PORTA = 0x00;
                delay_ms(sec); // 3번깜빡이면 탈출    
            }
            data = ( data << 1) | 0x01; // 데이터에 비트를 왼쪽 쉬프트 시킨값과 00000001을 OR연산 시킨다
        }
        data = 0x01; // 8번 반복시키면 초기화 시킨다.
    }
}




// 실습4
#include <io.h>
#include <delay.h>

int i = 0;
unsigned char data = 0x11; // 00010001로 설정
int sec = 200;

void main()
{
    DDRA = 0xFF;
    
    while(1)
    {
        for(i = 0; i < 5; i++) // 5번 깜빡이게 한다
        {
            PORTA = data;
            delay_ms(sec);
            PORTA = 0x00;
            delay_ms(sec);    
        } // 5번깜빡이면 탈출!
        
        data = data << 2; // 데이터비트를 두칸 좌측으로 이동시킨다.
        // 00010001
        // 01000100      1번째 이동하면 왼쪽으로 2칸씩 간다
        // 00010000 0x10 2번째 이동하면 생기는 현상 ( 중요 !!!!!! )
        
        if(data == 0x10) // 0x10까지 이동해버리면 초기화 시킨다.
        {
            data = 0x11;
        }
    }
}



// 바이너리 코드로 값 증가시키기
#include <io.h>
#include <delay.h>

void main()
{
    DDRA = 0xFF;
    
    while(1)
    {
        ++ PORTA; // 데이터비트 1씩 증가~
        delay_ms(30); // 풀로 찼다가 다시 0 이 되는게 아니다.
        // 11111111 다음에
        // 00000000 자동으로 로테이션(정수형 자료형의 특징)
        // 그러면 뭐다 if문이 필요없다!!
    }
}



// 왼쪽으로 쉬프트 시키기 1개씩 -> 오른쪽으로
#include <io.h>
#include <delay.h>

unsigned char n = 0;

void main()
{
    DDRA = 0xFF;
    n = 0x80; // 10000000으로 설정
    
    while(1)
    {
        PORTA = n;
        delay_ms(50);
        
        n = n >> 1; // 오른쪽으로 쉬프트
        
        if(n == 0)
        {
            n = 0x80; // n이 0이되면 다시 10000000으로 초기화
        }
    }
}





/*
// 실습 1-1 오른쪽으로
#include <io.h>
#include <delay.h>

unsigned char right_shift = 0x80; // MSB에서 시작
int i = 0;

void main()
{
    DDRA = 0xFF; // 모든포트를 출력으로
    
    while(1)
    {
        for(i = 0; i <3; i++) // 3번반복
        {
            PORTA = right_shift; // 포트A에 라이트쉬프트를 대입
            delay_ms(300);
            PORTA = 0x00; // 깜빡이게 출력을 0으로
            delay_ms(300); //3번 반복하면 탈출    
        }
        right_shift = right_shift >> 1; // 라이트쉬프트의 비트를 한칸 오른쪽으로
        
        if(right_shift == 0) // 라이트쉬프트가 0이면
        {
            right_shift = 0x80; // 원래대로 ㄱㄱ
        }
    }
}
*/

/*
// 1-2 좌우왔다갔다 하기
#include <io.h>
#include <delay.h>

int shift_bit = 0x80;
int i = 0, x = 0;

void main()
{
    DDRA = 0xFF;
    
    while(1)
    {
        shift_bit = 0x80;
        for(x = 0; x < 7; x ++)    
        {
            for(i = 0; i < 3; i ++)
            {
                PORTA = shift_bit;
                delay_ms(300);
                PORTA = 0x00;
                delay_ms(300);
            }
            shift_bit = shift_bit >> 1;
        }
        
        shift_bit = 0x01;        
        for(x = 0; x < 7; x ++)    
        {
            for(i = 0; i < 3; i ++)
            {
                PORTA = shift_bit;
                delay_ms(300);
                PORTA = 0x00;
                delay_ms(300);
            }
        shift_bit = shift_bit << 1;
        }      
    }
}
*/

/*
// 실습1-3 중간으로 오므리는거
#include <io.h>
#include <delay.h>

int right_bit = 0x80;
int left_bit = 0x01;
int shift_bit = 0x00;
int i = 0;

void main()
{
    DDRA = 0xFF;

    while(1)
    {
        shift_bit = left_bit | right_bit;
        
        for(i = 0; i < 3; i ++)
        {
            PORTA = shift_bit;
            delay_ms(300);
            PORTA = 0x00;
            delay_ms(300);
        }
        left_bit = left_bit << 1;
        right_bit = right_bit >> 1;
        
        if(shift_bit == 0x18)
        {
            right_bit = 0x80;
            left_bit = 0x01;
        }    
    }
}
*/