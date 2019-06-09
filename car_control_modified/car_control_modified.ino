#include<PS2X_lib.h>
//PS2手柄引脚；
#define PS2_DAT        13
#define PS2_CMD        11
#define PS2_SEL        10
#define PS2_CLK        12

// 电机控制引脚；
#define PWMD 3 //右后轮
#define DIRD 2
#define PWMC 5 //右前轮
#define DIRC 4
#define PWMB 6 //左后轮
#define DIRB 7
#define PWMA 9 //左前轮
#define DIRA 8

//AB同向前进时电机需逆时针转 CD同向前进时电机需顺时针

#define pressures false
#define rumble false

#define MAXSPEED 200
#define MINSPEED (-200)
#define DEFAULTSPEED 100

int speed = DEFAULTSPEED;//小车速度
int speed1;


PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

void (* resetFunc) (void) = 0;
void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(PWMC, OUTPUT);
  pinMode(DIRC, OUTPUT);
  pinMode(PWMD, OUTPUT);
  pinMode(DIRD, OUTPUT);

  Serial.begin(9600);
  delay(300) ; //added delay to give wireless ps2 module some time to startup, before configuring it
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

   if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
      if (rumble)
        Serial.println("true)");
      else
        Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
  {
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
    resetFunc();
    
  }

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
  type = ps2x.readType();
  switch (type) {
  case 0:
    Serial.print("Unknown Controller type found ");
    break;
  case 1:
    Serial.print("DualShock Controller found ");
    break;
  case 2:
    Serial.print("GuitarHero Controller found ");
    break;
  case 3:
    Serial.print("Wireless Sony DualShock Controller found ");
    break;
  }
}
//小车运动定义

void turnLeft(int &speed,int &speed1) { //小车左转
  if (speed!=0) speed1 = speed;
  if (speed1<0) speed1 = (-1)*speed1;
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,LOW);
  digitalWrite(DIRC,LOW);
  digitalWrite(DIRD,HIGH);
  analogWrite(PWMA, speed1);
  analogWrite(PWMB, speed1);
  analogWrite(PWMC, speed1);
  analogWrite(PWMD, speed1);
  speed = 0;
}

void turnRight(int &speed, int &speed1) { //小车右转
  if (speed!=0) speed1 = speed;
  if (speed1<0) speed1 = (-1)*speed1;
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,HIGH);
  digitalWrite(DIRC,HIGH);
  digitalWrite(DIRD,LOW);
  analogWrite(PWMA, speed1);
  analogWrite(PWMB, speed1);
  analogWrite(PWMC, speed1);
  analogWrite(PWMD, speed1);
  speed = 0;
}

void forward(int speed) { //小车前进
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  digitalWrite(DIRC, HIGH);
  digitalWrite(DIRD, HIGH);
  
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
  analogWrite(PWMC, speed);
  analogWrite(PWMD, speed);
}

void back(int speed) { //小车后退
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, HIGH);
  digitalWrite(DIRC, LOW);
  digitalWrite(DIRD, LOW);
  
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
  analogWrite(PWMC, speed);
  analogWrite(PWMD, speed);
}
void stop() // 停止；
{
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  digitalWrite(DIRC, LOW);
  digitalWrite(DIRD, LOW);
  
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  analogWrite(PWMC, 0);
  analogWrite(PWMD, 0);
}

//车体左平移
//
void motor_pmove_left(int &speed,int &speed1)
{
  if (speed!=0) speed1 = speed;
  if (speed1<0) speed1 = (-1)*speed1;
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,LOW);
  digitalWrite(DIRC,HIGH);
  digitalWrite(DIRD,LOW);

  analogWrite(PWMA,speed1);
  analogWrite(PWMB,speed1);
  analogWrite(PWMC,speed1);
  analogWrite(PWMD,speed1);

  speed = 0;
}

