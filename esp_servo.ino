#undef ESP32
#include <ros.h>
#define ESP32
#include <std_msgs/UInt16.h>

#include <ESP32Servo.h>

const int chooseBallServoStartPosition = 65;
const int shootBallServoStartPosition = 180;
ros::NodeHandle nh;

Servo chooseBallServo;
Servo shootBallServo;
void chooseBallServoCallback(const std_msgs::UInt16& cmd_msg){
  // it should go from 30 to 100 to choose ball (+/- 35)
  chooseBallServo.write(cmd_msg.data);
  delay(1000);
  chooseBallServo.write(chooseBallServoStartPosition);
}

void shootBallServoCallback(const std_msgs::UInt16& cmd_msg){ 
  // it should go to 130 to shoot
  shootBallServo.write(cmd_msg.data);
  delay(300);
  shootBallServo.write(shootBallServoStartPosition);
}

ros::Subscriber<std_msgs::UInt16> chooseSubscriber("chooseBall", chooseBallServoCallback);
ros::Subscriber<std_msgs::UInt16> shootSubscriber("shootBall", shootBallServoCallback);

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(chooseSubscriber);
  nh.subscribe(shootSubscriber);
  
  chooseBallServo.setPeriodHertz(50);
  chooseBallServo.attach(12);
  chooseBallServo.write(chooseBallServoStartPosition);

  shootBallServo.setPeriodHertz(50);
  shootBallServo.attach(14);
  shootBallServo.write(shootBallServoStartPosition);

}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(1);
}
