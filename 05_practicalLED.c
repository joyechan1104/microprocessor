// 반도체전자과 2614110179 조예찬
#include <io.h>
#include <delay.h>

// 예제3 시프트 속도 변화 시키기
void main()
{
    char i = 0; // 127이하로 반복문에 쓸거니까 캐릭터 변수로 충분
    unsigned int n; // 8비트니 인트 음수는 안쓰겠다. 딜레이값에 음수를 절대 안넣겠다는 의지
    // 모든 변수는 DDRA, PORTA위에 선언을 해야한다!
    DDRA = 0xFF; // 모든 포트를 출력으로
    
    while(1)
    {
         for(i=0;i<=8;i++)
         {
            PORTA = 1 << i; // 1번 돌때마다 비트를 1칸씩 왼쪽으로 옮기겠다.
            // 0주기 00000001 << 0
            // 1주기 00000001 << 1 -> 00000010 ...
            // 7주기 00000001 << 7 -> 10000000
            // 8주기 00000001 << 8 -> 00000000 좌측으로 8번 옮기면 8bit라서 다 사라진다.
            n = 1000 / ( (i+1)*(i+1) ); // 1>4>9>16으로 분모가 점점 작아짐
            delay_ms(n); // 0주기 1초 -> 1주기 1/4초(250) -> 2주기 1000/9초(111) 소수 인식 안시키게   
         }
         delay_ms(1000);
    }
}


// 실습1-1
#include <io.h>
#include <delay.h>

void main()
{
    unsigned char right_shift = 0x80; //10000000에서 시작
    DDRA = 0xFF; // 모든포트를 출력으로
    
    while(1)
    {
        PORTA = right_shift; // 포트A에 라이트쉬프트 변수 대입
        delay_ms(100);
        right_shift = right_shift >> 1; // 라이트쉬프트에 오른쪽으로 비트 1칸 이동시킨 변수를 대입
        if(right_shift == 0) // 만약 라이트쉬프트변수가 0이되면
        {
            right_shift = 0x80; // 다시 10000000으로 초기화
        }
    }
}


// 1-2.ver1 이중폴문 활용
#include <io.h>
#include <delay.h>

void main()
{
    int shift_bit = 0x80; // 이동변수 생성
    int i = 0, x = 0;
    int sec = 100; // 딜레이 시간 통일
    DDRA = 0xFF; // 모두출력으로
    
    while(1)
    {
        shift_bit = 0x80; // 10000000으로 시박
        for(x = 0; x < 7; x ++) // 1주차를 시작으로 7회 반복하도록 설정    
        {
            for(i = 0; i < 3; i ++) // 3번씩 깜빡이게
            {
                PORTA = shift_bit; // 시프트 비트를 포트A에 대입시켜 출력시킨다.
                delay_ms(sec);
                PORTA = 0x00; // all off
                delay_ms(sec);
            }
            shift_bit = shift_bit >> 1; // 3번 깜빡이면 비트를 오른쪽으로 한칸 이동시킨다.
        }
        
        shift_bit = 0x01; // 오른쪽으로 가는걸 끝내면 왼쪽으로 가는걸 세팅 00000001부터 시작        
        for(x = 0; x < 7; x ++) // 마찬가지로 7회 반복    
        {
            for(i = 0; i < 3; i ++) // 3번씩 깜빡이게 설정
            {
                PORTA = shift_bit; // 쉬프트비트를 대입해서 출력
                delay_ms(sec);
                PORTA = 0x00; // all off
                delay_ms(sec);
            }
        shift_bit = shift_bit << 1; // 3번깜빡이면 좌측으로 비트를 이동시킨다.
        }      
    }
}


// 1-2.ver2 토글로 만들어보기
#include <io.h>
#include <delay.h>

void main()
{
    int Toggle = 1; // 토근 1은 순차증가 0은 순차감소
    int shiftBit = 0x01;
    DDRA = 0xFF;
    
    while(1)
    {
        delay_ms(100);
        
        if(Toggle == 1) // 토글이 1이면 순차증가
        {
            PORTA = shiftBit; // 포트A에 쉬프트 비트를 대입한다.
            shiftBit = shiftBit << 1; // 비트를 한칸씩 왼쪽으로 이동시킨다
            if(shiftBit == 0x80) // 비트가 10000000이 된다면
            {
                Toggle = 0; // 토글을 0으로 만들겠다    
            }
        }
        
        else // 토글이 0이면 순차감소
        {
            PORTA = shiftBit; // 포트A에 쉬프트 비트를 대입한다.
            shiftBit = shiftBit >> 1; // 비트를 한칸씩 오른쪽으로 이동시킨다
            if(shiftBit == 0x01) // 비트가 00000001이 된다면
            {
                Toggle = 1; // 토글을 1로 만들겠다.    
            }
        }    
    }
}


// 1-3.ver1 폴문 2개 + OR연산 활용
#include <io.h>
#include <delay.h>

