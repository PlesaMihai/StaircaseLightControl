#define PIN_ON        LOW
#define PIN_OFF       HIGH

#define lightOnTime   10000
#define relaySwitchTime 750

uint8_t inputPin[5];
volatile uint8_t outputToBeSet = 0xFF;
uint8_t previousOutput = 0xFF;
uint8_t cycleOutput = 0xFF;

unsigned long currTime = 0;

typedef struct{
  uint8_t pin;
  uint8_t pinState;
} sRelay;

sRelay outRelay[4];

void setup() {
  // configure the input pins
  inputPin[0] = 0;
  inputPin[1] = 1;
  inputPin[2] = 2;
  inputPin[3] = 3;
  inputPin[4] = 7;

    for(uint8_t i = 0; i < 5; i++)
  {
    pinMode(inputPin[i], INPUT_PULLUP);
  }

  attachInterrupt(digitalPinToInterrupt(inputPin[0]), inputIsr1, FALLING);
  attachInterrupt(digitalPinToInterrupt(inputPin[1]), inputIsr2, FALLING);
  attachInterrupt(digitalPinToInterrupt(inputPin[2]), inputIsr3, FALLING);
  attachInterrupt(digitalPinToInterrupt(inputPin[3]), inputIsr4, FALLING);
  attachInterrupt(digitalPinToInterrupt(inputPin[4]), inputIsr5, FALLING);

  // Configure the ouput pins and put them all to low
  outRelay[0].pin = 4;
  outRelay[1].pin = 5;
  outRelay[2].pin = 6;
  outRelay[3].pin = 8;

  for(int i = 0; i < 4; i++)
  {
    pinMode(outRelay[i].pin, OUTPUT);
    digitalWrite(outRelay[i].pin, LOW);
    outRelay[i].pinState = LOW;
  }

  //Start serial communication
  Serial.begin(9600);
}

void setOutputsLow(uint8_t exception)
{
  if(!(exception >= 0 && exception < 4))
    return;
    
  for(uint8_t i = 0; i < 4; i++)
  {
    if(i != exception)
    {
      digitalWrite(outRelay[i].pin, LOW);
      outRelay[i].pinState = LOW;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(outputToBeSet != previousOutput)
  {
    setOutputsLow(outputToBeSet);
    delay(relaySwitchTime);
    if(outputToBeSet >= 0 && outputToBeSet < 4)
    {
      if(outRelay[outputToBeSet].pinState == LOW)
      {
        Serial.println("");
        Serial.print("Setting output ");
        Serial.println(outputToBeSet);
        digitalWrite(outRelay[outputToBeSet].pin, HIGH);
        currTime = millis();
        
      }
      previousOutput = outputToBeSet;
    }
  }
  if(millis() - currTime > lightOnTime)
  {
    digitalWrite(outRelay[outputToBeSet].pin, LOW);
    setOutputsLow(outputToBeSet);
    previousOutput = 0xFF;
    outputToBeSet = 0xFF;
    currTime = millis();
  }
}

void inputIsr1()
{
  outputToBeSet = 0;
}

void inputIsr2()
{
  outputToBeSet = 1;
}

void inputIsr3()
{
  outputToBeSet = 2;
}

void inputIsr4()
{
  outputToBeSet = 3;
}

void inputIsr5()
{
  if(cycleOutput > 3)
  {
    cycleOutput = 1;
  }

  outputToBeSet = cycleOutput;
  if(cycleOutput == previousOutput)
  {
    previousOutput = 0xFF;
  }
  cycleOutput++;
}
