
#include<Console.h>
//#include <Bounce2.h>
// constants won't change. They're used here to 
// set pin numbers:
const int redbuttonPin = 2;     // the number of the pushbutton pin
const int redledbuttonPin =3;  //ns is red
const int grnbuttonPin = 4;     // the number of the pushbutton pin
const int grnledbuttonPin =5;  //we is grn

//bounce add
const int buttonPin = 6;    // the number of the pushbutton pin: bounce add
const int ledPin = 13;      // the number of the LED pin: bounce add

// variables will change
int redbuttonstate = 0;         // variable for reading the pushbutton status
int grnbuttonstate = 0;
String buttonstate="btnstate";      //Machine on or off
int pcscount = 0;


// Variables will change:  bounce add
int newledState = HIGH;         // the current state of the output pin
int newbuttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

int time = 0;
int maxpress = 120;
int bounce = 12;

int change= 0;// 0 is neutral, 1 is green, 2 is red

int seqcounter = 0;
int counter = 0;
int anticounter = 0;
int ledstate = LOW;

//talking code
#include <Bridge.h>
#include <HttpClient.h>
String rhurl ="http://192.168.0.11:8000/?test=";

int acount =0;
String urladd = "";




void setup() {

  //initialize console and wait for port to open:
  Bridge.begin();
  Console.begin();
  //Wait for console port to connect
  while(!Console);
  //First send
  Console.println("In setup at the moment");
  
  
  
  // put your setup code here, to run once:
  // initialize the activate LED pin as an output:
  pinMode(redledbuttonPin, OUTPUT); 
  pinMode(grnledbuttonPin, OUTPUT); 
  
  // initialize the pushbutton pin as an input:
  pinMode(redbuttonPin, INPUT);//this one
  pinMode(grnbuttonPin, INPUT);//this one
  
  
  //bounce code
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, newledState);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  redbuttonstate = digitalRead(redbuttonPin);
  grnbuttonstate = digitalRead(grnbuttonPin);
  
  unsigned int spot = 0;
  unsigned int result= digitalRead(redbuttonPin);

    
      if (result){
        bounce++;
      }
      else {
        bounce--;
      }
  if (bounce>maxpress){
        bounce=maxpress;
  
  if (redbuttonstate==HIGH){
    if (change!=2){
     change = 2;
          
     buttonstate="Stop"; 
     //send to server
     Console.println(result);
     HttpClient client;
     urladd= buttonstate;//String(acount) ;
     client.get(rhurl+urladd);
     //delay(5000);
     
     
     Console.println("redbuttonPin is high"); 
     Console.println("grnbuttonPin is low");    
     } 
  }
  
   if (grnbuttonstate==HIGH){
     if (change!=1){
       change = 1;
       
       buttonstate="Go";  
       //send to server
       Console.println(result);
       HttpClient client;
       urladd= buttonstate+pcscount;//String(acount) ;
       client.get(rhurl+urladd);
       //delay(5000);
       
       Console.println("redbuttonPin is low");
       Console.println("grnbuttonPin is high");
       }
     }
     spot++;
  }
  
  acount++;
  
  //bounce add code
  
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != newbuttonState) {
      newbuttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (newbuttonState == HIGH && buttonstate=="Go" ) {
        if (newbuttonState == HIGH){
          pcscount++;
         Console.println (pcscount);
         change = 2;
                 
        }
        newledState = !newledState;
      }
    }
  }
  
  // set the LED:
  digitalWrite(ledPin, newledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
     
  
<<<<<<< HEAD
}

=======
}
>>>>>>> 08f8c424bb855f392a49e171a74a93897f349804
