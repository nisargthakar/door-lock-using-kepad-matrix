/* Connections:-
 *  1st column of keypad goes to pin 9 and follows the order 9,8,7,6,5,4,3 
 *  an LED is connected to pin13 (positive of LED to pin13 and negative to ground).
 *  a buzzer on pin11 (positive of buzzer to pin11 and negative to ground).
 *  servo motor- vcc to vcc
                 gnd to gnd
                 datapin to pin10 of arduino
  */


#include <Password.h> //http://playground.arduino.cc/uploads/Code/Password.zip //tells to use password library
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip  //tells to use keypad library
#include <Servo.h> //tells to use servo library


Servo myservo; //declares servo
Password password = Password( "3115" ); //password to unlock, can be changed

const byte ROWS = 4; // Four rows
const byte COLS = 4; // columns
// Define the Keymap
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9, 8, 7, 6 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3 };


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  Serial.write(254);
  Serial.write(0x01);
  delay(200); 
  pinMode(13, OUTPUT);  //green light
  pinMode(11, OUTPUT);  //attach buzzer
  myservo.attach(10); //servo on digital pin 10 //servo
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  }

void loop(){
  keypad.getKey();
  myservo.write(0);
  }
  //take care of some special events
  void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
  case PRESSED:
  
  Serial.print("Enter:");
  Serial.println(eKey);
  delay(10);
  
  Serial.write(254);
  
  switch (eKey){
    case '*': checkPassword(); delay(1); break;
    
    case '#': password.reset(); delay(1); break;
    
     default: password.append(eKey); delay(1);
}
}
}
void checkPassword(){
  
if (password.evaluate()){  //if password is right open
    
    Serial.println("Accepted");
    Serial.write(254);delay(10);

    //Add code to run if it works
    myservo.write(150); //deg
    
        digitalWrite(13, HIGH);//turn on
    delay(5000); //wait 5 seconds
    digitalWrite(13, LOW);// turn off
    
    
}else{
    Serial.println("Denied"); //if passwords wrong keep locked
    Serial.write(254);delay(10);
    //add code to run if it did not work
    myservo.write(0);
    for(int i=0; i<=255; i++)    //buzzer goes high
    {
     analogWrite(11,i);
     delay(20);
    }
    for(int i=255; i>=0; i--)    //buzzer goes low
    {
     analogWrite(11,i);
     delay(20);
    }

}
}

