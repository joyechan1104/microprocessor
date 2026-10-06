// 반도체전자과 2614110179 조예찬
// 예제1
#include <io.h>
#include <delay.h>

unsigned int cnt = 0; // 전역변수, 초기화
void checkKeyIn(char *pSw1, char *pSw2); // call by reference

void main(void)
{
    char sw1, sw2; // 8bit 데이터방
    unsigned int v1 = 0; // 지역변수, 초기화
    
    DDRA = 0xFF; // LED출력
    DDRE = 0x00; // 버튼입력
    while(1)
    {
        delay_ms(1); // 1초마다 와일문 실행
        ++cnt;
        if((cnt%20) == 0) // cnt를 20으로 나눈값이 0이면.. (20ms마다 실행)
        {
            checkKeyIn(&sw1, &sw2); // checkKeyIn 함수를 호출 스위치1과 2의 주소를 보낸다
            
            if(sw1 == 1) // 만약 sw1의 값이 1이면
            {
                ++v1; // v1의값을 증가시킨다
            }
            if(sw2 == 1) // 만약 sw2의 값이 1이면
            {
                --v1; // v1의값을 감소시킨다
            }
            
            PORTA = v1; // LED에 v1을 대입시킨다.    
        }
    }
}

void checkKeyIn(char *pSw1, char *pSw2) // sw1과2의 주소값을 가져온다  
{
    static unsigned char swRead_1, swRead_2; // static으로 스위치읽기 1, 2변수를 생성 함수종료후에도 값을 유지하며 checkKeyIn함수 내에서만 사용가능
    swRead_1 = swRead_1 << 1; // swRead_1에 들어있는 값을 1칸 좌측으로 이동시킨다.
    if(PINE.4) // 스위치를 누르지 않은 상태(1)이라면 참
    {
        swRead_1 |= 0x01; // 00000000 | 00000001 -> 00000001 (20ms후)  
// 위의 swRead_1 <<= 1; 이 실행 00000010 | 00000001 -> 00000011 (40ms후)  
                          // 00000110 | 00000001 -> 00000111 (60ms후) 계속되면~~~
                          // 11111110 | 00000001 -> 11111111 (160ms후) 실행되면 약 0.16초만에 비트가 풀로 채워진다.
    }
    swRead_2 = swRead_2 << 1; // swRead_2에 들어있는 값을 1칸 좌측으로 이동시킨다.
    if(PINE.5)
    {
        swRead_2 |= 0x01;    
    }
    
    // 만약 버튼을 누르면(0) 거짓이되므로 위의 if문이 스킵되는데
    // 11111111 << 1 -> 11111110 <------ 중요!!!!
    // 11111110 << 1 -> 11111100 계속되면
    // 10000000 << 1 -> 00000000
    if((swRead_1 & 0x0F) == 0x0E) // swRead_1의 값과 00001111을 AND연산한 값이 00001110이라면
    {              // (11111110 & 00001111) == 00001110이 된다.
        *pSw1 = 1; // *pSw1의 주소가 가르키는 값 즉sw1의 숫자를 1로 바꾼다.    
    }              // 20ms가 지나면 다시 (11111100 & 00001111) == 00001100이 되므로
    else           // *pSw1의 주소가 가르키는 값 즉sw1의 숫자를 다시 0으로 바꾸고 시간지 지나도 버튼을 누르고 있으면 00000000인 상태가 유지된다.
    {
        *pSw1 = 0;  
    }
    if((swRead_2 & 0x0F) == 0x0E) // swRead_2의 값과 00001111을 AND연산한 값이 00001110이라면
    {
        *pSw2 = 1;    
    }
    else
    {
        *pSw2 = 0;  
    } 
}

// 실습1
#include <io.h>
#include <delay.h>

unsigned int cnt = 0; // 전역변수, 초기화
void checkKeyIn(char *pSw1, char *pSw2); // call by reference
    
void main(void)
{
    char sw1, sw2; // 8bit 데이터방
    unsigned int v1 = 0, v2 = 0; // v1은 하위비트 v2는 상위비트를 담을 방을 만든다
    
    DDRA = 0xFF; // LED출력
    DDRE = 0x00; // 버튼입력
    while(1)
    {
        delay_ms(1); // 1초마다 와일문 실행
        ++cnt;
        if((cnt%20) == 0) // cnt를 20으로 나눈값이 0이면.. (20ms마다 실행)
        {
            checkKeyIn(&sw1, &sw2); // checkKeyIn 함수를 호출 스위치1과 2의 주소를 보낸다
            
            if(sw1 == 1) // 만약 sw1의 값이 1이면
            {
                ++v1; // v1의 하위4비트 값을 증가 + 00001111
            }
            if(sw2 == 1) // 만약 sw2의 값이 1이면
            {
                ++v2; // v2의 상위4비트 값을 증가 + 00010000  
            }
            PORTA = (v1 & 0x0F) | (v2 << 4);
            // v1은 넘어가서 00010001이 되도 어짜피 상위 비트는 AND연산으로 0처리해버리기 때문에 상관없다.
            // v2도 마찬가지로 00001111 << 4 -> 11110000에서 1이더 증가되면
            //             00010000 << 4 -> 00000000이 되버리기 때문에 상관없다.
   
        }
    }
}

// 위의 예제1과 동일
void checkKeyIn(char *pSw1, char *pSw2)
{
    static unsigned char swRead_1, swRead_2;
    swRead_1 = swRead_1 << 1; 
    if(PINE.4) 
    {
        swRead_1 |= 0x01;
    }
    swRead_2 = swRead_2 << 1;
    if(PINE.5)
    {
        swRead_2 |= 0x01;    
    }
    
    if((swRead_1 & 0x0F) == 0x0E)
    {              
        *pSw1 = 1;    
    }              
    else           
    {
        *pSw1 = 0;  
    }
    if((swRead_2 & 0x0F) == 0x0E)
    {
        *pSw2 = 1;    
    }
    else
    {
        *pSw2 = 0;  
    } 
}

