// 반도체 전자과 2614110179 조예찬
/*
// FND 플러스 마이너스 표시
#include <io.h>
#include <delay.h>

void CheckKeyIn(char *pSw1, char *pSw2); // 버튼감지
void FndControl(); // FND출력
unsigned int cnt = 0; // 1ms마다 카운트
void PutSignedDecimal(short inVal); // -값이면 -(-inVal)로 바꾸고 출력, FND3번째 자리에는 -가 들어오게함 

unsigned char fndDispVal[4]; // FND에 출력시킬 숫자를 저장
const unsigned char fndHexDisp[16] // 표시시킬 LED
= { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27,  // 0~7
    0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71}; // 8~F

void main(void)
{
    char sw1, sw2; // CheckKeyIn함수용  
    short val = 0; // val 변수의 data type이 short 임 (-32K ~ + 32K 범위의 값 저장 가능)
    int i;
    DDRC = 0xFF;
    DDRG = 0x0F;
    PutSignedDecimal(val); // 초기상태 000

    while (1)
    {
        delay_ms(1);
        ++ cnt;
        if((cnt%20) == 0) // 20ms마다 실행
        {
            CheckKeyIn(&sw1, &sw2);
            if(sw1 == 1)
            {
                ++ val; // 1번 스위치를 누르면 val값이 증가
                PutSignedDecimal(val);
            }
            // 중간에 연산 시키면 맛감
            //for(i=0; i<30000; i++)
            //{
            //    int sum=0;
            //    sum += i;
            //}
            
            if ( sw2 == 1 )
            {
                -- val; // 2번 스위치를 누르면 val값이 감소
                PutSignedDecimal(val);
            }
        }
        if ( ( cnt % 5 ) == 0 ) // 5ms마다 출력용 함수 호출
        FndControl(); 
    }
}

void CheckKeyIn(char *pSw1, char *pSw2) // 버튼 눌림을 확인
{
    static unsigned char swRead_1, swRead_2;
    
    swRead_1 = swRead_1 << 1; 
    if (PINE.4)
       swRead_1 |= 0x01; 
    swRead_2 = swRead_2 << 1;
    if (PINE.5)
       swRead_2 |= 0x01;

    if ((swRead_1&0x0F) == 0x0E ) 
       *pSw1 = 1; 
    else
       *pSw1 = 0; 
    if ((swRead_2&0x0F) == 0x0E )
       *pSw2 = 1;
    else
       *pSw2 = 0;
}

const unsigned char fndOn[4] = {0x01, 0x02, 0x04, 0x08};

void FndControl() // 5ms마다 호출당함
{
    static unsigned char pos = 0; // FndControl에서만 호출가능한 값이 유지되는 변수 
    PORTG = 0;
    PORTC = fndDispVal[pos]; // 값을 출력
    PORTG = fndOn[pos]; // 값을 출력하는 신호선
    pos = ( ++ pos ) % 4; // 5ms마다 1씩증가, 4 == 0번째
}

void PutSignedDecimal(short inVal) // 출력할 값을 저장
{
    unsigned char i;
    if ( inVal < 0 ) // inVal값이 0보다 작으면 -값
    {
        inVal = - inVal; // inVal이 -3인 상태면 inVal에 -(-3)이 대입된다. 따라서 inVal은 3이 된다. 
                         // ---> for문으로 (음수가 대입되어 버리면 fndHexDisp에 마이너스가 대입되서 동작오류 생김)
        fndDispVal[3] = 0x40; // 3번째에 - 를 표시
    }
    else // inVal값이 0보다 크면 + 값 
        fndDispVal[3] = 0x00; // 3번째에 아무것도 표시 안함
    for (i = 0; i < 3; i ++) // 0, 1, 2 --- 3번만 반복
    {
        fndDispVal[i] = fndHexDisp[inVal % 10]; // 234가 오면 나머지 4가 fndDispVal[0]에 fndHexDisp[4]가 대입된다. 
        inVal = inVal / 10; // 234/10 = 23이되고 다시 반복
    }
}
*/

/*
// 기존 버튼 함수 for문 사용중에 문제점이 있다. CheckKeyIn의 한계
#include <io.h>
#include <delay.h>

unsigned char cnt=0;
void CheckKeyIn(char *pSw1, char *pSw2);

void main(void)
{
    char sw1, sw2;
    unsigned int i=0;
    DDRA = 0xFF;
    DDRE = 0x00;
    
    PORTA = 0;
    while(1)
    {
        for(i=0; i<1000; i++)
            delay_ms(1);
            
        CheckKeyIn(&sw1, &sw2);
        
        if(sw1 == 1)
            cnt=0;
            
        PORTA = cnt++;
        delay_ms(100);
    }
}

void CheckKeyIn(char *pSw1, char *pSw2) // 버튼 눌림을 확인
{
    static unsigned char swRead_1, swRead_2;
    
    swRead_1 = swRead_1 << 1; 
    if (PINE.4)
       swRead_1 |= 0x01; 
    swRead_2 = swRead_2 << 1;
    if (PINE.5)
       swRead_2 |= 0x01;

    if ((swRead_1&0x0F) == 0x0E ) 
       *pSw1 = 1; 
    else
       *pSw1 = 0; 
    if ((swRead_2&0x0F) == 0x0E )
       *pSw2 = 1;
    else
       *pSw2 = 0;
}
*/

