unsigned char incomingByte = 0; // for incoming serial data

void setup() {
  
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // if data on Serial line is available
    if (Serial.available() > 0)
    {
    // read the incoming byte
    analogWrite(9, 70);
    incomingByte = Serial.read();
   
    switch(incomingByte)
    {
      case '1':
        moveStraight(30);
      break;
      
      case '2':
        moveBack(30);
      break;
      
      case '3':
        turnLeft(30);
      break;
      
      case '4':
        turnRight(30);
      break;
      
      case '5':
        stop(30);
      break;
      
      default:
        Serial.print("!!! Incorrect Incoming Byte !!!");
      break;
    }
  }
}

void moveStraight(int s) {
	digitalWrite(34, HIGH);
	digitalWrite(35, LOW);
	digitalWrite(36, HIGH);
	digitalWrite(37, LOW);
	delay(s);

}

void moveBack(int s) {
	digitalWrite(34, LOW);
	digitalWrite(35, HIGH);
	digitalWrite(36, LOW);
	digitalWrite(37, HIGH);
	delay(s);

}

void turnLeft(int s) {
	//analogWrite(9, 65);
	digitalWrite(34, HIGH);
	digitalWrite(35, LOW);
	digitalWrite(36, LOW);
	digitalWrite(37, HIGH);
	delay(s);
	//analogWrite(9, 50);

}

void turnRight(int s) {
	digitalWrite(34, LOW);
	digitalWrite(35, HIGH);
	digitalWrite(36, HIGH);
	digitalWrite(37, LOW);
	delay(s);

}

void stop(int s) {
	digitalWrite(34, LOW);
	digitalWrite(35, LOW);
	digitalWrite(36, LOW);
	digitalWrite(37, LOW);
	delay(s);

}
