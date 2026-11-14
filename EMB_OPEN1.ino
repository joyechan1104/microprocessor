// 임베디드 기능사 공개1
#define sw1 0
#define sw2 1
#define sw3 2
#define R 3
#define G 4
#define B 5

char tsw1=0, tsw2=0, tsw3=0; // toggle sw 포인터 함수는 unsigned치면 전부다 입력해야 하니 귀찮
unsigned int cnt=0; // 카운트세기
unsigned int nowNum = 0;
void RGB_Alloff(); // RGB램프모두끄기
void segment_Alloff(); // 세그먼트램프끄기
void checkKeyIn(char *psw1, char *psw2, char *psw3); // 버튼입력 감지 함수
void decore(char num); // 입력된 숫자를 7447에 뿌려주기
void fastBlink(int num, int ms, int mode); // 숫자를 좌우측 세그먼트에 뿌리기
void up99(); // 동작1
void down99(); // 동작2
void phase(); // 동작3
void reset(); // 초기화동작

void setup()
{
  pinMode(0, INPUT); // SW1 안누르면1
  pinMode(1, INPUT); // SW2 누르면0
  pinMode(2, INPUT); // SW3
  pinMode(3, OUTPUT); // R
  pinMode(4, OUTPUT); // G
  pinMode(5, OUTPUT); // B
  pinMode(6, OUTPUT); // LSB 2^0
  pinMode(7, OUTPUT); // 2^1
  pinMode(8, OUTPUT); // 2^2
  pinMode(9, OUTPUT); // MSB 2^3
  pinMode(10, OUTPUT); // 좌측세그먼트 10의자리
  pinMode(11, OUTPUT); // 우측세그먼트 1의자리
  reset(); // 전원인가시 동작
}

void loop()
{
  fastBlink(nowNum, 10, 0); // 10ms마다 동작 초기화-3
  cnt++;
  if((cnt % 2) == 0) // 20ms마다 실행
  {
    checkKeyIn(&tsw1, &tsw2, &tsw3);
    if(tsw1 == 1)
    {
      tsw1 = 0;
      up99();
    }
    else if(tsw2 == 1)
    {
      tsw2 = 0;
      down99();
    }
    else if(tsw3 == 1)
    {
      tsw3 = 0;
      reset();
    }
  }
}

void RGB_Alloff() 
{
  digitalWrite(R, 0);
  digitalWrite(G, 0);
  digitalWrite(B, 0);
}

void segment_Alloff() 
{
  digitalWrite(10, 0);
  digitalWrite(11, 0);
}

void checkKeyIn(char *psw1, char *psw2, char *psw3)
{
  static unsigned char swRead1, swRead2, swRead3;
  static unsigned char swMode1, swMode2, swMode3; // 처음에 실행을 방지
  swRead1 <<= 1; // 버튼을 누르면 11111110 -> 00000000, 떼면 00000001 -> 11111111
  if(digitalRead(sw1) == 1) // 버튼을 안누르면 0xFF로 
  {
    swRead1 |= 0x01;
    if(swRead1 == 0xFF)
      swMode1 = 1; // 처음실행방지
  }
  if(swMode1 == 1 && swRead1 == 0x01) // 처음 실행을 막음, 버튼을 뗄때!
    *psw1 = 1; // *psw1이 가리키는값 즉 tsw1은 1이된다.

  swRead2 <<= 1; // sw2
  if(digitalRead(sw2) == 1)
  {
    swRead2 |= 0x01;
    if(swRead2 == 0xFF)
      swMode2 = 1; 
  }
  if(swMode2 == 1 && swRead2 == 0x01) 
    *psw2 = 1; 

  swRead3 <<= 1; // sw3
  if(digitalRead(sw3) == 1) 
  {
    swRead3 |= 0x01;
    if(swRead3 == 0xFF)
      swMode3 = 1; 
  }
  if(swMode3 == 1 && swRead3 == 0x01) 
    *psw3 = 1;
}

