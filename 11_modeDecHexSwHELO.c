// 반도체전자 2614110179 조예찬
/*
// FND에 16진수 표시하기
#include <io.h>
#include <delay.h>

void DisplayHex();
void FndControl();

unsigned char fnd[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, // 10진수 0~9
                        0x77, 0x7c,0x39, 0x5e, 0x79, 0x71}; // 16진수용 abcder추가
unsigned char fndOn[4] = {0x01, 0x02, 0x04, 0x08}; // PORTG용
unsigned int cnt = 0;
unsigned char fndDispval[4]; // 디스플레이 표시 함수 PORTG, PORTC이용

void main()
{
    DDRC = 0xFF;
    DDRG = 0x0F;
    // 초기상태 0000이 출력 되도록 한다.
    fndDispval[0] = fnd[0];
    fndDispval[1] = fnd[0];
    fndDispval[2] = fnd[0];
    fndDispval[3] = fnd[0];
    
    while(1)
    {
        delay_ms(1); // 1ms마다 반복되도록 실행
        ++cnt; // 1ms마다 1씩 증가
        // 1ms마다 2개의 함수를 호출
        DisplayHex(); // 값을 갱신 시키는 함수
        FndControl(); // 값을 뿌리는 함수
    }
}

void DisplayHex() // 10진수 -> 16진수로 변경하는 곳
{
    static unsigned int num = 0;
    if((cnt%60) == 0) // <---------------------------------- 값을 갱신 시키는 속도 (1000이면 1초에 1씩증가)
    {
        num++;
        fndDispval[0] = fnd[(num/1)%16];    // 1의자리    num/(16^0)%16
        fndDispval[1] = fnd[(num/16)%16];   // 10의자리   num/(16^1)%16
        fndDispval[2] = fnd[(num/256)%16];  // 100의자리  num/(16^2)%16
        fndDispval[3] = fnd[(num/4096)%16]; // 1000의자리 num/(16^3)%16
    }
}

void FndControl()
{
    static unsigned char pos = 0; // 0.005초마다 출력되는 포트c,g값바꾸기 위함
    
    if(cnt % 5 != 0) // 5ms가 될 때마다 실행
        return; // 5의 배수가 아니면 탈출
    PORTG = 0; // 잔상을 확실히 끄기 위함
    PORTC = fndDispval[pos]; // 출력할 숫자
    PORTG = fndOn[pos]; // 어느 세그먼트에 출력할지
    pos = (++pos) % 4; // 5ms마다 1씩증가 따라서 4개의 세그먼트를 다 도는데 20ms가 걸린다.
}
*/

