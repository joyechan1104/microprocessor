/*
#include <io.h>
#include <delay.h>

unsigned char FND_loop[16] = {0x3f, 0x3f, 0x3f, 0x3f,  // 0000       [0~3]
0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,  // 123456789  [4~12]
0x3f, 0x3f, 0x3f};                                     // 000        [13~15]
unsigned char FND_on[4] = {0x08, 0x04, 0x02, 0x01}; // PORTG제어용 순서대로 MSB, bit1, bit2, LSB이다.

void main()
{
    int i=0, j=0, k=0;

    DDRC = 0xFF; // DDR 세그먼트를 전부 출력으로
    DDRG = 0x0F; // DDR 신호선의 하위4비트만 출력으로
    
    while(1)
    {
        for(i=0; i<13; i++) // 1번 반복 할 때마다 FND에 출력되는 숫자를 왼쪽으로 밀어주기 위한 용도
        {
            for(j=0; j<50; j++) // 딜레이 시간으로 활용하는 폴문 다음 K폴문의 (지속시간 * 50)[ms] 동안 지속된다.
            {
                for(k=0; k<4; k++) // PORTG 4군데를 활용해야 하므로 4번 반복
                {
                    PORTC = FND_loop[i+k]; // 반복횟수 + 출력하는FND위치 
                    PORTG = FND_on[k]; // 출력하는 FND위치
                    delay_ms(5);
                    PORTG = 0x00; // 잔상방지용 끄기
                    // loop 0*0 i가0 k도0이면 0+0, FND MSB에 FND_loop[0]가 출력 = 0
                    // loop 2*0 i가2 k는0이면 2+0, FND MSB에 FND_loop[2]가 출력 = 0
                    // loop 2*1 i가2 k는0이면 2+1, FND bit1에 FND_loop[3]가 출력 = 0
                    // loop 2*1 i가2 k는0이면 2+2, FND bit2에 FND_loop[4]가 출력 = 1
                    // loop 2*1 i가2 k는0이면 2+3, FND LSB에 FND_loop[5]가 출력 = 2 따라서 loop 2*n의 FND에는 0012가 출력된다.
                }
            } 
        }
    }
} */

#include <io.h>
#include <delay.h>

unsigned char FND_num[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0~9까지의 숫자
unsigned char FND_on[4] = {0x08, 0x04, 0x02, 0x01}; // PORTG 출력용
unsigned int outPut[3][13] =  {
    {0, 1, 12, 123, 1234, 2345, 3456, 4567, 5678, 6789, 7890, 8900, 9000}, 
    {0, 9, 89, 789, 6789, 5678, 4567, 3456, 2345, 1234, 1230, 1200, 1000}
}; // 0을 붙이면 8진수라고 인색해버림
unsigned int delayTime = 300; // <----- 화면에 출력할 시간 입력

void segment_num(int num, int ms) // num 4자리에 출력할 숫자,  ms 유지시킬 시간
{
    int i=0, j=0;
    unsigned char FND_value[4]; // 천[0]백[1]십[2]일[3]의 자리에 들어갈 숫자를 배열로 저장, 지역변수
    
    FND_value[0] = FND_num[(num/1000) % 10]; // 2345/1000 = 2, 2%10 = 0 ... 2
    FND_value[1] = FND_num[(num/100) % 10];  // 2345/100 = 23, 23%10 = 2 ... 3 
    FND_value[2] = FND_num[(num/10) % 10];   // 2345/10 = 234, 234%10 = 3 ... 4 
    FND_value[3] = FND_num[num % 10];        // 2345%10 = 234 ... 5
    
    for(i=0; i<(ms/20); i++) // 내부 j폴문이 반복되는 시간으로 나눈수 만큼 실행
    {
        for(j=0; j<4; j++) // 4회반복 * 5ms딜레이 = 20ms의 딜레이 발생
        {
            PORTC = FND_value[j]; // 출력되는 숫자: loop1 천의자리, loop2 백의자리, loop3 십의자리, loop4 일의자리   
            PORTG = FND_on[j];    // 제어신호 위치: loop1 천의자리, loop2 백의자리, loop3 십의자리, loop4 일의자리  
            delay_ms(5);
            PORTG = 0x00;
        }
    }
} 

void main()
{
    int i=0, j=0
    // int k=0, a=0; // 시계돌리는 변수

    DDRC = 0xFF;
    DDRG = 0x0F;
    
    while(1)
    {   
        
        for(i=0; i<2; i++)
        {
            for(j=0; j<13; j++) // 배열의 개수만큼 반복
            {   
                segment_num(outPut[i][j], delayTime); // 4자리에 무슨 숫자를 출력할지?, 한사이클에 몇ms동안 표시하게 할지?
            }
        }
        
        /* // 시계
        for(a=0; a<12; a++)
        {
            for(k=0; k<60; k++)
            {
                segment_num(k + (a*100), delayTime);
            }
        }
        */   
    }
}