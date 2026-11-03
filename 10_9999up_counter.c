// 반도체 전자과 2614110179 조예찬
// 세그먼트 a b c d e f g dp 순서대로 표시하기
#include <io.h>
#include <delay.h>

void main()
{
    unsigned char buff = 1;
    int i=0, j=0;

    DDRC = 0xFF; // 포트C를 모두 출력으로
    DDRG = 0x0F; // 포트G 하위 4비트를 출력으로
    PORTG = 0x01; // 처음은 가장 우측 세그먼트만 표시
    
    while(1)
    {   
        // 방법1 if문 활용 둘중하나 주석처리 하고 사용
        PORTC = buff;
        delay_ms(50);
        buff = buff << 1; // 5ms가 지나면 a b c d e f g dp 순으로 표시되게 한다.
        if(buff == 0) // 만약 dp다음으로가서 버프가 0이 되면
        {
            buff = 0x01; // 버프를 다시 a가 출력되도록하고
            PORTG = PORTG << 1; // 다음 세그먼트에 한바퀴돌도록
            if(PORTG == 0x10) // 4개의 세그먼트를 다 돌면
                PORTG = 0x01; // 다시 가장 우측 세그먼트부터 표시되도록 한다.
        }
        
        // 방법2 for문 활용 둘중하나 주석처리 하고 사용
        
        for(i=0; i<4; i++)
        {
            for(j=0; j<8; j++)
            {
                PORTC = 0x01 << j; // 돌떄마다 a b c d e f g dp순으로 
                PORTG = 0x01 << i; // j가 한바퀴돌면 다음 세그먼트 신호선에 출력
                delay_ms(50);  
            }
        }
            
    }
}

// 배열을 이용한 방법
#include <io.h>
#include <delay.h>

void main()
{
    int i=0;
    unsigned char buff;
    unsigned char fnd_sel[4] = {0x01, 0x02, 0x04, 0x08}; // 포트G 출력
    
    DDRC = 0xFF;
    DDRG = 0x0F;
    
    buff = 0x01; // 버프 초기값을 1로 설정
    
    while(1)
    {
        delay_ms(50);
        PORTC = buff;
        PORTG = fnd_sel[i]; // 포트G는 배열을 대입
        buff = buff << 1; // 50ms마다 출력되는 LED를 변경 00000001(a) -> 00000010(b) ... 
        if(buff == 0) // 만약 10000000에서 한번더 << 되면 0이 된다.
        {
            buff = 0x01; // 버프를 1로 초기화시키고
            i = (++i % 4); // 1%4 = 1, 2%4 = 2, 3%4 = 3, 4%4 = 0, 5%4 = 1... 
            // 한사이클마다 i값이 증가 하는데 4로나누면 0이되고 나머지로 1씩 증가시키게 만든다.
        }
    }    
}

// 레이저빔 쏘기
#include <io.h>
#include <delay.h>

void main()
{
    int i=0, j=0;
    unsigned char beam[3] = {0x01, 0x40, 0x08};
    unsigned char fnd_sel[4] = {0x08, 0x04, 0x02, 0x01}; // 포트G 출력
    
    DDRC = 0xFF;
    DDRG = 0x0F;
        
    while(1)
    {
        delay_ms(50);
        PORTC = beam[i];
        PORTG = fnd_sel[j];
        j++; // 50ms 마다 출력되는 세그먼트를 한칸씩 왼쪽으로
        if(j == 4) // 가장왼쪽 세그먼트에 출력이 되고 한바퀴더돌면
        {
            j = 0; // fnd_sel[]을 다시 0으로 초기화 
            i = (++i % 3); // i를 추가하고 3으로 나눈값의 나머지를 beam[]에 대입
        }   
    }    
}

// 9999진 업 카운터
#include <io.h>
#include <delay.h>

