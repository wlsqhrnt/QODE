//레이저 센서 적용
//골먹힐 때 라켓 리셋 적용 -> 통신 안되는 문제
//V + PCB Version + PC Software Version + Application Version + Firmware Version
//현재파일  V2_2_2_1
//새로운 변수 정리 완료

#include <DueTimer.h>
#define HORIZONTAL 1
#define VERTICAL 2
#define X 1960
#define Y 2710
#define RACKETSIZE (int)(9*X)/74
#define BALLSIZE (int)(5.5*X)/74
#define RACKETSECTOR (int)RACKETSIZE/15

int startCheck = 0;
volatile char send_buffer[26];
int startAngle;
volatile unsigned char new_receive_buffer[14];
volatile unsigned char old_receive_buffer[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// detail stat variable for check 상시 1 or 0 으로 바뀌며 PC쪽으로 데이터를 수신할때 하는 버퍼값을 정하는 변수 

volatile char serial1InterruptCheck = 0;

// send data variable
volatile char wall_crash = 0; //벽에 부딪힘
volatile char A_return = 0; //A 받아침
volatile char B_return = 0; //B 받아침
char A_get_score = 0; // A 득점
char B_get_score = 0; // B 득점
volatile char completion_of_money_input = 0; // 동전 투입 완료
volatile char single_mode_selection = 0; //라켓 A 모드 싱글 모드 선택
volatile char PVP_mode_selection = 0; //라켓 A 모드 대전 모드 선택

volatile char A_AR_ready = 0;//라켓 A AR 증강 준비 완료
volatile char A_pre_game_selected = 0; //라켓 A 선공게임 완료
volatile char A_use_fireball = 0; //라켓 A 파이어볼 사용
volatile char A_use_tornado = 0; //라켓 A 토네이도 사용
volatile char A_use_hacking = 0; //라켓 A 해킹 사용
volatile char A_use_EMP = 0; //라켓 A EMP사용
volatile char A_use_changeup = 0;//라켓 A change up 사용
volatile char A_use_iceball = 0;//라켓 A 아이스볼 사용
volatile char A_use_mine_1 = 0;//라켓 A 지뢰 1위치 사용
volatile char A_use_mine_2 = 0;//라켓 A 지뢰 2위치 사용
volatile char A_use_mine_3 = 0;//라켓 A 지뢰 3위치 사용
volatile char A_use_defender_1 = 0;//라켓 A 수비수 1위치 사용
volatile char A_use_defender_2 = 0;//라켓 A 수비수 2위치 사용
volatile char A_use_defender_3 = 0;//라켓 A 수비수 3위치 사용
volatile char A_activated_mine_1 = 0;//라켓 A 지뢰 1위치 발동
volatile char A_activated_mine_2 = 0;//라켓 A 지뢰 2위치 발동
volatile char A_activated_mine_3 = 0;//라켓 A 지뢰 3위치 발동
volatile char A_activated_defender_1 = 0;//라켓 A 수비수 1위치 발동
volatile char A_activated_defender_2 = 0;//라켓 A 수비수 2위치 발동
volatile char A_activated_defender_3 = 0;//라켓 A 수비수 3위치 발동
volatile char A_delete_mine = 0; //라켓 A 지뢰 소멸
volatile char A_delete_defender = 0;//라켓 A 수비수 소멸
volatile char A_move_right = 0;// 라켓 A 오른쪽으로 움직임
volatile char A_move_left = 0;//라켓 A 왼쪽으로 움직임
volatile char A_move_stop = 0;//라켓 A 멈춤

volatile char B_AR_ready = 0;//라켓 B AR 증강 준비 완료
volatile char B_pre_game_selected = 0;//라켓 B 선공게임 완료
volatile char B_use_fireball = 0;//라켓 B 파이어볼 사용
volatile char B_use_tornado = 0;//라켓 B 토네이도 사용
volatile char B_use_hacking = 0;//라켓 B 해킹 사용
volatile char B_release_hacking = 0;//라켓 B 해킹 해제
volatile char B_use_EMP = 0;// 라켓 B EMP사용
volatile char B_use_changeup = 0;//라켓 B changeup 사용
volatile char B_use_iceball = 0;//라켓 B 아이스볼 사용
volatile char B_use_mine_1 = 0;//라켓 B 지뢰 1위치 사용
volatile char B_use_mine_2 = 0;//라켓 B 지뢰 2위치 사용
volatile char B_use_mine_3 = 0;//라켓 B 지뢰 3위치 사용
volatile char B_use_defender_1 = 0;//라켓 B 수비수 1위치 사용
volatile char B_use_defender_2 = 0;//라켓 B 수비수 2위치 사용
volatile char B_use_defender_3 = 0;//라켓 B 수비수 3위치 사용
volatile char B_activated_mine_1 = 0;//라켓 B 지뢰 1위치 발동
volatile char B_activated_mine_2 = 0;//라켓 B 지뢰 2위치 발동
volatile char B_activated_mine_3 = 0;//라켓 B 지뢰 3위치 발동
volatile char B_activated_defender_1 = 0;//라켓 B 수비수 1위치 발동
volatile char B_activated_defender_2 = 0;//라켓 B 수비수 2위치 발동
volatile char B_activated_defender_3 = 0;//라켓 B 수비수 3위치 발동
volatile char B_delete_mine = 0; //라켓 B 지뢰 소멸
volatile char B_delete_defender = 0;//라켓 B 수비수 소멸
volatile char B_move_right = 0;//라켓 B 오른쪽 움직임
volatile char B_move_left = 0;//라켓 B 왼쪽으로 움직임
volatile char B_move_stop = 0;//라켓 B 멈춤

volatile char insert_coin_1000 = 0;//1000원 투입
volatile char insert_coin_5000 = 0;//5000원 투입
volatile char insert_coin_10000 = 0;//10000원 투입시
// 3번 송신을 위한 카운트 변수
volatile char wall_crashCnt = 0;
volatile char A_returnCnt = 0; //A 받아침
volatile char B_returnCnt = 0; //B 받아침
volatile char A_get_scoreCnt = 0; // A 득점
volatile char B_get_scoreCnt = 0; // B 득점
//게임 세팅 관련 카운트 변수
volatile char completion_of_money_inputCnt = 0;
volatile char single_mode_selectionCnt = 0; //라켓 A 모드 싱글 모드 선택
volatile char PVP_mode_selectionCnt = 0; //라켓 A 모드 대전 모드 선택
//A 통신 관련 카운트 변수
volatile char A_AR_readyCnt = 0;//라켓 A AR 증강 준비 완료
volatile char A_pre_game_selectedCnt = 0;
volatile char A_use_fireballCnt = 0;
volatile char A_use_tornadoCnt = 0;
volatile char A_use_hackingCnt = 0;
volatile char A_use_EMPCnt = 0;
volatile char A_use_changeupCnt = 0;
volatile char A_use_iceballCnt = 0;//라켓 A 아이스볼 사용
volatile char A_use_mine_1Cnt = 0;//라켓 A 지뢰 1위치 사용
volatile char A_use_mine_2Cnt = 0;//라켓 A 지뢰 2위치 사용
volatile char A_use_mine_3Cnt = 0;//라켓 A 지뢰 3위치 사용
volatile char A_use_defender_1Cnt = 0;//라켓 A 수비수 1위치 사용
volatile char A_use_defender_2Cnt = 0;//라켓 A 수비수 2위치 사용
volatile char A_use_defender_3Cnt = 0;//라켓 A 수비수 3위치 사용
volatile char A_activated_mine_1Cnt = 0;//라켓 A 지뢰 1위치 발동
volatile char A_activated_mine_2Cnt = 0;//라켓 A 지뢰 2위치 발동
volatile char A_activated_mine_3Cnt = 0;//라켓 A 지뢰 3위치 발동
volatile char A_activated_defender_1Cnt = 0;//라켓 A 수비수 1위치 발동
volatile char A_activated_defender_2Cnt = 0;//라켓 A 수비수 2위치 발동
volatile char A_activated_defender_3Cnt = 0;//라켓 A 수비수 3위치 발동
volatile char A_delete_mineCnt = 0; //라켓 A 지뢰 소멸
volatile char A_delete_defenderCnt = 0;//라켓 A 수비수 소멸
//B 통신 관련 카운트 변수
volatile char B_AR_ready = 0;//라켓 B AR 증강 준비 완료
volatile char B_pre_game_selectedCnt = 0;
volatile char B_use_fireballCnt = 0;
volatile char B_use_tornadoCnt = 0;
volatile char B_use_hackingCnt  = 0;
volatile char B_use_EMPCnt = 0;
volatile char B_use_changeupCnt = 0;
volatile char B_use_iceballCnt = 0;//라켓 B 아이스볼 사용
volatile char B_use_mine_1Cnt = 0;//라켓 B 지뢰 1위치 사용
volatile char B_use_mine_2Cnt = 0;//라켓 B 지뢰 2위치 사용
volatile char B_use_mine_3Cnt = 0;//라켓 B 지뢰 3위치 사용
volatile char B_use_defender_1Cnt = 0;//라켓 B 수비수 1위치 사용
volatile char B_use_defender_2Cnt = 0;//라켓 B 수비수 2위치 사용
volatile char B_use_defender_3Cnt = 0;//라켓 B 수비수 3위치 사용
volatile char B_activated_mine_1Cnt = 0;//라켓 B 지뢰 1위치 발동
volatile char B_activated_mine_2Cnt = 0;//라켓 B 지뢰 2위치 발동
volatile char B_activated_mine_3Cnt = 0;//라켓 B 지뢰 3위치 발동
volatile char B_activated_defender_1Cnt = 0;//라켓 B 수비수 1위치 발동
volatile char B_activated_defender_2Cnt = 0;//라켓 B 수비수 2위치 발동
volatile char B_activated_defender_3Cnt = 0;//라켓 B 수비수 3위치 발동
volatile char B_delete_mineCnt = 0; //라켓 B 지뢰 소멸
volatile char B_delete_defenderCnt = 0;//라켓 B 수비수 소멸
//AR 아이템 획득
volatile char A_get_mine = 0;
volatile char A_get_defender = 0;
volatile char B_get_mine = 0;
volatile char B_get_defender = 0;

volatile char A_get_mineCnt = 0;
volatile char A_get_defenderCnt = 0;
volatile char B_get_mineCnt = 0;
volatile char B_get_defenderCnt = 0;
//동전 투입
volatile char insert_coin_1000Cnt = 0;
volatile char insert_coin_5000Cnt = 0;
volatile char insert_coin_10000Cnt = 0;
// receive data variable
//공 아이템 사용
volatile char move_fireball = 0;
volatile char move_tornado = 0;
volatile char move_change_up = 0;
volatile char move_iceball = 0;
//Coordinates
long ball_X_Cood = 0; // 공의 X 좌표
long ball_Y_Cood = 0;//  공의 Y 좌표
long A_X_Cood = 0; // 라켓 A의 좌표
long B_X_Cood = 0;// 라켓 B의 좌표
//Coordinates for send data
volatile unsigned char ball_X_Cood_High = 0;
volatile unsigned char ball_X_Cood_Low = 0;
volatile unsigned char ball_Y_Cood_High = 0;
volatile unsigned char ball_Y_Cood_Low = 0;
volatile unsigned char A_X_Cood_High = 0;
volatile unsigned char A_X_Cood_Low = 0;
volatile unsigned char B_X_Cood_High = 0;
volatile unsigned char B_X_Cood_Low = 0;
volatile unsigned char checkSum = 0;// start와 end 필드를 제외한 나머지 필드들의 합 XOR FF 한 값.
//ball variable
char ball_X_dir = 0;
char ball_Y_dir = 0;
int ball_X_stpPin = 2;
int ball_X_dirPin = 3;
int ball_Y_stpPin = 4;
int ball_Y_dirPin = 5;
int ball_X_limitSwitch1 = 22;
int ball_X_limitSwitch2 = 23;
//int ball_Y_limitSwitch1 = 24;
//int ball_Y_limitSwitch2 = 25;

int ball_Y_limitSwitch1_1 = 0;
int ball_Y_limitSwitch1_2 = 1;
int ball_Y_limitSwitch2_1 = 2;
int ball_Y_limitSwitch2_2 = 3;

int ball_Y_dirCheck1 = 0;//레이저 센서 체크
int ball_Y_dirCheck2 = 0;
//A_racket variable
volatile char A_X_dir = 0;
int A_X_stpPin = 6;
int A_X_dirPin = 7;
int A_X_limitSwitch1 = 26;
int A_X_limitSwitch2 = 27;
volatile char A_bluetooth_data = 0;
volatile char A_hacking_check = 0; //상대방이 해킹 아이템을 사용하면 1 아니면 0
volatile char A_moveCtl = 0;
//B_racket variable
volatile char B_X_dir = 0;
int B_X_stpPin = 8;
int B_X_dirPin = 9;
int B_X_limitSwitch1 = 28;
int B_X_limitSwitch2 = 29;
volatile char B_bluetooth_data = 0;
volatile char B_hacking_check;//상대방이 해킹 아이템을 사용하면 1 아니면 0
volatile char B_moveCtl = 0;
//ect variable
char firstAt = 0; // 시작 방향이 어디인지.
char startDir = 0;
volatile int step_ =  0;
volatile int data_len = 0;
int collision_check2 = 0;
int firstCheck = 0;
//led GPIO
int led_left_pin = 49;
int led_right_pin = 51;
int led_top_pin = 52; //B
int led_bottom_pin = 48; //A
int led_left_count = 0;
int led_right_count = 0;
char left_startCnt = 0;
char right_startCnt = 0;
//thermoelectric variable
char A_thermoelectric_GPIOPin = 24;
char B_thermoelectric_GPIOPin = 25;
char A_thermoelectric_PWMPin = 10;
char B_thermoelectric_PWMPin = 11;
//timer variable
volatile int ball_X_timerCnt = 0;
volatile int ball_X_timerLimit = 3;//start speed
volatile int ball_X_timercheck = 0;
volatile int ball_X_speedCheck = 0;
volatile int ball_X_maxSpeed = 0;
volatile int ball_Y_timerCnt = 0;
volatile int ball_Y_timerLimit = 3;//start speed
volatile int ball_Y_timercheck = 0;
volatile int ball_Y_speedCheck = 0;
volatile int ball_Y_maxSpeed = 0;
volatile int A_X_timerCnt = 0;
volatile int A_X_timerLimit = 3;//start speed
volatile int A_X_timercheck = 0;
volatile int A_X_speedCheck = 0;
volatile int B_X_timerCnt = 0;
volatile int B_X_timerLimit = 3;//start speed
volatile int B_X_timercheck = 0;
volatile int B_X_speedCheck = 0;
//brensham variable
long p_value = 0; // line 함수 내부에서 사용하는 전역 변수
long inc_2dy = 0; // line 함수 내부에서 사용하는 전역 변수
long inc_2dydx = 0; // line 함수 내부에서 사용하는 전역 변수
long inc_value = 0; // line 함수 내부에서 사용하는 전역 변수
long ndx = 0; // line 함수 내부에서 사용하는 전역 변수
long ndy = 0; // line 함수 내부에서 사용하는 전역 변수
long tx = 0;
long ty = 0;
long diff = 0; // line 함수 내부에서 사용하는 전역 변수
long linetype = 0; // line 함수 내부에서 사용하는 전역 변수 (가로로 긴 이동인지 세로로 긴 이동인지 구분)
long maxX = 115400; // 가로 길이  1154
long maxY = 127300; // 세로 길이  1373
int angle = 0;
long speed = maxX + maxY; // 각도로 이동을 시키기 때문에 기본이동은 경기장을 넘어갈 정도로 지정
int x_move_check = 0;
int y_move_check = 0;
//item variable
int A_tornado_stat = 0;
int A_tornadoCnt = 0;
int A_item = 0;
int A_changeUpCheck = 0;
int A_tornadoCheck = 0;

int B_tornado_stat = 0;
int B_tornadoCnt = 0;
int B_changeUpCheck = 0;
int B_tornadoCheck = 0;
int B_item = 0;

//

volatile int restart_check = 0;
volatile int restartCnt = 0;
//function prototype
//send data function
void serial_send_data(void);

void ball_X_Cood_function(void);
void ball_Y_Cood_function(void);
void A_X_Cood_function(void);
void B_X_Cood_function(void);
char ball_check_function(void);
char game_ready_function(void);
char A_use_item_1_function(void);
char A_use_item_2_function(void);
char A_activate_or_delete_item_function(void); 
char A_move_function(void);
char B_use_item_1_function(void);
char B_use_item_2_function(void);
char B_activate_or_delete_item_function(void);
char B_move_function(void); 
char insert_coin_function(void);
char get_AR_item_function(void);
//receive data function
void ball_move_item(void);
void ball_receive_move(void);
void ball_stat(void);
void A_using_item(void);
void A_get_item(void);
void A_choose(void);
void B_using_item(void);
void B_get_item(void);
void B_choose(void);

void initing(void);
void fireball(void);
void tornado(void);
void changeup(void);
void A_change_left_dir(void);
void A_change_rigth_dir(void);
void B_change_left_dir(void);
void B_change_right_dir(void);
void line_step(void);
void line(int,int,int,int);
int getAngle(int,int);
void setAngle(int,double);
void A_Collision_check(void);
void B_Collision_check(void);
void restart(void);

void serial1Interrupt(void);
void serial2InterruptBeforeInGame(void);
void serial2InterruptAfterInGame(void);
void serial3InterruptBeforeInGame(void);
void serial3InterruptAfterInGame(void);

void initRandomFunction(void);
void initPinConfiguration(void);
void initTimer(void);
void initSerial(void);
void firstCheckFuntion(void);
void gameControl(void);
void coordinateCheck(void);
void limitSwitchCheck(void);
void ballMoveControl(void);
void rackectMoveControl(void);
void ledControl(void);
void itemControl(void);


void initRandomFunction(void)
{
    randomSeed(analogRead(0));
}
void initSerial(void)
{
    Serial.begin(115200);// USB
    Serial1.begin(115200); // ttl to rs232 <-> rs232 to usb
    Serial2.begin(115200); // bluetooth A module
    Serial3.begin(115200); // bluetooth B module
}
void initTimer(void)//timer interrupt
{
    Timer0.attachInterrupt(ball_X_timerHandler).start(100);
    Timer1.attachInterrupt(ball_Y_timerHandler).start(100);
    Timer2.attachInterrupt(A_X_timerHandler).start(100);
    Timer3.attachInterrupt(B_X_timerHandler).start(100); //100us
    Timer4.attachInterrupt(restart).start(1000000);//1s
}
void initPinConfiguration(void)
{
    //Set pin mode of motor output
    pinMode(ball_X_dirPin,OUTPUT);
    pinMode(ball_X_stpPin,OUTPUT);
    pinMode(ball_Y_dirPin,OUTPUT);
    pinMode(ball_Y_stpPin,OUTPUT);
    pinMode(A_X_dirPin,OUTPUT);
    pinMode(A_X_stpPin,OUTPUT);
    pinMode(B_X_dirPin,OUTPUT);
    pinMode(B_X_stpPin,OUTPUT);
    //Set pin mode ofswitch input
    pinMode(ball_X_limitSwitch1,INPUT);
    pinMode(ball_X_limitSwitch2,INPUT);
    pinMode(ball_Y_limitSwitch1_1,INPUT);
    pinMode(ball_Y_limitSwitch1_2,INPUT);
    pinMode(ball_Y_limitSwitch2_1,INPUT);
    pinMode(ball_Y_limitSwitch2_2,INPUT);
    pinMode(A_X_limitSwitch1,INPUT);
    pinMode(A_X_limitSwitch2,INPUT);
    pinMode(B_X_limitSwitch1,INPUT);
    pinMode(B_X_limitSwitch2,INPUT);
    //Set direction of motor
    digitalWrite(ball_X_dirPin,ball_X_dir);
    digitalWrite(ball_Y_dirPin,ball_Y_dir);
    digitalWrite(A_X_dirPin,A_X_dir);
    digitalWrite(B_X_dirPin,B_X_dir);
    //Set pin mode of led
    pinMode(led_left_pin,OUTPUT);
    pinMode(led_right_pin,OUTPUT);
    pinMode(led_top_pin,OUTPUT);
    pinMode(led_bottom_pin,OUTPUT);
    //set pin of thermoelectric
    pinMode(A_thermoelectric_PWMPin,OUTPUT);
    pinMode(B_thermoelectric_PWMPin,OUTPUT);
    pinMode(A_thermoelectric_GPIOPin,OUTPUT);
    pinMode(B_thermoelectric_GPIOPin,OUTPUT);
}
void setup(void)
{
    initRandomFunction();
    initSerial();
    initPinConfiguration();
    initTimer();
}
void firstCheckFuntion(void)
{
    if(startCheck == 0){
        initing();
        startAngle = 90;
        startCheck = 1;
    }
    if(serial1InterruptCheck != 0)
        serial1Interrupt();
    if(A_bluetooth_data != 0)
        serial2InterruptBeforeInGame();
    if(B_bluetooth_data != 0)
        serial3InterruptBeforeInGame();
    if(firstAt == 1){ //A 선공
        Serial2.write('U');
        Serial3.write('U');
        angle = 270;
        ball_Y_dir = 1;
        digitalWrite(ball_Y_dirPin,ball_Y_dir);
        firstCheck = 1;
        setAngle(angle,speed);
    }else if(firstAt == 2){//B선공 
        Serial2.write('U');
        Serial3.write('U');
        ball_Y_dir = 0;
        digitalWrite(ball_Y_dirPin,ball_Y_dir);
        firstCheck = 1;
        setAngle(angle,speed);
    }
}
void coordinateCheck(void)
{
    if (ndx == ball_X_Cood && ndy == ball_Y_Cood) {
        // 현재 좌표와 목적지 좌표가 같 경우
        line_step();
        x_move_check = 0;
        y_move_check = 0;
    }
    if (ndx != ball_X_Cood && x_move_check == 0) { // 현재 x좌
        if (ndx > ball_X_Cood) {
            if(ball_X_dir != 0){
                ball_X_dir = 0; digitalWrite(ball_X_dirPin,ball_X_dir);
            }
            x_move_check = 1;
        } else if (ndx < ball_X_Cood ) { // 좌측에 있을 경우
            if(ball_X_dir != 1){
                ball_X_dir = 1; digitalWrite(ball_X_dirPin,ball_X_dir);   
            }
            x_move_check = 1;
        }
    }
    // 현재 y 좌표와 목적지 y 좌료가 틀릴 경우             
    if (ball_Y_Cood != ndy && y_move_check == 0) {
        // 아래쪽에 있을 경우
        if (ndy > ball_Y_Cood) {// 계속 위로 이동
            if(ball_Y_dir != 0){
                ball_Y_dir = 0; digitalWrite(ball_Y_dirPin,ball_Y_dir);
            }
            y_move_check = 1;
        } else if (ndy < ball_Y_Cood) { // 위쪽에 있을 경우
            if(ball_Y_dir != 1){
                ball_Y_dir = 1; digitalWrite(ball_Y_dirPin,ball_Y_dir);
            }
            y_move_check = 1;
        }
    }
}
void limitSwitchCheck(void)
{
    //스위치 체크 
    if(digitalRead(ball_X_limitSwitch1) == LOW && ball_X_dir == 1){
        Serial2.write('U');
        Serial3.write('U');
        ball_X_dir = 0;
        digitalWrite(ball_X_dirPin,ball_X_dir);
        ball_X_Cood = 0;
        wall_crash = 1; 
        ball_X_speedCheck = 0;
        ball_X_timerLimit = 3;
        ball_X_timerCnt = 0;
        digitalWrite(led_left_pin,HIGH);
        int new_angle = getAngle(angle,VERTICAL);
        setAngle(new_angle,speed);
        left_startCnt = 1; 
    }
    if(digitalRead(ball_X_limitSwitch2) == LOW && ball_X_dir == 0){
        Serial2.write('U');
        Serial3.write('U');
        ball_X_dir = 1;
        digitalWrite(ball_X_dirPin,ball_X_dir);
        ball_X_Cood = 1960;
        wall_crash = 1;
        ball_X_speedCheck = 0;
        ball_X_timerLimit = 3;
        ball_X_timerCnt = 0;
        digitalWrite(led_right_pin,HIGH);
        int new_angle = getAngle(angle,VERTICAL);
        setAngle(new_angle,speed);
        right_startCnt = 1;
    }
    if((analogRead(ball_Y_limitSwitch1_1) > 1000 && ball_Y_dirCheck1 == 0 ) && ball_Y_dir == 1){
        ball_Y_dirCheck1 = 1;
    }
    if((analogRead(ball_Y_limitSwitch1_2) > 1000 && ball_Y_dirCheck1 == 1 ) && ball_Y_dir == 1){
        Serial2.write('U');
        collision_check2 = 1;
        ball_Y_dirCheck1 = 2;
        ball_Y_dirCheck2 = 0;
        ball_Y_dir = 0;
        digitalWrite(ball_Y_dirPin,ball_Y_dir);
        ball_Y_Cood = 0;
        ball_Y_speedCheck = 0;
        ball_Y_timerLimit = 3;
        ball_Y_timerCnt = 0;
        if(A_hacking_check == 1)
            A_hacking_check = 0;
        B_item = 0;
        Serial3.write('U');
        A_Collision_check();
    }
    if((analogRead(ball_Y_limitSwitch2_1) > 1000 && ball_Y_dirCheck2 == 0 ) && ball_Y_dir == 0){
        ball_Y_dirCheck2 = 1;
    }
    if((analogRead(ball_Y_limitSwitch2_2) > 1000 && ball_Y_dirCheck2 == 1 ) && ball_Y_dir == 0){
        Serial2.write('U');
        collision_check2 = 1;
        ball_Y_dirCheck2 = 2;
        ball_Y_dirCheck1 = 0;
        ball_Y_dir = 1;
        digitalWrite(ball_Y_dirPin,ball_Y_dir);
        ball_Y_Cood = 2720;
        ball_Y_speedCheck = 0;
        ball_Y_timerLimit = 3;
        ball_Y_timerCnt = 0;
        if(B_hacking_check == 1)
            B_hacking_check = 0;
        A_item = 0;
        Serial3.write('U');
        B_Collision_check();
    }
    if(digitalRead(A_X_limitSwitch1) == LOW && A_X_dir == 0){
        Serial2.write('U');
        A_X_dir = 1; digitalWrite(A_X_dirPin,A_X_dir);
        A_X_Cood = 0; A_X_timerLimit = 3;
        A_X_timerCnt = 0;
    }
    if(digitalRead(A_X_limitSwitch2) == LOW && A_X_dir == 1){
        Serial2.write('U');
        A_X_dir = 0; digitalWrite(A_X_dirPin,A_X_dir);
        A_X_Cood = X; A_X_timerLimit = 3;
        A_X_timerCnt = 0;
    }
    if(digitalRead(B_X_limitSwitch1) == LOW && B_X_dir == 0){
        Serial3.write('U');
        B_X_dir = 1; digitalWrite(B_X_dirPin,B_X_dir);
        B_X_Cood = 0; B_X_timerLimit = 3;
        B_X_timerCnt = 0;
    }
    if(digitalRead(B_X_limitSwitch2) == LOW && B_X_dir == 1){
        Serial3.write('U');
        B_X_dir = 0; digitalWrite(B_X_dirPin,B_X_dir);
        B_X_Cood = X; B_X_timerLimit = 3;
        B_X_timerCnt = 0;
    }
}
void ballMoveControl(void)
{
    //move
    if(ball_X_timerCnt >= ball_X_timerLimit && collision_check2 == 0 
        && x_move_check == 1){ //ball X motor timer
        if(ball_X_timercheck == 0){
            digitalWrite(ball_X_stpPin,HIGH);
            ball_X_timercheck = 1;
            if(ball_X_dir == 1 && ball_X_Cood > 0 )
                ball_X_Cood--;
            else if(ball_X_dir == 0 && ball_X_Cood < 1960)
                ball_X_Cood++;
        }else if(ball_X_timercheck == 1){
            digitalWrite(ball_X_stpPin,LOW);
            ball_X_timercheck = 0;
            x_move_check = 0;
        }
        ball_X_timerCnt = 0;
        ball_X_speedCheck++;
        if(ball_X_timerLimit > 20 && ball_X_speedCheck == 100){
            //ball_X_timerLimit-=1;
            ball_X_speedCheck=0;
        }
    }
    if(ball_Y_timerCnt >= ball_Y_timerLimit && collision_check2 == 0
            &&y_move_check == 1){//ball Y Motor timer
        if(ball_Y_timercheck == 0){
            digitalWrite(ball_Y_stpPin,HIGH);
            ball_Y_timercheck = 1;
            if(ball_Y_dir == 0 && ball_Y_Cood < 2720 )
                ball_Y_Cood++;
            else if(ball_Y_dir == 1 && ball_Y_Cood > 0)
                ball_Y_Cood--;
            if(A_item == 2)
                A_tornadoCnt++;
            if(B_item == 2)
                B_tornadoCnt++;
        }else if(ball_Y_timercheck == 1){
            digitalWrite(ball_Y_stpPin,LOW);
            ball_Y_timercheck = 0;
            y_move_check = 0;
        }
        ball_Y_timerCnt = 0;
        ball_Y_speedCheck++;
        if(ball_Y_timerLimit > 20 && ball_Y_speedCheck == 100){//가
            //ball_Y_timerLimit-=1;
            ball_Y_speedCheck = 0;
        }
    }
}
void rackectMoveControl(void)
{
    if(A_moveCtl != 0){  // Racket A motor
        if(A_X_timerCnt >= A_X_timerLimit){
            if(A_X_timercheck == 0){
                digitalWrite(A_X_stpPin,HIGH);
                A_X_timercheck = 1;
                if(A_X_dir == 1){
                    A_X_Cood++;
                }else if(A_X_dir == 0){
                    A_X_Cood--;
                }
            }else if(A_X_timercheck == 1){
                digitalWrite(A_X_stpPin,LOW);
                A_X_timercheck = 0;
            }
            A_X_timerCnt = 0;
            A_X_speedCheck++;
        }
    }
    if(B_moveCtl != 0){ // Racket B Motor
        if(B_X_timerCnt >= B_X_timerLimit){
            if(B_X_timercheck == 0){
                digitalWrite(B_X_stpPin,HIGH);
                B_X_timercheck = 1;
                if(B_X_dir == 1){
                    B_X_Cood++;
                }else if(B_X_dir == 0){
                    B_X_Cood--;
                }
            }else if(B_X_timercheck == 1){
                digitalWrite(B_X_stpPin,LOW);
                B_X_timercheck = 0;
            }
            B_X_timerCnt = 0;
            B_X_speedCheck++;
        }
    }
}
void ledControl(void)
{
 //led
    if(left_startCnt == 1)
        led_left_count++;
    if(led_left_count >= 20000){
        digitalWrite(led_left_pin,LOW);
        led_left_count = 0;
        left_startCnt = 0;
    }
    if(right_startCnt == 1)
        led_right_count++;
    if(led_right_count >= 20000){
        digitalWrite(led_right_pin,LOW);
        led_right_count = 0;
        right_startCnt = 0;
    }
    if(restartCnt >= 3){
        collision_check2 = 0;
        digitalWrite(led_bottom_pin,LOW);
        digitalWrite(led_top_pin,LOW);
        restartCnt = 0;
        restart_check = 0;
    }   
}
void itemControl(void)
{   
    if(A_item == 1){ // fireball
        if(ball_Y_dir == 0){
            if(ball_Y_Cood < ((int)(Y * 0.58))){
                angle = 90;
                setAngle(angle,speed);
            }
            if(ball_Y_Cood >= ((int)(Y * 0.58))){
                int randNum = rand() % 2;
                if(randNum == 0){
                    angle = rand() % 20 + 40;
                }else if(randNum == 1){
                    angle = rand() % 20 + 120;
                }
                setAngle(angle,speed);
                A_item = 0;
            }
        }
    }
    if(B_item == 1){
        if(ball_Y_dir == 1){
            if(ball_Y_Cood > ((int)(Y * 0.34))){
                angle = 270;
                setAngle(angle,speed);
            }else if(ball_Y_Cood <= ((int)(Y * 0.34))){
                int randNum = rand() % 2;
                if(randNum == 0){
                    angle = rand() % 20 + 220;
                }else if(randNum == 1){
                    angle = rand() % 20 + 300;
                }
                setAngle(angle,speed);
                B_item = 0;
            }
        }
    }    
    if(A_item == 2){ // tornado
        if(ball_Y_dir == 0){
            if(ball_X_Cood < ((int)(X * 0.24))){
                if(ball_Y_Cood < ((int)(Y * 0.18)) && A_tornadoCheck == 0){
                    A_tornadoCheck++;
                    angle = 90;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood >= ((int)(Y * 0.18)) && A_tornadoCheck == 1){
                    A_tornadoCheck++;
                    angle = 80;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood >= ((int)(Y * 0.36)) && A_tornadoCheck == 2){//휘기 시작
                    if(A_tornadoCnt >= 8 && angle > 40){
                    //tornadoCnt 크면 각 휘는 빈도수 증가, Anlge 최종적 휘는 정도
                        angle -= 1;
                        A_tornadoCnt = 0;
                        setAngle(angle,speed);
                        if(angle == 40){
                            A_item = 0;
                            A_tornadoCheck = 0;
                        }
                    }
                }
            }
            else if(((int)(X * 0.24))<= ball_X_Cood && ball_X_Cood < ((int)(X * 0.42))){
                if(ball_Y_Cood < ((int)(Y * 0.18)) && A_tornadoCheck == 0){
                    A_tornadoCheck++;
                    angle = 110;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood >= ((int)(Y * 0.18)) && A_tornadoCheck == 1){
                    A_tornadoCheck++;
                    angle = 100;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood >= ((int)(Y * 0.36)) && A_tornadoCheck == 2){//휘기 시작
                    if(A_tornadoCnt >= 8 && angle > 40){
                        //tornadoCnt 크면 각 휘는 빈도수 증가, Anlge 최종적 휘는 정도
                        angle -= 1;
                        A_tornadoCnt = 0;
                        setAngle(angle,speed);
                        if(angle == 40){
                            A_item = 0;
                            A_tornadoCheck = 0;
                        }
                    }
                }   
            }
            else if(((int)(X * 0.42)) <= ball_X_Cood && ball_X_Cood < ((int)(X * 0.74))){
                if(ball_Y_Cood < ((int)(Y * 0.18)) && A_tornadoCheck == 0){
                    A_tornadoCheck++;
                    angle = 70;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood >= ((int)(Y * 0.18)) && A_tornadoCheck == 1){
                    A_tornadoCheck++;
                    angle = 80;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood >= ((int)(Y * 0.36)) && A_tornadoCheck == 2){//휘기 시작
                    if(A_tornadoCnt >= 8 && angle < 140){
                    //tornadoCnt 크면 각 휘는 빈도수 증가, Anlge 최종적 휘는 정도
                        angle += 1;
                        A_tornadoCnt = 0;
                        setAngle(angle,speed);
                        if(angle == 140){
                            A_tornadoCheck = 0;
                            A_item = 0;
                        }
                    }
                }
            }
            else if(ball_X_Cood >= ((int)(X * 0.74))){
                if(ball_Y_Cood < ((int)(Y * 0.18)) && A_tornadoCheck == 0){
                    A_tornadoCheck++;
                    angle = 90;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood >= ((int)(Y * 0.18)) && A_tornadoCheck == 1){
                    A_tornadoCheck++;
                    angle = 100;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood >= ((int)(Y * 0.36)) && A_tornadoCheck == 2){//휘기 시작
                    if(A_tornadoCnt >= 8 && angle < 140){
                    //tornadoCnt 크면 각 휘는 빈도수 증가, Anlge 최종적 휘는 정도
                        angle += 1;
                        A_tornadoCnt = 0;
                        setAngle(angle,speed);
                        if(angle == 140){
                            A_item = 0;
                            A_tornadoCheck = 0;
                        }
                    }
                }
            }
        }
    }
    if(B_item == 2){
        if(ball_Y_dir == 1){
            if(ball_X_Cood < ((int)(X * 0.24))){ 
                if(ball_Y_Cood > ((int)(Y * 0.74)) && B_tornadoCheck == 0){
                    B_tornadoCheck++;
                    angle = 270;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood <= ((int)(Y * 0.74)) && B_tornadoCheck == 1){
                    B_tornadoCheck++;
                    angle = 280;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood <= ((int)(Y * 0.41)) && B_tornadoCheck == 2){//휘기 시작
                    if(B_tornadoCnt >= 8 && angle < 320){
                    //tornadoCnt 크면 각 휘는 빈도수 증가, Anlge 최종적 휘는 정도
                        angle += 1;
                        B_tornadoCnt = 0;
                        setAngle(angle,speed);
                        if(angle == 320){
                            B_tornadoCheck = 0;
                            B_item = 0;
                        }
                    }
                }
            }
            else if(((int)(X * 0.24)) <= ball_X_Cood && ball_X_Cood < ((int)(X * 0.42))){
                if(ball_Y_Cood > ((int)(Y * 0.74)) && B_tornadoCheck == 0){
                    B_tornadoCheck++;
                    angle = 250;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood <= ((int)(Y * 0.74)) && B_tornadoCheck == 1){
                    B_tornadoCheck++;
                    angle = 260;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood <= ((int)(Y * 0.41)) && B_tornadoCheck == 2){//휘기 시작
                    if(B_tornadoCnt >= 8 && angle < 320){
                    //tornadoCnt 크면 각 휘는 빈도수 증가, Anlge 최종적 휘는 정도
                        angle += 1;
                        B_tornadoCnt = 0;
                        setAngle(angle,speed);
                        if(angle == 320){
                            B_tornadoCheck = 0;
                            B_item = 0;
                        }
                    }
                }
            }
            else if(((int)(X * 0.42)) <= ball_X_Cood && ball_X_Cood < ((int)(X * 0.74))){
                if(ball_Y_Cood > ((int)(Y * 0.74)) && B_tornadoCheck == 0){
                    B_tornadoCheck++;
                    angle = 300;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood <= ((int)(Y * 0.74)) && B_tornadoCheck == 1){
                    B_tornadoCheck++;
                    angle = 290;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood >= ((int)(Y * 0.41)) && B_tornadoCheck == 2){//휘기 시작
                    if(B_tornadoCnt >= 8 && angle > 220){
                    //tornadoCnt 크면 각 휘는 빈도수 증가, Anlge 최종적 휘는 정도
                        angle -= 1;
                        B_tornadoCnt = 0;
                        setAngle(angle,speed);
                        if(angle == 220){
                            B_tornadoCheck = 0;
                            B_item = 0;
                        }
                    }
                }
            }
            else if(ball_X_Cood >= ((int)(X * 0.74))){
                if(ball_Y_Cood > ((int)(Y * 0.74)) && B_tornadoCheck == 0){
                    B_tornadoCheck++;
                    angle = 270;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood <= ((int)(Y * 0.74)) && B_tornadoCheck == 1){
                    B_tornadoCheck++;
                    angle = 260;
                    setAngle(angle,speed);
                }
                if(ball_Y_Cood >= ((int)(Y * 0.41)) && B_tornadoCheck == 2){//휘기 시작
                    if(B_tornadoCnt >= 8 && angle > 220){
                    //tornadoCnt 크면 각 휘는 빈도수 증가, Anlge 최종적 휘는 정도
                        angle -= 1;
                        B_tornadoCnt = 0;
                        setAngle(angle,speed);
                        if(angle == 220){
                            B_tornadoCheck = 0;
                            B_item = 0;
                        }
                    }
                }
            }
        }
    }
    if(A_item == 3){ // change up
        if(A_changeUpCheck == 0) 
            A_changeUpCheck+=1;
        if(ball_Y_dir == 0){
            if(( ball_Y_Cood == ((int)(Y * 0.11)) && A_changeUpCheck == 1) ||
                (ball_Y_Cood == ((int)(Y * 0.34)) && A_changeUpCheck == 2) ||
                (ball_Y_Cood == ((int)(Y * 0.46)) && A_changeUpCheck == 3) ||
                (ball_Y_Cood == ((int)(Y * 0.57)) && A_changeUpCheck == 4) ){
                    if(ball_X_dir == 1)
                        angle = rand() % 20 + 30; // 30 ~ 50 도
                    else if(ball_X_dir == 0)
                        angle = rand() % 20 + 130;// 130 ~ 150 도
                    A_changeUpCheck++;
                    setAngle(angle,speed);
            }else if(ball_Y_Cood == 1113 && A_changeUpCheck == 5){
                if(ball_X_dir == 1)
                    angle = rand() % 20 + 30; // 30 ~ 50 도
                else if(ball_X_dir == 0)
                    angle = rand() % 20 + 130;// 130 ~ 150 도
                A_changeUpCheck = 0;
                A_item = 0;
                setAngle(angle,speed);
            }       
        }
    }
    if(B_item == 3){
        if(B_changeUpCheck == 0) 
            B_changeUpCheck+=1;
        if(ball_Y_dir == 1){
            if((ball_Y_Cood == ((int)(Y * 0.81)) && B_changeUpCheck == 1) ||
                (ball_Y_Cood == ((int)(Y * 0.57)) && B_changeUpCheck == 2) ||
                (ball_Y_Cood == ((int)(Y * 0.46)) && B_changeUpCheck == 3) ||
                (ball_Y_Cood == ((int)(Y * 0.34)) && B_changeUpCheck == 4) ){
                    if(ball_X_dir == 1)
                        angle = rand() % 20 + 310; // 310 ~ 330 도
                    else if(ball_X_dir == 0)
                        angle  = rand() % 20 + 210; // 210 ~ 210도
                    B_changeUpCheck++;
                    setAngle(angle,speed);
            }else if(ball_Y_Cood == 159 && B_changeUpCheck == 5){
                if(ball_X_dir == 1)
                    angle = rand() % 20 + 310; // 310 ~ 330 도
                else if(ball_X_dir == 0)
                    angle  = rand() % 20 + 210; // 210 ~ 210도
                B_changeUpCheck = 0;
                B_item = 0;
                setAngle(angle,speed);
            }
        }
    }
}
void gameControl(void)
{
    coordinateCheck();
    limitSwitchCheck();
    ballMoveControl();
    rackectMoveControl();
    ledControl();
    itemControl();
    if(serial1InterruptCheck != 0)
        serial1Interrupt();
    if(A_bluetooth_data != 0)
        serial2InterruptAfterInGame();
    if(B_bluetooth_data != 0)
        serial3InterruptAfterInGame();
}
void initing(void)
{
    char check = 0;
    char ball_X_check = 0;
    char ball_Y_check = 0;
    char A_X_check = 0;
    char B_X_check = 0;
    int delay_ = 100;
    int delay_for_Y = 300;
    digitalWrite(ball_X_dirPin, 1);
    digitalWrite(ball_Y_dirPin, 1);
    digitalWrite(A_X_dirPin,0);
    digitalWrite(B_X_dirPin,0);
    while(check != 3){
        if(ball_X_check == 0){
            if(digitalRead(ball_X_limitSwitch1) == LOW){
                ball_X_check = 1;
                check += 1;
                delay_+=100;
            }
            digitalWrite(ball_X_stpPin, HIGH);
            delayMicroseconds(delay_);
            digitalWrite(ball_X_stpPin, LOW);
            delayMicroseconds(delay_);
        }
        if(A_X_check == 0){
            if(digitalRead(A_X_limitSwitch1) == LOW){
                A_X_check = 1;
                check += 1;
                delay_+=100;
            }
            digitalWrite(A_X_stpPin, HIGH);
            delayMicroseconds(delay_);
            digitalWrite(A_X_stpPin, LOW);
            delayMicroseconds(delay_);
        }
        if(B_X_check == 0){
            if(digitalRead(B_X_limitSwitch1) == LOW){
                B_X_check = 1;
                check += 1;
                delay_+=100;
            }
            digitalWrite(B_X_stpPin, HIGH);
            delayMicroseconds(delay_);
            digitalWrite(B_X_stpPin, LOW);
            delayMicroseconds(delay_);
        }
    }
    while(!(digitalRead(ball_Y_limitSwitch1_2) > 1000)){
        digitalWrite(ball_Y_stpPin, HIGH);
        delayMicroseconds(400);
        digitalWrite(ball_Y_stpPin, LOW);
        delayMicroseconds(400);
    }
    digitalWrite(ball_X_dirPin, 0);
    digitalWrite(ball_Y_dirPin, 0);
    digitalWrite(A_X_dirPin,1);
    digitalWrite(B_X_dirPin,1);
    ball_X_dir = 0; ball_Y_dir = 0; A_X_dir = 1; B_X_dir =1;

    for (int i = 0; i < X/2; i++) {
        digitalWrite(ball_X_stpPin, HIGH);digitalWrite(ball_Y_stpPin, HIGH);
        digitalWrite(A_X_stpPin,HIGH);digitalWrite(B_X_stpPin,HIGH);
        delayMicroseconds(400);
        digitalWrite(ball_X_stpPin, LOW );
        digitalWrite(ball_Y_stpPin, LOW);
        digitalWrite(A_X_stpPin,LOW);
        digitalWrite(B_X_stpPin,LOW);
        delayMicroseconds(400);
    }
    for (int i = 0; i < ((int)(Y/2) - (int)(X/2)) ; i++) {
        digitalWrite(ball_Y_stpPin, HIGH);
        delayMicroseconds(400);
        digitalWrite(ball_Y_stpPin, LOW);
        delayMicroseconds(400);
    }
    ball_X_Cood = X/2;
    ball_Y_Cood = Y/2;
    A_X_Cood = X/2;
    B_X_Cood = X/2;
}
//****************************************************************************************************************//
//**************************************** Bresenham Algorithm function ******************************************//
//****************************************************************************************************************//
void line_step(void)
{
    if (linetype == 1) {
        if (diff == 0) {
            if (ndx < tx) {
                if ( 0 > p_value) {
                    p_value  += inc_2dy;
                } else {
                    p_value  += inc_2dydx;
                    ndy      += inc_value;
                }
            }
            ndx++;
        } else {
            if (ndx > tx) {
                if ( 0 > p_value) {
                    p_value  += inc_2dy;
                } else {
                    p_value  += inc_2dydx;
                    ndy      += inc_value;
                }
            }   
            ndx--;            
        }
    } else {
        if (diff == 0) {
            if (ndy < ty) {
                if ( 0 > p_value) {
                    p_value  += inc_2dy;
                } else {
                    p_value  += inc_2dydx;
                    ndx      += inc_value;
                }
            }   
            ndy++;
        } else {
            if (ndy > ty) {
                if ( 0 > p_value) {
                    p_value  += inc_2dy;
                } else {
                    p_value  += inc_2dydx;
                    ndx      += inc_value;
                }
            }   
            ndy--;            
        }            
    }
}
void line(long x1, long y1, long x2, long y2)
{
    long dx = 0;
    long dy = 0;
    p_value = 0;
    inc_2dy = 0;
    inc_2dydx = 0;
    inc_value = 0;
    dx = x2 - x1;
    if (dx < 0)
        dx = dx * -1;
    dy = y2 - y1;
    if (dy < 0)
        dy = dy * -1;
    if (dy <= dx) {
        if (x1 > x2)
            diff = 1;
        else
            diff = 0;
        linetype = 1;
        inc_2dy     = 2 * dy;
        inc_2dydx   = 2 * (dy - dx);
        if (y1 < y2)
            inc_value   = 1;
        else
            inc_value   = -1;
        p_value  = 2 * dy - dx;
        tx = x2;
        ty = y2;
        ndx = x1;
        ndy = y1;
    } else {
        if (y1 > y2)
            diff = 1;
        else
            diff = 0;
        linetype = 2;
        inc_2dy     = 2 * dx;
        inc_2dydx   = 2 * (dx - dy);
        if (x1 < x2)
            inc_value   = 1;
        else
            inc_value   = -1;
        p_value  = 2 * dx - dy;
        tx = x2;            
        ty = y2;
        ndx = x1;
        ndy = y1;
    }
}
int getAngle(int r, int direction)
{
    r = r % 360;
    if (direction == HORIZONTAL) {// 라켓에 맞았을때나 골인 될때 각도 변화
        r = 360.0 - r;
    } else {//벽에 맞았을때 각도 변화
        if (r <= 180.0) {
            r = 180.0 - r;
        } else {
            r = 360.0 - r + 180.0;
        }
    }   
    return r;
}
void setAngle(int r, long length)
{
    double radian = r * PI / 180;
    long x = (long)((double)ball_X_Cood + cos(radian) * (double)length);
    long y = (long)((double)ball_Y_Cood + sin(radian) * (double)length);
    angle = r;
    speed = length;
    line(ball_X_Cood, ball_Y_Cood , x, y);
}
//***************************************************************************************************************//
//*********************************************** Timer function ************************************************//
//***************************************************************************************************************//
void ball_X_timerHandler(void)
{
    if(firstCheck != 0) {//선공게임이 정해져 있는지 체크 
        if(collision_check2 == 0){ // 충돌 체크시 카운트 증가 x
            if((new_receive_buffer[3] & 8) != 8){
                ball_X_timerCnt++;  
            }
        }
    }
}
void ball_Y_timerHandler(void)
{
    if(firstCheck != 0){ //선공게임이 정해져 있는지 체크  -> 게임 끝나면 다시 1 
        if(collision_check2 == 0){
            if((new_receive_buffer[3] & 8) != 8){
            ball_Y_timerCnt++;   
            }
        }
    } 
}
void A_X_timerHandler(void)
{
    if(collision_check2 == 0){
        if(firstCheck != 0){
            A_X_timerCnt++;
        }
    }
}
void B_X_timerHandler(void)
{
    if(collision_check2 == 0){
        if(firstCheck != 0){
            B_X_timerCnt++;
        }
    }
}
void restart(void)
{
    if(restart_check == 1){
        restartCnt++;
    }
}

//***************************************************************************************************************//
//*********************************************** Serial Events *************************************************//
//***************************************************************************************************************//
void serialEvent1(void)
{//PC 
    unsigned char data = 0;
    data_len = Serial1.available();
    if(data_len > 0){
        for(int i = 0;i < data_len; i++){
            data = (unsigned char)Serial1.read();
            if(step_ == 0){
                if(data == 0x5B){
                    new_receive_buffer[step_] = data;
                    ++step_;
                }
            }else if(step_ < 12){
                new_receive_buffer[step_] = data;
                ++step_;
            }else if(step_ == 12){
                if(data == 0x5C){
                    new_receive_buffer[step_] = data;
                    ++step_;
                }else{
                    step_ = 0;
                }
            }else if(step_ == 13){
                unsigned char checkSum_check = 0;
                for(int i = 0; i < 13; i++){
                    checkSum_check += new_receive_buffer[i];
                }
                checkSum_check = checkSum_check ^ 0xFF;
                if(checkSum_check == data){
                    new_receive_buffer[step_] = data;
                }
                checkSum_check = 0;
                step_ = 0;
                serial1InterruptCheck = 1;
            }
        }
    }
}
void serial1Interrupt(void)
{
    if(serial1InterruptCheck == 1){
        serial_send_data();
        ball_move_item();
        ball_stat();
        A_using_item();
        A_get_item();
        B_using_item();
        B_get_item();
        if(firstCheck == 0){
            A_choose();
            B_choose(); 
        }
        for(int i = 0;i<14;i++){
            old_receive_buffer[i] = new_receive_buffer[i];
        }
        serial1InterruptCheck = 0;
    }
}
void serialEvent2(void)
{
    if((A_bluetooth_data = Serial2.read()) != -1){ //스마트폰 -> 아두이노 -> PC
    }
}
void serialEvent3(void)
{
    if((B_bluetooth_data = Serial3.read()) != -1){ //스마트폰 -> 아두이노 -> PC
    }
}


//***************************************************************************************************************//
//********************************************* function definition *********************************************//
//***************************************************************************************************************//

//***************************************************************************************************************//
//******************************************* Serial send data function *****************************************//
//***************************************************************************************************************//

void serial_send_data(void)
{
    ball_X_Cood_function();
    ball_Y_Cood_function();
    A_X_Cood_function();
    B_X_Cood_function();
    send_buffer[0] = 0xFF;
    send_buffer[1] = 0xFF;
    send_buffer[2] = 0x4;
    send_buffer[3] = ball_X_Cood_High;
    send_buffer[4] = ball_X_Cood_Low;
    send_buffer[5] = ball_Y_Cood_High;
    send_buffer[6] = ball_Y_Cood_Low;
    send_buffer[7] = ball_check_function();
    send_buffer[8] = A_X_Cood_High;
    send_buffer[9] = A_X_Cood_Low;
    send_buffer[10] = game_ready_function();
    send_buffer[11] = A_use_item_1_function();
    send_buffer[12] = A_use_item_2_function();
    send_buffer[13] = A_activate_or_delete_item_function();
    send_buffer[14] = A_move_function();
    send_buffer[15] = B_X_Cood_High;
    send_buffer[16] = B_X_Cood_Low;
    send_buffer[17] = B_use_item_1_function();
    send_buffer[18] = B_use_item_2_function();
    send_buffer[19] = B_activate_or_delete_item_function();
    send_buffer[20] = B_move_function();
    send_buffer[21] = insert_coin_function();
    send_buffer[22] = get_AR_item_function();
    send_buffer[23] = 0xFE;//end
    
    for(int i = 0 ; i <= 24 ; i++){
        checkSum+=send_buffer[i];
        Serial1.write(send_buffer[i]);
    }
    send_buffer[25] = checkSum ^ 0xFF;//check sum
    Serial1.write(send_buffer[25]);
}
void ball_X_Cood_function(void)
{//17,18번째 데이터 공의 X 좌표를 high , low 두 비트로 나눠서 표현하는 함수 
    ball_X_Cood_High = (unsigned char)((ball_X_Cood & 65280)>>8);
    ball_X_Cood_Low = (unsigned char)(ball_X_Cood & 255);
}
void ball_Y_Cood_function(void)
{//15,16번째 데이터 공의 Y 좌표를 high , low 두 비트로 나눠서 표현하는 함수
    ball_Y_Cood_High = (unsigned char)((ball_Y_Cood & 65280)>>8);
    ball_Y_Cood_Low = (unsigned char)(ball_Y_Cood & 255);
}
char ball_check_function(void)
{//14번째 데이터 공의 상태를 종합하는 함수
    char ball_check = 0;
    if(wall_crash == 1 || wall_crashCnt != 0){//벽에 부딪힘
        wall_crash = 0;
        ball_check += 1;    
        wall_crashCnt += 1;
        if(wall_crashCnt == 3)
            wall_crashCnt = 0;
    }
    if(A_get_score == 1 || A_get_scoreCnt != 0){//A 득점
        A_get_score = 0;
        ball_check += 2;
        A_get_scoreCnt += 1;
        if(A_get_scoreCnt == 3)
            A_get_scoreCnt = 0;
    }
    if(B_get_score == 1 || B_get_scoreCnt != 0){//B 득점 
        B_get_score = 0;
        ball_check += 4;
        B_get_scoreCnt += 1;
        if(B_get_scoreCnt == 3)
            B_get_scoreCnt = 0;
    }
    if(A_return == 1 || A_returnCnt != 0){//A 받아침 
        A_return = 0;
        ball_check += 8;
        A_returnCnt += 1;
        if(A_returnCnt == 3)
            A_returnCnt = 0;
    }
    if(B_return == 1 || B_returnCnt != 0){//B 받아침 
        B_return = 0;
        ball_check += 16;
        B_returnCnt += 1;
        if(B_returnCnt == 3)
            B_returnCnt = 0;
    }
    return ball_check;
}
void A_X_Cood_function(void)
{//12,13번째 데이터 라켓 A의 좌표를 high, low 두 비트로 나눠서 표현하는 함수 
    A_X_Cood_High = (unsigned char)((A_X_Cood & 65280)>>8);
    A_X_Cood_Low = (unsigned char)(A_X_Cood & 255);
}
char game_ready_function(void)
{//11번째 데이터 A 플레이어가 블루투스로 통해 보낸 신호 처리
    char game_ready = 0;
    if(A_pre_game_selected == 1 || A_pre_game_selectedCnt != 0){//선공게임 완료
        A_pre_game_selected = 0;
        game_ready += 1;
        A_pre_game_selectedCnt += 1;
        if(A_pre_game_selectedCnt == 3)
            A_pre_game_selectedCnt = 0;
    }
    if(B_pre_game_selected == 1 || A_pre_game_selectedCnt != 0){
        B_pre_game_selected = 0;
        game_ready += 2;
        B_pre_game_selectedCnt += 1;
        if(B_pre_game_selectedCnt == 3)
            B_pre_game_selectedCnt = 0;
    }
    if(A_AR_ready == 1 || A_AR_readyCnt != 0){
        A_AR_ready = 0;
        game_ready += 4;
        A_AR_readyCnt += 1;
        if(A_AR_readyCnt == 3)
            A_AR_readyCnt = 0;
    }
    if(B_AR_ready == 1 || B_AR_readyCnt != 0){
        B_AR_ready = 0;
        game_ready += 8;
        B_AR_readyCnt += 1;
        if(B_AR_readyCnt == 3)
            B_AR_readyCnt = 0;
    }
    if(single_mode_selection == 1 || single_mode_selectionCnt != 0){
        single_mode_selection = 0;
        game_ready += 16;
        single_mode_selectionCnt += 1;
        if(single_mode_selectionCnt == 3)
            single_mode_selectionCnt = 0;
    }
    if(PVP_mode_selection == 1 || PVP_mode_selectionCnt != 0){
        PVP_mode_selection = 0;
        game_ready += 32;
        PVP_mode_selectionCnt += 1;
        if(PVP_mode_selectionCnt == 3)
            PVP_mode_selectionCnt = 0;
    }
    if(completion_of_money_input == 1 || completion_of_money_inputCnt != 0){
        completion_of_money_input = 0;
        game_ready += 64;
        completion_of_money_inputCnt += 1;
        if(completion_of_money_inputCnt == 3)
            completion_of_money_inputCnt = 0;
    }
    return game_ready;
}
char A_use_item_1_function(void)
{//10번째 데이터
    char A_use_item_1
    if(A_use_fireball == 1 || A_use_fireballCnt != 0){//파이어볼 사용  
        A_use_fireball = 0;
        A_use_item_1 += 1;
        A_use_fireballCnt += 1;
        if(A_use_fireballCnt == 3)
            A_use_fireballCnt = 0;
    } 
    else if(A_use_tornado == 1 || A_use_tornadoCnt != 0){//토네이도 사용  
        A_use+tornado = 0;
        A_use_item_1 += 2;
        A_use_tornadoCnt += 1;
        if(A_use_tornado == 3)
            A_use_tornado = 0;
    } 
    else if(A_use_hacking == 1 || A_use_hackingCnt != 0){//해킹 사용  
        A_use_hacking = 0;
        A_use_item_1 += 4;
        A_use_hackingCnt += 1;
        if(A_use_hackingCnt == 3)
            A_use_hackingCnt = 0;
    }
    else if(A_use_EMP == 1 || A_use_EMPCnt != 0){//EMP 사용  
        A_use_EMP = 0;
        A_use_item_1 += 8;
        A_use_EMPCnt += 1;
        if(A_use_EMPCnt == 3)
            A_use_EMPCnt = 0;
    } 
    else if(A_use_changeup == 1 || A_use_changeupCnt != 0){//체인지업 사용  
        A_use_changeup = 0;
        A_use_item_1 += 16;
        A_use_changeupCnt += 1;
        if(A_use_changeupCnt == 3)
            A_use_changeupCnt = 0;
    }
    else if(A_use_iceball == 1 || A_use_iceballCnt != 0){//use iceball
        A_use_iceball = 0;
        A_use_item_1 += 16;
        A_use_iceballCnt += 1;
        if(A_use_iceballCnt == 3)
            A_use_iceballCnt = 0;
    }
    return A_use_item_1;
}
char A_use_item_2_function(void)
{
    char A_use_item_2 = 0;
    if(A_use_mine_1 == 1 || A_use_mine_1Cnt != 0){// A 지뢰 1위치 사용 
        A_use_mine_1 = 0
        A_use_item_2 += 1;
        A_use_mine_1Cnt += 1;
        if(A_use_mine_1Cnt == 3)
            A_use_mine_1Cnt = 0;
    }
    if(A_use_mine_2 == 1 || A_use_mine_2Cnt != 0){// A 지뢰 2위치 사용 
        A_use_mine_2 = 0
        A_use_item_2 += 2;
        A_use_mine_2Cnt += 1;
        if(A_use_mine_2Cnt == 3)
            A_use_mine_2Cnt = 0;
    }
    if(A_use_mine_3 == 1 || A_use_mine_3Cnt != 0){// A 지뢰 3위치 사용 
        A_use_mine_3 = 0
        A_use_item_2 += 4;
        A_use_mine_3Cnt += 1;
        if(A_use_mine_3Cnt == 3)
            A_use_mine_3Cnt = 0;
    }
    if(A_use_defender_1 == 1 || A_use_defender_1Cnt != 0){// A 수비수 1위치 사용
        A_use_defender_1 = 0;
        A_use_item_2 += 8;
        A_use_defender_1Cnt += 1;
        if(A_use_defender_1Cnt == 3)
            A_use_defender_1Cnt = 0;
    }
    if(A_use_defender_2 == 1 || A_use_defender_2Cnt != 0){//A 수비수 2위치 사용
        A_use_defender_2 = 0;
        A_use_item_2 += 16;
        A_use_defender_2Cnt += 1;
        if(A_use_defender_2Cnt == 3)
            A_use_defender_2Cnt = 0;
    }
    if(A_use_defender_3 == 1 || A_use_defender_3Cnt != 0){//A 수비수 3위치 사용
        A_use_defender_3 = 0;
        A_use_item_2 += 32;
        A_use_defender_3Cnt += 1;
        if(A_use_defender_3Cnt == 3)
            A_use_defender_3Cnt = 0;
    }
    return A_use_item_2;
}
char A_activate_or_delete_item_function(void)
{
    char A_activate_or_delete_item = 0;
    if(A_activated_mine_1 == 1 || A_activated_mine_1Cnt != 0){
        A_activated_mine_1 = 0;
        A_activate_or_delete_item += 1;
        A_activated_mine_1Cnt += 1;
        if(A_activated_mine_1Cnt == 3)
            A_activated_mine_1Cnt = 0;
    }
    if(A_activated_mine_2 == 1 || A_activated_mine_2Cnt != 0){
        A_activated_mine_2 = 0;
        A_activate_or_delete_item += 2;
        A_activated_mine_2Cnt += 1;
        if(A_activated_mine_2Cnt == 3)
            A_activated_mine_2Cnt = 0;
    }
    if(A_activated_mine_3 == 1 || A_activated_mine_3Cnt != 0){
        A_activated_mine_3 = 0;
        A_activate_or_delete_item += 4;
        A_activated_mine3Cnt += 1;
        if(A_activated_mine3Cnt == 3)
            A_activated_mine3Cnt = 0;
    }
    if(A_activated_defender_1 == 1 || A_activated_defender_1Cnt != 0){
        A_activated_defender_1 = 0;
        A_activate_or_delete_item += 8;
        A_activated_defender_1Cnt += 1;
        if(A_activated_defender_1Cnt == 3)
            A_activated_defender_1Cnt = 0;
    }
    if(A_activated_defender_2 == 1 || A_activated_defender_2Cnt != 0){
        A_activated_defender_2 = 0;
        A_activate_or_delete_item += 16;
        A_activated_defender_2Cnt += 1;
        if(A_activated_defender_2Cnt == 3)
            A_activated_defender_2Cnt = 0;
    }
    if(A_activated_defender_3 == 1 || A_activated_defender_3Cnt != 0){
        A_activated_defender_3 = 0;
        A_activate_or_delete_item += 32;
        A_activated_defender_3Cnt += 1;
        if(A_activated_defender_3Cnt == 3)
            A_activated_defender_3Cnt = 0;
    }
    if(A_delete_mine == 1 || A_delete_mineCnt != 0){
        A_delete_mine = 0;
        A_activate_or_delete_item += 64;
        A_delete_mineCnt += 1;
        if(A_delete_mineCnt == 3)
            A_delete_mineCnt = 0;
    }
    if(A_delete_defender == 1 || A_delete_defender != 0){
        A_delete_defender = 0;
        A_activate_or_delete_item += 128;
        A_delete_defenderCnt += 1;
        if(A_delete_defenderCnt == 3)
            A_delete_defenderCnt = 0;
    }
    return A_activate_or_delete_item;
}

char A_move_function(void)
{//9번째 데이터
    char A_move = 0;
    if(A_move_right == 1){// A 오른쪽으로 이동
        A_move_right = 0;
        A_move += 1;
    } 
    else if(A_move_left == 1){// A 왼쪽으로 이동
        A_move_left = 0;
        A_move += 2;
    } 
    else if(A_move_stop == 1){// A 정지
        A_move_stop = 0;
        A_move += 4;
    } 
    return A_move;
}
void B_X_Cood_function(void)
{//7,8번째 데이터 라켓 B의 좌표를 high, low 두 비트로 나눠서 표현하는 함수
    B_X_Cood_High = (unsigned char)((B_X_Cood & 65280)>>8);
    B_X_Cood_Low = (unsigned char)(B_X_Cood & 255);
}

char B_use_item_1_function(void)
{//10번째 데이터
    char B_use_item_1
    if(B_use_fireball == 1 || B_use_fireballCnt != 0){//파이어볼 사용  
        B_use_fireball = 0;
        B_use_item_1 += 1;
        B_use_fireballCnt += 1;
        if(B_use_fireballCnt == 3)
            B_use_fireballCnt = 0;
    } 
    if(B_use_tornado == 1 || B_use_tornadoCnt != 0){//토네이도 사용  
        B_use_tornado = 0;
        B_use_item_1 += 2;
        B_use_tornadoCnt += 1;
        if(B_use_tornado == 3)
            B_use_tornado = 0;
    } 
    if(B_use_hacking == 1 || B_use_hackingCnt != 0){//해킹 사용  
        B_use_hacking = 0;
        B_use_item_1 += 4;
        B_use_hackingCnt += 1;
        if(B_use_hackingCnt == 3)
            B_use_hackingCnt = 0;
    }
    if(B_use_EMP == 1 || B_use_EMPCnt != 0){//EMP 사용  
        B_use_EMP = 0;
        B_use_item_1 += 8;
        B_use_EMPCnt += 1;
        if(B_use_EMPCnt == 3)
            B_use_EMPCnt = 0;
    } 
    if(B_use_changeup == 1 || B_use_changeupCnt != 0){//체인지업 사용  
        B_use_changeup = 0;
        B_use_item_1 += 16;
        B_use_changeupCnt += 1;
        if(B_use_changeupCnt == 3)
            B_use_changeupCnt = 0;
    }
    if(B_use_iceball == 1 || B_use_iceballCnt != 0){//use iceball
        B_use_iceball = 0;
        B_use_item_1 += 16;
        B_use_iceballCnt += 1;
        if(B_use_iceballCnt == 3)
            B_use_iceballCnt = 0;
    }
    return B_use_item_1;
}
char B_use_item_2_function(void)
{
    char B_use_item_2 = 0;
    if(B_use_mine_1 == 1 || B_use_mine_1Cnt != 0){// B 지뢰 1위치 사용 
        B_use_mine_1 = 0;
        B_use_item_2 += 1;
        B_use_mine_1Cnt += 1;
        if(B_use_mine_1Cnt == 3)
            B_use_mine_1Cnt = 0;
    }
    if(B_use_mine_2 == 1 || B_use_mine_2Cnt != 0){// B 지뢰 2위치 사용 
        B_use_mine_2  = 0;
        B_use_item_2 += 2;
        B_use_mine_2Cnt += 1;
        if(B_use_mine_2Cnt == 3)
            B_use_mine_2Cnt = 0;
    }
    if(B_use_mine_3 == 1 || B_use_mine_3Cnt != 0){// B 지뢰 3위치 사용 
        B_use_mine_3 = 0;
        B_use_item_2 += 4;
        B_use_mine_3Cnt += 1;
        if(B_use_mine_3Cnt == 3)
            B_use_mine_3Cnt = 0;
    }
    if(B_use_defender_1 == 1 || B_use_defender_1Cnt != 0){// B 수비수 1위치 사용
        B_use_defender_1 = 0;
        B_use_item_2 += 8;
        B_use_defender_1Cnt += 1;
        if(B_use_defender_1Cnt == 3)
            B_use_defender_1Cnt = 0;
    }
    if(B_use_defender_2 == 1 || B_use_defender_2Cnt != 0){//B 수비수 2위치 사용
        B_use_defender_2 = 0;
        B_use_item_2 += 16;
        B_use_defender_2Cnt += 1;
        if(B_use_defender_2Cnt == 3)
            B_use_defender_2Cnt = 0;
    }
    if(B_use_defender_3 == 1 || B_use_defender_3Cnt != 0){//B 수비수 3위치 사용
        B_use_defender_3 = 0;
        B_use_item_2 += 32;
        B_use_defender_3Cnt += 1;
        if(B_use_defender_3Cnt == 3)
            B_use_defender_3Cnt = 0;
    }
    return B_use_item_2;
}
char B_activate_or_delete_item_function(void)
{
    char B_activate_or_delete_item = 0;
    if(B_activated_mine_1 == 1 || B_activated_mine_1Cnt != 0){
        B_activated_mine_1 = 0;
        B_activate_or_delete_item += 1;
        B_activated_mine_1Cnt += 1;
        if(B_activated_mine_1Cnt == 3)
            B_activated_mine_1Cnt = 0;
    }
    if(B_activated_mine_2 == 1 || B_activated_mine_2Cnt != 0){
        B_activated_mine_2 = 0;
        B_activate_or_delete_item += 2;
        B_activated_mine_2Cnt += 1;
        if(B_activated_mine_2Cnt == 3)
            B_activated_mine_2Cnt = 0;
    }
    if(B_activated_mine_3 == 1 || B_activated_mine_3Cnt != 0){
        B_activated_mine_3 = 0;
        B_activate_or_delete_item += 4;
        B_activated_mine3Cnt += 1;
        if(B_activated_mine3Cnt == 3)
            B_activated_mine3Cnt = 0;
    }
    if(B_activated_defender_1 == 1 || B_activated_defender_1Cnt != 0){
        B_activated_defender_1 = 0;
        B_activate_or_delete_item += 8;
        B_activated_defender_1Cnt += 1;
        if(B_activated_defender_1Cnt == 3)
            B_activated_defender_1Cnt = 0;
    }
    if(B_activated_defender_2 == 1 || B_activated_defender_2Cnt != 0){
        B_activated_defender_2 = 0;
        B_activate_or_delete_item += 16;
        B_activated_defender_2Cnt += 1;
        if(B_activated_defender_2Cnt == 3)
            B_activated_defender_2Cnt = 0;
    }
    if(B_activated_defender_3 == 1 || B_activated_defender_3Cnt != 0){
        B_activated_defender_3 = 0;
        B_activate_or_delete_item += 32;
        B_activated_defender_3Cnt += 1;
        if(B_activated_defender_3Cnt == 3)
            B_activated_defender_3Cnt = 0;
    }
    if(B_delete_mine == 1 || B_delete_mineCnt != 0){
        B_delete_mine = 0;
        B_activate_or_delete_item += 64;
        B_delete_mineCnt += 1;
        if(B_delete_mineCnt == 3)
            B_delete_mineCnt = 0;
    }
    if(B_delete_defender == 1 || B_delete_defender != 0){
        B_delete_defender = 0;
        B_activate_or_delete_item += 128;
        B_delete_defenderCnt += 1;
        if(B_delete_defenderCnt == 3)
            B_delete_defenderCnt = 0;
    }
    return B_activate_or_delete_item;
}
char B_move_function(void)
{   
    char B_move = 0;
    if(B_move_right == 1){
        B_move_right = 0;
        B_move += 1;
    } 
    else if(B_move_left == 1){
        B_move_left = 0;
        B_move += 2;
    } 
    else if(B_move_stop == 1){
        B_move_stop = 0;
        B_move += 4;
    } 
    return B_move;
}
char insert_coin_function(void)
{//3번째 데이터
    char insert_coin = 0;
    if(insert_coin_1000 == 1 || insert_coin_1000Cnt != 0){
        insert_coin_1000 = 0;
        insert_coin += 1;
        insert_coin_1000Cnt += 1;
        if(insert_coin_1000Cnt == 3)
            insert_coin_1000Cnt = 0;  
    } 
    else if(insert_coin_5000 == 1 || insert_coin_5000Cnt != 0){
        insert_coin_5000 = 0;
        insert_coin += 2;
        insert_coin_5000Cnt += 1;
        if(insert_coin_5000Cnt == 3)
            insert_coin_1000Cnt = 0;  
    } 
    else if(insert_coin_10000 == 1 || insert_coin_10000Cnt != 0){
        insert_coin_10000 = 0;
        insert_coin += 4;
        insert_coin_10000Cnt += 1;
        if(insert_coin_10000Cnt == 3)
            insert_coin_10000Cnt = 0;
    }
    return insert_coin;
}
char get_AR_item_function(void)
{
    char get_AR_item = 0;
    if(A_get_mine == 1 || A_get_mineCnt != 0){
        A_get_mine = 0;
        get_AR_item += 1;
        A_get_mineCnt +=1;
        if(A_get_mineCnt == 3)
            A_get_mineCnt = 0;
    }
    if(A_get_defender == 1 || A_get_defenderCnt != 0){
        A_get_defender = 0;
        get_AR_item += 2;
        A_get_defenderCnt += 1;
        if(A_get_defenderCnt == 3)
            A_get_defenderCnt = 0;
    }
    if(B_get_mine == 1 || B_get_mineCnt != 0){
        B_get_mine = 0;
        get_AR_item += 4;
        B_get_mineCnt +=1;
        if(B_get_mineCnt == 3)
            B_get_mineCnt = 0;
    }
    if(B_get_defender == 1 || B_get_defenderCnt != 0){
        B_get_defender = 0;
        get_AR_item += 8;
        B_get_defenderCnt += 1;
        if(B_get_defenderCnt == 3)
            B_get_defenderCnt = 0;
    }
    return get_AR_item;
}
//******************************************************************************************************************//
//******************************************* Serial receive data function *****************************************//
//******************************************************************************************************************//

void ball_move_item(void)
{
    if((new_receive_buffer[1] & 1)== 1 && (old_receive_buffer[1] & 1)== 0){
        if(ball_Y_Cood < 500)
            A_item = 1;
        else if(ball_Y_Cood > 500)
            B_item = 1;
    } 
    if((new_receive_buffer[1] & 2) == 2 && (old_receive_buffer[1] & 2)== 0){
        if(ball_Y_Cood < 500)
            A_item = 2;
        else if(ball_Y_Cood > 500)
            B_item = 2;
    }
    if((new_receive_buffer[1] & 4) == 4 && (old_receive_buffer[1] & 4)== 0){
        if(ball_Y_Cood < 500)
            A_item = 3;
        else if(ball_Y_Cood > 500)
            B_item = 3;
    }if((new_receive_buffer[1] & 8) == 8 && (old_receive_buffer[1] & 8)== 0){
        if(ball_Y_Cood < 500)
            A_item = 4;
        else if(ball_Y_Cood > 500)
            B_item = 4;
}

void ball_stat(void)
{
    if((new_receive_buffer[3] & 1 ) == 1 && (old_receive_buffer[3] & 1) == 0) firstAt = 1;//A 선공
    else if((new_receive_buffer[3] & 2 ) == 2 && (old_receive_buffer[3] & 2) == 0) firstAt = 2;//B 선공
    if((new_receive_buffer[3] & 8) == 8 && (old_receive_buffer[3] & 8) == 0){//게임 종료
        Serial2.write('T');
        Serial3.write('T');
        firstAt = 0;
        startCheck = 0;
        firstCheck = 0;
        ball_X_dir = 0;
        ball_Y_dir = 0;
        A_X_dir = 0;
        B_X_dir = 0;
        startDir = 0;
        step_ = 0;
        ball_X_timerCnt = 0;
        ball_X_timerLimit = 3;//start speed
        ball_X_timercheck = 0;
        ball_X_speedCheck = 0;
        ball_Y_timerCnt = 0;
        ball_Y_timerLimit = 3;//start speed
        ball_Y_timercheck = 0;
        ball_Y_speedCheck = 0;
        A_X_timerCnt = 0;
        A_X_timerLimit = 3;//start speed
        A_X_timercheck = 0;
        A_X_speedCheck = 0;
        B_X_timerCnt = 0;
        B_X_timerLimit = 3;//start speed
        B_X_timercheck = 0;
        B_X_speedCheck = 0;
        collision_check2 = 0;
        A_item = 0;
        B_item = 0;
        ball_Y_dirCheck1 = 0;
        ball_Y_dirCheck2 = 0;
        digitalWrite(led_top_pin,LOW);
        digitalWrite(led_left_pin,LOW);
        digitalWrite(led_right_pin,LOW);
        digitalWrite(led_bottom_pin,LOW);
    }
}
void A_using_item(void)
{//8번째 데이터 A 아이템 사용
    if(new_receive_buffer[4] != 0){
        if((new_receive_buffer[4] & 1) == 1 && (old_receive_buffer[4] & 1)== 0) Serial2.write('O');//파이어볼 사용
        if((new_receive_buffer[4] & 2) == 2 && (old_receive_buffer[4] & 2)== 0) Serial2.write('P');//토네이도 사용
        if((new_receive_buffer[4] & 4) == 4 && (old_receive_buffer[4] & 4)== 0){ B_hacking_check = 1; Serial2.write('Q');}//해킹 사용
        if((new_receive_buffer[4] & 8) == 8 && (old_receive_buffer[4] & 8)== 0) Serial2.write('R');//EMP 사용
        if((new_receive_buffer[4] & 16) == 16 && (old_receive_buffer[4] & 16)== 0) Serial2.write('S');//체인지업 사용
        if((new_receive_buffer[4] & 32) == 32 && (old_receive_buffer[4] & 32)== 0) Serial2.wrtie('');//아이스볼 사용 
    }
}
void A_get_item(void)
{//7번째 데이터
    if(new_receive_buffer[5] != 0){
        if((new_receive_buffer[5] & 1 ) == 1 && (old_receive_buffer[5] & 1)== 0) Serial2.write('J');// 파이어볼 획득
        if((new_receive_buffer[5] & 2 ) == 2 && (old_receive_buffer[5] & 2)== 0)  Serial2.write('K');// 토네이도 획득
        if((new_receive_buffer[5] & 4 ) == 4 && (old_receive_buffer[5] & 4)== 0) Serial2.write('L');// 해킹 획득
        if((new_receive_buffer[5] & 8 ) == 8 && (old_receive_buffer[5] & 8)== 0) Serial2.write('M');//EMP 획득
        if((new_receive_buffer[5] & 16 ) == 16 && (old_receive_buffer[5] & 16)== 0) Serial2.write('N');//change up 획득
        if((new_receive_buffer[5] & 32) == 32 && (old_receive_buffer[5] & 32)== 0) Serial2.wrtie('');//아이스볼 획득
    }
}
void completion_choose(void)
{//6번째 데이터
    if(new_receive_buffer[6] != 0){
        if((new_receive_buffer[6] & 1) == 1 && (old_receive_buffer[6] & 1)== 0){
            Serial2.write('A');//동전 투입 완료
            Serial3.write('A');//동전 투입 완료
        } 
        else if((new_receive_buffer[6] & 2) == 2 && (old_receive_buffer[6] & 2)== 0){
            Serial2.write('D');//모드 선택 완료
            Serial3.write('D');//모드 선택 완료
        } 
        else if((new_receive_buffer[6] & 4) == 4 && (old_receive_buffer[6] & 4)== 0){
            Serial3.write('G');//선공 게임 선택 완료
            Serial3.write('G');//선공 게임 선택 완료
        } 
        else if((new_receive_buffer[6] & 8) == 8 && (old_receive_buffer[6] & 8)== 0){
            Serial2.write('H');//증강 완료
            Serial3.write('H');//증강 완료
        } 
    }
}
void B_using_item(void)
{//5번째 데이터
    if(new_receive_buffer[7] != 0){
        if((new_receive_buffer[7] & 1) == 1 && (old_receive_buffer[7] & 1)== 0) Serial3.write('O');//파이어볼 사용
        else if((new_receive_buffer[7] & 2) == 2 && (old_receive_buffer[7] & 2)== 0) Serial3.write('P');//토네이도 사용
        else if((new_receive_buffer[7] & 4) == 4 && (old_receive_buffer[7] & 4)== 0){ A_hacking_check = 1; Serial3.write('Q');}//해킹 사용
        else if((new_receive_buffer[7] & 8) == 8 && (old_receive_buffer[7] & 8)== 0)  Serial3.write('R');// EMP 사용
        else if((new_receive_buffer[7] & 16) == 16 && (old_receive_buffer[7] & 16)== 0) Serial3.write('S');// 체인지업 사용
        else if((new_receive_buffer[7] & 32) == 32 && (old_receive_buffer[7] & 32)== 0) Serial3.write('');//아이스볼 사용
    }
}
void B_get_item(void)
{//4번째 데이터
    if(new_receive_buffer[8] != 0){
        if((new_receive_buffer[8] & 1 ) == 1 && (old_receive_buffer[8] & 1)== 0) Serial3.write('J');// 파이어볼 획득
        else if((new_receive_buffer[8] & 2 ) == 2 && (old_receive_buffer[8] & 2)== 0) Serial3.write('K');// 토네이도 획득
        else if((new_receive_buffer[8] & 4 ) == 4 && (old_receive_buffer[8] & 4)== 0) Serial3.write('L');// 해킹 획득
        else if((new_receive_buffer[8] & 8 ) == 8 && (old_receive_buffer[8] & 8)== 0) Serial3.write('M');//EMP 획득
        else if((new_receive_buffer[8] & 16 ) == 16 && (old_receive_buffer[8] & 16)== 0) Serial3.write('N');//change up 획득
        else if((new_receive_buffer[8] & 32 ) == 32 && (old_receive_buffer[8] & 32)== 0) Serial3.write('N');//아이스볼  획득
    }
}
//******************************************************************************************************************//
//*********************************************** The others function **********************************************//
//******************************************************************************************************************//
void racketReset(void)
{
    char check = 0;
    char A_X_check = 0;
    char B_X_check = 0;
    int delay_ = 100;
    digitalWrite(A_X_dirPin,0);
    digitalWrite(B_X_dirPin,0);
    while(check != 2){
        if(A_X_check == 0){
            if(digitalRead(A_X_limitSwitch1) == LOW){
                A_X_check = 1;
                check += 1;
                delay_+=100;
            }
            digitalWrite(A_X_stpPin, HIGH);
            delayMicroseconds(delay_);
            digitalWrite(A_X_stpPin, LOW);
            delayMicroseconds(delay_);
        }
        if(B_X_check == 0){
            if(digitalRead(B_X_limitSwitch1) == LOW){
                B_X_check = 1;
                check += 1;
                delay_+=100;
            }
            digitalWrite(B_X_stpPin, HIGH);
            delayMicroseconds(delay_);
            digitalWrite(B_X_stpPin, LOW);
            delayMicroseconds(delay_);
        }
    }
    digitalWrite(A_X_dirPin,1);
    digitalWrite(B_X_dirPin,1);
    A_X_dir = 1; B_X_dir =1;
    for (int i = 0; i < X/2; i++) {
        digitalWrite(A_X_stpPin,HIGH);
        digitalWrite(B_X_stpPin,HIGH);
        delayMicroseconds(400);
        digitalWrite(A_X_stpPin,LOW);
        digitalWrite(B_X_stpPin,LOW);
        delayMicroseconds(400);
    }
    A_X_Cood = X/2;
    B_X_Cood = X/2;
}

void A_Collision_check(void)
{
    if(ball_X_Cood < A_X_Cood){//라켓의 왼쪽
        if(A_X_Cood - RACKETSECTOR/2 <= ball_X_Cood){//90
            angle = 90;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(A_X_Cood - RACKETSECTOR*3/2 <= ball_X_Cood && ball_X_Cood <= A_X_Cood - RACKETSECTOR/2){//70
            angle = 110;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(A_X_Cood - RACKETSECTOR*5/2 <= ball_X_Cood && ball_X_Cood <= A_X_Cood - RACKETSECTOR*3/2){//60
            angle = 120;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(A_X_Cood - RACKETSECTOR*9/2 <= ball_X_Cood && ball_X_Cood <= A_X_Cood - RACKETSECTOR*5/2){//50
            angle = 130;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(A_X_Cood - RACKETSECTOR*17/2 <= ball_X_Cood && ball_X_Cood <= A_X_Cood - RACKETSECTOR*9/2){//40
            angle = 140;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(ball_X_Cood - BALLSIZE/2 <= A_X_Cood - RACKETSECTOR*17/2 && A_X_Cood - RACKETSECTOR*17/2 <= ball_X_Cood + BALLSIZE/2){//30
            angle = 150;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }
    }else if(ball_X_Cood > A_X_Cood){//라켓의 오른쪽
        if(ball_X_Cood <= A_X_Cood + RACKETSECTOR/2){//90
            angle = 90;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(A_X_Cood + RACKETSECTOR/2 <= ball_X_Cood && ball_X_Cood <= A_X_Cood + RACKETSECTOR*3/2){//70
            angle = 70;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(A_X_Cood + RACKETSECTOR*3/2 <= ball_X_Cood && ball_X_Cood <= A_X_Cood + RACKETSECTOR*5/2){//60
            angle = 60;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(A_X_Cood + RACKETSECTOR*5/2 <= ball_X_Cood && ball_X_Cood <= A_X_Cood + RACKETSECTOR*9/2){//50
            angle = 50;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(A_X_Cood + RACKETSECTOR*9/2 <= ball_X_Cood && ball_X_Cood <= A_X_Cood + RACKETSECTOR*17/2){//40
            angle = 40;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(ball_X_Cood - BALLSIZE/2 <= A_X_Cood + RACKETSECTOR*17/2 && A_X_Cood + RACKETSECTOR*17/2 <= ball_X_Cood + BALLSIZE/2){//30
            angle = 30;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }
    }else if(ball_X_Cood == A_X_Cood){
        angle = 90;
        setAngle(angle,speed);
        collision_check2 = 0;
        A_return = 1;
    }
    if(collision_check2 == 1){//Goal B득점
        Serial2.write('W');
        B_get_score = 1;
        restart_check = 1;
        angle = getAngle(angle,HORIZONTAL);
        setAngle(angle,speed);
        digitalWrite(led_bottom_pin,HIGH);
        Serial3.write('W');
        racketReset();
    }
}
void B_Collision_check(void)
{
    if(ball_X_Cood < B_X_Cood){
        if(B_X_Cood - RACKETSECTOR/2 <= ball_X_Cood){//90
            angle = 270;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }else if(B_X_Cood - RACKETSECTOR*3/2 <= ball_X_Cood && ball_X_Cood <= B_X_Cood - RACKETSECTOR/2){//70
            angle = 250;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }else if(B_X_Cood - RACKETSECTOR*5/2 <= ball_X_Cood && ball_X_Cood <= B_X_Cood - RACKETSECTOR*3/2){//60
            angle = 240;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }else if(B_X_Cood - RACKETSECTOR*9/2 <= ball_X_Cood && ball_X_Cood <= B_X_Cood - RACKETSECTOR*5/2){//50
            angle = 230;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }else if(B_X_Cood - RACKETSECTOR*17/2 <= ball_X_Cood && ball_X_Cood <= B_X_Cood - RACKETSECTOR*9/2){//40
            angle = 220;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }else if(ball_X_Cood - BALLSIZE/2 <= B_X_Cood - RACKETSECTOR*17/2 && B_X_Cood - RACKETSECTOR*17/2 <= ball_X_Cood + BALLSIZE/2){//30
            angle = 210;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }
    }else if(ball_X_Cood > B_X_Cood){
        if(ball_X_Cood <= B_X_Cood + RACKETSECTOR/2 ){//90
            angle = 270;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }else if(B_X_Cood + RACKETSECTOR/2 <= ball_X_Cood && ball_X_Cood <= B_X_Cood + RACKETSECTOR*3/2){//70
            angle = 290;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }else if(B_X_Cood + RACKETSECTOR*3/2 <= ball_X_Cood && ball_X_Cood <= B_X_Cood + RACKETSECTOR*5/2){//60
            angle = 300;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }else if(B_X_Cood + RACKETSECTOR*5/2 <= ball_X_Cood && ball_X_Cood <= B_X_Cood + RACKETSECTOR*9/2){//50
            angle = 310;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }else if(B_X_Cood + RACKETSECTOR*9/2 <= ball_X_Cood && ball_X_Cood <= B_X_Cood + RACKETSECTOR*17/2){//40
            angle = 320;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }
        else if(ball_X_Cood - BALLSIZE/2 <= B_X_Cood + RACKETSECTOR*17/2 && B_X_Cood + RACKETSECTOR*17/2 <= ball_X_Cood + BALLSIZE/2){//30
            angle = 330;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }
    }else if(ball_X_Cood == B_X_Cood){//4번
        angle = 270;
        setAngle(angle,speed);
        collision_check2 = 0;
        B_return = 1;
    }
    if(collision_check2 == 1){//Goal A득점
        Serial2.write('V');
        A_get_score = 1;
        restart_check = 1;
        angle = getAngle(angle,HORIZONTAL);
        setAngle(angle,speed);
        digitalWrite(led_top_pin,HIGH);
        Serial3.write('V');
        racketReset();
    }
}
void A_change_left_dir(void)
{
    if(A_hacking_check==0){ // 해킹 아닐때
        A_X_dir = 0;
        digitalWrite(A_X_dirPin,A_X_dir);
    }else if(A_hacking_check == 1){ // 해킹일때
        A_X_dir = 1;
        digitalWrite(A_X_dirPin,A_X_dir);
    }
    A_move_left = 1;
}
void A_change_right_dir(void)
{
    if(A_hacking_check==0){ // 해킹 아닐때
        A_X_dir = 1;
        digitalWrite(A_X_dirPin,A_X_dir);
    }else if(A_hacking_check == 1){ //해킹 일때
        A_X_dir = 0;
        digitalWrite(A_X_dirPin,A_X_dir);
    }
    A_move_right = 1;
}
void B_change_left_dir(void)
{
    if(B_hacking_check==0){ // 해킹 아닐때
        B_X_dir = 1;
        digitalWrite(B_X_dirPin,B_X_dir);
    }else if(B_hacking_check == 1){ // 해킹일때
        B_X_dir = 0;
        digitalWrite(B_X_dirPin,B_X_dir);
    }
    B_move_left = 1;
}
void B_change_right_dir(void)
{
    if(B_hacking_check==0){ // 해킹 아닐때
        B_X_dir = 0;
        digitalWrite(B_X_dirPin,B_X_dir);
    }else if(B_hacking_check == 1){ //해킹 일때
        B_X_dir = 1;
        digitalWrite(B_X_dirPin,B_X_dir);
    }
    B_move_right = 1;
}
void serial2InterruptBeforeInGame(void)
{
    switch(A_bluetooth_data){
        case 'a' : completion_of_money_input = 1; Serial3.write('A'); break; // 동전 투입 완료
        case 'b' : A_mode_selection_left = 1; break;// 모드 선택 좌
        case 'c' : A_mode_selection_right = 1; break;// 모드 선택 우
        case 'd' : A_mode_selected = 1; Serial3.write('D'); break;// 모드 선택
        case 'e' : A_controller_left = 1; break;// 컨트롤러 선택 좌
        case 'f' : A_controller_right = 1; break;// 컨트롤러 선택 우
        case 'g' : A_controller_selected = 1; break;// 컨트롤러 선택
        case 'h' : A_pre_game_selected = 1; break;// 선공 게임 선택
    }
    A_bluetooth_data = 0;
}
void serial2InterruptAfterInGame(void)
{
    switch(A_bluetooth_data){
        case 'j' : A_moveCtl = 1; A_X_timerLimit = 7; A_change_left_dir(); break;//왼쪽으로 1속도 이동
        case 'k' : A_moveCtl = 2; A_X_timerLimit = 6; A_change_left_dir(); break;//왼쪽으로 2속도 이동
        case 'l' : A_moveCtl = 3; A_X_timerLimit = 5; A_change_left_dir(); break;//왼쪽으로 3속도 이동
        case 'm' : A_moveCtl = 4; A_X_timerLimit = 4; A_change_left_dir(); break;//왼쪽으로 4속도 이동
        case 'n' : A_moveCtl = 5; A_X_timerLimit = 3; A_change_left_dir(); break;//왼쪽으로 5속도 이동
        case 'o' : A_moveCtl = 0;  A_move_stop = 1; break;// 정지
        case 'p' : A_moveCtl = 1; A_X_timerLimit = 7; A_change_right_dir(); break;//오른쪽으로 1속도 이동
        case 'q' : A_moveCtl = 2; A_X_timerLimit = 6; A_change_right_dir(); break;//오른쪽으로 2속도 이동
        case 'r' : A_moveCtl = 3; A_X_timerLimit = 5; A_change_right_dir(); break;//오른쪽으로 3속도 이동
        case 's' : A_moveCtl = 4; A_X_timerLimit = 4; A_change_right_dir(); break;//오른쪽으로 4속도 이동
        case 't' : A_moveCtl = 5; A_X_timerLimit = 3; A_change_right_dir(); break;//오른쪽으로 5속도 이동
        case 'u' : A_use_fireball = 1; break; //파이어볼사용
        case 'v' : A_use_tornado = 1; break;//토네이도 사용
        case 'w' : A_use_hacking = 1; break;//해킹 사용
        case 'x' : A_use_EMP = 1; break;//EMP 사용
        case 'y' : A_use_changeup = 1; break;//CHANGE UP 사용
    }
    A_bluetooth_data = 0;
}
void serial3InterruptBeforeInGame(void)
{
    switch(B_bluetooth_data){
        case 'a' : completion_of_money_input = 1; Serial2.write('A'); break; // 동전 투입 완료
        case 'b' : A_mode_selection_left = 1; break;// 모드 선택 좌
        case 'c' : A_mode_selection_right = 1; break;// 모드 선택 우
        case 'd' : A_mode_selected = 1; Serial2.write('D'); break;// 모드 선택
        case 'e' : B_controller_left = 1; break;// 컨트롤러 선택 좌
        case 'f' : B_controller_right = 1; break;// 컨트롤러 선택 우
        case 'g' : B_controller_selected = 1; break;// 컨트롤러 선택
        case 'h' : B_pre_game_selected = 1; break;// 선공 게임 선택
    } 
    B_bluetooth_data = 0;
}
void serial3InterruptAfterInGame(void)
{
    switch(B_bluetooth_data){
        case 'j' : B_moveCtl = 1; B_X_timerLimit = 7; B_change_left_dir(); break;//왼쪽으로 1속도 이동
        case 'k' : B_moveCtl = 2; B_X_timerLimit = 6; B_change_left_dir(); break;//왼쪽으로 2속도 이동
        case 'l' : B_moveCtl = 3; B_X_timerLimit = 5; B_change_left_dir(); break;//왼쪽으로 3속도 이동
        case 'n' : B_moveCtl = 4; B_X_timerLimit = 4; B_change_left_dir(); break;//왼쪽으로 4속도 이동
        case 'm' : B_moveCtl = 5; B_X_timerLimit = 3; B_change_left_dir(); break;//왼쪽으로 5속도 이동
        case 'o' : B_moveCtl = 0; B_move_stop = 1; break;// 정지
        case 'p' : B_moveCtl = 1; B_X_timerLimit = 7; B_change_right_dir(); break;//오른쪽으로 1속도 이동
        case 'q' : B_moveCtl = 2; B_X_timerLimit = 6; B_change_right_dir(); break;//오른쪽으로 2속도 이동
        case 'r' : B_moveCtl = 3; B_X_timerLimit = 5; B_change_right_dir(); break;//오른쪽으로 3속도 이동
        case 's' : B_moveCtl = 4; B_X_timerLimit = 4; B_change_right_dir(); break;//오른쪽으로 4속도 이동
        case 't' : B_moveCtl = 5; B_X_timerLimit = 3; B_change_right_dir(); break;//오른쪽으로 5속도 이동
        case 'u' : B_use_fireball = 1; break;//파이어볼사용
        case 'v' : B_use_tornado = 1; break;//토네이도 사용
        case 'w' : B_use_hacking = 1; break;//해킹 사용
        case 'x' : B_use_EMP = 1; break; //EMP 사용
        case 'y' : B_use_changeup = 1; break;//CHANGE UP 사용
    } 
    B_bluetooth_data = 0;
}
void loop(void)
{
    if(firstCheck == 0){// 선공게임이 정해지지 않았을때 ( 게임 시작 전 )
        firstCheckFuntion();
    }else if(firstCheck == 1){ // 선공게임 정해진 후 ( 게임 중 )
        gameControl();
    }  
}