#include <Arduino.h>
#line 1 "C:\\Users\\Administrator\\Desktop\\Dò Line New\\Main\\Main.ino"
#line 1 "C:\\Users\\Administrator\\Desktop\\Dò Line New\\Main\\Main.ino"
//File lấy dữ liệu
//Số đc lấy từ trái sang phải

#define motor1 10
#define motor2 11
#define hongngoai 2
const int qtro[7] = {A0,A1,A2,A3,A4,A5,A7};
int ktraqtro[7] = {0,0,0,0,0,0,0};
#line 9 "C:\\Users\\Administrator\\Desktop\\Dò Line New\\Main\\Main.ino"
void setup();
#line 16 "C:\\Users\\Administrator\\Desktop\\Dò Line New\\Main\\Main.ino"
void loop();
#line 21 "C:\\Users\\Administrator\\Desktop\\Dò Line New\\Main\\Main.ino"
void laydulieu();
#line 4 "C:\\Users\\Administrator\\Desktop\\Dò Line New\\Main\\2.xulyloi.ino"
int xulyloi();
#line 4 "C:\\Users\\Administrator\\Desktop\\Dò Line New\\Main\\3.pidcontrol.ino"
void LinePIDFilter();
#line 9 "C:\\Users\\Administrator\\Desktop\\Dò Line New\\Main\\Main.ino"
void setup() {
  Serial.begin(9600);
  for(int i = 0; i<=6;i++){
   pinMode(qtro[i], INPUT);
  }
}

void loop() {
  laydulieu();
  delay(100);
}

void laydulieu(){
  
  //clear ktraqtro
  for(int i = 0; i<=6;i++){
   ktraqtro[i] = 0;
  }
  
  //Lấy max,min
  int max = analogRead(qtro[0]);
  int min = analogRead(qtro[0]);
  
  for(int i = 0; i<=6;i++){
   if(analogRead(qtro[i]) > max){
    max = analogRead(qtro[i]);
   }
   if(analogRead(qtro[i]) < min){
    min = analogRead(qtro[i]);
   }
  }
  
  //Lấy trb rồi gán digital từng cái
  int trungbinh = (min + max) /2;
  
  for(int i = 0; i<=6;i++){
   if(analogRead(qtro[i]) > max){
    ktraqtro[i] = 1;
   }
  }

  //Chuyển động
  LinePIDFilter();
  
}

#line 1 "C:\\Users\\Administrator\\Desktop\\Dò Line New\\Main\\2.xulyloi.ino"

bool Line[7] = {false};

