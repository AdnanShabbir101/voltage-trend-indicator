int readPin = A0;

int redPin = 8;
int bluePin = 12;
int greenPin = 6;

float prev_volts = 0.0;
float current_volts;

int readVal;

float change;

long prev_time = 0;
long curr_time;
const long interval = 200;      //ms between each sample taking.

void setup() {
  // put your setup code here, to run once:

  pinMode(readPin,INPUT);

  pinMode(redPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(greenPin,OUTPUT);

  Serial.begin(2000000);
}

void loop() {
  // put your main code here, to run repeatedly:

  readVal = analogRead(readPin);              //0 - 1023
  current_volts = (5.0/1023.0)*readVal;       //Converting the 10bit analog Signal input from binary to voltage 0-5v
  
  curr_time = millis();                       //noting the time when voltage was checked

  Serial.print(change);
  Serial.print("   ");
  Serial.println(curr_time);

  if(curr_time - prev_time >= interval){

    prev_time = curr_time;
    change = current_volts - prev_volts;

    if(change > 0.05){
      digitalWrite(bluePin,HIGH);
      digitalWrite(redPin,LOW);
    }

    else if(change < -0.05){
       digitalWrite(bluePin,LOW);
       digitalWrite(redPin,HIGH);
    }

    else{
      digitalWrite(bluePin,LOW);
      digitalWrite(redPin,LOW);
    }

    prev_volts = current_volts;

    analogWrite(greenPin,(255.0/1023.0)*readVal);


  }



}
