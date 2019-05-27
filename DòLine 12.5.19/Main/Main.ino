//File lấy dữ liệu
//Số đc lấy từ trái sang phảiic

#define motor1 10
#define motor2 11
#define hongngoai 2
const int qtro[7] = {A0,A1,A2,A3,A4,A5,A6};
int ktraqtro[7] = {0,0,0,0,0,0,0};
void setup() {
  Serial.begin(19200);
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
   if(analogRead(qtro[i]) > trungbinh){
    ktraqtro[i] = 1;
   }
  }

  //Chuyển động
  LinePIDFilter();
  
}
