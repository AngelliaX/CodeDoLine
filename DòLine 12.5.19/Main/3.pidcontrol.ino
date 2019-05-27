int pid;
void LinePIDFilter() { //PID control in line tracking mode
  static double kP = 5, kI = 0, kD = 0;
  static double gain = 100;
  static double prev_error = 0, prev_I = 0;
  double p = 0, i = 0, d = 0, pid_value;

  p = xulyloi();
  i = p + prev_I;
  d = p - prev_error;

  pid_value = kP * p + kI * i + kD * d;
    pid = pid_value;
  prev_I = i;
  prev_error = p;
  pid_value *= gain/100;
 
    float ratio=0;
float x = 255+pid;
float y = 255-pid;
    if(x<y){
        ratio = 255/y;
    }else{
        ratio = 255/x;
    }

  x *= ratio;
  y *= ratio;
  analogWrite(motor1,255-(int)x);
  analogWrite(motor2,255-(int)y);
    //Serial.print("----------");
    //Serial.println("----------");
    //Serial.print("----------");
    //Serial.println("----------");
    //Serial.print("Error: ");
    //Serial.println(prev_error);
    Serial.print("X: ");
    Serial.println(x);
     Serial.print("Y: ");
    Serial.println(y);
    Serial.print("Pid: ");
    Serial.println(pid_value);
    //Serial.print("soluong :");
    //Serial.println(soluongqtrophiatrenline);
   // for(int i = 0; i<=6;i++){
       // Serial.print("I = "+i);
   //     Serial.println(ktraqtro[i]);
       // Serial.println("=======");
  //  }
   //  Serial.println("---------------");
}
