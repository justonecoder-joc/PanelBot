// Rotary Encoder Inputs
#define CLK PB3
#define DT PB4
#define SW PB5

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;

// Speed calculation.
float current_time;
float new_time;

float avg_t1;
float avg_t2;
float avg_time;
int current_count = 0;

void setup() {
        
	// Set encoder pins as inputs
	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);

	// Setup Serial1 Monitor
	Serial1.begin(9600);

	// Read the initial state of CLK
	lastStateCLK = digitalRead(CLK);
    current_time = micros();
}

void loop() {
  current_time = micros();  
  // current_count = counter;    
  // if (counter % 20 == 0)
  // {
  //   new_time = millis();
  //   int delta_time = (new_time - current_time) * 1000;
  //   Serial1.print("Speed = ");
  //   Serial1.println(delta_time);
  //   current_time = new_time;
  // }
	// Read the current state of CLK
	currentStateCLK = digitalRead(CLK);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DT) != currentStateCLK) {
			counter --;
			currentDir ="CCW";
		} else {
			// Encoder is rotating CW so increment
			counter ++;
			currentDir ="CW";
		}

		Serial1.print("Direction: ");
		Serial1.print(currentDir);
		Serial1.print(" | Counter: ");
		Serial1.println(counter);
	}


  if ( (counter != current_count))
  {
  
  avg_t1 = micros();

    if ( (current_count - counter) % 4 == 0){
    avg_t2 = micros();
    Serial1.print("current_count = ");
    Serial1.println(current_count);

    new_time = micros();

    Serial1.print("current_time = ");
    Serial1.println(float(current_time));
    Serial1.print("new_time = ");
    Serial1.println(float(new_time));

    float delta_time = (new_time - current_time);
    avg_time = avg_t2 - avg_t1;
    Serial1.print("avg_time = ");
    Serial1.println(float(avg_time));

    Serial1.print("delta_time = ");
    Serial1.println(float(delta_time));

    Serial1.print("Ticks = ");
    Serial1.println(( counter - current_count) );

    Serial1.print("Ticks per milli second = ");
    //Serial1.println(float( ( counter - current_count)*1000 / delta_time));
    Serial1.println(float( ( counter - current_count)*1000 / avg_time));
    current_count = counter;
  
  }
    

  }

	// Remember last CLK state
	lastStateCLK = currentStateCLK;

	// Read the button state
	int btnState = digitalRead(SW);

	//If we detect LOW signal, button is pressed
	if (btnState == LOW) {
		//if 50ms have passed since last LOW pulse, it means that the
		//button has been pressed, released and pressed again
		if (millis() - lastButtonPress > 50) {
			Serial1.println("Button pressed!");
		}

		// Remember last button press event
		lastButtonPress = millis();
	}
	// Put in a slight delay to help debounce the reading
	delay(1);
}