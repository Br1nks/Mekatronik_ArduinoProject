#include <Servo.h>                                 // Include servo library

Servo servoLeft;                                   // Servo object instances
Servo servoRight;
Servo servoTurret;  

const int servoLeftPin = 12;                       // I/O Pin constants
const int servoRightPin = 11;
const int servoTurretPin = 10;
const int pingPin = 13;
const int piezoPin = 4;

const int msPerTurnDegree = 6;                     // For maneuvers  
const int tooCloseCm = 30;                         // For distance decisions
const int bumpedCm = 6;
int ccwLim = 1400;                                 // For turret servo control
int rtAngle = 900;
const int usTocm = 29;                             // Ping))) conversion constant


// Sequence of turret positions.
int sequence[] = {0, 2, 4, 6, 8, 10, 9, 7, 5, 3, 1};

// Declare array to store that many cm distance elements using pre-calculated
// number of elements in array.
const int elements = sizeof(sequence);
int cm[elements];
int angle[elements];

int cmMax = 0;
int angleMax = 0;

// Pre-calculate degrees per adjustment of turret servo.
const int degreesTurret = 180/(sizeof(sequence)/sizeof(int)-1);

int i = -1;                                         // Global index
int j = 0;
int h = 0;
int sign = 1;                                      // Sign of increments
int theta = -degreesTurret;                        // Set up initial turret angle

int b =1;
void setup() {
  tone(piezoPin, 3000, 1000);                      // Play tone for 1 second
  delay(1000);                                     // Delay to finish tone
 
  Serial.begin(9600);                              // Open serial connection

  servoLeft.attach(servoLeftPin);                  // Attach left signal to pin 13
  servoRight.attach(servoRightPin);                // Attach right signal to pin 12
  servoTurret.attach(servoTurretPin);              // Attach turret signal to pin 12
  maneuver(0, 0, 1000);                            // Stay still for 1 second
  turret(0);                                       // Set turret to 0 degrees
  

  while (h != 2) {
  i++;
   // Advance turret servo to next position in sequence and wait for it to get there.
  theta = sequence[i] * degreesTurret;       
  turret(theta);
  delay(100);                                

  cm[i] = cmDistance();                             // Measure cm from this turret angle
  angle[i] = sequence[i]*degreesTurret;

  if (cm[i] > cmMax){
    if (j == 1) {
      b = 0;
    }
    cmMax = cm[i];
    angleMax = angle[i] + b*180;
  }
  
  if (h == 1) {
    // Convert degree angle to time the BOE Shield-Bot wheels will have to turn to face
    // direction of turret.
    int turnAngleTime = (90 - angleMax) * msPerTurnDegree;
    Serial.println("turnangletime: ");
    Serial.println(turnAngleTime);
    Serial.println("angleMax: ");
    Serial.println(angleMax);
    turret(90); 
    
    if(turnAngleTime < 0)                          // If negative turning angle,
    {
      turret(90);
      maneuver(-200, 200, -turnAngleTime);         // then rotate CCW for turningAngleTime ms
      maneuver(0,0,100);
      h = 2;
    }
    else                                           // If positive turning angle,
    {
      turret(90); 
      maneuver(200, -200, turnAngleTime);          // then rotate CW for turningAngleTime ms
      //turret(0);
      maneuver(0,0,100);
      h =2 ;
    }
    //maneuver(200, 200);                            // Start going forward again
  } else {
    maneuver(0,0);
    //turret(0);
    
  }

  if(i == 10 && j == 0)                                      // If turret at max, go back to zero
  {
    maneuver(-200,200,180*msPerTurnDegree);
    i = -1;
    j = 1;
  }
  if (i == 10 && j == 1 ) {
    Serial.println("hej");
    i = -1;
    h = 1;
  }
  }
}

void loop() {

  
}



/*
 * Control BOE Shield-Bot servo direction, speed, set and forget version.
 * Parameters: speedLeft - left servo speed
 *             speedRight - right servo speed
 *             Backward  Linear  Stop  Linear   Forward
 *             -200      -100......0......100       200
 */
void maneuver(int speedLeft, int speedRight)
{
  // Call maneuver with just 1 ms blocking; servos will keep going indefinitely.
  maneuver(speedLeft, speedRight, 1);              
}

/*
 * Control BOE Shield-Bot servo direction, speed and maneuver duration.   
 * Parameters: speedLeft - left servo speed
 *             speedRight - right servo speed
 *             Backward  Linear  Stop  Linear   Forward
 *             -200      -100......0......100       200
 *             msTime - time to block code execution before another maneuver
 * Source:     http://learn.parallax.com/ManeuverFunction
 */
void maneuver(int speedLeft, int speedRight, int msTime)
{
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
  if(msTime==-1)                                   // if msTime = -1
  {                                  
    servoLeft.detach();                            // Stop servo signals
    servoRight.detach();   
  }
  delay(msTime);                                   // Delay for msTime
}

/*
 * Position the horn of a Parallax Standard Servo
 * Parameter: degreeVal in a range from 90 to -90 degrees.
 */
void turret(int degreeVal)
{
  servoTurret.writeMicroseconds(ccwLim - rtAngle + (degreeVal * 10));
}

/*
 * Get cm distance measurment from Ping Ultrasonic Distance Sensor
 * Returns: distance measurement in cm.   
 */
int cmDistance()
{
  int distance = 0;                                // Initialize distance to zero    
  do                                               // Loop in case of zero measurement
  {
    int us = ping(pingPin);                        // Get Ping))) microsecond measurement
    distance = convert(us, usTocm);                // Convert to cm measurement
    delay(3);                                      // Pause before retry (if needed)
  }
  while(distance == 0);                            
  return distance;                                 // Return distance measurement
}

/*
 * Converts microsecond Ping))) round trip measurement to a useful value.
 * Parameters: us - microsecond value from Ping))) echo time measurement.
 *             scalar - 29 for us to cm, or 74 for us to in.
 * Returns:    distance measurement dictated by the scalar.   
 */
int convert(int us, int scalar)
{
    return us / scalar / 2;                        // Echo round trip time -> cm
}

/*
 * Initiate and capture Ping))) Ultrasonic Distance Sensor's round trip echo time.
 * Parameter: pin - Digital I/O pin connected to Ping)))
 * Returns:   duration - The echo time in microseconds
 * Source:    Ping by David A. Mellis, located in File -> Examples -> Sensors
 * To-Do:     Double check timing against datasheet
 */
long ping(int pin){
  long duration;                                   // Variables for calculating distance
  pinMode(pin, OUTPUT);                            // I/O pin -> output
  digitalWrite(pin, LOW);                          // Start low
  delayMicroseconds(2);                            // Stay low for 2 us
  digitalWrite(pin, HIGH);                         // Send 5 us high pulse
  delayMicroseconds(5);                            
  digitalWrite(pin, LOW);                          
  pinMode(pin, INPUT);                             // Set I/O pin to input
  duration = pulseIn(pin, HIGH, 25000);            // Measure echo time pulse from Ping)))
  return duration;                                 // Return pulse duration
}
/*
 * Finds the first instance of a value in an array.
 * Parameters: value to search for
 *             array[] to search in
 *             elements - number of elements to search
 * Returns:    index where the matching element was found    
 */
int findIn(int value, int array[], int elements)
{
  for(int i = 0; i < elements; i++)
  {
    if(value == array[i]) return i;
  }
  return -1;
}  