void decore(char num) // ex.0101 숫자를 디코딩해서 7447에 쏴준다.
{
  digitalWrite(6, (num>>0)&1); // 0101 -> 1
  digitalWrite(7, (num>>1)&1); // 0010 -> 0
  digitalWrite(8, (num>>2)&1); // 0001 -> 1
  digitalWrite(9, (num>>3)&1); // 0000 -> 0
}

void fastBlink(int num, int ms, int mode) // 출력할수, 딜레이시간, 모드(reset, phase: 0, up99: 1, down99: 2)
{
  unsigned int i=0, j=0;
  unsigned char fndValue[2];
  fndValue[0] = (num/1)%10; // 31 ... 1
  fndValue[1] = (num/10)%10; // 31 -> 3
  for(i=0; i<(ms/10); i++) // 한사이클이 10ms
  {
    for(j=0; j<2; j++)
    {
      segment_Alloff(); // 잔상방지
      decore(fndValue[j]);
      digitalWrite(11-j, 1);
      delay(5);
    }
    checkKeyIn(&tsw1, &tsw2, &tsw3); // 10ms마다 누름 감지
    if(tsw1 == 1) // 1번 스위치를 눌렀다 떼면, 모드 0이면 그냥 통과 시키기
    {
      if(mode == 1) // 동작1이면 일시정지
      {
        phase();
        tsw1 = 0; // 안바꾸면 무한 일시정지에 빠짐
      } 
      else if(mode == 2) // 동작2면 패스트 블링크 탈출후 down99로 복귀...
        return;
    }
    if(tsw2 == 1)
    {
      if(mode == 2)
      {
        phase();
        tsw2 = 0;
      }  
      else if(mode == 1)
        return;
    }
  }
}

void up99()
{
  unsigned int i=0;
  RGB_Alloff();
  segment_Alloff();
  fastBlink(88, 2000, 1); // 동작 1-1
  for(i=0; i<100; i++)
  {
    nowNum = i; // 정지시 숫자용
    if(i%2 == 0) // 동작1-2
      digitalWrite(B, 1);
    else
      RGB_Alloff();
    fastBlink(i, 500, 1); // 동작1-3
    if(tsw2 == 1) // 안써주면 5ms채우고 리턴 반복하기를 몇번해서 지직임
      return;
  }
}

void down99() // 모드2로
{
  unsigned int i=0;
  RGB_Alloff();
  segment_Alloff();
  fastBlink(88, 2000, 2); // 동작 2-1
  for(i=100; i>0; i--) // 오버플로우 방지
  {
    nowNum = i-1; // 정지시 숫자용
    if(i%2 == 0) // 동작2-2
      digitalWrite(G, 1);
    else
      RGB_Alloff();
    fastBlink(i-1, 500, 2); // 동작1-3
    if(tsw1 == 1) // 복귀후 다시 탈출
      return;
  }  
}

void phase() 
{
  unsigned int i = 0;
  for(i=0; i<2; i++) // 동작 3-1 현재숫자 2초점등 2초소등 2회반복
  {
    fastBlink(nowNum, 2000, 0); // 동작 3-2 어떤 스위치 입력도 무시
    segment_Alloff();
    delay(2000);
  }
} // 탈출 후 동작은 이어서 하기

void reset()
{
  unsigned int i=0;
  RGB_Alloff();
  segment_Alloff();
  for(i=0; i<2; i++) // 동작 초기화-1 88을 1초점등 1초소등 2회반복
  {
    fastBlink(88, 1000, 0);
    segment_Alloff();
    delay(1000);
  }
  nowNum = 0; // 다음 00을 표시
  for(i=3; i<6; i++) // 초기화동작-2, 3=R, 4=G, 5=B 
  {
    digitalWrite(i, 1);
    fastBlink(nowNum, 1000, 0); 
    RGB_Alloff();
  }
  digitalWrite(R, 1); // 수행완료상태 적색점등
}