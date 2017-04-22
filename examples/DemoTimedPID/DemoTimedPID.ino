#include <TimedPID.h>

float Kp = 10.0;
float Ki = 0.15;
float Kd = 5.0;

TimedPID pid(Kp, Ki, Kd);

float speed = 0;
float accel = 0;
float force = 0;
float fDrag = 0;
float mass = 0.2;

float fMax = 300;

unsigned long initialTime;
unsigned long lastTime;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  pid.setCmdRange(-fMax, fMax);
  initialTime = micros();
  lastTime = initialTime;
  delay(1);
}

void loop() {
  unsigned long currentTime = micros();
  float timeStep = float(currentTime - lastTime) / 1E6;
  lastTime = currentTime;
  
  float targetSpeed = 0;
  if (currentTime - initialTime > 8E6){
    // Reset initial time
    initialTime = currentTime;
  }
  else if (currentTime - initialTime > 6E6)
  {
    targetSpeed = 200;
  }
    else if (currentTime - initialTime > 5E6)
  {
    targetSpeed = 180;
  }
  else if (currentTime - initialTime > 3E6) {
    targetSpeed = 200;
  }

  targetSpeed += 5 * sin(micros() / 2.5E5);
  
  fDrag = .003 * speed * speed;
  force = pid.getCmd(targetSpeed, speed);
  accel = (force - fDrag) / mass;
  speed += accel * timeStep;

  Serial.print(targetSpeed);
  Serial.print("\t");
  //Serial.print(force);
  //Serial.print("\t");
  Serial.println(speed);
  while (micros() - currentTime < 10000)
  {
    // Wait until time step is reached
  }
}

