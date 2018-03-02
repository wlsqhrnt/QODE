#include <DueTimer.h>
#define HORIZONTAL 1
#define VERTICAL 2
#define X 1154
#define Y 1373
#define RACKETSIZE (int)(9*X)/74
#define BALLSIZE (int)(5.5*X)/74
#define RACKETSECTOR (int)RACKETSIZE/15

int startCheck = 0;
char send_buffer[22];
int startAngle;
unsigned char new_receive_buffer[14];
unsigned char old_receive_buffer[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// detail stat variable for check 상시 1 or 0 으로 바뀌며 PC쪽으로 데이터를 수신할때 하는 버퍼값을 정하는 변수 
// send data variable
char wall_crash = 0; //벽에 부딪힘
char A_return = 0; //A 받아침
char B_return = 0; //B 받아침
char A_get_score = 0; // A 득점
char B_get_score = 0; // B 득점
char completion_of_money_input = 0; // 동전 투입 완료
char A_mode_selection_left = 0; //라켓 A 모드 선택 좌
char A_mode_selection_right = 0; //라켓 A 모드 선택 우
char A_mode_selected = 0; //라켓 A 모드 선택 완료
char A_controller_left = 0; // 라켓 A 컨트롤러 선택 좌
char A_controller_right = 0; // 라켓 A 컨트롤러 선택 우
char A_controller_selected = 0; // 라켓 A 컨트롤러 선택 완료
char A_pre_game_selected = 0; //라켓 A 선공게임 완료
char A_use_fireball = 0; //라켓 A 파이어볼 사용
char A_use_tornado = 0; //라켓 A 토네이도 사용
char A_use_hacking = 0; //라켓 A 해킹 사용
char A_release_hacking = 0; // 라켓 A 해킹 해제
char A_use_EMP = 0; //라켓 A EMP사용
char A_use_changeup = 0;//라켓 A change up 사용
char A_move_right = 0;// 라켓 A 오른쪽으로 움직임
char A_move_left = 0;//라켓 A 왼쪽으로 움직임
char A_move_stop = 0;//라켓 A 멈춤
char B_controller_left = 0;//라켓 B 컨트롤러 선택 좌
char B_controller_right = 0;//라켓 B 컨트롤러 선택 우
char B_controller_selected = 0; // 라켓 B 컨트롤러 선택 완료
char B_pre_game_selected = 0;//라켓 B 선공게임 완료
char B_use_fireball = 0;//라켓 B 파이어볼 사용
char B_use_tornado = 0;//라켓 B 토네이도 사용
char B_use_hacking = 0;//라켓 B 해킹 사용
char B_release_hacking = 0;//라켓 B 해킹 해제
char B_use_EMP = 0;// 라켓 B EMP사용
char B_use_changeup = 0;//라켓 B changeup 사용
char B_move_right = 0;//라켓 B 오른쪽 움직임
char B_move_left = 0;//라켓 B 왼쪽으로 움직임
char B_move_stop = 0;//라켓 B 멈춤
char insert_coin_1000 = 0;//1000원 투입
char insert_coin_5000 = 0;//5000원 투입
char insert_coin_10000 = 0;//10000원 투입시
// 3번 송신을 위한 카운트 변수
char wall_crashCnt = 0;
char A_returnCnt = 0; //A 받아침
char B_returnCnt = 0; //B 받아침
char A_get_scoreCnt = 0; // A 득점
char B_get_scoreCnt = 0; // B 득점
char A_pre_game_selectedCnt = 0;
char A_controller_selectedCnt = 0;
char A_controller_rightCnt = 0;
char A_controller_leftCnt = 0;
char A_mode_selectedCnt = 0;
char A_mode_selection_rightCnt = 0;
char A_mode_selection_leftCnt = 0;
char completion_of_money_inputCnt = 0;
char A_use_fireballCnt = 0;
char A_use_tornadoCnt = 0;
char A_use_hackingCnt = 0;
char A_release_hackingCnt = 0;
char A_use_EMPCnt = 0;
char A_use_changeupCnt = 0;
char B_pre_game_selectedCnt = 0;
char B_controller_selectedCnt = 0;
char B_controller_rightCnt = 0;
char B_controller_leftCnt = 0;
char B_use_fireballCnt = 0;
char B_use_tornadoCnt = 0;
char B_use_hackingCnt  = 0;
char B_release_hackingCnt = 0;
char B_use_EMPCnt = 0;
char B_use_changeupCnt = 0;
char insert_coin_1000Cnt = 0;
char insert_coin_5000Cnt = 0;
char insert_coin_10000Cnt = 0;
//stat variable for check 디테일한 상태 변수들의 값을 확인하고 변하는 값들.
unsigned char ball_check = 0; //벽 충돌 여부 및 득점인지 받아쳤는지를 알려주는 값
unsigned char A_game_ready = 0;// A 플레이어의 게임 시작 전 상태를 알려주는 값
unsigned char A_use_item = 0;// A 플레이어의 게임중 아이템 사용 상태를 알려주는 값
unsigned char A_move = 0;// A 플레이어의 게임중 움직임 상태를 알려주는 값
unsigned char B_game_ready = 0;// B 플레이어의 게임 시작 전 상태를 알려주는 값
unsigned char B_use_item = 0;// B 플레이어의 게임중 아이템 사용 상태를 알려주는 값
unsigned char B_move = 0;// B 플레이어의 게임중 움직임 상태를 알려주는 값
unsigned char insert_coin = 0;// 플레이어들의 동전 투입 상태를 알려주는 값
// receive data variable
//공 아이템 사용
char move_fireball = 0;
char move_tornado = 0;
char move_change_up = 0;
//Coordinates
long ball_X_Cood = 0; // 공의 X 좌표
long ball_Y_Cood = 0;//  공의 Y 좌표
long A_X_Cood = 0; // 라켓 A의 좌표
long B_X_Cood = 0;// 라켓 B의 좌표
//Coordinates for send data
unsigned char ball_X_Cood_High = 0;
unsigned char ball_X_Cood_Low = 0;
unsigned char ball_Y_Cood_High = 0;
unsigned char ball_Y_Cood_Low = 0;
unsigned char A_X_Cood_High = 0;
unsigned char A_X_Cood_Low = 0;
unsigned char B_X_Cood_High = 0;
unsigned char B_X_Cood_Low = 0;
unsigned char checkSum = 0;// start와 end 필드를 제외한 나머지 필드들의 합 XOR FF 한 값.
//ball variable
char ball_X_dir = 0;
char ball_Y_dir = 0;
int ball_X_stpPin = 2;
int ball_X_dirPin = 3;
int ball_Y_stpPin = 4;
int ball_Y_dirPin = 5;
int ball_X_limitSwitch1 = 22;
int ball_X_limitSwitch2 = 23;
int ball_Y_limitSwitch1 = 24;
int ball_Y_limitSwitch2 = 25;
//A_racket variable
char A_X_dir = 0;
int A_X_stpPin = 6;
int A_X_dirPin = 7;
int A_X_limitSwitch1 = 26;
int A_X_limitSwitch2 = 27;
char A_bluetooth_data = 0;
char A_hacking_check = 0; //상대방이 해킹 아이템을 사용하면 1 아니면 0
char A_GoStop = 0;
char A_moveCtl = 0;
//B_racket variable
char B_X_dir = 0;
int B_X_stpPin = 8;
int B_X_dirPin = 9;
int B_X_limitSwitch1 = 28;
int B_X_limitSwitch2 = 29;
char B_bluetooth_data = 0;
char B_hacking_check;//상대방이 해킹 아이템을 사용하면 1 아니면 0
char B_GoStop = 0;
char B_moveCtl = 0;
//ect variable
char firstAt = 0; // 시작 방향이 어디인지.
char startDir = 0;
int step_ =  0;
int data_len = 0;
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
//timer variable
int ball_X_timerCnt = 0;
int ball_X_timerLimit = 8;//start speed
int ball_X_timercheck = 0;
int ball_X_speedCheck = 0;
int ball_X_maxSpeed = 0;
int ball_Y_timerCnt = 0;
int ball_Y_timerLimit = 15;//start speed
int ball_Y_timercheck = 0;
int ball_Y_speedCheck = 0;
int ball_Y_maxSpeed = 0;
int A_X_timerCnt = 0;
int A_X_timerLimit = 8;//start speed
int A_X_timercheck = 0;
int A_X_speedCheck = 0;
int B_X_timerCnt = 0;
int B_X_timerLimit = 8;//start speed
int B_X_timercheck = 0;
int B_X_speedCheck = 0;
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

int restart_check = 0;
int restartCnt = 0;
//function prototype
void serial_send_data(void);
void ball_X_Cood_function(void);
void ball_Y_Cood_function(void);
void ball_check_function(void);
void A_X_Cood_function(void);
void A_game_ready_function(void);
void A_use_item_function(void);
void A_move_function(void);
void B_X_Cood_function(void);
void B_game_ready_function(void);
void B_use_item_function(void);
void B_move_function(void);
void insert_coin_function(void);
void reset_data_after_send(void);
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
void BallMove60Angle(void);
void BallMove45Angle(void);
void BallMove30Angle(void);
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
    Timer1.attachInterrupt(ball_X_timerHandler).start(100);
    Timer2.attachInterrupt(ball_Y_timerHandler).start(100);
    Timer3.attachInterrupt(A_X_timerHandler).start(100);
    Timer4.attachInterrupt(B_X_timerHandler).start(100); //100us
    Timer5.attachInterrupt(restart).start(1000);//1ms
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
    pinMode(ball_Y_limitSwitch1,INPUT);
    pinMode(ball_Y_limitSwitch2,INPUT);
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
        startAngle = rand() % 100 + 40; // 40~ 140;
        startCheck = 1;
    }
    if(firstAt == 1){ //A 선공
        ball_Y_dir = 0;
        digitalWrite(ball_Y_dirPin,ball_Y_dir);
        firstCheck = 1;
        setAngle(startAngle,speed);
    }else if(firstAt == 2){//B선공 
        ball_Y_dir = 1;
        digitalWrite(ball_Y_dirPin,ball_Y_dir);
        firstCheck = 1;
        angle = getAngle(startAngle,HORIZONTAL);
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
            if(ball_X_dir != 1){
                ball_X_dir = 1; digitalWrite(ball_X_dirPin,ball_X_dir);
            }
            x_move_check = 1;
        } else if (ndx < ball_X_Cood ) { // 좌측에 있을 경우
            if(ball_X_dir != 0){
                ball_X_dir = 0; digitalWrite(ball_X_dirPin,ball_X_dir);   
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
    if(digitalRead(ball_X_limitSwitch1) == LOW && ball_X_dir == 0){
        ball_X_dir = 1;
        digitalWrite(ball_X_dirPin,ball_X_dir);
        ball_X_Cood = 0;
        wall_crash = 1; 
        ball_X_speedCheck = 0;
        ball_X_timerLimit = 8;
        ball_X_timerCnt = 0;
        digitalWrite(led_left_pin,HIGH);
        int new_angle = getAngle(angle,VERTICAL);
        setAngle(new_angle,speed);
        left_startCnt = 1; 
    }
    if(digitalRead(ball_X_limitSwitch2) == LOW && ball_X_dir == 1){
        ball_X_dir = 0;
        digitalWrite(ball_X_dirPin,ball_X_dir);
        ball_X_Cood = 1154;
        wall_crash = 1;
        ball_X_speedCheck = 0;
        ball_X_timerLimit = 8;
        ball_X_timerCnt = 0;
        digitalWrite(led_right_pin,HIGH);
        int new_angle = getAngle(angle,VERTICAL);
        setAngle(new_angle,speed);
        right_startCnt = 1;
    }
    if(digitalRead(ball_Y_limitSwitch1) == LOW && ball_Y_dir == 1){
        ball_Y_dir = 0;
        digitalWrite(ball_Y_dirPin,ball_Y_dir);
        collision_check2 = 1;
        ball_Y_Cood = 0;
        ball_Y_speedCheck = 0;
        ball_Y_timerLimit = 12;
        ball_Y_timerCnt = 0;
        if(A_hacking_check == 1)
            A_hacking_check = 0;
        A_Collision_check();
        B_item = 0;
    }
    if(digitalRead(ball_Y_limitSwitch2) == LOW && ball_Y_dir == 0){
        ball_Y_dir = 1;
        digitalWrite(ball_Y_dirPin,ball_Y_dir);
        collision_check2 = 1;
        ball_Y_Cood = 1343;
        ball_Y_speedCheck = 0;
        ball_Y_timerLimit = 12;
        ball_Y_timerCnt = 0;
        if(B_hacking_check == 1)
            B_hacking_check = 0;
        B_Collision_check();
        A_item = 0;
    }
    if(digitalRead(A_X_limitSwitch1) == LOW && A_X_dir == 0){
        A_X_dir = 1; digitalWrite(A_X_dirPin,A_X_dir);
        A_X_Cood = 0; A_X_timerLimit = 8;
        A_X_timerCnt = 0;
    }
    if(digitalRead(A_X_limitSwitch2) == LOW && A_X_dir == 1){
        A_X_dir = 0; digitalWrite(A_X_dirPin,A_X_dir);
        A_X_Cood = X; A_X_timerLimit = 8;
        A_X_timerCnt = 0;
    }
    if(digitalRead(B_X_limitSwitch1) == LOW && B_X_dir == 1){
        B_X_dir = 0; digitalWrite(B_X_dirPin,B_X_dir);
        B_X_Cood = 0; B_X_timerLimit = 8;
        B_X_timerCnt = 0;
    }
    if(digitalRead(B_X_limitSwitch2) == LOW && B_X_dir == 0){
        B_X_dir = 1; digitalWrite(B_X_dirPin,B_X_dir);
        B_X_Cood = X; B_X_timerLimit = 8;
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
            if(ball_X_dir == 0 && ball_X_Cood > 0 )
                ball_X_Cood--;
            else if(ball_X_dir == 1 && ball_X_Cood < 1160)
                ball_X_Cood++;
        }else if(ball_X_timercheck == 1){
            digitalWrite(ball_X_stpPin,LOW);
            ball_X_timercheck = 0;
            x_move_check = 0;
        }
        ball_X_timerCnt = 0;
        ball_X_speedCheck++;
        if(ball_X_timerLimit > 6 && ball_X_speedCheck == 100){
            ball_X_timerLimit-=1;
            ball_X_speedCheck=0;
        }
    }
    if(ball_Y_timerCnt >= ball_Y_timerLimit && collision_check2 == 0
            &&y_move_check == 1){//ball Y Motor timer
        if(ball_Y_timercheck == 0){
            digitalWrite(ball_Y_stpPin,HIGH);
            ball_Y_timercheck = 1;
            if(ball_Y_dir == 0 && ball_Y_Cood < 1345 )
                ball_Y_Cood++;
            else if(ball_Y_dir == 1 && ball_Y_Cood > 0)
                ball_Y_Cood--;
            if(A_item == 2 || B_item == 2)
                tornadoCnt++;
        }else if(ball_Y_timercheck == 1){
            digitalWrite(ball_Y_stpPin,LOW);
            ball_Y_timercheck = 0;
            y_move_check = 0;
        }
        ball_Y_timerCnt = 0;
        ball_Y_speedCheck++;
        if(ball_Y_timerLimit > 8 && ball_Y_speedCheck == 300){//가
            ball_Y_timerLimit-=1;
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
                    B_X_Cood--;
                }else if(B_X_dir == 0){
                    B_X_Cood++;
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
    if(restartCnt >= 3000){
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
                angle = rand() % 100 + 40;
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
                angle = rand() % 100 + 220;
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
                        if(angle == 40)
                            A_item = 0;
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
                    if(angle == 40)
                        A_item = 0;
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
                        if(angle == 140)
                            A_item = 0;
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
                        if(angle == 140)
                            A_item = 0;
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
                        if(angle == 320)
                            B_item = 0;
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
                        if(angle == 320)
                            B_item = 0;
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
                    if(B_ornadoCnt >= 8 && angle > 220){
                    //tornadoCnt 크면 각 휘는 빈도수 증가, Anlge 최종적 휘는 정도
                        angle -= 1;
                        B_tornadoCnt = 0;
                        setAngle(angle,speed);
                        if(angle == 220)
                            B_item = 0;
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
                        if(angle == 220)
                            B_item = 0;
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
                    if(ball_X_dir == 0)
                        angle = rand() % 20 + 30; // 30 ~ 50 도
                    else if(ball_X_dir == 1)
                        angle = rand() % 20 + 130;// 130 ~ 150 도
                    A_changeUpCheck++;
                    setAngle(angle,speed);
            }else if(ball_Y_Cood == 1113 && A_changeUpCheck == 5){
                if(ball_X_dir == 0)
                    angle = rand() % 20 + 30; // 30 ~ 50 도
                else if(ball_X_dir == 1)
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
                    if(ball_X_dir == 0)
                        angle = rand() % 20 + 310; // 310 ~ 330 도
                    else if(ball_X_dir == 1)
                        angle  = rand() % 20 + 210; // 210 ~ 210도
                    B_changeUpCheck++;
                    setAngle(angle,speed);
            }else if(ball_Y_Cood == 159 && B_changeUpCheck == 5){
                if(ball_X_dir == 0)
                    angle = rand() % 20 + 310; // 310 ~ 330 도
                else if(ball_X_dir == 1)
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
}
void initing(){
    char check = 0;
    char ball_X_check = 0;
    char ball_Y_check = 0;
    char A_X_check = 0;
    char B_X_check = 0;
    int delay_ = 350;
    int delay_for_Y = 200;
    digitalWrite(ball_X_dirPin, 1);
    digitalWrite(ball_Y_dirPin, 1);
    digitalWrite(A_X_dirPin,0);
    digitalWrite(B_X_dirPin,1);
    while(check != 3){
        if(ball_X_check == 0){
            if(digitalRead(ball_X_limitSwitch2) == LOW){
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
    while(!(digitalRead(ball_Y_limitSwitch1) == LOW)){
        digitalWrite(ball_Y_stpPin, HIGH);
        delayMicroseconds(1200);
        digitalWrite(ball_Y_stpPin, LOW);
        delayMicroseconds(1200);
    }
    digitalWrite(ball_X_dirPin, 0);
    digitalWrite(ball_Y_dirPin, 0);
    digitalWrite(A_X_dirPin,1);
    digitalWrite(B_X_dirPin,0);
    ball_X_Cood = X; ball_Y_Cood=0; A_X_Cood = 0; B_X_Cood = 0;
    ball_X_dir = 0; ball_Y_dir = 0; A_X_dir = 1; B_X_dir =0;
    
    for (int i = 0; i < X/2; i++) {
        digitalWrite(ball_X_stpPin, HIGH);digitalWrite(ball_Y_stpPin, HIGH);
        digitalWrite(A_X_stpPin,HIGH);digitalWrite(B_X_stpPin,HIGH);
        delayMicroseconds(1200);
        digitalWrite(ball_X_stpPin, LOW );
        digitalWrite(ball_Y_stpPin, LOW);
        digitalWrite(A_X_stpPin,LOW);
        digitalWrite(B_X_stpPin,LOW);
        delayMicroseconds(1200);
        ball_X_Cood--;
        ball_Y_Cood++;
        A_X_Cood++;
        B_X_Cood++;
    }
    for (int i = 0; i < ((int)(Y/2) - (int)(X/2)) ; i++) {
        digitalWrite(ball_Y_stpPin, HIGH);
        delayMicroseconds(1200);
        digitalWrite(ball_Y_stpPin, LOW);
        delayMicroseconds(1200);
        ball_Y_Cood++;
    } 
}
//****************************************************************************************************************//
//**************************************** Bresenham Algorithm function ******************************************//
//****************************************************************************************************************//
void line_step() {
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
void line(long x1, long y1, long x2, long y2) {
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
int getAngle(int r, int direction) {
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
void setAngle(int r, long length) {
    double radian = r * PI / 180;
    long x = (long)((double)ball_X_Cood + cos(radian) * (double)length);
    long y = (long)((double)ball_Y_Cood + sin(radian) * (double)length);
    angle = r;
    speed = length;
    //Serial.println(angle);
    line(ball_X_Cood, ball_Y_Cood , x, y);
}
//***************************************************************************************************************//
//*********************************************** Timer function ************************************************//
//***************************************************************************************************************//
void ball_X_timerHandler(){
    if(firstCheck != 0) {//선공게임이 정해져 있는지 체크 
        if(collision_check2 == 0){ // 충돌 체크시 카운트 증가 x
            if((new_receive_buffer[3] & 8) != 8){
                ball_X_timerCnt++;  
            }
        }
    }
}
void ball_Y_timerHandler(){
    if(firstCheck != 0){ //선공게임이 정해져 있는지 체크  -> 게임 끝나면 다시 1 
        if(collision_check2 == 0){
            if((new_receive_buffer[3] & 8) != 8){
            ball_Y_timerCnt++;   
            }
        }
    } 
}
void A_X_timerHandler(){
    if(collision_check2 == 0){
        if(firstCheck != 0){
            A_X_timerCnt++;
        }
    }
}
void B_X_timerHandler(){
    if(collision_check2 == 0){
        if(firstCheck != 0){
            B_X_timerCnt++;
        }
    }
}
void restart(){
    if(restart_check == 1){
        restartCnt++;
    }
}

//***************************************************************************************************************//
//*********************************************** Serial Events *************************************************//
//***************************************************************************************************************//
void serialEvent1(){//PC 
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

                }
                checkSum_check = 0;
                step_ = 0;
                for(int i = 0;i<14;i++){
                    old_receive_buffer[i] = new_receive_buffer[i];
                }
            }
        }
    }
}

void serialEvent2(){
    if((A_bluetooth_data = Serial2.read()) != -1){ //스마트폰 -> 아두이노 -> PC
        switch(A_bluetooth_data){
            case 'C' : completion_of_money_input = 1; break; // 동전 투입 완료
            case '[' : A_mode_selection_left = 1; break;// 모드 선택 좌
            case ']' : A_mode_selection_right = 1; break;// 모드 선택 우
            case 'F' : A_mode_selected = 1; break;// 모드 선택
            case 'G' : A_controller_left = 1; break;// 컨트롤러 선택 좌
            case 'H' : A_controller_right = 1; break;// 컨트롤러 선택 우
            case 'I' : A_controller_selected = 1; break;// 컨트롤러 선택
            case 'O' : A_pre_game_selected = 1; break;// 선공 게임 선택
            case '!' : A_moveCtl = 1; A_X_timerLimit = 18; A_change_left_dir(); break;//왼쪽으로 1속도 이동
            case '"' : A_moveCtl = 2; A_X_timerLimit = 15; A_change_left_dir(); break;//왼쪽으로 2속도 이동
            case '#' : A_moveCtl = 3; A_X_timerLimit = 12; A_change_left_dir(); break;//왼쪽으로 3속도 이동
            case '$' : A_moveCtl = 4; A_X_timerLimit = 9; A_change_left_dir(); break;//왼쪽으로 4속도 이동
            case '&' : A_moveCtl = 5; A_X_timerLimit = 6; A_change_left_dir(); break;//왼쪽으로 5속도 이동
            case '(' : A_moveCtl = 0;  A_move_stop = 1; break;// 정지
            case 'Z' : A_moveCtl = 1; A_X_timerLimit = 18; A_change_right_dir(); break;//오른쪽으로 1속도 이동
            case 'a' : A_moveCtl = 2; A_X_timerLimit = 15; A_change_right_dir(); break;//오른쪽으로 2속도 이동
            case 'b' : A_moveCtl = 3; A_X_timerLimit = 12; A_change_right_dir(); break;//오른쪽으로 3속도 이동
            case 'c' : A_moveCtl = 4; A_X_timerLimit = 9; A_change_right_dir(); break;//오른쪽으로 4속도 이동
            case 'd' : A_moveCtl = 5; A_X_timerLimit = 6; A_change_right_dir(); break;//오른쪽으로 5속도 이동
            case 'P' : A_use_fireball = 1; break; //파이어볼사용
            case 'Q' : A_use_tornado = 1; break;//토네이도 사용
            case 'R' : A_use_hacking = 1; break;//해킹 사용
            case 'S' : A_use_EMP = 1; break;//EMP 사용
            case 'T' : A_use_changeup = 1; break;//CHANGE UP 사용
            case '6' : A_hacking_check = 0; break;//해킹해제
        }
    }
}
void serialEvent3(){
    if((B_bluetooth_data = Serial3.read()) != -1){ //스마트폰 -> 아두이노 -> PC
        switch(B_bluetooth_data){
            case 'G' : B_controller_left = 1; break;// 컨트롤러 선택 좌
            case 'H' : B_controller_right = 1; break;// 컨트롤러 선택 우
            case 'I' : B_controller_selected = 1; break;// 컨트롤러 선택
            case 'O' : B_pre_game_selected = 1; break;// 선공 게임 선택
            case '!' : B_moveCtl = 1; B_X_timerLimit = 18; B_change_left_dir(); break;//왼쪽으로 1속도 이동
            case '"' : B_moveCtl = 2; B_X_timerLimit = 15; B_change_left_dir(); break;//왼쪽으로 2속도 이동
            case '#' : B_moveCtl = 3; B_X_timerLimit = 12; B_change_left_dir(); break;//왼쪽으로 3속도 이동
            case '$' : B_moveCtl = 4; B_X_timerLimit = 9; B_change_left_dir(); break;//왼쪽으로 4속도 이동
            case '&' : B_moveCtl = 5; B_X_timerLimit = 6; B_change_left_dir(); break;//왼쪽으로 5속도 이동
            case '(' : B_moveCtl = 0; B_move_stop = 1; break;// 정지
            case 'Z' : B_moveCtl = 1; B_X_timerLimit = 18; B_change_right_dir(); break;//오른쪽으로 1속도 이동
            case 'a' : B_moveCtl = 2; B_X_timerLimit = 15; B_change_right_dir(); break;//오른쪽으로 2속도 이동
            case 'b' : B_moveCtl = 3; B_X_timerLimit = 12; B_change_right_dir(); break;//오른쪽으로 3속도 이동
            case 'c' : B_moveCtl = 4; B_X_timerLimit = 9; B_change_right_dir(); break;//오른쪽으로 4속도 이동
            case 'd' : B_moveCtl = 5; B_X_timerLimit = 6; B_change_right_dir(); break;//오른쪽으로 5속도 이동
            case 'P' : B_use_fireball = 1; break;//파이어볼사용
            case 'Q' : B_use_tornado = 1; break;//토네이도 사용
            case 'R' : B_use_hacking = 1; break;//해킹 사용
            case 'S' : B_use_EMP = 1; break; //EMP 사용
            case 'T' : B_use_changeup = 1; break;//CHANGE UP 사용
            case '6' : B_hacking_check = 0; break;//해킹해제
        }
    }
}

//***************************************************************************************************************//
//********************************************* function definition *********************************************//
//***************************************************************************************************************//

//***************************************************************************************************************//
//******************************************* Serial send data function *****************************************//
//***************************************************************************************************************//

void serial_send_data(){
    ball_X_Cood_function();
    ball_Y_Cood_function();
    A_X_Cood_function();
    B_X_Cood_function();
    ball_check_function();
    A_use_item_function();
    A_move_function();
    B_use_item_function();
    B_move_function();
    if(firstCheck == 0){
        A_game_ready_function();
        B_game_ready_function();
        //insert_coin_function();
    }
    send_buffer[21] = 0xFF;
    send_buffer[20] = 0xFF;//CMD
    send_buffer[19] = 4;//CMD
    send_buffer[18] = ball_X_Cood_High;
    send_buffer[17] = ball_X_Cood_Low;
    send_buffer[16] = ball_Y_Cood_High;
    send_buffer[15] = ball_Y_Cood_Low;
    send_buffer[14] = ball_check;
    send_buffer[13] = A_X_Cood_High;
    send_buffer[12] = A_X_Cood_Low;
    send_buffer[11] = A_game_ready;
    send_buffer[10] = A_use_item;
    send_buffer[9] = A_move;
    send_buffer[8] = B_X_Cood_High;
    send_buffer[7] = B_X_Cood_Low;
    send_buffer[6] = B_game_ready;
    send_buffer[5] = B_use_item;
    send_buffer[4] = B_move;
    send_buffer[3] = 0;//0x1;//insert_coin;
    send_buffer[2] = 0;//14;//게임 전 설정
    send_buffer[1] = 0xFE;//end
    
    for(int i = 21 ; i >= 1 ; i--){
        checkSum+=send_buffer[i];
    }
    send_buffer[0] = checkSum ^ 0xFF;//check sum
    for(int i = 21 ; i >= 0 ; i--){
        Serial1.write(send_buffer[i]);
    }
    reset_data_after_send();
}
void ball_X_Cood_function(){//17,18번째 데이터 공의 X 좌표를 high , low 두 비트로 나눠서 표현하는 함수 
    ball_X_Cood_High = (unsigned char)((ball_X_Cood & 65280)>>8);
    ball_X_Cood_Low = (unsigned char)(ball_X_Cood & 255);
}
void ball_Y_Cood_function(){//15,16번째 데이터 공의 Y 좌표를 high , low 두 비트로 나눠서 표현하는 함수
    ball_Y_Cood_High = (unsigned char)((ball_Y_Cood & 65280)>>8);
    ball_Y_Cood_Low = (unsigned char)(ball_Y_Cood & 255);
}
void ball_check_function(){//14번째 데이터 공의 상태를 종합하는 함수
    if(wall_crash == 1 || wall_crashCnt != 0){//벽에 부딪힘
        ball_check += 1;    
        wall_crashCnt += 1;
        if(wall_crashCnt == 3)
            wall_crashCnt = 0;
    }
    if(A_get_score == 1 || A_get_scoreCnt != 0){
        ball_check += 2;
        A_get_scoreCnt += 1;
        if(A_get_scoreCnt == 3)
            A_get_scoreCnt = 0;
    }
    if(B_get_score == 1 || B_get_scoreCnt != 0){
        ball_check += 4;
        B_get_scoreCnt += 1;
        if(B_get_scoreCnt == 3)
            B_get_scoreCnt = 0;
    }
    if(A_return == 1 || A_returnCnt != 0){
        ball_check += 8;
        A_returnCnt += 1;
        if(A_returnCnt == 3)
            A_returnCnt = 0;
    }
    if(B_return == 1 || B_returnCnt != 0){
        ball_check += 16;
        B_returnCnt += 1;
        if(B_returnCnt == 3)
            B_returnCnt = 0;
    }
}
void A_X_Cood_function(){//12,13번째 데이터 라켓 A의 좌표를 high, low 두 비트로 나눠서 표현하는 함수 
    A_X_Cood_High = (unsigned char)((A_X_Cood & 65280)>>8);
    A_X_Cood_Low = (unsigned char)(A_X_Cood & 255);
}
void A_game_ready_function(){//11번째 데이터 A 플레이어가 블루투스로 통해 보낸 신호 처리
    if(A_pre_game_selected == 1 || A_pre_game_selectedCnt != 0){//선공게임 완료
        A_game_ready += 1;
        A_pre_game_selectedCnt += 1;
        if(A_pre_game_selectedCnt == 3)
            A_pre_game_selectedCnt = 0;
    }
    else if(A_controller_selected == 1 ){//컨트롤러 선택 완료
        A_game_ready += 2;
    }
    else if(A_controller_right == 1){ //컨트롤러 선택 우
        A_game_ready += 4;
    } 
    else if(A_controller_left == 1){ //컨트롤러 선택 좌
        A_game_ready += 8;
    }
    else if(A_mode_selected == 1){ // 모드 선택 완료
        A_game_ready += 16;
    }
    else if(A_mode_selection_right == 1){ //모드 선택 우
        A_game_ready += 32;
    }
    else if(A_mode_selection_left == 1 ){//모드 선택 좌  
        A_game_ready += 64;
    } 
    else if(completion_of_money_input == 1 ){//동전 투입 완료  
        A_game_ready += 128;
    } 
}
void A_use_item_function(){//10번째 데이터
    if(A_use_fireball == 1 || A_use_fireballCnt != 0){//파이어볼 사용  
        A_use_item += 1;
        A_use_fireballCnt += 1;
        if(A_use_fireballCnt == 3)
            A_use_fireballCnt = 0;
    } 
    else if(A_use_tornado == 1 || A_use_tornadoCnt != 0){//토네이도 사용  
        A_use_item += 2;
        A_use_tornadoCnt += 1;
        if(A_use_tornado == 3)
            A_use_tornado = 0;
    } 
    else if(A_use_hacking == 1 || A_use_hackingCnt != 0){//해킹 사용  
        A_use_item += 4;
        A_use_hackingCnt += 1;
        if(A_use_hackingCnt == 3)
            A_use_hackingCnt = 0;
    } 
    else if(A_release_hacking == 1 || A_release_hackingCnt != 0){//해킹 해제  
        A_use_item += 8;
        A_release_hackingCnt += 1;
        if(A_release_hackingCnt == 3)
            A_release_hackingCnt = 0;
    } 
    else if(A_use_EMP == 1 || A_use_EMPCnt != 0){//EMP 사용  
        A_use_item += 16;
        A_use_EMPCnt += 1;
        if(A_use_EMPCnt == 3)
            A_use_EMPCnt = 0;
    } 
    else if(A_use_changeup == 1 || A_use_changeupCnt != 0){//체인지업 사용  
        A_use_item += 32;
        A_use_changeupCnt += 1;
        if(A_use_changeupCnt == 3)
            A_use_changeupCnt = 0;
    } 
}
void A_move_function(){//9번째 데이터
    if(A_move_right == 1) A_move += 1;// A 오른쪽으로 이동
    else if(A_move_left == 1) A_move += 2;// A 왼쪽으로 이동
    else if(A_move_stop == 1) A_move += 4;// A 정지
}
void B_X_Cood_function(){//7,8번째 데이터 라켓 B의 좌표를 high, low 두 비트로 나눠서 표현하는 함수
    B_X_Cood_High = (unsigned char)((B_X_Cood & 65280)>>8);
    B_X_Cood_Low = (unsigned char)(B_X_Cood & 255);
}
void B_game_ready_function(){//6번째 데이터
    if(B_pre_game_selected == 1 || B_pre_game_selectedCnt != 0){//선공 게임 완료  
        B_game_ready += 1;
        B_pre_game_selectedCnt += 1;
        if(B_pre_game_selectedCnt == 3)
            B_pre_game_selectedCnt = 0;
    } 
    else if(B_controller_selected == 1 ){//컨트롤러 선택 완료  
        B_game_ready += 2;
    } 
    else if(B_controller_right == 1){//컨트롤러 선택 우  
        B_game_ready += 4;
    } 
    else if(B_controller_left == 1 ){//컨트롤러 선택 좌  
        B_game_ready += 8;
    } 
}
void B_use_item_function(){//5번째 데이터  
    if(B_use_fireball == 1 || B_use_fireballCnt != 0){
        B_use_item += 1;
        B_use_fireballCnt += 1;
        if(B_use_fireballCnt == 3)
            B_use_fireballCnt = 0;  
    }else if(B_use_tornado == 1 || B_use_tornadoCnt != 0){
        B_use_item += 2;
        B_use_tornadoCnt += 1;
        if(B_use_tornadoCnt == 3)
            B_use_tornadoCnt = 0;  
    }else if(B_use_hacking == 1 || B_use_hackingCnt != 0){
        B_use_item += 4;
        B_use_hackingCnt += 1;
        if(B_use_hackingCnt == 3)
            B_use_hackingCnt = 0;  
    }else if(B_release_hacking == 1 || B_release_hackingCnt != 0){
        B_use_item += 8;
        B_release_hackingCnt += 1;
        if(B_release_hackingCnt == 3)
            B_release_hackingCnt = 0;
    }
    else if(B_use_EMP == 1 || B_use_EMPCnt != 0){
        B_use_item += 16;
        B_use_EMPCnt += 1;
        if(B_use_EMPCnt == 3)
            B_use_EMPCnt = 0;  
    } 
    else if(B_use_changeup == 1 || B_use_changeupCnt != 0){
        B_use_item += 32;
        B_use_changeupCnt += 1;
        if(B_use_changeupCnt == 3)
            B_use_changeupCnt = 0;
    } 
}
void B_move_function(){
    if(B_move_right == 1) B_move += 1;
    else if(B_move_left == 1) B_move += 2;
    else if(B_move_stop == 1) B_move += 4;//4번째 데이터
}
void insert_coin_function(){//3번째 데이터
    if(insert_coin_1000 == 1 || insert_coin_1000Cnt != 0){
        insert_coin += 1;
        insert_coin_1000Cnt += 1;
        if(insert_coin_1000Cnt == 3)
            insert_coin_1000Cnt = 0;  
    } 
    else if(insert_coin_5000 == 1 || insert_coin_5000Cnt != 0){
        insert_coin += 2;
        insert_coin_5000Cnt += 1;
        if(insert_coin_5000Cnt == 3)
            insert_coin_1000Cnt = 0;  
    } 
    else if(insert_coin_10000 == 1 || insert_coin_10000Cnt != 0){
        insert_coin += 4;
        insert_coin_10000Cnt += 1;
        if(insert_coin_10000Cnt == 3)
            insert_coin_10000Cnt = 0;
    }   
}
void reset_data_after_send(){//PC로 데이터 보낸 후에 변수 0으로 리셋
    wall_crash = 0;
    A_return = 0;
    B_return = 0;
    A_get_score = 0;
    B_get_score = 0;
    completion_of_money_input = 0;
    A_mode_selection_left = 0;
    A_mode_selection_right = 0;
    A_mode_selected = 0;
    A_controller_left = 0;
    A_controller_right = 0;
    A_controller_selected = 0;
    A_pre_game_selected = 0;
    A_use_fireball = 0;
    A_use_tornado = 0;
    A_use_hacking = 0;
    A_release_hacking = 0;
    A_use_EMP = 0;
    A_use_changeup = 0;
    A_move_right = 0;
    A_move_left = 0;
    A_move_stop = 0;
    B_controller_left = 0;
    B_controller_right = 0;
    B_controller_selected = 0;
    B_pre_game_selected = 0;
    B_use_fireball = 0;
    B_use_tornado = 0;
    B_use_hacking = 0;
    B_release_hacking = 0;
    B_use_EMP = 0;
    B_use_changeup = 0;
    B_move_right = 0;
    B_move_left = 0;
    B_move_stop = 0;
    insert_coin_1000 = 0;
    insert_coin_5000 = 0;
    insert_coin_10000 = 0;
    ball_check = 0;
    A_game_ready = 0;
    A_use_item = 0;
    A_move = 0;
    B_game_ready = 0;
    B_use_item = 0;
    B_move = 0;
    insert_coin = 0;
    checkSum = 0;
}
//******************************************************************************************************************//
//******************************************* Serial receive data function *****************************************//
//******************************************************************************************************************//
void ball_move_item(){//11번째 데이터
    if((new_receive_buffer[1] & 1)== 1 && (old_receive_buffer[1] & 1)== 0){
        if(ball_Y_Cood < 500)
            A_item = 1;
        else if(ball_Y_Cood > 500)
            B_item = 1;
    } 
    else if((new_receive_buffer[1] & 2) == 2 && (old_receive_buffer[1] & 2)== 0){
        if(ball_Y_Cood < 500)
            A_item = 2;
        else if(ball_Y_Cood > 500)
            B_item = 2;
    }
    else if((new_receive_buffer[1] & 4) == 4 && (old_receive_buffer[1] & 4)== 0){
        if(ball_Y_Cood < 500)
            A_item = 3;
        else if(ball_Y_Cood > 500)
            B_item = 3;
    }
}

void ball_stat(){//9번째 데이터
    if((new_receive_buffer[3] & 1 ) == 1 && (old_receive_buffer[3] & 1) == 0) firstAt = 1;//A 선공
    else if((new_receive_buffer[3] & 2 ) == 2 && (old_receive_buffer[3] & 2) == 0) firstAt = 2;//B 선공
    if((new_receive_buffer[3] & 8) == 8 && (old_receive_buffer[3] & 8)== 0){//게임 종료
        firstAt = 0;
        startCheck = 0;
        firstCheck = 0;
        ball_X_dir = 0;
        ball_Y_dir = 0;
        A_X_dir = 0;
        B_X_dir = 0;
        A_GoStop = 0;
        B_GoStop = 0;
        startDir = 0;
        step_ = 0;
        ball_X_timerCnt = 0;
        ball_X_timerLimit = 8;//start speed
        ball_X_timercheck = 0;
        ball_X_speedCheck = 0;
        ball_Y_timerCnt = 0;
        ball_Y_timerLimit = 15;//start speed
        ball_Y_timercheck = 0;
        ball_Y_speedCheck = 0;
        A_X_timerCnt = 0;
        A_X_timerLimit = 8;//start speed
        A_X_timercheck = 0;
        A_X_speedCheck = 0;
        B_X_timerCnt = 0;
        B_X_timerLimit = 8;//start speed
        B_X_timercheck = 0;
        B_X_speedCheck = 0;
        collision_check2 = 0;
        A_item = 0;
        B_item = 0;
        digitalWrite(led_top_pin,LOW);
        digitalWrite(led_left_pin,LOW);
        digitalWrite(led_right_pin,LOW);
        digitalWrite(led_bottom_pin,LOW);
    }
}
void A_using_item(){//8번째 데이터
    if(new_receive_buffer[4] != 0){
        if((new_receive_buffer[4] & 1) == 1 && (old_receive_buffer[4] & 1)== 0) Serial2.write('a');
        else if((new_receive_buffer[4] & 2) == 2 && (old_receive_buffer[4] & 2)== 0) Serial2.write('a');
        else if((new_receive_buffer[4] & 4) == 4 && (old_receive_buffer[4] & 4)== 0) B_hacking_check = 1;
        else if((new_receive_buffer[4] & 8) == 8 && (old_receive_buffer[4] & 8)== 0) B_hacking_check = 0;
        else if((new_receive_buffer[4] & 16) == 16 && (old_receive_buffer[4] & 16)== 0) Serial2.write('a');
        else if((new_receive_buffer[4] & 32) == 32 && (old_receive_buffer[4] & 32)== 0) Serial2.write('a');
    }
}
void A_get_item(){//7번째 데이터
    if(new_receive_buffer[5] != 0){
        if((new_receive_buffer[5] & 1 ) == 1 && (old_receive_buffer[5] & 1)== 0) Serial2.write('e');// 파이어볼 획득
        else if((new_receive_buffer[5] & 2 ) == 2 && (old_receive_buffer[5] & 2)== 0)  Serial2.write('f');// 토네이도 획득
        else if((new_receive_buffer[5] & 4 ) == 4 && (old_receive_buffer[5] & 4)== 0) Serial2.write('g');// 해킹 획득
        else if((new_receive_buffer[5] & 8 ) == 8 && (old_receive_buffer[5] & 8)== 0) Serial2.write('h');//EMP 획득
        else if((new_receive_buffer[5] & 16 ) == 16 && (old_receive_buffer[5] & 16)== 0) Serial2.write('i');//change up 획득
    }
}
void A_choose(){//6번째 데이터
    if(new_receive_buffer[6] != 0){
        if((new_receive_buffer[6] & 1) == 1 && (old_receive_buffer[6] & 1)== 0) Serial2.write('a');
        else if((new_receive_buffer[6] & 2) == 2 && (old_receive_buffer[6] & 2)== 0) Serial2.write('a');
        else if((new_receive_buffer[6] & 4) == 4 && (old_receive_buffer[6] & 4)== 0) Serial2.write('a');
        else if((new_receive_buffer[6] & 8) == 8 && (old_receive_buffer[6] & 8)== 0) Serial2.write('a');
    }
}
void B_using_item(){//5번째 데이터
    if(new_receive_buffer[7] != 0){
        if((new_receive_buffer[7] & 1) == 1 && (old_receive_buffer[7] & 1)== 0) Serial3.write('a');
        else if((new_receive_buffer[7] & 2) == 2 && (old_receive_buffer[7] & 2)== 0) Serial3.write('a');
        else if((new_receive_buffer[7] & 4) == 4 && (old_receive_buffer[7] & 4)== 0) A_hacking_check = 1;
        else if((new_receive_buffer[7] & 8) == 8 && (old_receive_buffer[7] & 8)== 0) A_hacking_check = 0;
        else if((new_receive_buffer[7] & 16) == 16 && (old_receive_buffer[7] & 16)== 0) Serial3.write('a');
        else if((new_receive_buffer[7] & 32) == 32 && (old_receive_buffer[7] & 32)== 0) Serial3.write('a');
    }
}
void B_get_item(){//4번째 데이터
    if(new_receive_buffer[8] != 0){
        if((new_receive_buffer[8] & 1 ) == 1 && (old_receive_buffer[8] & 1)== 0) Serial3.write('e');// 파이어볼 획득
        else if((new_receive_buffer[8] & 2 ) == 2 && (old_receive_buffer[8] & 2)== 0) Serial3.write('f');// 토네이도 획득
        else if((new_receive_buffer[8] & 4 ) == 4 && (old_receive_buffer[8] & 4)== 0) Serial3.write('g');// 해킹 획득
        else if((new_receive_buffer[8] & 8 ) == 8 && (old_receive_buffer[8] & 8)== 0) Serial3.write('h');//EMP 획득
        else if((new_receive_buffer[8] & 16 ) == 16 && (old_receive_buffer[8] & 16)== 0) Serial3.write('i');//change up 획득
    }
}
void B_choose(){//3번째 데이터
    if(new_receive_buffer[9] != 0){
        if((new_receive_buffer[9] & 1) == 1 && (old_receive_buffer[9] & 1)== 0) Serial3.write('a');
        else if((new_receive_buffer[9] & 2) == 2 && (old_receive_buffer[9] & 2)== 0) Serial3.write('a');
    }
}
//******************************************************************************************************************//
//*********************************************** The others function **********************************************//
//******************************************************************************************************************//
void A_Collision_check(){
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
        }else if(A_X_Cood - RACKETSECTOR*15/2 <= ball_X_Cood && ball_X_Cood <= A_X_Cood - RACKETSECTOR*9/2){//40
            angle = 140;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(ball_X_Cood - BALLSIZE/2 <= A_X_Cood - RACKETSECTOR*15/2 && A_X_Cood - RACKETSECTOR*15/2 <= ball_X_Cood + BALLSIZE/2){//30
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
        }else if(A_X_Cood + RACKETSECTOR*9/2 <= ball_X_Cood && ball_X_Cood <= A_X_Cood + RACKETSECTOR*15/2){//40
            angle = 40;
            setAngle(angle,speed);
            collision_check2 = 0;
            A_return = 1;
        }else if(ball_X_Cood - BALLSIZE/2 <= A_X_Cood + RACKETSECTOR*15/2 && A_X_Cood + RACKETSECTOR*15/2 <= ball_X_Cood + BALLSIZE/2){//30
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
        B_get_score = 1;
        restart_check = 1;
        angle = getAngle(angle,HORIZONTAL);
        setAngle(angle,speed);
        digitalWrite(led_bottom_pin,HIGH);
    }
}
void B_Collision_check(){
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
        }else if(B_X_Cood - RACKETSECTOR*15/2 <= ball_X_Cood && ball_X_Cood <= B_X_Cood - RACKETSECTOR*9/2){//40
            angle = 220;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }else if(ball_X_Cood - BALLSIZE/2 <= B_X_Cood - RACKETSECTOR*15/2 && B_X_Cood - RACKETSECTOR*15/2 <= ball_X_Cood + BALLSIZE/2){//30
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
        }else if(B_X_Cood + RACKETSECTOR*9/2 <= ball_X_Cood && ball_X_Cood <= B_X_Cood + RACKETSECTOR*15/2){//40
            angle = 320;
            setAngle(angle,speed);
            collision_check2 = 0;
            B_return = 1;
        }
        else if(ball_X_Cood - BALLSIZE/2 <= B_X_Cood + RACKETSECTOR*15/2 && B_X_Cood + RACKETSECTOR*15/2 <= ball_X_Cood + BALLSIZE/2){//30
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
        A_get_score = 1;
        restart_check = 1;
        angle = getAngle(angle,HORIZONTAL);
        setAngle(angle,speed);
        digitalWrite(led_top_pin,HIGH);
    }
}
void A_change_left_dir(){
    if(A_hacking_check==0){ // 해킹 아닐때
        A_X_dir = 0;
        digitalWrite(A_X_dirPin,A_X_dir);
    }else if(A_hacking_check == 1){ // 해킹일때
        A_X_dir = 1;
        digitalWrite(A_X_dirPin,A_X_dir);
    }
    A_move_left = 1;
}
void A_change_right_dir(){
    if(A_hacking_check==0){ // 해킹 아닐때
        A_X_dir = 1;
        digitalWrite(A_X_dirPin,A_X_dir);
    }else if(A_hacking_check == 1){ //해킹 일때
        A_X_dir = 0;
        digitalWrite(A_X_dirPin,A_X_dir);
    }
    A_move_right = 1;
}
void B_change_left_dir(){
    if(B_hacking_check==0){ // 해킹 아닐때
        B_X_dir = 0;
        digitalWrite(B_X_dirPin,B_X_dir);
    }else if(B_hacking_check == 1){ // 해킹일때
        B_X_dir = 1;
        digitalWrite(B_X_dirPin,B_X_dir);
    }
    B_move_left = 1;
}
void B_change_right_dir(){
    if(B_hacking_check==0){ // 해킹 아닐때
        B_X_dir = 1;
        digitalWrite(B_X_dirPin,B_X_dir);
    }else if(B_hacking_check == 1){ //해킹 일때
        B_X_dir = 0;
        digitalWrite(B_X_dirPin,B_X_dir);
    }
    B_move_right = 1;
}

void loop(){
    if(firstCheck == 0){// 선공게임이 정해지지 않았을때 ( 게임 시작 전 )
        firstCheckFuntion();
    }else if(firstCheck == 1){ // 선공게임 정해진 후 ( 게임 중 )
        gameControl();
    }
    
}