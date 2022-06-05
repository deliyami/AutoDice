// 0번이랑 1번핀은 상시 켜져있어서 지금 의도랑은 안 될것 같다
/*
 * 가능성이 3가지 정도 있다
 * 1. 4, 5, 6번 버튼 전부 같은 기능?하게 해서 4->5->6->4... 이런식으로 하는 방식으로 하고 팬을 어느 핀에다 연결
 * 2. 4, 5, 6번 버튼 전부 같은 기능으로 하는데, 시나리오에 맞게 작동하도록 할거야... ex) 처음 4->6->5->6->... 반복, 3개 버튼 전부 같은기능... 이건 시나리오에 맞게 흘러가도록 코딩해놓으면 됨<- 발표나 영상 찍기전에 순서 정해주면 됨
 * 3. 4, 5, 6번 버튼 중에 하나 제거 or 다른 버튼이랑 기능 겹치게 하던가... 그런식으로 해서 0번 핀이랑 n번 핀이랑 꽂고 둘 다 high로 해서 정지, n번 핀 low로 해서 작동... ex) 4번은 4번, 5랑 6은 5,6 이렇게 되면 5번만 눌러도 5->6->5->6, 6번만 눌러도 5->6->5->6
*/

int leds[] = {2, 3, 4, 5, 6, 7, 8}; // 지정된 7세그먼트 led 개수
int led_num = 7; // 7세그먼트 led 
int button4 = 10; // 4인용 버튼
int button5 = 11; // 5인용 버튼
int button6 = 12; // 6인용 버튼
int main_button = 13; // 택트 스위치 핀번호
int mode = 4; // 현재 LED에 사용 될 유저의 수 모드
int num = 0;  // 현재 LED에 표시되고 있는 숫자
int INA = 9; // 원래 dp꽂는 곳, 근데 dp(점)자체가 필요없어서 뺌
int INB = 0; // 통신, 항상 HIGH상태
// INA랑 INB 둘 다 HIGH로 끄고 INA를 LOW해서 작동
 
int set_number[10][7] = {  // 각 숫자에 대한 LED 설정 값을 정의.
//{b,a,c,d,e,g,f} 이거는 꽂을 떄 마다 확인해봐야 됨
  {1,1,1,1,1,0,1}, // 0
  {1,0,1,0,0,0,0}, // 1
  {1,1,0,1,1,1,0}, // 2
  {1,1,1,1,0,1,0}, // 3
  {1,0,1,0,0,1,1}, // 4
  {0,1,1,1,0,1,1}, // 5
  {0,1,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}, // 9
};
void setup() { // 시작하는 곳

  for (int i = 0 ; i < sizeof(leds) ; i++) {    // 7세그먼트 led에 연결된 핀을 출력으로 설정
    pinMode(leds[i], OUTPUT);
  }
  pinMode(main_button, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("this is setup test");
  pinMode(main_button, INPUT_PULLUP);    // 택트 스위치를 input_pullup으로 설정
}
/**
 * @param int btn 버튼의 pin
 * 
 * 사용법
 * change_mode(버튼 변수); <- n버튼이 눌렀을 때 n명의 모드가 됨
*/
void change_mode(int btn){ 
  if(digitalRead(btn) == HIGH){     // 버튼이 한번 눌릴때마다 7세그먼트 숫자가 하나씩 올라감
    mode = btn - 6;
    Serial.println("change mode " + mode);
  }
}
 
void loop() { // 반복하는 곳

  
  
  if(digitalRead(main_button) == HIGH){     // 버튼이 한번 눌릴때마다 7세그먼트 숫자가 하나씩 올라감
    Serial.println("here is main button");
    num ++;
    // fan코드가 들어갈 장소... 어떻게 작동하는지 모름
  }
  
  if(num > mode) num = 1;
  change_mode(button4);
  change_mode(button5);
//  change_mode(button6); // 주석처리 앞에 슬러시 두개된거는 버튼 하나 더 추가하고.. 버튼이 없으니까 무조건 실행이 됨... == 무조건 6인용됨...
  
  for (int j = 0 ; j < led_num ; j++) {      // 7 세그먼트 LED 출력
      digitalWrite(leds[j], set_number[num][j]);
  }

  if(digitalRead(main_button) == HIGH){
    digitalWrite(INA, LOW);
    digitalWrite(INB, HIGH);
    // 무한 반복
    while(true){
      if(digitalRead(main_button) == LOW) {
        digitalWrite(INA, HIGH);
        digitalWrite(INB, HIGH);
        break;
      }
    }
  }
  
  delay(150);    
}