// Define pin numbers for LEDs
const int greenPin = 5;
const int yellowPin = 6;
const int redPin = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
    // Initialize LED pins as output
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);


  //Serial.println("This is my first Arduino program!"); 
}

// Function to handle Green light ON
void GreenLightOn() {
  digitalWrite(greenPin, HIGH);  // Turn on green light
  digitalWrite(yellowPin, LOW);  // Turn off yellow light
  digitalWrite(redPin, LOW);     // Turn off red light
  Serial.println("GO!");         // Send instruction for drivers
}

// Function to handle Yellow light ON
void YellowLightOn() {
  digitalWrite(greenPin, LOW);   // Turn off green light
  digitalWrite(yellowPin, HIGH); // Turn on yellow light
  digitalWrite(redPin, LOW);     // Turn off red light
  Serial.println("SLOW DOWN!");  // Send instruction for drivers
}

// Function to handle Red light ON
void RedLightOn() {
  digitalWrite(greenPin, LOW);   // Turn off green light
  digitalWrite(yellowPin, LOW);  // Turn off yellow light
  digitalWrite(redPin, HIGH);    // Turn on red light
  Serial.println("STOP!");       // Send instruction for drivers
}

void loop() {
  // put your main code here, to run repeatedly:
   RedLightOn();
   YellowLightOn();
   GreenLightOn();
  
}
