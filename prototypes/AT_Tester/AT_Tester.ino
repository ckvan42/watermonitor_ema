/* UART Serial Passthrough for NB-IoT hat.
 *  
 * Connect thru PuTTY or Arduino Serial Terminal with 115200 baud.
 * To get connected to the internet run these commands exactly:
 * 
 * at+cfun=1 
 * at+cops=0 
 * at+qcfg="NWSCANSEQ",020301 
 * at+qcfg="IOTOPMODE",0 
 * at+qcfg="BAND",0,80A,80A 
 *
 * Now run at+csq to make sure it does not say 99,99 
 *
 * AT+QICSGP=1,1,"m2minternet.apn","","",1 
 * at+qiact=1 
 * 
 * You should be connected now. 
 */
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  if (Serial.available()) {      // If anything comes in Serial (USB),
    Serial1.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
  }

  if (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(Serial1.read());   // read it and send it out Serial (USB)
  }
}
