#define IR D7

bool ir;

void setup() {
  pinMode(IR,INPUT);
  Serial.begin(9600);
}

void loop() {
  ir = digitalRead(IR);

  if(ir == 1){
    Serial.println("Empty");
  }else if(ir == 0){
    Serial.println("Object");
  }
  delay(100);
}