unsigned char FND_num[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 0~9까지의 숫자
unsigned char FND_on[4] = {0x08, 0x04, 0x02, 0x01}; // PORTG 출력용 천의자리를 먼저뿌리기 위해 0x08부터 시작
unsigned int up9999 = 0; // 0~9999까지 올라가는 변수
unsigned int delayTime = 20; // <------------------------------------------------------------- 이시간 마다 up카운트 된다. 최소20부터 20의 배수

void segment_num(int num, int ms) // num 4자리에 출력할 숫자,  ms 유지시킬 시간
{
    int i=0, j=0;
    unsigned char FND_value[4]; //    천[0],    백[1],    십[2],   일[3]의 자리에 들어갈 숫자를 배열로 저장, 지역변수
    // PORTG와 PORTC의 자릿수를 통일 시킨다. 0x08[0], 0x04[1], 0x02[2], 0x01[3]
    FND_value[0] = FND_num[(num/1000) % 10]; // 2345/1000 = 2, 2%10 = 0 ... 2       천의자리 추출
    FND_value[1] = FND_num[(num/100) % 10];  // 2345/100 = 23, 23%10 = 2 ... 3      백의자리 추출
    FND_value[2] = FND_num[(num/10) % 10];   // 2345/10 = 234, 234%10 = 23 ... 4    십의자리 추출 
    FND_value[3] = FND_num[num % 10];        // 2345%10 = 234 ... 5                 일의자리 추출
    
    for(i=0; i<(ms/20); i++) // 내부 j폴문이 반복되는 시간으로 나눈수 만큼 실행, ms변수가 1000이면 1000/20 = 50회 반복
    {
        for(j=0; j<4; j++) // 4회반복 * 5ms딜레이 = 20ms의 딜레이 발생, 20ms가 50회 반복되므로 20*50=1000ms 따라서 함수는 1000ms동안 실행된다.
        {
            PORTC = FND_value[j]; // 출력되는 숫자: loop1 천의자리, loop2 백의자리, loop3 십의자리, loop4 일의자리   
            PORTG = FND_on[j];    // 제어신호 위치: loop1 천의자리, loop2 백의자리, loop3 십의자리, loop4 일의자리  
            delay_ms(5);
            PORTG = 0x00; // 잔상방지를 위한 off
        }
    }
} 

void main()
{
    DDRC = 0xFF;
    DDRG = 0x0F;
    
    while(1)
    {   
        segment_num(up9999, delayTime); // 4자리에 무슨 숫자를 출력할지?, 한사이클에 몇ms동안 표시하게 할지?
        ++up9999; // 함수 실행 할때마다 1씩 증가 
        if(up9999 == 10000)
            up9999 = 0; // 9999다음에 0000이 나오게함
    }
}

// 교수님 수업
#include <io.h>
#include <delay.h>

void DisplayDec();
void FndControl();

unsigned char fnd[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
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
        DisplayDec();
        FndControl();
    }
}

void DisplayDec()
{
    static unsigned int num = 0;
    if((cnt%1000) == 0) // 1초마다 값을 갱신 시킨다.
    {
        num++;
        fndDispval[0] = fnd[num%10]; // 1의 자리에 1234 % 10 = 123 ... 4를 대입
        fndDispval[1] = fnd[(num/10)%10]; // 10의자리에 1234 / 10 = 123.4, 123 % 10 = 12 ... 3을 대입
        fndDispval[2] = fnd[(num/100)%10]; // 100의자리에 1234 / 10 = 12.34, 12 % 10 = 1 ... 2을 대입
        fndDispval[3] = fnd[(num/1000)%10]; // 1000의자리에 1234 / 10 = 1.234, 1 % 10 = 0 ... 1을 대입
    }
}

void FndControl()
{
    static unsigned char pos = 0; // 0.005초마다 출력되는 포트c,g값을 올리기 위함
    
    if(cnt % 5 != 0) // 5ms가 될 때마다 실행
        return; // 5의 배수가 아니면 탈출
    PORTG = 0; // 잔상을 확실히 끄기 위함
    PORTC = fndDispval[pos]; // 출력할 숫자
    PORTG = fndOn[pos]; // 어느 세그먼트에 출력할지
    pos = (++pos) % 4; // 5ms마다 1씩증가 따라서 4개의 세그먼트를 다 도는데 20ms가 걸린다.
}