/*
//------------------------------------------------------------------------------------------------------------------------------------------------------
// 버튼으로 FND값 증감 시키기 + k값이 0이면 HELO출력 시키기
#include <io.h>
#include <delay.h>

// void DisplayHex(); // 필요없음
void sw2Display(); // 스위치2를 누르면 갱신되는 함수
void FndControl();
void checkKeyIn(char *pSw1, char *pSw2); // call by reference

unsigned char fnd[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, // 10진수 0~9
                        0x77, 0x7c,0x39, 0x5e, 0x79, 0x71};                          // 16진수 abcdef
unsigned char fndOn[4] = {0x01, 0x02, 0x04, 0x08}; // PORTG용
unsigned char fndDispval[4]; // FndControl함수에서 사용, 디스플레이 표시 함수 PORTG, PORTC이용 
unsigned char HELO[4] = {0x3f, 0x38, 0x79, 0x76}; // 세그먼트에 helo를 표시시키는 배열
unsigned int cnt = 0;
unsigned int k = 0; // 세그먼트에 출력시킬 숫자

void main()
{
    char sw1, sw2; // sw2DisplayHex 함수용 스위치 변수

    DDRC = 0xFF;
    DDRG = 0x0F;
    // 초기상태 HELO가 출력 되도록 한다.
    fndDispval[0] = HELO[0]; // O: 0x3f
    fndDispval[1] = HELO[1]; // L: 0x38
    fndDispval[2] = HELO[2]; // E: 0x79
    fndDispval[3] = HELO[3]; // H: 0x76
    
    while(1)
    {
        delay_ms(1); // 1ms마다 반복되도록 실행
        ++cnt; // 1ms마다 1씩 증가
        
        if((cnt%20) == 0)
        {
            checkKeyIn(&sw1, &sw2); // 스위치 추가! 버튼 눌러짐을 감지
            if(sw2 == 1) // sw2를 누를 때마다 k값을 증가시킨다.
                k++;
            else if(sw1 == 1) // k값을 빼면 (2^16)-1인 65535가 뜨는데 6이 잘려서 5535가 뜬다.
                k--; 
        }
        
        // 1ms마다 2개의 함수를 호출
        sw2Display(); // 스위치 추가로 인한 변경! 값을 갱신 시키는 함수
        FndControl(); // 값을 뿌리는 함수
    }
}

void sw2Display() // 스위치 추가! sw2를 누르때마다 값을 증가
{
    if(k == 0) // 0인상태에서는 HELO가 출력
    {
        fndDispval[0] = HELO[0];
        fndDispval[1] = HELO[1];
        fndDispval[2] = HELO[2];
        fndDispval[3] = HELO[3];
    }
    else // K값이 0이 아니면 숫자를 출력 시킨다.
    {
        fndDispval[0] = fnd[(k/1)%10];    // 1의자리    k/(10^0)%10
        fndDispval[1] = fnd[(k/10)%10];   // 10의자리   k/(10^1)%10
        fndDispval[2] = fnd[(k/100)%10];  // 100의자리  k/(10^2)%10
        fndDispval[3] = fnd[(k/1000)%10]; // 1000의자리 k/(10^3)%10
    }
}

void FndControl() // fnd에 값을 뿌려줌
{
    static unsigned char pos = 0; // 0.005초마다 출력되는 포트c,g값바꾸기 위함
    
    if(cnt % 5 != 0) // 5ms가 될 때마다 실행
        return; // 5의 배수가 아니면 탈출
    PORTG = 0; // 잔상을 확실히 끄기 위함
    PORTC = fndDispval[pos]; // 출력할 숫자
    PORTG = fndOn[pos]; // 어느 세그먼트에 출력할지
    pos = (++pos) % 4; // 5ms마다 1씩증가 따라서 4개의 세그먼트를 다 도는데 20ms가 걸린다.
}


void checkKeyIn(char *pSw1, char *pSw2) 
{
    static unsigned char swRead_1, swRead_2;
    swRead_1 = swRead_1 << 1; // 스위치1 
    if(PINE.4) // 스위치를 누르지 않은 상태(1)이라면 참
        swRead_1 |= 0x01; // 0.16초만에 swRead_1은 0xFF가 된다.  
    swRead_2 = swRead_2 << 1; // 스위치2
    if(PINE.5)
        swRead_2 |= 0x01;
            
    if((swRead_1 & 0x0F) == 0x0E) // 스위치1을 누르는 순간 위에서 OR연산이 안일어 나므로 swRead_1은 2ms만에 0xFE가 된다.           
        *pSw1 = 1;             
    else           
        *pSw1 = 0; // 2ms가 또지나면 다시 0으로  
    if((swRead_2 & 0x0F) == 0x0E) // 스위치2 
       *pSw2 = 1;    
    else
        *pSw2 = 0;  
}
*/

//-------------------------------------------------------------------------------------------------------------------------------------------
// 통합한것
#include <io.h>
#include <delay.h>