int xulyloi(){
 //Kiểm tra số quang trở phía trên line 
 int soluongqtrophiatrenline = 0;  
 for(int i = 0; i<=6;i++){
  if(ktraqtro[i] == 1){
   soluongqtrophiatrenline = soluongqtrophiatrenline + ktraqtro[i];
  }
 }
 //Chuyển từ 0001000 sang false,true
 for(int i = 0; i<=6;i++){
  if(ktraqtro[i] == 1){
    Line[i] = true;
  }
 }

 //Xác định lỗi
 static int prev_error = 0;
 switch(soluongqtrophiatrenline){
    case 0: {      
        if (prev_error == 0) {
          return 0;
        } else if (prev_error == 6 || prev_error == 7) {
          prev_error = 7;
          return 7;
        } else if (prev_error == -6 || prev_error == -7) {
          prev_error = -7;
          return -7;
        }
        else return prev_error;
        break;
      }
    case 1: {
        for (int i = 0; i < 7; i++){
          if (Line[i]) {
            switch (i) {
              case 0: {
                  prev_error = -6;
                  return -6;
                  break;
                }
              case 1: {
                  prev_error = -4;
                  return -4;
                  break;
                }
              case 2: {
                  prev_error = -2;
                  return -2;
                  break;
                }
              case 3: {
                  prev_error = 0;
                  return 0;
                  break;
                }
              case 4: {
                  prev_error = 2;
                  return 2;
                  break;
                }
              case 5: {
                  prev_error = 4;
                  return 4;
                  break;
                }
              case 6: {
                  prev_error = 6;
                  return 6;
                  break;
                }
              default: {
                  return prev_error;
                  break;
                }
            }
            break;
          }
        }
        break;
      }
    case 2: {
        if (Line[0] && Line[1]) {
          prev_error = -5;
          return -5;
        } else if (Line[1] && Line[3]) {
          prev_error = -7;
          return -7;
        } else if (Line[1] && Line[2]) {
          prev_error = -3;
          return -3;
        } else if (Line[2] && Line[3]) {
          prev_error = -1;
          return -1;
        } else if (Line[3] && Line[4]) {
          prev_error = 1;
          return 1;
        } else if (Line[4] && Line[5]) {
          prev_error = 3;
          return 3;
        } else if (Line[5] && Line[3]) {
          prev_error = 7;
          return 7;
        } else if (Line[5] && Line[6]) {
          prev_error = 5;
          return 5;
        } else return prev_error;
        break;
      }
    case 3: {
        if (Line[1] && Line[2] && Line[3]) {
          switch (-1) {
            case 0: {
                prev_error = 0;
                return 0;
              }
            case -1: case 1: {
                prev_error = -4;
                return -4;
              }
          }
        } else if (Line[0] && Line[1] && Line[2]) {
          prev_error = -6;
          return -6;
        } else if (Line[3] && Line[4] && Line[5]) {
          switch (1) {
            case 0: {
                prev_error = 0;
                return 0;
              }
            case 1: case -1: {
                prev_error = 4;
                return 4;
              }
          }
        } else if (Line[4] && Line[5] && Line[6]) {
          prev_error = 6;
          return 6;
        } else if (Line[2] && Line[3] && Line[4]) {
          prev_error = 0;
          return 0;
        } else return prev_error;
        break;
      }
    case 4: {
        if (Line[0] && Line[1] && Line[2] && Line[3]) {     
                prev_error = -8;
                return -8;         
        }     
        else if (Line[6] && Line[5] && Line[4] && Line[3]) {        
                prev_error = 8;
                return 8;           
        }
        else {
          return prev_error;
        }
        break;
      }
    case 5: {
        if (Line[0] && Line[1] && Line[2] && Line[3] && Line[4]) {
          prev_error = -2;
          return -2;
        } else if (Line[1] && Line[2] && Line[3] && Line[4] && Line[5]) {
          prev_error = 0;
          return 0;
        } else if (Line[2] && Line[3] && Line[4] && Line[5] && Line[6]) {
          prev_error = 2;
          return 2;
        }
      }
    case 6: {
      if (Line[0] && Line[1] && Line[2] && Line[3] && Line[4] && Line[5]) {
        prev_error = -1;
        return -1;
      } else if (Line[1] && Line[2] && Line[3] && Line[4] && Line[5] && Line[6]) {
        prev_error = 1;
        return 1;
      }
    }
    case 7: {
      prev_error = 0;
      return 0;
    }
    default: {
        /*int temp = CountLeft() - CountRight();
          if (temp < -1) {
          prev_error = 8;
          return 8;
          } else if (temp > 1) {
          prev_error = -8;
          return -8;
          } else*/
        return 0;
        break;
    }
 }
 
}

#line 1 "C:\\Users\\Administrator\\Desktop\\Dò Line New\\Main\\3.pidcontrol.ino"



void LinePIDFilter() { //PID control in line tracking mode
  static double kP = 39, kI = 0.005, kD = 30;
  static double gain = 100;
  static double prev_error = 0, prev_I = 0;
  double p = 0, i = 0, d = 0, pid_value;

  p = xulyloi();
  i = p + prev_I;
  d = p - prev_error;

  pid_value = kP * p + kI * i + kD * d;
  prev_I = i;
  prev_error = p;
  pid_value *= gain/100;

  constrain(motor1, 0, 255);
  constrain(motor2, 0, 255);
  analogWrite(motor1, 255 - pid_value);
  analogWrite(motor2,255 + pid_value);
}

