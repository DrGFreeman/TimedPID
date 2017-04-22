/*
TimedPID.h
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
A simple PID controller for the Arduino IDE featuring different time step
calculation options.
*/

#ifndef PID_h
#define PID_h

#include <Arduino.h>

class TimedPID
{
public:
  /* Constructor:
  Kp: the proportional gain
  Ki: the integral gain
  Kd: the derivative gain
  */
  TimedPID(float Kp = 1.0, float Ki = 0.0, float Kd = 0.0);

  /* Get command without time step
   * setPoint it the desired process set point
   * procVar is the currrent value of the process variable to be controlled
   * No time step is used (assumed = 1)
  */
  float getCmd(float setPoint, float procVar);

  /* Get command with auto time step calculation
   * setPoint it the desired process set point
   * procVar is the currrent value of the process variable to be controlled
   * The time step is calculated from the last call to the method
  */
  float getCmdAutoStep(float setPoint, float procVar);

  /* Get command with specified time step
   * setPoint it the desired process set point
   * procVar is the currrent value of the process variable to be controlled
   * timeStep is the timeStep to be used for integration / derivation
  */
  float getCmdStep(float setPoint, float procVar, float timeStep);

  // Reset the PID error terms
  void reset();

  /* Set the maximum command range. Commands calculated outside the cmdMin and
   * cmdMax range will be set to cmdMin or cmdMax respectively.
  */
  void setCmdRange(float cmdMin, float cmdMax);

  /* Set the PID gains:
  Kp: the proportional gain
  Ki: the integral gain
  Kd: the derivative gain
  */
  void setGains(float Kp, float Ki, float Kd);

private:
  // Command range
  float _cmdMin;
  float _cmdMax;
  bool _boundRange;

  // Error terms
  float _errorPrevious;
  float _errorIntegral;

  // Gains
  float _Kp, _Ki, _Kd;

  // Last time the getCmd method was called
  unsigned long _lastCmdTime;

  // Bound the command within command range
  float boundCmd(float cmdIn);
};

#endif
