// 반도체전자과 2614110179 조예찬
#include <io.h>
#include <delay.h>

unsigned char digit[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, // 0~9
                           0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x80};                  // a~e, dp 
                        // 0~9랑 a~e, 도트까지의 출력을 배열로 작성, 8비트이므로 char면 충분

unsigned char sec = 5; // 딜레이값 고정 모든화면 번갈아가며 출력할때 5m초 정도면 우리가 인지를 못한다.
unsigned char digit_09[11] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x3f}; // 01234567890 반복

// 4배열 코드
unsigned char fndOn[4] = {0x01, 0x02, 0x04, 0x08}; // fnd출력을 위한 포트G제어용
unsigned char fnd_1[13] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x3f, 0x3f, 0x3f}; // 0123456789000
unsigned char fnd_2[13] = {0x3f, 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x3f, 0x3f}; // 0012345678900
unsigned char fnd_3[13] = {0x3f, 0x3f, 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x3f}; // 0001234567890
unsigned char fnd_4[13] = {0x3f, 0x3f, 0x3f, 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67}; // 0000123456789

void main()
{
    int i = 0;
    int j = 0;
    DDRC = 0xFF; // 포트C는 모든핀을 출력으로
    DDRG = 0x0F; // 포트G는 하위4핀만 출력으로
    // PORTC = 0x3F; // 세그먼트에 0을 출력시킨다 
    // PORTG = 0x01; // 가장우측 01 02 04 08로 가면 한칸씩 왼쪽으로 이동
    
    /* // 장난치기
    PORTC = 0x3f; // xxx0
    PORTG = 0x01;
    delay_ms(100);
            
    PORTC = 0x06; // xx1x
    PORTG = 0x02;
    delay_ms(100);
            
    PORTC = 0x5b; // x2xx
    PORTG = 0x04;
    delay_ms(100);
            
    PORTC = 0x4f; // 3xxx
    PORTG = 0x08;
    delay_ms(100);
            
    PORTC = 0x66; // xx44
    PORTG = 0x03;
    delay_ms(100);
            
    PORTC = 0x6d; // x55x
    PORTG = 0x06;
    delay_ms(100);
            
    PORTC = 0x7c; // 66xx
    PORTG = 0x0c;
    delay_ms(100);
            
    PORTC = 0x07; // x7x7
    PORTG = 0x05;
    delay_ms(100);
            
    PORTC = 0x7f; // 8x8x
    PORTG = 0x0a;
    delay_ms(100);
            
    PORTC = 0x67; // 9999
    PORTG = 0x0f;
    delay_ms(100);
    */
    
    /* // 3210 동시에 표시시켜보기        
    while(1)
    {
        PORTC = 0x3f; // xxx0
        PORTG = 0x01;
        delay_ms(sec);
                
        PORTC = 0x06; // xx1x
        PORTG = 0x02;
        delay_ms(sec);
                
        PORTC = 0x5b; // x2xx
        PORTG = 0x04;
        delay_ms(sec);
                
        PORTC = 0x4f; // 3xxx
        PORTG = 0x08;
        delay_ms(sec);    
    }
    */
    
    /* // 0~9, a~e, dp 출력시키기
    PORTG = 0x01; // 가장우측 세그먼트부터 출력할것이라 0001로 시작
    while(1)
    {
        for(j=0; j<4; j++) // 출력되는 세그먼트를 한칸씩 왼쪽으로 이동시키는것 세그먼트가 4개이므로 4회 반복
        {
            for(i=0; i<17; i++) // 0 1 2 3 4 5 6 7 8 9 a b c d e dp 까지 총 17회 반복
            {
            PORTC = digit[i]; // 세그먼트에 i를 출력 (반복된 횟수에 해당하는 수)
            // PORTG = fndOn[j]; // 세그먼트에 j출력(이걸 쓰려면 폴문 바깥쪽 오프시키기)
            delay_ms(100);
            }
        PORTG = PORTG << 1; // 0~dp까지 완주하면 한칸 왼쪽의 세그먼트를 출력시킴    
        }
        PORTG = 1; // 4바퀴 돌면 처음부터
    } 
    */
    
    /*
    // 0000 0001 0012 0123 1234 ... 로 계속 반복하기 (엄청 이상하게 만든버전)
    PORTG = 0x0F; // 모두출력
    while(1)
    {   
        for(j=-3; j<11; j++) // -3 ~ 11 까지 반복
        {
            for(i=0; i<50; i++) // 20*50은 1초
            {
                PORTC = digit_09[j];
                PORTG = 0x08;
                delay_ms(4);
                
                PORTC = digit_09[j+1];
                PORTG = 0x04;
                delay_ms(4);
                
                PORTC = digit_09[j+2];
                PORTG = 0x02;
                delay_ms(4);
                
                PORTC = digit_09[j+3];
                PORTG = 0x01;
                delay_ms(4);
                
                if(j==-3)
                {
                    PORTG = 0x0e;
                    PORTC = 0x3f;
                    delay_ms(4);
                }
                else if(j==-2)
                {
                    PORTG = 0x0c;
                    PORTC = 0x3f;
                    delay_ms(4);
                }                
                else if(j==-1)
                {
                    PORTG = 0x08;
                    PORTC = 0x3f;
                    delay_ms(4);
                }                
                else if(j==8)
                {
                    PORTG = 0x01;
                    PORTC = 0x3f;
                    delay_ms(4);
                }                
                else if(j==9)
                {
                    PORTG = 0x03;
                    PORTC = 0x3f;
                    delay_ms(4);
                }                
                else if(j==10)
                {
                    PORTG = 0x07;
                    PORTC = 0x3f;
                    delay_ms(4);
                }
            } 
        }   
    }
    */
    
    // 배열 4개를 이용한 방법
    while(1)
    {
        for(i=0; i<13; i++) // 1바퀴돌때마다 배열4개로 한칸씩 이동하게 한다.
        {
            for(j=0; j<25; j++) // 20ms가 50번 반복 = 1초  j값을 수정해서 빠르기를 조절 할 수 있다.
            {
                PORTC = fnd_1[i]; // 0123456789000
                PORTG = fndOn[0]; // 가장오른쪽 출력
                delay_ms(5); // 잔상출력을 위해 5ms만 출력
                
                PORTC = fnd_2[i]; // 0012345678900
                PORTG = fndOn[1]; // 우측에서 2번째 출력
                delay_ms(5);
                
                PORTC = fnd_3[i]; // 0123456789000
                PORTG = fndOn[2]; // 우측에서 3번째 출력
                delay_ms(5);
                
                PORTC = fnd_4[i]; // 123456789000
                PORTG = fndOn[3]; // 가장왼쪽 출력
                delay_ms(5);
            }
        }
    }
}