//车体右平移
void motor_pmove_right(int &speed,int &speed1)
{
  if (speed!=0) speed1 = speed;
  if (speed1<0) speed1 = (-1)*speed1;
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,HIGH);
  digitalWrite(DIRC,LOW);
  digitalWrite(DIRD,HIGH);

  analogWrite(PWMA,speed1);
  analogWrite(PWMB,speed1);
  analogWrite(PWMC,speed1);
  analogWrite(PWMD,speed1);

  speed = 0;
}
//车体左上45度平移
void LeftUp_run(int &speed,int &speed1)
{
  if (speed!=0) speed1 = speed;
  if (speed1<0) speed1 = (-1)*speed1;
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,LOW);
  digitalWrite(DIRC,HIGH);
  digitalWrite(DIRD,LOW);

  analogWrite(PWMA,0);
  analogWrite(PWMB,speed1);
  analogWrite(PWMC,speed1);
  analogWrite(PWMD,0);

  speed = 0;
}
//车体右上45度平移
void RightUp_run(int &speed, int &speed1)
{
  if (speed!=0) speed1 = speed;
  if (speed1<0) speed1 = (-1)*speed1;
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,LOW);
  digitalWrite(DIRC,LOW);
  digitalWrite(DIRD,HIGH);

  analogWrite(PWMA,speed1);
  analogWrite(PWMB,0);
  analogWrite(PWMC,0);
  analogWrite(PWMD,speed1);

  speed = 0;
}
//车体左下45度平移
void LeftDown_run(int &speed,int &speed1)
{
  if (speed!=0) speed1 = speed;
  if (speed1<0) speed1 = (-1)*speed1;
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,LOW);
  digitalWrite(DIRC,LOW);
  digitalWrite(DIRD,LOW);

  analogWrite(PWMA,speed1);
  analogWrite(PWMB,0);
  analogWrite(PWMC,0);
  analogWrite(PWMD,speed1);

  speed = 0;
}
//车体右下45度平移
void RightDown_run(int &speed,int &speed1)
{
  if (speed!=0) speed1 = speed;
  if (speed1<0) speed1 = (-1)*speed1;
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,HIGH);
  digitalWrite(DIRC,LOW);
  digitalWrite(DIRD,LOW);

  analogWrite(PWMA,0);
  analogWrite(PWMB,speed1);
  analogWrite(PWMC,speed1);
  analogWrite(PWMD,0);

  speed = 0;
}
//缓慢加速
void accerlerate(){
  speed += 2;
  if (speed > MAXSPEED){
    speed = MAXSPEED;
  }
  if (speed<0){
    int speed2 = speed *(-1);
    back(speed2); 
  }
  else{
    forward(speed);
  }
}