/*
// 인터럽트 함수
#include <io.h>
#include <delay.h>

unsigned char cnt=0;

interrupt [EXT_INT4] void Extlntr4()
{
    cnt=0;
}
interrupt [EXT_INT5] void Extlntr5()
{
    cnt=0xF0;
}

void main(void)
{
    unsigned int i=0;
    SREG = 0x80; // 인터럽트 사용은 최상위 비트를 1로 설정한다.
    EIMSK = 0x30; // 외부인터럽트 PINE.4, PINE.5를 설정 00110000
    EICRB = 0x0A; // ISC51: 1, ISC50: 0, ISC41: 1, ISC40: 0
                  // 하강엣지, 버튼을 누를 때 동작  ---!\!___/---
    
    DDRA = 0xFF; // LED모두 출력
    PORTA = 0; // 초기 LED모두 off
    
    while(1)
    {
        for(i=0; i<1000; i++)
            delay_ms(1);
        
        PORTA = cnt++;
        delay_ms(100);
    }
}
*/

// 인터럽트 활용 CheckKeyIn함수 제거
#include <io.h>
#include <delay.h>

void FndControl(); // FND출력
void PutSignedDecimal(short inVal); // -값이면 -(-inVal)로 바꾸고 출력, FND3번째 자리에는 -가 들어오게함 

unsigned char fndDispVal[4]; // FND에 출력시킬 숫자를 저장
const unsigned char fndHexDisp[16] // 표시시킬 LED
= { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27,  // 0~7
    0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71}; // 8~F

unsigned int cnt = 0; // 1ms마다 카운트
short val = 0; // 2^15 ~ -2^15 값을 저장 가능
interrupt [EXT_INT4] void Extlntr4() // 인터럽트 4가 눌리면 ++ 서비스 함수는 짧게!
{
    ++val;
}
interrupt [EXT_INT5] void Extlntr5() // 인터럽트 5가 눌리면 --
{
    --val;
}

void main(void)
{
    SREG = 0x80;  // 상태레지스터: 인터럽트 사용은 최상위 비트를 1로 설정한다.
    EIMSK = 0x30; // 외부인터럽트 PINE.4, PINE.5를 설정 00110000
    EICRB = 0x0F; // 0x00: 둘다로우일때, 0x0A: 둘다 하강, 0x0F: 둘다 상승 // ISC51:  ISC50:  ISC41:  ISC40:   
    // EICRB의 비트 0000[11]{11}, [11]부분이 핀5, {11}아 핀4이다. 00이면 로우일때 항상동작, 10이면 하강엣지, 11이면 상승엣지에서 동작
    
    DDRA = 0xFF;                    
    DDRC = 0xFF;
    DDRG = 0x0F;
    PutSignedDecimal(val); // 초기상태 000

    while (1)
    {
        delay_ms(1);
        cnt++;
        PutSignedDecimal(val); // 1ms 마다 val값을 fndDispVal에 대입
        if ((cnt%5) == 0) // 5ms마다 출력용 함수 호출
            FndControl();
        PORTA = val; 
    }
}

const unsigned char fndOn[4] = {0x01, 0x02, 0x04, 0x08};

void FndControl() // 5ms마다 호출당함
{
    static unsigned char pos = 0; // FndControl에서만 호출가능한 값이 유지되는 변수 
    PORTG = 0;
    PORTC = fndDispVal[pos]; // 값을 출력
    PORTG = fndOn[pos]; // 값을 출력하는 신호선
    pos = ( ++ pos ) % 4; // 5ms마다 1씩증가, 4 == 0번째
}

void PutSignedDecimal(short inVal) // 출력할 값을 저장
{
    unsigned char i;
    if ( inVal < 0 ) // inVal값이 0보다 작으면 -값
    {
        inVal = - inVal; // inVal이 -3인 상태면 inVal에 -(-3)이 대입된다. 따라서 inVal은 3이 된다. 
                         // ---> for문으로 (음수가 대입되어 버리면 fndHexDisp에 마이너스가 대입되서 동작오류 생김)
        fndDispVal[3] = 0x40; // 3번째에 - 를 표시
    }
    else // inVal값이 0보다 크면 + 값 
        fndDispVal[3] = 0x00; // 3번째에 아무것도 표시 안함
    for (i = 0; i < 3; i ++)
    {
        fndDispVal[i] = fndHexDisp[inVal % 16]; // 234가 오면 나머지 4가 fndDispVal[0]에 fndHexDisp[4]가 대입된다. 
        inVal = inVal / 16; // 234/10 = 23이되고 다시 반복
    }
}