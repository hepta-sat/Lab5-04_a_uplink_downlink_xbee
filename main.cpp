#include "mbed.h"
#include"HEPTA_EPS.h"
#include"HEPTA_SENSOR.h"
#include"HEPTA_COM.h"

RawSerial pc(USBTX,USBRX,9600);
HEPTA_EPS eps(p16,p26);
HEPTA_SENSOR sensor(p17,
                  p28,p27,0x19,0x69,0x13,
                  p13, p14,p25,p24);
HEPTA_COM com(p9,p10,9600);

int main()
{
    int i = 0,rcmd=0,cmdflag=0;
    float bt,ax,ay,az;
    com.printf("Count Up!\r\n");
    while(1) {
        com.printf("num = %d\r\n",i);
        i++;
        wait(1.0);
        com.xbee_receive(&rcmd,&cmdflag);
        pc.printf("rcmd=%d, cmdflag=%d\r\n",rcmd, cmdflag);
        if (cmdflag == 1) {
            if (rcmd == 'a') {
                pc.printf("Command Get %d\r\n",rcmd);
                com.printf("HEPTA Uplink OK\r\n");
                pc.printf("===================\r\n");
                pc.printf("Accel sensing Mode\r\n");
                pc.printf("===================\r\n");
                for(int ii = 0; ii < 10; ii++) {
                    sensor.sen_acc(&ax,&ay,&az);
                    eps.vol(&bt);
                    com.printf("AX = %f\r\n",ax);
                    com.printf("AY = %f\r\n",ay);
                    com.printf("AZ = %f\r\n",az);
                    com.printf("V = %f\r\n",bt);
                    wait(0.5);
                }
            }
            com.initialize();
        }
    }
}