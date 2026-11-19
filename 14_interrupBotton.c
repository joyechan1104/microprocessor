// 반도체전자과 2614110179 조예찬
#include <io.h>
#include <delay.h>

char num=0;

interrupt [EXT_INT4] void Extlntr4() // 인터럽트 함수 버튼4
{
   PORTA--; // 01 상태에선 누를때와 뗄때 각 1씩 감소됨을 확인가능
}
interrupt [EXT_INT5] void Extlntr5() // 인터럽트 함수 버튼5
{
   PORTA++;
   delay_ms(20); // 00 상태일때 0.02초마다 1씩 증가됨을 확인가능
}

void main(void)
{           
   DDRA = 0xFF;
   PORTA = num;
   SREG = 0x80; // 상태레지스터 최상위 비트를 1로해야 인터럽트 활성화
   EIMSK = 0x30; //  외부 인터럽트 PINE.4, PINE.5를 설정 00110000
   EICRB = 0x01; // 0x01 <- 00000001 이면 핀4는 누를때와 뗄때 핀5는 누르는 동안 인터럽트가 적용된다.
                 // ISC4, ISC5: 00 LOW 상태에서 인터럽트 발생,              0x00: 0000 누르는 동안 계속 인터럽트 발생
                 // ISC4, ISC5: 01 falling, rising edge에서 인터럽트 발생 0x05: 0101 버튼 누를때와 뗄때 인터럽트 발생
                 // ISC4, ISC5: 10 falling edge에서 인터럽트 발생         0x0A: 1010 버튼 누를때 인터럽트 발생
                 // ISC4, ISC5: 11 rising edge에서 인터럽트 발생          0x0F: 1111 버튼을 뗄때 인터럽트 발생
}