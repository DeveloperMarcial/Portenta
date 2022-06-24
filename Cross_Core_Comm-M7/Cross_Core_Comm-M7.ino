// Sketch uses 188,136 bytes (23%) of program storage space.
// Maximum is  786,432 bytes.
// Global variables use 69,760 bytes (13%) of dynamic memory,
// leaving             453,864 bytes for local variables.
// Maximum is          523,624 bytes.
/* Include the Libararies --------------------------------------------------- */
#include "RPC.h"                        // Comes with the mbed board installation. Used for cross core communication: M7 <---> M4.

using namespace rtos;                   // Since the Portenta cores are based on the Mbed real-time OS,
                                        // this allows access to the many features of the RTOS and its functions in your Arduino sketches
                                        // such as for a multi-threaded Arduino sketch.
                                        // Use the RTOS namespace to create, synchronize, and manage threads. 

Thread blinkRGB_Thread;                 // Define a thread that will control the on-board LED.

/* Initialize M7 Core Global Variable --------------------------------------- */
int m7IntGlobalVar1 = 1111;             // M7 global variables that the M4 can change.
int m7IntGlobalVar2 = 2222;
int m7IntGlobalVar3 = 3333;

/**
 * @brief      Blink the Portenta Red, Green, Blue Light Emitting Diode.
 *             This routine works in unison with a routine on the M4 called BinkR()
 *             so that the on-board LED blink Red--Green--Purple.
 *
 *             This function is spawned once from setup() via:
 *             blinkRGB_Thread.start(BlinkRGB);
 */
void BlinkRGB()
{
  while(true)
  {
    digitalWrite(LEDR, LOW);              // Turn the red LED on (LOW is the voltage level).
    delay(500);                           // Wait for 500 milliseconds.
    digitalWrite(LEDR, HIGH);             // Turn the LED off by setting the voltage HIGH.
    delay(500);                           // Wait for 500 milliseconds.
    
    digitalWrite(LEDG, LOW);              // Turn the green LED on (LOW is the voltage level).
    delay(500);                           // Wait for 500 milliseconds.
    digitalWrite(LEDG, HIGH);             // Turn the LED off by setting the voltage HIGH.
    delay(500);                           // Wait for 500 milliseconds.
    
    digitalWrite(LEDB, LOW);              // Turn the blue LED on (LOW is the voltage level).
    delay(500);                           // Wait for 500 milliseconds.
    digitalWrite(LEDB, HIGH);             // Turn the LED off by setting the voltage HIGH.
    delay(500);                           // Wait for 5200 milliseconds.
  }
}

/**
 * @brief      Get user input via keyboard.
 */
void handleSerial()
{
  while (Serial.available() > 0)
  {
    char incomingCharacter = Serial.read();
    if ( (10==incomingCharacter) || (13==incomingCharacter) )
    {
      continue;
    }
    Serial.print("incomingCharacter=");
    Serial.println(incomingCharacter, DEC);
    switch (incomingCharacter)
    {
      case 'D':
      case 'd':
      {
        // Delay M7 Code.
        delay(0xACE);                   // Delay for about 3 seconds.
        break;
      }
      case 'P':
      case 'p':
      {
        // Send a Value of Unity to M4.
        int res = RPC.call("setOneVarInM4", 1).as<int>(); // Proof-of-concept of how to set an integer value in M4
                                                          // and have the M4 return an integer back to M7.
        // Print a Status Update.
        String toPrint = "M7 is calling setOneVarInM4() with a value of " + String(res);       
        Serial.println(toPrint);
        break;
      }
      case 'X':
      {
        // Do Something eXtremely Useful.
        break;
      }
    }
 }
}

bool micInferenceComplete = true;             // When M4 starts a mic inference it will set this false.
                                              // This assures multiple groupings of M4 RPC.println() are completely
                                              // sent to the M7, aka, the serial output is kept organized and pretty.
                                              // Otherwise, for all other M4 println() we will just let them print.
/**
 * @brief      To prevent the serial output from looking garbled we wait in
 *             RPC.avaliable() until "micInferenceComplete" asserts.
 *             NOTE: In setup() make sure to do something like:
 *                   RPC.bind("setMicInferenceComplete", setMicInferenceComplete);
 *
 * @return     Value set in M7.
 */