void decerlerate(){
  speed -= 2;
  if(speed < MINSPEED){
    speed = MINSPEED;
  }
  if (speed >=0){
    forward(speed);
  }
  else{
    int speed2 = speed *(-1);
    back(speed2);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (error == 1) //skip loop if no controller found
    return;

  if (type == 2) { //Guitar Hero Controller
    return;
  }
  else  { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    
    //start 重置电机PWM为DEFAULT；
    if (ps2x.Button(PSB_START))  {
      Serial.println("Start is being held");
      speed = DEFAULTSPEED;
      forward(speed);
    }
    // Stop 并将速度设为0
    if (ps2x.Button(PSB_SELECT)) {
      Serial.println("stop");
      stop();
      speed = 0;
    }
// 当按下上方向键；
    if (ps2x.Button(PSB_PAD_UP)) {
      //上加左一起按
      if (ps2x.Button(PSB_PAD_LEFT)){
      Serial.println("UP & LEFT"); 
      LeftUp_run(speed,speed1);
    }
      //上加右
      else if (ps2x.Button(PSB_PAD_RIGHT)){
      Serial.println("UP & RIGHT");
      RightUp_run(speed,speed1);
    }
      //只按下上方向键
      else{
      Serial.println("Moving forward");
      forward(speed);
      }
    }
    //当按下左方向键
    else if (ps2x.Button(PSB_PAD_LEFT)) {
      //左加上 等同于上加左一起按
      if (ps2x.Button(PSB_PAD_UP)){
        Serial.println("UP & LEFT");
        LeftUp_run(speed,speed1);
      }
      //左加下
      else if (ps2x.Button(PSB_PAD_DOWN)){
        Serial.println("DOWN & LEFT");
        LeftDown_run(speed,speed1);
      }
      //只按下左
      else{
      Serial.println("Moving left ");
      motor_pmove_left(speed,speed1);
      }
    }
    //当按下右方向键
    else if (ps2x.Button(PSB_PAD_RIGHT)) {
      //上加右
      if (ps2x.Button(PSB_PAD_UP)){
        Serial.println("UP & RIGHT");
        RightUp_run(speed,speed1);
      }
      //右加下
      else if (ps2x.Button(PSB_PAD_DOWN)){
        Serial.println("DOWN & RIGHT");
        RightDown_run(speed,speed1);
      }
      //只有右
      else{
      Serial.println("Moving right");
      motor_pmove_right(speed,speed1);
      }
    }
    //当按下下方向键
    else if (ps2x.Button(PSB_PAD_DOWN)) {
      //下加右
      if (ps2x.Button(PSB_PAD_RIGHT)){
      Serial.println("DOWN & RIGHT");
      RightDown_run(speed,speed1);
      }
      //下加左
      else if (ps2x.Button(PSB_PAD_LEFT)){
      Serial.println("DOWN & LEFT");
      LeftDown_run(speed,speed1);
      }
      //只按下下方向键
      else{
      Serial.println("Moving Backwards");
      back(speed);
    } 
    
    }

// 按下正方形向左原地转圈
    if (ps2x.Button(PSB_PINK)) {
      Serial.println("turing left");
      turnLeft(speed,speed1);
    }
// 按下圆形向右原地转圈
    if (ps2x.Button(PSB_RED)) {
      Serial.println("turning right");
      turnRight(speed,speed1);
    }
// 按下三角缓慢加速
    if (ps2x.Button(PSB_GREEN)){
      Serial.println("accerlerateion!");
      accerlerate();
    }
// 按下X缓慢减速
    if (ps2x.Button(PSB_BLUE)){
      Serial.println("decerleration");
      decerlerate();
    }
//Using joystick to control
    int LY = ps2x.Analog(PSS_LY);
    int LX = ps2x.Analog(PSS_LX);
    int RY = ps2x.Analog(PSS_RY);
    int RX = ps2x.Analog(PSS_RX);

    //左摇杆向上
    if (LY<128){
      //摇杆向左上
      if (LX<128){
        Serial.println("UP AND LEFT");
        LeftUp_run(speed,speed1);
      }
      //摇杆向右上
      else if( LX>128){
        Serial.println("UP AND RIGHT");
        RightUp_run(speed,speed1);
      }
      //只向上
      else{
        Serial.println("Moving forward");
        forward(speed);
      }
    }
    //左摇杆向下
    else if (LY>128){
      //摇杆左下
      if (LX<128){
        Serial.println("DOWN AND LEFT");
        LeftDown_run(speed,speed1);
      }
      //摇杆右下
      else if( LX>128){
        Serial.println("DOWN AND RIGHT");
        RightDown_run(speed,speed1);
      }
      //只向下
      else{
        Serial.println("Moving down");
        back(speed);
      }
    }
    //左摇杆向左
    else if (LX<128){
      //左然后向上
      if (LY<128){
        Serial.println("UP AND LEFT");
        LeftUp_run(speed,speed1);
      }
      //左然后向下
      else if (LY > 128){
        Serial.println("DOWN AND RIGHT");
        LeftDown_run(speed,speed1);
      }
      //只向左
      else{
        Serial.println("MOVING LEFT");
        motor_pmove_left(speed,speed1);
      }
    }
    //左摇杆向右
    else if (LX>128){
      //右然后向上
      if (LY<128){
        Serial.println("UP AND RIGHT");
        RightUp_run(speed,speed1);
      }
      //右然后向下
      else if (LY > 128){
        Serial.println("DOWN AND RIGHT");
        RightDown_run(speed,speed1);
      }
      //只向右
      else{
        Serial.println("MOVING RIGHT");
        motor_pmove_right(speed,speed1);
      }
    }
    //右摇杆
    if (RY<128){
      Serial.println("ACCERLERATION!");
      accerlerate();
    }
    else if (RY>128){
      Serial.println("DECERLERATION!");
      decerlerate();
    }
    else if (RX<128){
      Serial.println("TURNING LEFT");
      turnLeft(speed,speed1);
    }
    else if (RX>128){
      Serial.println("TURNING RIGHT");
      turnRight(speed,speed1);
    }
  }
}
