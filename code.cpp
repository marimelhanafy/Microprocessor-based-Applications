#include "mbed.h"

DigitalOut L1(LED1);
DigitalOut L2(LED2);
DigitalOut Buz(p5);

AnalogIn temp(p16);
AnalogIn light(p18);
DigitalIn B(p20);

Serial pc(USBTX,USBRX);

int main() {
    float t=0, data;
    bool DoorStillOpen=false;
    B.mode(PullUp);

    while(1) {
      
      pc.printf("Time             = %f\n\r",t);
      data = temp.read();
      pc.printf("Tempreture       = %f\n\r",data);
      data= light.read();
      pc.printf("Light Brightness = %f\n\n\n\n\r",data); 
      
      wait(1);
      
    // Light status
      if(light.read()<=0.3){
          pc.printf("Light Status: OPEN \n\r");
          L1=1;
      }else{
          pc.printf("Light Status: CLOSE \n\r");
          L1=0;
        }

    // Temp status
      if(temp.read()>=0.3){
          pc.printf("Temperature Status: OPEN \n\r");
          L2=1;
      }else{
          pc.printf("Temperature Status: CLOSE \n\r");
          L2=0;
        }

    // Door status
    // 1) Check if door's open
      if(!B && !DoorStillOpen)
          DoorStillOpen=true;

    // 2) Count time while door's open (increment 1 sec)
      if(DoorStillOpen){
          t++;
          wait(1);
      }   
    
    // 3) Check if door's been closed
      if(B) {
          Buz=0;
          DoorStillOpen=false;
          t=0; //reset timer
      }

    // 4) If door's been open for t>5
      if(!B && t>=5) {
          Buz=1;
      }

      if(Buz==1)
        pc.printf("Alarm Status: OPEN \n\r");
      else
        pc.printf("Alarm Status: CLOSE \n\r");
      
      if(DoorStillOpen)
        pc.printf("Door Status: OPEN \n\n\n\n\r");
      else
        pc.printf("Door Status: CLOSE \n\n\n\n\r");
    }
}
