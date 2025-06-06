const int segmentPins[4] = {
  2,   // - D4
  14,  // - D5
  12,  // - D6
  13   // - D7
};

const int digitPins[3] = {0, 4, 5}; //selector pins

void setup() {
  // Set segment pins as OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  //configuring selector pins
  pinMode(digitPins[0], OUTPUT);
  pinMode(digitPins[1], OUTPUT);
  pinMode(digitPins[2], OUTPUT);
  
  //setting selector pin initially low
  digitalWrite(digitPins[0], LOW);
  digitalWrite(digitPins[1], LOW);
  digitalWrite(digitPins[2], LOW);
}



const byte digitCodes[10] = {
  0b0000, // 0
  0b1000, // 1
  0b0100, // 2
  0b1100, // 3
  0b0010, // 4
  0b1010, // 5
  0b0110, // 6
  0b1110, // 7
  0b0001, // 8
  0b1001, // 9
};


void displayDigit(byte code) {
  for (int i = 0; i < 4; i++) {
    bool state = bitRead(code, 3 - i); // MSB is segment a
    digitalWrite(segmentPins[i], state ? HIGH : LOW);//turnary operator
  }
}


void displayNumber(int num) {
  int hundreds = num / 100;
  int tens = (num / 10) % 10;
  int ones = num % 10;

// Show hundreds digit
  digitalWrite(digitPins[2], LOW); // Turn OFF digit1
  digitalWrite(digitPins[1], HIGH);// Turn ON digit2
  digitalWrite(digitPins[0], HIGH);//Turn OFF digit3
  displayDigit(digitCodes[hundreds]);
  delay(5); 

// Show tens digit
  digitalWrite(digitPins[0], LOW); 
  digitalWrite(digitPins[1], HIGH);
  digitalWrite(digitPins[2], HIGH); 
  displayDigit(digitCodes[tens]);
  delay(5); // Short delay for persistence

// Show ones digit
  digitalWrite(digitPins[0], HIGH);
  digitalWrite(digitPins[1], LOW);
  digitalWrite(digitPins[2], HIGH);
  displayDigit(digitCodes[ones]);
  delay(5);
}

void loop() {
  for (int num = 0; num < 1000; num++) {
    unsigned long startTime = millis();
    while (millis() - startTime < 1000) {
      displayNumber(num); // Refresh all digits repeatedly for 1 second
    }
  }
}
