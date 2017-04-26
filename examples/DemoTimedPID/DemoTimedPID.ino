/*
DemoTimedPID.ino
Source: https://github.com/DrGFreeman/TimedPID

MIT License

Copyright (c) 2017 Julien de la Bruere-Terreault <drgfreeman@tuta.io>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
This example demonstrates how to use the TimedPID class to control the speed of
a mass subject to inertial and drag forces by controlling the force applied to
the mass. The controller reacts to changes in the desired speed.

The getCmdStep() is used in this case since the time step is calculated in the
main loop and used to update the speed of the mass under acceleration.
*/

#include <TimedPID.h>

// Define the PID controller proportional, integral and derivative gains
float Kp = 10.0;
float Ki = 0.15;
float Kd = 5.0;

// Create a TimedPID object instance
TimedPID pid(Kp, Ki, Kd);

// Initialize the mass system variables
float speed = 0;    // the speed of the mass
float accel = 0;    // the acceleration of the mass
float fDrag = 0;    // the drag force on the mass
float mass = 0.2;   // the mass value
float force;        // the force applied to the mass by the control system

// Define the maximum force the system can apply
float fMax = 300;

// Variables used for set point control and time step calculation
unsigned long initialTime;
unsigned long lastTime;

void setup() {
  // Open Serial communication and wait for monitor to be opened
  Serial.begin(9600);
  while(!Serial);

  // Set the PID controller command range
  pid.setCmdRange(-fMax, fMax);

  // Initialize time variables
  initialTime = micros();
  lastTime = initialTime;
  delay(1);
}

void loop() {

  // Calculate the time step between passes of the main loop
  // Get current time
  unsigned long currentTime = micros();
  // Calculate time step in seconds (micro seconds / 1 000 000)
  float timeStep = float(currentTime - lastTime) / 1E6;
  // Store current time as last time for next pass of the loop
  lastTime = currentTime;

  // Define the target speed as function of time
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
  // Add continuous variation of the target speed
  targetSpeed += 5 * sin(micros() / 2.5E5);

  // Calculate drag force proportional to speed squared
  fDrag = .003 * speed * speed;

  // Get the system command from the PID based on target speed and current speed
  force = pid.getCmd(targetSpeed, speed);

  // Calculate mass acceleration using Newton's second law (F=ma -> a=F/m)
  accel = (force - fDrag) / mass;
  // Update mass speed based on acceleration and time step
  speed += accel * timeStep;

  // Print target speed, force command and mass speed to Serial port
  Serial.print(targetSpeed);
  Serial.print("\t");
  Serial.print(force);
  Serial.print("\t");
  Serial.println(speed);

  // Ensure a constant time step of the main loop (10 milliseconds)
  while (micros() - currentTime < 10000)
  {
    // Wait until time step is reached
  }
}
