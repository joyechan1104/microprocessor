
#include <io.h>
#include <delay.h>

int i = 0, s = 0;
int turn_on = 0xFF; // 일단 전부 점등되게 상행
int blink = 0x7F; // 최상위만 깜빡이게(오프시킨다)
int next_on = 0xFF; // 일단 전부 점등되게 하행
int next_blink = 0xFE; // 최하위만 깜빡이게(오프시킨다)  
int sec = 500; 

void main()
{
    DDRA = 0xFF; 
    while(1) 
    {   
        // 왕(상행)
        PORTA = 0xFF; // 일단 모두 점등되는걸 확인
        delay_ms(500);
        turn_on = 0xFF;
        blink = 0x7F;
        
        for(s=0; s<8; s++)
        {   
            for(i=0; i<3; i++)
            {
                PORTA = blink; // 먼저 최상위 1칸을 깜빡이게 한다
                delay_ms(sec);
                PORTA = turn_on; // 그리고 다시 모두 점등시킨다
                delay_ms(sec);   // 모두 켜진상태에서 최상위만 깜빡거림
                // 이걸 n번 만큼 반복하면 탈출        
            }
            turn_on = turn_on >> 1; // 모두 점등되는 비트를 한칸 오른쪽으로 그럼 최상위는 안켜짐
            blink = blink >> 1; // 마찬가지로 점멸되는 비트도 한칸 오른쪽으로 옮기면 최상위 다음 비트가 깜빡임
            // 총 n번 반복되면 종료               
        }
        
        // 복(하행)
        PORTA = 0xFF; // 일단 모두 점등되는걸 확인
        delay_ms(500);
        next_on = 0xFF;
        next_blink = 0xFE;
        
        for(s=0; s<8; s++)
        {   
            for(i=0; i<3; i++)
            {
                PORTA = next_blink; // 먼저 최하위 1칸을 오프시켜서 깜빡이게 한다
                delay_ms(sec);
                PORTA = next_on; // 그리고 모두다시킨다
                delay_ms(sec);
                // 총 n번 반복되면 탈출           
            }
            next_on = next_on << 1; // 전부 온 되는 비트를 한칸 왼쪽으로 옮기면 최하위는 항상 오프
            next_blink = next_blink << 1; // 깜빡이는 비트도 왼쪽으로 옮기니 최하위다음비트가 깜빡임                 
        }
    }    
}