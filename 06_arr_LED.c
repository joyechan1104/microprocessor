// 반도체전자과 2614110179 조예찬
// 실습1-1 swing에 걸리는 시간이 일정!
#include <io.h>
#include <delay.h>
void swing1(int dist, int duration); // 메인함수 아래로 함수 배치를 하기 위함

const unsigned char value[4][16] =
{
    {0x10, 0x08},                                                                        // 2
    {0x10, 0x20, 0x10, 0x08, 0x04, 0x08},                                                // 6
    {0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08},                        // 10
    {0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08} // 14
};
void main()
{
    int i; // main 지역변수i
    unsigned int d; // delay용
    DDRA = 0xFF;
    d = 1000; // 지연시간을 1초로
    
    while(1)
    {
        for(i=1; i<5; i++) // i가 1~4일때 까지 반복
        {
            swing1(i,d); // i값과 d값을 스윙함수로 보내겠다 
        }
        for(i=3; i>1; i--) // i가 3~2일때 까지 반복 그래야 다시 1~4가 반복
        {
            swing1(i,d);    
        }
    }
}

void swing1(int dist, int duration) // i값을 2차원배열의 행으로, d를 딜레이시간으로
{
    int i; // swing1 함수 지역변수
    for(i=0; i<(dist*4 - 2); i++) // 등비수열
    {
        PORTA = value[dist-1][i]; // 1회차 2, 2회차 6, 3회차 10, 4회차 14
        delay_ms(duration/(dist*4-2)); // duration을 100이라 가정하고 dist(메인함수i값)의 증가함에 따라 분모가 작아지게 만듬
                                       // 1회차 100/(1*4-2) == 100/2 == 50을 2회반복 == 100
                                       // 2회차 100/(2*4-2) == 100/6을 6회반복 == 100
                                       // 3회차 100/(3*4-2) == 100/10 == 10을 10회반복 == 100
                                       // 4회차 100/(4*4-2) == 100/14를 14회 반복 == 100 
    }
}

// 실습1-2 패턴을 변경
#include <io.h>
#include <delay.h>
void swing1(int dist, int duration);

const unsigned char value[4][10] =
{
    {0x00, 0x18},                                    // 2                            
    {0x00, 0x18, 0x3C, 0x18},                        // 4                 
    {0x00, 0x18, 0x3C, 0x7E, 0x3C, 0x18},            // 6     
    {0x00, 0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18} // 8
};

void main()
{
    int i; // main 지역변수i
    unsigned int d; // delay용
    DDRA = 0xFF;
    d = 200;
    
    while(1)
    {
        for(i=1; i<5; i++) // i가 1~4일때 까지 반복
        {
            swing1(i,d);  
        }
        for(i=3; i>1; i--) // i가 3~2일때 까지 반복
        {
            swing1(i,d);    
        }
    }
}

void swing1(int dist, int duration) // i값을 2차원배열의 행으로, d를 딜레이시간으로
{
    int i; // swing1 함수 지역변수
    for(i=0; i<(dist*2); i++) // 디스트에 * 2를 한 수만큼 반복하고 탈출 1회차 1*2 == 2회반복 , 2회차 2*2 == 4회반복...
    {
        PORTA = value[dist-1][i]; // 메인함수 i값에 1을 뺀값에, 스윙함수 i값
        delay_ms(duration); // d의값에서온 듀레이션을 대입 
    }
}

// 실습1-3 위와같은 스윙패턴이되 한번에 걸리는 시간을 일정하게
#include <io.h>
#include <delay.h>
void swing1(int dist, int duration);

const unsigned char value[4][10] =
{
    {0x00, 0x18},                                    // 2                            
    {0x00, 0x18, 0x3C, 0x18},                        // 4                 
    {0x00, 0x18, 0x3C, 0x7E, 0x3C, 0x18},            // 6     
    {0x00, 0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18} // 8
};

void main()
{
    int i; // main 지역변수i
    unsigned int d; // delay용
    DDRA = 0xFF;
    d = 1000; 
    
    while(1)
    {
        for(i=1; i<5; i++) // i가 1~4일때 까지 반복
        {
            swing1(i,d);  
        }
        for(i=3; i>1; i--) // i가 3~2일때 까지 반복
        {
            swing1(i,d);    
        }
    }
}

void swing1(int dist, int duration) // i값을 2차원배열의 행으로, d를 딜레이시간으로
{
    int i; // swing1 함수 지역변수
    for(i=0; i<(dist*2); i++) // 디스트에 * 2를 한 수만큼 반복하고 탈출 1회차 1*2, 2회차 2*2 ...
    {                         // 등비수열을 그대로~~
        PORTA = value[dist-1][i]; // 메인함수 i값에 1을 뺀값에, 스윙함수 i값
        delay_ms(duration/(dist*2)); // duration이 100이라 가정
                                     // 1회차 100/(1*2) == 100/2을 2회 == 100 
                                     // 2회차 100/(2*2) == 100/4를 4회 == 100
                                     // 3회차 100/(3*2) == 100/6을 6회 == 100
                                     // 4회차 100/(4*2) == 100/8을 8회 == 100
        
    }
}

// 실습2
#include <io.h>
#include <delay.h>

unsigned int cnt = 0; // 전역변수, 초기화

void main()
{
    int count = 0x01; // LED에 출력할 변수    

    DDRA = 0xFF; // LED를 모두 출력으로
    DDRE = 0x00; // 버튼을 입력으로
    
    while(1)
    {   
        delay_ms(1); // 와일문을 0.001초마다 반복되게
        ++cnt; // 반복될때마다 1씩 쌓인다
        if((cnt % 20) == 0) // cnt를 20으로 나눈값의 나머지가 0이면 (20ms마다)
        {
            if((PINE & 0x10) == 0) // 핀4번이 눌리면
            {   
                ++count; // 1씩증가    
            }
            if((PINE & 0x20) == 0) // 핀5번이 눌리면
            {
                --count; // 1씩감소  
            }
            PORTA = count; // 포트A에 카운트를 대입
        }
    }
}
