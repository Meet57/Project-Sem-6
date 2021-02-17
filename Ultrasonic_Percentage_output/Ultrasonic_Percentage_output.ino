#define TankBase 40
#define TankTop 5

const int trigPin = D4;
const int echoPin = D5;

long duration;
long distance;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
}

int UltrasonicLength(int tri,int echo){
  digitalWrite(tri, LOW);
  delayMicroseconds(2);

  digitalWrite(tri, HIGH);
  delayMicroseconds(10);
  digitalWrite(tri, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration * 0.034 / 2;
  
  if(distance <= TankTop){
    return 100;
  }

  if(distance >= TankBase){
    return 0;
  }

  return 100 - ((distance-TankTop)*100)/(TankBase-TankTop);
}

void loop() {
  distance = UltrasonicLength(D4,D5);
  Serial.print(distance);
  Serial.println(" %");
  
  delay(1000);
}
