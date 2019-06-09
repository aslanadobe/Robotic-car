#include"ros/ros.h"
#include"std_msgs/Char.h"

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define KEYCODE_q 0x71 
#define KEYCODE_w 0x77
#define KEYCODE_e 0x65
#define KEYCODE_a 0x61
#define KEYCODE_s 0x73
#define KEYCODE_d 0x64
#define KEYCODE_z 0x7A
#define KEYCODE_x 0x78
#define KEYCODE_c 0x63

int kfd = 0;
struct termios cooked, raw;

int main(int argc, char **argv)
{
	ros::init(argc,argv,"keyboard_publisher");  
	ros::NodeHandle nh;
	
	ros::Publisher keyboard_pub = nh.advertise<std_msgs::Char>("keyboard_message",1);
	
	std_msgs::Char msg;
	
	char c;

  // get the console in raw mode                                                              
  tcgetattr(kfd, &cooked); // 得到 termios 结构体保存，然后重新配置终端
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file                         
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use wasd keys to move the robot.");
  puts("Use qezc to move 45 up/down and left/right");
  puts("Use x to stop");
	
	while(ros::ok()){
	
    // get the next event from the keyboard  
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }
    
    switch(c)
    {
    	case KEYCODE_q:
    		msg.data = 'q';
    		break;
    	case KEYCODE_w:
    		msg.data = 'w';
    		break;
    	case KEYCODE_e:
    		msg.data = 'e';
    		break;
    	case KEYCODE_a:
    		msg.data = 'a';
    		break;
    	case KEYCODE_s:
    		msg.data = 's';
    		break;
    	case KEYCODE_d:
    		msg.data = 'd';
    		break;
    	case KEYCODE_z:
    		msg.data = 'z';
    		break;
    	case KEYCODE_x:
    		msg.data = 'x';
    		break;
    	case KEYCODE_c:
    		msg.data = 'c';
    		break;
    	default:
    		msg.data = '0';
    		ROS_INFO("No such command");
    	}
    	
    ROS_INFO("Send msg = %c", msg.data);
		keyboard_pub.publish(msg);	
	}
	tcsetattr(kfd, TCSANOW, &cooked);
	return (0);
}
	
	
	
	