bool setMicInferenceComplete(bool var1_FromCM4) 
{
    micInferenceComplete = (bool)var1_FromCM4;// Set M7 variable to M4 sent in value.
    return micInferenceComplete;              // Return value set in M7.                   
}

/**
 * @brief      Get value that M4 sent to M7.
 *             NOTE: In setup() make sure to do something like:
 *                   RPC.bind("setOneM7Var", setOneM7Var);
 *
 * @return     Value set in M7.
 */
int setOneM7Var(int var1_FromCM4)
{
    m7IntGlobalVar1 = (int)var1_FromCM4;// Set M7 variable to M4 sent in value.
    return m7IntGlobalVar1;             // Return value set in M7.                   
}

/**
 * @brief      Get some values M4 sent to M7.
 *             NOTE: In setup() make sure to do something like:
 *                   RPC.bind("setTwoVar", setTwoVar);
 */
void setTwoVar(int var1_FromCM4, int var2_FromCM4)
{
    m7IntGlobalVar2 = (int)var1_FromCM4;
    m7IntGlobalVar3 = (int)var2_FromCM4;
    // TODO: Investigate returning strings or a buffer[] or better yet a MsgBlock.
    //       To pass multiple values between cores and return multiple values look
    //       at MsgBlock: https://github.com/hideakitai/MsgPack
    // String sentFromM4Value = String(m7IntGlobalVar1) + " and " + String(m7IntGlobalVar2);
    // return sentFromM4Value;
}

/**
 * @brief      The setup() function runs once when you press reset or power the board.
 */
void setup()
{
  // When programming M7 core maximum is 1,048,576 bytes.
  // When programming M4 core maximum is   786,432 bytes.

  // Start the remote procedure caller object.
  // This allows M7 full duplex communication with M4.
  RPC.begin();                        

  // Allow M7 to print to serial output.
 //Serial.begin(115200);                 
  Serial.begin(921600);                 
  
  // Initialize digital pin LED_BUILTIN as an output.
  pinMode(LEDR, OUTPUT);        
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Start M4 core.
  //bootM4();                             
  
  //
  // Create Boundens.
  //

  // Allow M4 to set a variable in M7.
  RPC.bind("setOneVar", setOneM7Var);   // These do not have to be the same.
                                        // M4 calls setOneVar().
                                        // M7 has a routine called setOneM7Var().
                                        // Thus bind() is a bounden between the name and function.
  // Allow M4 to set multiple variables in M7.
  RPC.bind("setTwoVar", setTwoVar);   

  // When an audio prediction is complete on the M4,
  // the M4 sends multiple text statements to the M7 to be sent to the serial output.
  // To assure the M7 prints all these statements as one grouping, we use this binding.
  RPC.bind("setMicInferenceComplete", setMicInferenceComplete);   
  
  // M7 is flashing the LED       Red--Green--Blue.
  // M4 is flashing the LED       ***--*****--Red
  // This causes the LED to flash Red--Green--Purple.
  //
  // Since each core puts the mechanis of flashing the LED on individual threads
  // hopefully there will not be much skew of the colors.
  // This purple color is due to the M7 and M4 cores working together.
  blinkRGB_Thread.start(BlinkRGB);

  //delay(5000);
  Serial.println("M7 is exiting setup()...");
}

/**
 * @brief      The loop() function runs over and over again forever.
 */
void loop()
{
    // Did the user send in a keystroke?
    handleSerial();

    // Blink the LED 3 times for a total of 3 seconds.
    // BlinkRGB(); <-- This is being handled on a thread.

    // Start printing the M4 status update to the serial output.
    // On M7, print everything that is received over the RPC stream interface.
    // Buffer it, otherwise all characters will be interleaved by other prints.
    String buffer = "";
    while (RPC.available() || !micInferenceComplete)
    {
      // M4 has sent an RPC println().
      buffer += (char)RPC.read(); // Fill the buffer with characters.
    }

    if (buffer.length() > 0)
    {
      // Start printing the M7 status update to the serial output.
      Serial.println("--- M7 --- --- M7 --- --- M7 --- --- M7 --- --- M7 ---");
      Serial.println("M7 global variable #1: "+ String(m7IntGlobalVar1));
      Serial.println("M7 global variable #2: "+ String(m7IntGlobalVar2));

      Serial.print(buffer);
    }
}
