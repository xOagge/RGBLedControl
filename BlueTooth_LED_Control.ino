#define BLUETOOTH_BAUD 9600
#define redPin 10
#define greenPin 9
#define bluePin 11
#define brightnessPin A4

bool changedIndex = false;

String command = "";
int trueRed = 0;
int trueGreen = 0;
int trueBlue = 0;
int PValue = 0;
float brightness = 0.0;
bool changedBrightness = false;
bool changedColor = false;

void setup() {
  // Initialize serial communication with the computer
  Serial.begin(9600);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(brightnessPin, INPUT);

  // Initialize serial communication with the Bluetooth module
  Serial1.begin(BLUETOOTH_BAUD); // Ensure this matches your Bluetooth module's baud rate
  Serial.println("Bluetooth module is ready.");
  Serial.println("Available commands:");
  Serial.println("1. RGB Command: Send 9 digits (RRGGGBBB) where R, G, B are color values (0-255).");
  Serial.println("2. Brightness Command: Adjusts the brightness based on a potentiometer connected to the analog pin.");
  Serial.println("Example: '123456789' for setting RGB values.");
  Serial.println("Commands are processed when received in full. Ensure the Bluetooth baud rate matches the module's setting.");
}

void loop() {
  // Serial -> Code
  if (Serial1.available()) {
    char incomingChar = Serial1.read();
    //add info to command
    if(incomingChar != '\n'){
      command += incomingChar;
      command.trim();
      //verify if there is new color or change in brightness
    }
  }
  //Code -> LED
  readBrightness();
  VerifyNewcolor();
  //update LED status
  UpdateLED();
}

bool isNumeric(String S){
  for(int i = 0; i<S.length(); i++){
    if(!isdigit(S[i])) return false;
  }
  return true;
}

// Function to set the RGB color
void setColor() {
  analogWrite(redPin, (int)(255-(float)trueRed*brightness));
  analogWrite(greenPin, (int)(255-(float)trueGreen*brightness));
  analogWrite(bluePin, (int)(255-(float)trueBlue*brightness));
}

void readBrightness(){
  PValue = analogRead(brightnessPin);
  float B = (float)PValue / 1023.0;
  if(B != brightness){
    brightness = B;
    changedBrightness = true;
  }
}

void VerifyNewcolor(){
  if(command.length() == 9 and isNumeric(command)) changedColor = true;
}

void UpdateLED(){
  if(changedColor){
    trueRed = command.substring(0,3).toInt();
    trueGreen = command.substring(3,6).toInt();
    trueBlue = command.substring(6,9).toInt();
    Serial.print("RED: ");
    Serial.println((int)(255-(float)trueRed*brightness));
    Serial.print("GREEN: ");
    Serial.println((int)(255-(float)trueGreen*brightness));
    Serial.print("Blue: ");
    Serial.println((int)(255-(float)trueBlue*brightness));
    if (trueRed >= 0 && trueRed <= 255 && trueGreen >= 0 && trueGreen <= 255 && trueBlue >= 0 && trueBlue <= 255){
      setColor();
    }
    changedColor = false;
    command = "";
  } else if(changedBrightness){
    setColor();
  }
  changedBrightness = false;
}
