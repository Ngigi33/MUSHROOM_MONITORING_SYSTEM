//GSM RX TX PIN DEFINITIONS
#define RXD2 16
#define TXD2 17
char c;

//GSM FUNCTINS
void update_Serial();
void Send_Msg();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  Serial.println("Initializing...........");
  delay(1000);

  Serial2.println("AT");  //Once the handshake test is successful, it will back to OK
  update_Serial();
  Serial2.println("AT+CSQ");  //Signal quality test, value range is 0-31 , 31 is the best
  update_Serial();
  Serial2.println("AT+CCID");  //Read SIM information to confirm whether the SIM is plugged
  update_Serial();
  Serial2.println("AT+CREG?");  //Check whether it has registered in the network
  update_Serial();

  Send_Msg();
}

void loop() {
  // put your main code here, to run repeatedly:
  update_Serial();
}
void update_Serial() {
  //read from SIM900 and send to Serial Monitor
  if (Serial2.available()) {
    c = Serial2.read();
    Serial.write(c);
  }

  //read from Serial Monitor and send to SIM900
  if (Serial.available()) {
    c = Serial.read();
    Serial2.write(c);
  }
}

void Send_Msg() {
  Serial.println("..................Sending Message Started...............");
  Serial2.println("AT+CMGF=1");  //Configuring Text mode
  delay(500);

  Serial2.println("AT+CMGS=\"+254721954135\"");  // Replace x with mobile number
  delay(500);

  Serial.println("Sending Message.........................");
  Serial2.println("Temperature Over 30.....");  //SMS text you want to send
  delay(100);

  Serial2.println((char)26);  //ASCII code of CTRL+Z
  delay(500);

  Serial.println("..................Sending Message Ended...............");
}