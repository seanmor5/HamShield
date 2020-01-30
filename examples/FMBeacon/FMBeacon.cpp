/* Hamshield
 * Example: Morse Code Beacon
 * 
 * Test beacon will transmit and wait 10 seconds. 
 * Beacon will check to see if the channel is clear before it 
 * will transmit.
 * Connect the HamShield to your Pi. Screw the antenna 
 * into the HamShield RF jack. Connect the Pi to wall 
 * power. To compile, run `make` in this directory.
 * Run the executable. To test, set a HandyTalkie 
 * to 438MHz. You should hear the message " BEAT NAVY" 
 * in morse code.
*/

#define DDS_REFCLK_DEFAULT 9600
#include <HamShield.h>

// Need some C++ functionality to mirror Arduino stuff
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#if GPIOBOARD
#define MIC_PIN 18
#define RESET_PIN 23
#else
#define MIC_PIN 3
#define RESET_PIN 4
#endif

HamShield radio;

// Run our start up things here
void setup() { 
  // NOTE: if not using PWM out, it should be held low to avoid tx noise
  pinMode(MIC_PIN, OUTPUT);
  digitalWrite(MIC_PIN, LOW);
  
  // set up the reset control pin
  // NOTE: HamShieldMini doesn't have a reset pin, so this has no effect
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH);
  
  usleep(5000); // wait for device to come up, usleep in microseconds
  
  // Send some stdout stuff
  std::cout << "HamShield FM Beacon Example" << std::endl;

  // Query the HamShield for status information
  std::cout << "Radio status: ";
  int result = radio.testConnection();
  if(result == 0){ // connection failed, quit program
    std::cout << "failed" << std::endl;
    std::exit(1);
  } else { // connection success, continue
    std::cout << "success" << std::endl;
  }
  
  // Tell the HamShield to start up
  radio.initialize();

  // Set the transmit power level (0-8)
  radio.setRfPower(0);

  // Set the morse code characteristics
  radio.setMorseFreq(600);
  radio.setMorseDotMillis(100);

  // Configure the HamShield
  radio.frequency(432300); // 438 MHz
  
  std::cout << "Radio Configured." << std::endl;
}

int main(int argc, char **argv){
    setup();
    // We'll wait up to 10 seconds for a clear channel, requiring that the channel is clear for 2 seconds before we transmit
    while(true){
    if (radio.waitForChannel(30000,2000,-5)) {
      // If we get here, the channel is clear. Let's print the RSSI to the serial port as well.
      std::cout << "Signal is clear, RSSI: ";
      std::cout << radio.readRSSI() << std::endl;
      
      // Start transmitting by putting the radio into transmit mode.
      std::cout << "Transmitting... " << std::endl;
      radio.setModeTransmit();
      
      // Send a message out in morse code
      char msg[] = " BEAT NAVY";
      radio.morseOut(msg);
      
      // We're done sending the message, set the radio back into recieve mode.
      radio.setModeReceive();
      std::cout << "Done." << std::endl;
    } else {
      // If we get here, the channel is busy. Let's also print out the RSSI.
      std::cout << "The channel was busy. Waiting 10 seconds. RSSI: ";
      std::cout << radio.readRSSI() << std::endl;
    }

    // Wait 10 seconds before we send our beacon again.
    sleep(10); // sleep in seconds
    }
}