void DisplayHex(); // 16진수 출력함수 mode0
void DisplayDec(); // 10진수 출력함수 mode1
void sw2Display(); // 스위치 제어 함수 mode2
void HeloDisplay(); // HELO출력 함수 mode3
void FndControl(); // FND출력용 함수
void checkKeyIn(char *pSw1, char *pSw2); // call by reference
unsigned char fndDec[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 10진수 출력 배열
unsigned char fndHex[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,0x77, 0x7c,0x39, 0x5e, 0x79, 0x71}; // 16진수 출력 배열
unsigned char fndOn[4] = {0x01, 0x02, 0x04, 0x08}; // PORTG용
unsigned char fndDispval[4]; // FndControl함수에서 사용, 디스플레이 표시 함수 PORTG, PORTC이용 
unsigned char HELO[4] = {0x3f, 0x38, 0x79, 0x76}; // 세그먼트에 helo를 표시시키는 배열
unsigned int cnt = 0, k = 0; // 시간에따라 증가, 누른 횟수에 따라 증가

void main()
{
    char sw1, sw2; // sw2DisplayHex 함수용 스위치 변수
    char mode = 0; // sw1을 누르면 모드가 변하도록

    DDRC = 0xFF;
    DDRG = 0x0F;
    // 초기상태 HELO가 출력 되도록 한다.
    fndDispval[0] = HELO[0]; // O: 0x3f
    fndDispval[1] = HELO[1]; // L: 0x38
    fndDispval[2] = HELO[2]; // E: 0x79
    fndDispval[3] = HELO[3]; // H: 0x76
    
    while(1)
    {
        delay_ms(1); // 1ms마다 반복되도록 실행
        ++cnt; // 1ms마다 1씩 증가
        
        if((cnt%20) == 0) // 20ms마다 체크키인 함수 실행, 버튼 누름 감지
        {
            checkKeyIn(&sw1, &sw2);
            if(sw1 == 1)
            {
                mode = (++mode)%5; // 0 1 2 3 4 으로 총 5가지의 모드가 있다.
            }
            if(sw2 == 1) 
            {
               if(mode == 2) // 모드2인 상태에서 스위치가 눌리면 k값이 증가
                k++;
               else if(mode == 3) // 모드3인 상태에서 눌리면 k값이 감소
               {
                if(k == 0)
                    k = 9999; // unsigned int 0에서 1이 감소하면 65535[(2^16)-1]를 표시해버린다.
                else
                    k--;
               }
            } 
        }
        /*
        // else if 문으로 만드는 방법 (비효율적: 맞는지 틀린지 계속 확인한다)
        if(mode == 0)
            DisplayHex();
        else if(mode == 1)
            DisplayDec();
        else if(mode == 2 || mode == 3) // 모드가 2이거나 3이면 스위치디스플레이 함수를 호출
            sw2Display();
        else if(mode == 4)
            HeloDisplay();
        */
        
        // switch case 문으로 만드는 방법 (효율적: 아니면 바로 탈출해버린다)   
        switch(mode)
        {
            case 0:
                DisplayHex(); // 16진수모드
                break;
            case 1:
                DisplayDec(); // 10진수모드
                break;
            case 2:
                sw2Display(); // 버튼 증가모드
                break; 
            case 3:
                sw2Display(); // 버튼 감소모드 !! 추가기능 !!
                break; 
            case 4:
                HeloDisplay(); // HELO 모드
                break;     
        }     
        FndControl(); // 값을 뿌리는 함수
    }
}

void DisplayHex() // mode0 16진수로 출력
{
    static unsigned int numHex = 0; // num이라고 값을 통일해도 스태틱 변수이기에 동일하다.
    if((cnt%200) == 0) // <--------------------------------------------- 갱신속도
    {
        numHex++;
        fndDispval[0] = fndHex[(numHex/1)%16];    // 1의자리    numHex/(16^0)%16
        fndDispval[1] = fndHex[(numHex/16)%16];   // 10의자리   numHex/(16^1)%16
        fndDispval[2] = fndHex[(numHex/256)%16];  // 100의자리  numHex/(16^2)%16
        fndDispval[3] = fndHex[(numHex/4096)%16]; // 1000의자리 numHex/(16^3)%16
    }
}

void DisplayDec() // mode1 10진수 출력
{
    static unsigned int numDec = 0;
    if((cnt%200) == 0) // <--------------------------------------------- 갱신속도
    {
        numDec++;
        fndDispval[0] = numDec[(numDec/1)%10];    // 1의자리    numDec/(10^0)%10
        fndDispval[1] = numDec[(numDec/10)%10];   // 10의자리   numDec/(10^1)%10
        fndDispval[2] = numDec[(numDec/100)%10];  // 100의자리  numDec/(10^2)%10
        fndDispval[3] = numDec[(numDec/1000)%10]; // 1000의자리 numDec/(10^3)%10
    }
}

void sw2Display() // mode2 sw2를 누르때마다 값을 증가
{                 // mode3 sw1를 누르때마다 값이 감소
    fndDispval[0] = fndDec[(k/1)%10];    // 1의자리    k/(10^0)%10
    fndDispval[1] = fndDec[(k/10)%10];   // 10의자리   k/(10^1)%10
    fndDispval[2] = fndDec[(k/100)%10];  // 100의자리  k/(10^2)%10
    fndDispval[3] = fndDec[(k/1000)%10]; // 1000의자리 k/(10^3)%10
}

void HeloDisplay() // mode4 HELO출력
{
    fndDispval[0] = HELO[0];
    fndDispval[1] = HELO[1];
    fndDispval[2] = HELO[2];
    fndDispval[3] = HELO[3];
}

void FndControl() // fnd에 값을 뿌려주는 함수
{
    static unsigned char pos = 0; // 0.005초마다 출력되는 포트C, G값바꾸기 위함
    
    if(cnt % 5 != 0)         // 5ms가 될 때마다 실행
        return;              // 5의 배수가 아니면 탈출하기 때문
    PORTG = 0;               // 잔상을 확실히 끄기 위함
    PORTC = fndDispval[pos]; // PORTC 출력할 숫자
    PORTG = fndOn[pos];      // PORTG 출력할 포드
    pos = (++pos) % 4;       // 5ms마다 1씩증가, 20ms면 세그먼트 4개를 한바퀴 돈다.
}


void checkKeyIn(char *pSw1, char *pSw2) // 스위치 제어용 함수
{
    static unsigned char swRead_1, swRead_2;
    swRead_1 = swRead_1 << 1; // 스위치1 
    if(PINE.4)                // 스위치를 누르지 않은 상태(1)이라면 참
        swRead_1 |= 0x01;     // 0.16초만에 swRead_1은 0xFF가 된다.  
    swRead_2 = swRead_2 << 1; // 스위치2
    if(PINE.5)
        swRead_2 |= 0x01;
            
    if((swRead_1 & 0x0F) == 0x0E) // 스위치1을 누르는 순간 위에서 OR연산이 안일어 나므로 swRead_1은 2ms만에 0xFE가 된다.           
        *pSw1 = 1;                // 0xFE & 0x0F = 0x0E             
    else           
        *pSw1 = 0;                // 2ms가 또지나면 다시 0으로  
    if((swRead_2 & 0x0F) == 0x0E) // 스위치2 
       *pSw2 = 1;    
    else
        *pSw2 = 0;  
}