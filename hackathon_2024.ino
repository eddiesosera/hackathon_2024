// INPUT: Button Variables
const int buttonPlay = 12;
const int buttonPowerUp = 11;
const int buttonWin = 13;

// OUTPUT: LED Variables
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int led5 = 6;
const int led6 = 7;
const int led7 = 8;

// OUTPUT: Buzzer variables
const int buzzer1 = 10;
const int buzzer2 = 9;
// OUTPUT: An array of all the components
const int allOutputs[] = { led1, led2, led3, led4, led5, led6, led7};
const int numOfOutputs = sizeof(allOutputs) / sizeof(allOutputs[0]);
// OUTPUT: An array of Powerups LEDs
const int allPowerUps[] = { led1, led2, led3};
const int numOfPowerUps = sizeof(allPowerUps) / sizeof(allPowerUps[0]);

void setup() {
  // 1. INIT: Initialize Serial Monitor
  Serial.begin(9600);

  // 2.1 INIT: Input Comoponents assigned type
  pinMode(buttonPlay, INPUT);
  pinMode(buttonPowerUp, INPUT);
  pinMode(buttonWin, INPUT);

  // 2.2 INIT: Output Comoponents assigned type
  for (int i = 0; i < numOfOutputs; i++) {
    pinMode(allOutputs[i], OUTPUT);
  }
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);

  // 2.3 INIT: All LEDs and BUzzer is on for 2 seconds
  for (int i = 0; i < numOfOutputs; i++) {
    digitalWrite(allOutputs[i], HIGH);
    digitalWrite(buzzer1, HIGH);
    digitalWrite(buzzer2, HIGH);
  }
  delay(600);
  // 2.4 INIT: LEDs and Buzzer are off
  for (int i = 0; i < numOfOutputs; i++) {
    digitalWrite(allOutputs[i], LOW);
    digitalWrite(buzzer1, LOW);
    digitalWrite(buzzer2, LOW);
  }
  delay(600);
    // 2.3 INIT: All LEDs and BUzzer is on for 2 seconds
  for (int i = 0; i < numOfOutputs; i++) {
    digitalWrite(allOutputs[i], HIGH);
    digitalWrite(buzzer1, HIGH);
    digitalWrite(buzzer2, HIGH);
  }
  delay(600);
  // 2.4 INIT: LEDs and Buzzer are off
  for (int i = 0; i < numOfOutputs; i++) {
    digitalWrite(allOutputs[i], LOW);
    digitalWrite(buzzer1, LOW);
    digitalWrite(buzzer2, LOW);
  }

  Serial.println("Initialization Complete.");
}


void loop() {
  // PROGRAM LIFECYCLE
  bool isPlaying = false;
  int gameSpeed = 50;
  static int lastActiveIndex = -1;  // Remember the last active LED index

  // 3. Player play
  if (digitalRead(buttonPlay) == HIGH) {
    // Reset initial light:
    for (int i = 0; i < numOfOutputs; i++) {
    digitalWrite(allOutputs[i], LOW);
  }
    delay(50);  // Debounce delay
    if (digitalRead(buttonPlay) == HIGH) {  // Check again
      isPlaying = !isPlaying;  // Toggle the state
      delay(500);  // Allow time for the button to be released

      if (!isPlaying && lastActiveIndex != -1) {
        // When stopping, turn off the buzzer and keep the last LED on
        digitalWrite(buzzer1, LOW);
        for (int i = 0; i < numOfOutputs; i++) {
          if (i != lastActiveIndex) {
            digitalWrite(allOutputs[i], LOW);
          }
        }
      }
    }
  }

  if (isPlaying) {
    Serial.println("Play pressed: Starting sequence");

    while (isPlaying) {
      for (int i = 0; i < numOfOutputs; i++) {
        digitalWrite(allOutputs[i], HIGH);
        digitalWrite(buzzer2, HIGH);
        delay(gameSpeed);
        digitalWrite(allOutputs[i], LOW);
        digitalWrite(buzzer2, LOW);
        delay(gameSpeed / 4);

        lastActiveIndex = i;  // Remember the last active LED index

        if (digitalRead(buttonPlay) == HIGH) {
          delay(50);  // Debounce delay
          if (digitalRead(buttonPlay) == HIGH) {  // Check again
            isPlaying = false;  // Stop the sequence
            delay(500);  // Allow time for the button to be released
            break;  // Exit the for loop
          }
        }
      }
    }
  } else if (lastActiveIndex != -1) {
    // Ensure the last active LED remains on when the loop is not running
    digitalWrite(allOutputs[lastActiveIndex], HIGH);
  }

  // 4. POWER UP
  // if (digitalRead(buttonPowerUp) == HIGH) {
  //   Serial.println("Power Up pressed: Starting sequence");

  //   int randomIterations = random(5, 15); // Generate a random number of iterations between 5 and 15

  //   int lastLedIndex = 0;
  //   for (int i = 0; i < randomIterations; i++) {
  //     lastLedIndex = i % numOfOutputs;
  //     digitalWrite(allPowerUps[lastLedIndex], HIGH);
  //     digitalWrite(buzzer1, HIGH);
  //     delay(gameSpeed);
  //     digitalWrite(allPowerUps[lastLedIndex], LOW);
  //     digitalWrite(buzzer1, LOW);
  //     delay(gameSpeed / 4);
  //   }

  //   // Keep the last LED on
  //   digitalWrite(allPowerUps[lastLedIndex], HIGH);
  //   Serial.print("Final LED: ");
  //   Serial.println(lastLedIndex);

  // }


  // 5. Obstacle Encounter
  // if (digitalRead(buttonObstacle) == HIGH) {
  //   Serial.println("Obstacle button pressed: Flashing LEDs.");
  //   digitalWrite(ledStrip1, HIGH);
  //   digitalWrite(ledStrip2, HIGH);
  //   delay(500);
  //   digitalWrite(ledStrip1, LOW);
  //   digitalWrite(ledStrip2, LOW);
  //   Serial.println("LED flash complete.");
  // }


  // 5.1 WINNER
  if (digitalRead(buttonWin) == HIGH) {
  for (int i = 0; i < numOfOutputs; i++) {
    digitalWrite(allOutputs[i], HIGH);
    digitalWrite(buzzer1, HIGH);
    delay(gameSpeed);
    digitalWrite(allOutputs[i], LOW);
    digitalWrite(buzzer1, LOW);
    delay(gameSpeed / 2);
  }
  delay(800);

  // 2.3 WINNER: All LEDs and BUzzer is on for 2 seconds
  for (int i = 0; i < numOfOutputs; i++) {
    digitalWrite(allOutputs[i], HIGH);
    digitalWrite(buzzer1, HIGH);
  }
  delay(1000);

  // 2.4 WINNER: LEDs and Buzzer are off
  for (int i = 0; i < numOfOutputs; i++) {
    digitalWrite(allOutputs[i], LOW);
    digitalWrite(buzzer1, LOW);
  }

  }
}
