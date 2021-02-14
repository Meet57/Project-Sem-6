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
  
  return distance;
}

void loop() {
  distance = UltrasonicLength(D4,D5);
  Serial.println(distance);
  
  delay(1000);
}
