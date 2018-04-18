int PIN_SPEAKER = 9;


void play(){
    tone(PIN_SPEAKER,500);
    delay(500);   //这里用来根据节拍调节延时，500这个指数可以自己调整，在该音乐中，我发现用500比较合适。
    noTone(PIN_SPEAKER);
}

void play2(){
    tone(PIN_SPEAKER,300);
    delay(500);   //这里用来根据节拍调节延时，500这个指数可以自己调整，在该音乐中，我发现用500比较合适。
    noTone(PIN_SPEAKER);
}
 
void play3(){
    digitalWrite(PIN_SPEAKER, HIGH);
    delay(100);
    digitalWrite(PIN_SPEAKER, LOW);
    delay(100);
    digitalWrite(PIN_SPEAKER, HIGH);
    delay(100);
    digitalWrite(PIN_SPEAKER, LOW);
}
 



void setup() {
  Serial.begin(9600); //Open serial connection at 9600 baud
  pinMode(PIN_SPEAKER, OUTPUT);
}

void loop() {
    play3();
}


