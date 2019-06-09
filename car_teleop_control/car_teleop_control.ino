#include<ros.h>
#include<std_msgs/Char.h>

// 电机控制引脚；
#define PWMD 3 //右后轮
#define DIRD 2
#define PWMC 5 //右前轮
#define DIRC 4
#define PWMB 6 //左后轮
#define DIRB 7
#define PWMA 9 //左前轮
#define DIRA 8

#define MAXSPEED 80
#define MINSPEED (-80)

ros::NodeHandle nh;

char msg;
int speed = 0;
int speed1 = speed;

void messageCb(const std_msgs::Char &kb_msg){
  msg = kb_msg.data;
  switch(msg){
    case 'q':
      LeftUp_run();
      break;
    case 'w':
      accerlerate();
      break;
    case 'e':
      RightUp_run();
      break;
    case 'a':
      turnLeft();
      break;
    case 's':
      decerlerate();
      break;
    case 'd':
      turnRight();
      break;
    case 'z':
      LeftDown_run();
      break;
    case 'x':
      stop();
      break;
    case 'c':
      RightDown_run();
      break;
  }
}

ros::Subscriber<std_msgs::Char> sub("keyboard_message",&messageCb);
void setup() {
  // put your setup code here, to run once:
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(PWMC, OUTPUT);
  pinMode(DIRC, OUTPUT);
  pinMode(PWMD, OUTPUT);
  pinMode(DIRD, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}
//小车运动定义

void turnLeft() { //小车左转
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

void turnRight() { //小车右转
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

void forward() { //小车前进
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  digitalWrite(DIRC, HIGH);
  digitalWrite(DIRD, HIGH);
  
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
  analogWrite(PWMC, speed);
  analogWrite(PWMD, speed);
}

void back() { //小车后退
  if (speed!=0) speed1 = speed;
  if (speed1<0) speed1 = (-1)*speed1;
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, HIGH);
  digitalWrite(DIRC, LOW);
  digitalWrite(DIRD, LOW);
  
  analogWrite(PWMA, speed1);
  analogWrite(PWMB, speed1);
  analogWrite(PWMC, speed1);
  analogWrite(PWMD, speed1);
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

//车体左上45度平移
void LeftUp_run()
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
void RightUp_run()
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
void LeftDown_run()
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
void RightDown_run()
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
  speed += 5;
  if (speed > MAXSPEED){
    speed = MAXSPEED;
  }
  if (speed<0){
    back(); 
  }
  else{
    forward();
  }
}

void decerlerate(){
  speed -= 5;
  if(speed < MINSPEED){
    speed = MINSPEED;
  }
  if (speed >=0){
    forward();
  }
  else{
    back();
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
}
