// 반도체전자과 2614110179 조예찬
// 예제 1. SW1을 누르면 현재 값이 1 감소하면서 16진수로 표현되고, SW2를 누르면 현재
// 값에서 1 이 증가되면서 10진수로 값이 표현됨.
/*
#include <io.h>
#include <delay.h>

void CheckKeyIn(char *pSw1, char *pSw2);
void FndControl();
unsigned int cnt = 0;
void PutDecimal(unsigned short inVal);
void PutHexadecimal(unsigned short inVal);
unsigned char fndDispVal[4]; // fnd에 표시시킬 숫자
const unsigned char fndHexDisp[16] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F, // 0~9
                                       0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};                        // A~F

void main(void)
{
    char sw1, sw2;
    unsigned int i = 0; // 폴문용
    unsigned short val = 0;

    DDRC = 0xFF;
    DDRG = 0x0F;
    
    for(i = 0; i < 4; i ++) // 초기상태 0000으로 만들기(1회만실행)
    {
        fndDispVal[i] = fndHexDisp[0]; // 0x3f를 fndDispVal의 [0]~[3]에 채워넣기
    }
    
    while (1)
    {
        delay_ms(1);
        ++ cnt;
        if ( ( cnt % 20 ) == 0 ) // 20ms마다 실행
        {
            CheckKeyIn(&sw1, &sw2);
            if ( sw1 == 1 ) // 1번스위치 누르면 1감소, 16진수모드
            {
                -- val;
                PutHexadecimal(val); 
            }
            

            if ( sw2 == 1 ) // 2번스위치를 누르면 1증가, 10진수모드         
            {
                ++ val;
                PutDecimal(val);
            }
        }    
        if((cnt%5) == 0 ) // 5ms마다 함수호출
            FndControl();
    }
}

void CheckKeyIn(char *pSw1, char *pSw2)
{
    static unsigned char swRead_1, swRead_2;

    swRead_1 = swRead_1 << 1;
    if ( PINE.4 )
       swRead_1 |= 0x01;
    swRead_2 = swRead_2 << 1;
    if ( PINE.5 )
       swRead_2 |= 0x01;

    if ( (swRead_1 & 0x0F) == 0x0E )
       *pSw1 = 1;
    else
       *pSw1 = 0;
    if ( (swRead_2 & 0x0F) == 0x0E )
       *pSw2 = 1;
    else
       *pSw2 = 0;
}

const unsigned char fndOn[4] = {0x01, 0x02, 0x04, 0x08}; // PORTG 표시용

void FndControl()
{
    static unsigned char pos = 0; // pos변수 숫자유지 FndControl함수에서만 호출가능

    PORTG = 0; // 잔상제거
    PORTC = fndDispVal[pos]; // 포트C에 출력할 숫자정보를 가진 배열을
    if(pos == 2) // 2번쨰에 .을 출력시키기 위함
        PORTC |= 0x80;     
    PORTG = fndOn[pos]; // 포트G에 어느 FND에 출력할지 신호를
    pos = ( ++ pos ) % 4; // 20/4=5 5ms마다 뿌려주는 위치를 바꿈
}

void PutDecimal(unsigned short inVal)
{
    unsigned char i;
    
    for (i = 0; i < 4; i ++)
    {
        fndDispVal[i] = fndHexDisp [ inVal % 10 ];
        inVal = inVal / 10;
    }
}

void PutHexadecimal(unsigned short inVal)
{
    unsigned char i;

    for (i = 0; i < 4; i ++)
    {
        fndDispVal[i] = fndHexDisp [ inVal % 16 ];
        inVal = inVal / 16;
    }
}
*/

//실습 1. SW1을 누르면 FND 값이 0으로 초기화 되면서 stop watch가 동작하기 시작하고
//SW2를 누르면 stop watch가 멈춘다. stop watch는 10 msec 단위로 표시되고, sec 와  /45.67s 이렇게 표시
//msec 값을 구분하기 위하여 FND 2에는 ‘.’ 을 추가 한다.
//[힌트] ‘.’을 추가하기 위해서 FND 2에 값을 보낼 때 PORTC = fndDispVal[pos] | 0x80;

//실습 2. 예제 1 과 같이 SW1을 누르면 현재 값이 1 감소하고, SW2를 누르면 현재 값에서 1
//이 증가되는데, 값을 표시할 때 10진수로만 표시함. + 값은 FND 3에 아무것도 표시하지 않
//고 FND2~0 에만 숫자를 표시하고, - 값은 FND 3에 ‘-’ 표시를 하고, FND2~0 에만 숫자
//를 표시한다.
//[힌트] 값이 ? 일 때는 부호를 정해놓고 값을 + 값으로 바꾼 후 처리함