void main()
{
    int leftShift = 0x01; // 00000001 좌측이동 변수
    int rightShift = 0x80; // 10000000 우측이동 변수
    int orShift = 0; // 변수2개를 합친다
    int sec = 100; // 딜레이시간
    char i = 0; // 반복문에 쓸놈
    DDRA = 0xFF;
    orShift = leftShift | rightShift; // 일단 먼저 변수로 지정해둔 두 수를 오아연산해서 대입
    
    while(1)
    {   
        for(i=0;i<3;i++) // 안쪽으로 모여들어가는 순서 3번반복 (4번반복하면 중간에서 오래 머무른다)
        {
            PORTA = orShift; // 포트A에는 오아쉬프트를 대입
            delay_ms(sec);
            leftShift = 0x01 << i; // 00000001 에서 좌로이동 반복 횟수에 따라 i값에 따라 이동
            rightShift = 0x80 >> i; // 10000000 에서 우로이동 
            orShift = leftShift | rightShift; // OR연산 10000001
        }
        
        for(i=0;i<3;i++) // 밖으로 퍼져나가는 순서 3번반복 (4번반복하면 끝에서 오래 머무른다)
        {
            PORTA = orShift; // 포트A에는 오아쉬프트를 대입
            delay_ms(sec);
            leftShift = 0x10 << i; // 00001000 에서 좌측으로 마찬가지로 반복 회수에 따라 i값에 따라 이동
            rightShift = 0x08 >> i; // 00001000 에서 우측으로 
            orShift = leftShift | rightShift; // OR연산 00011000
        }
        // 01000010 에서 끝내면 다시 10000001에서 시작하게 된다.   
    }
}


// 1-3.ver2 토글과 비트 AND OR연산 활용
#include <io.h>
#include <delay.h>

void main()
{
    int Toggle = 1; // 오므라드는걸 1로 퍼져나가는걸0으로 설정
    DDRA = 0xFF;
    PORTA = 0x81; // 시작비트를 10000001로 설정

    while(1)
    {
        delay_ms(500); // 0.5초 대기
        
        if(Toggle == 1) // 토글이 1이면 오므라든다
        {
            PORTA = (PORTA & 0xF0) >> 1 | (PORTA & 0x0F) << 1;
            //     10000001     10000001
            // AND 11110000 AND 00001111
            //     10000000     00000001
            //  >> 01000000  << 00000010 이 두개를 OR -> 01000010
            // 반복하면 00100100 -> 00011000 
            if(PORTA == 0x18) // 만약 00011000인 상황이되면
            {
                Toggle = 0; // 토글을 0으로 만든다.    
            } 
        }
        
        else // 토글이 0인상황 숫자가 퍼져나간다.
        // if(Toggle == 0) 분석한다고 컴퓨터가 잡아먹기 때문에 if else를 써야한다
        {
            PORTA = (PORTA & 0xF0) << 1 | (PORTA & 0x0F) >> 1;
            //     00011000     00011000
            // AND 11110000 AND 00001111
            //     00010000     00001000
            //  << 00100000  >> 00000100 OR연산 하면 00100100
            // 반복하면 01000010 -> 10000001
            if(PORTA == 0x81) // 10000001인 상황이되면
            {
                Toggle = 1; // 토글을 1로 만든다.   
            } 
        }
    }    
}                   


// 실습 2-1 바이너리로 감소시키기
#include <io.h>
#include <delay.h>

void main()
{
    DDRA = 0xFF;
    PORTA = 0xFF;
    
    while(1)
    {
        -- PORTA; // 1씩감소
        delay_ms(30);
        if(PORTA == 0x00)// 비트가 00000000이 된다면
        {
            PORTA = 0xFF;
        }   
    }
}


// 실습 2-2 바이너리 증가시키다가 0xFF되면 감소시키기
#include <io.h>
#include <delay.h>

void main()
{
    int Toggle = 1; // 반전시키는 변수 1은 증가 0은 감소
    DDRA = 0xFF; // 모든 포트를 출력으로
    PORTA = 0x00; // 시작은 00000000부터
       
    while(1)
    {
        delay_ms(30); // 대기시간
        
        if(Toggle == 1) // 토글이 1이면(순차증가)
        {
            ++PORTA; // 포트A를 1개씩 증가시키겠다.
            if(PORTA == 0xFF) // 만약 포트A가 11111111이면
            {
                Toggle = 0; // 토글을 0으로 한다.   
            }    
        }
        
        else // 토글이 0이면(순차감소)
        {
            --PORTA; // 포트A를 1개씩 감소시키겠다.
            if(PORTA == 0x00) // 만약 포트A가 00000000이면
            {
                Toggle = 1; // 토글을 1으로 한다.    
            } 
        }    
    }
}


// 실습 3
#include <io.h>
#include <delay.h>

void main()
{
    int more = 0; // LED값을 순차적으로 증가시키는 연산
    char i = 0;
    unsigned int sec = 1000; // 딜레이 변수
    DDRA = 0xFF;
    
    while(1)
    {
        for(i=0;i<=8;i++) // 모두꺼짐 0 ~ 모두켜점 8 까지 총 9주기 반복
        {
            PORTA = more;
            delay_ms(sec);
            more = more | ( 0x01 << i ); // 지금 켜진 비트에서 OR연산으로 반복주기에따라 추가
            sec = 1000 / ( (i+1) * (i+1) ); // 점점 배속으로 빠르게 한다. 
        }
        more = 0x00; // 9번 반복을 끝내면 초기화 시킨다.
    }
}