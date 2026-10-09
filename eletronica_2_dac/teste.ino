byte a = 0b00000000;
void setup() {
  Serial.begin(9600);
  DDRD = 0b11111100;
  DDRB = 0b00000011;

  while (!Serial) {
    // wait for it to become ready
  }
}
byte lsb[] = {
  0b00000000,
  0b00000001,
  0b00000010,
  0b00000011,
  0b00000100,
  0b00000101,
  0b00000110,
  0b00000111,
  0b00001000,
  0b00001001,
  0b00001010,
  0b00001011,
  0b00001100,
  0b00001101,
  0b00001110,
  0b00001111
};

byte fundo[] = {
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000,
  0b11000000,
  0b11100000,
  0b11110000,
  0b11111000,
  0b11111100,
  0b11111110,
  0b11111111
 
};


void loop() {
  byte valor,teste;
  int r = 0;

  while (Serial.available() == 0) {
    //Espera para fazer a primeira leitura da serial
  }

  valor = Serial.parseInt();
  // Discarte do (\n) do buffer 
  Serial.read();
 
  if(valor == 1) {
     Serial.println("modo lsb");
     delay(100);
     for(r = 0; r < 16; r++) {
        buffer();
        PORTD = ((lsb[r]<<2)|(PORTD & 0b00000011));
        //Serial.print("saida atual: ");
        //Serial.println(PORTD,BIN);
        delay(100);  
      }
   }
  if(valor == 2){
     Serial.println("modo fundo escala");
     delay(100);
     for(int r = 0; r<11; r++){
      buffer();
      PORTD = (fundo[r]<<2)|(PORTD & 0b00000011);
      PORTB = fundo[r]>>6;
      //Serial.println(PORTB,BIN);
      delay(100);
     }
  }
  if(valor == 3){
    Serial.println("modo escada");
    delay(100);
    for(int i = 0; i<255; i++){
      a = a + 0b00000001;
      PORTD = (a<<2)|(PORTD & 0b00000011);
      PORTB = a>>6;
      //Serial.print(PORTB,BIN);
      //Serial.println(PORTD,BIN);
      delay(50);
    }
  }
}


void buffer(){
  while (Serial.available() == 0) {
      }
  delay(100);
  while (Serial.available() > 0) {
    // Discarte de caracteres do buffer
    Serial.read();
  }
}