#include <io.h>
#include <delay.h>

void CheckKeyIn(char *pSw1, char *pSw2);
void FndControl();
unsigned int cnt = 0;
void PutDecimal(unsigned short inVal); // 10진수 출력
void PutHexadecimal(unsigned short inVal); // 16진수 출력
unsigned char fndDispVal[4]; // fnd에 표시시킬 숫자
const unsigned char fndHexDisp[16] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F, // 0~9
                                       0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};                        // A~F

void main(void)
{
    char sw1, sw2;
    unsigned int i = 0; // 폴문용
    unsigned short val = 0; // fnd에 출력시킬 숫자 2345이면 23.45로 출력
    unsigned char mode = 0; // 초기에는 00.00으로 정지상태

    DDRC = 0xFF;
    DDRG = 0x0F;
    
    for(i=0; i<4; i++) // 초기상태 0000으로 만들기(1회만실행)
    {
        fndDispVal[i] = fndHexDisp[0]; // 0x3f를 fndDispVal의 [0]~[3]에 채워넣기
    }
    
    while (1)
    {
        delay_ms(1); // 1ms마다 실행
        ++ cnt; // 1ms마다 카운터값 증가
        if ((cnt%20) == 0) // 20ms마다 CheckKeyIn호출 및 버튼 감지
        {
            CheckKeyIn(&sw1, &sw2); // 버튼누름 감지
            if(sw1 == 1) // 1번스위치 누르면 스톱워치 초기화
            {
                mode = 1; // 모드를 1, 1초에 1씩증가
                val = 0; // 스톱워치 값 초기화 
            }
            if(sw2 == 1)
                mode = !mode; // 0->1, 1->0 누를때마다 0과 1이 반전
            /* 이거 말고 위에 엄청나게 쉬운 방법이.....
            else if(mode == 0 && sw2 == 1) // 모드가 0이면서 스위치2를 누르면 다시실행
                mode = 1;
            else if(mode == 1 && sw2 == 1) // 모드가 1이면서 스위치2를 누르면 일시정지         
                mode = 0;
            */     
        }
        
        if((cnt%10) == 0 && mode == 1) // 모드1 이면서 10ms마다
            ++ val; // 모드가 0이되면 값이 증가를 안한다 == 일시정지
        if((cnt%10) == 0) // 10ms마다 호출
            PutDecimal(val); // val값을 보내줘야 된다.
        if(val == 9999) // 99.99가 되면 강제 일시정지
            mode = 0;  
        if((cnt%5) == 0 ) // 5ms마다 FndControl호출
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

const unsigned char fndOn[4] = {0x01, 0x02, 0x04, 0x08}; // PORTG 표시용

void FndControl() // fnd에 PutDecimal에서 갱신시킨 값을 뿌려주는 함수
{
    static unsigned char pos = 0; // pos변수 숫자유지 FndControl함수에서만 호출가능

    PORTG = 0; // 잔상제거
    PORTC = fndDispVal[pos]; // 포트C에 출력할 숫자정보를 가진 배열
    if(pos == 2) // 2번쨰에 .을 출력시키기 위함
        PORTC |= 0x80;     
    PORTG = fndOn[pos]; // 포트G에 어느 FND에 출력할지 신호를
    pos = (++pos) % 4; // 20/4=5 5ms마다 뿌려주는 위치를 바꿈
}

void PutDecimal(unsigned short inVal) // 10진수 데이터값 갱신
{
    unsigned char i;
    
    for (i=0; i<4; i++)
    {   // 만약 2345라는 값이 inval로 들어왔다고 하면
        fndDispVal[i] = fndHexDisp[inVal%10];
        // 1주기 2345%10 = 5, 2주기 234%10 = 4, 3주기 23%10 = 3, 4주기 2%10 = 2
        inVal = inVal/10;
        // 1주기 2345/10 = 234, 2주기 234/10 = 23, 3주기 23/10 = 2, 4주기는 이미 fndDispVal[i]에 다 들어갔기 때문에 상관없음
        // 1바퀴 돌때마다 inval의 값이 일의자리 십의자리 백의자리 천의자리로 간다.
        // fndDispVal[0] = 5, fndDispVal[1] = 4, fndDispVal[2] = 3, fndDispVal[3] = 2의 값이 대입된다.
    }
}

void PutHexadecimal(unsigned short inVal) // 16진수 데이터값 갱신
{
    unsigned char i;

    for (i=0; i<4; i++)
    {
        fndDispVal[i] = fndHexDisp[inVal%16 ];
        inVal = inVal/16;
    }
}