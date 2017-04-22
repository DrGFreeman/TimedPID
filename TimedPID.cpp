/*
TimedPID.cpp
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

#include <TimedPID.h>

// Constructor
TimedPID::TimedPID(float Kp, float Ki, float Kd)
{
  setGains(Kp, Ki, Kd);
  reset();
  _boundRange = false;
}

// Bound the command within the command range
float TimedPID::boundCmd(float cmdIn)
{
  float cmdOut = cmdIn;

  if (_boundRange)
  {
    cmdOut = constrain(cmdIn, _cmdMin, _cmdMax);
  }
  return cmdOut;
}

// Get command without time step
float TimedPID::getCmd(float setPoint, float procVar)
{
  // Calculate error terms
  float error = setPoint - procVar;
  _errorIntegral += error;
  float errorDerivative = error - _errorPrevious;

  // Set last error to current error
  _errorPrevious = error;

  // Calculate command
  float cmd = _Kp * error + _Ki * _errorIntegral + _Kd * errorDerivative;

  // return bound command
  return boundCmd(cmd);
}

// Get command with auto time step calculation
float TimedPID::getCmdAutoStep(float setPoint, float procVar)
{
  // Calculate time step from last time method was called
  unsigned long currentTime = micros();
  unsigned long timeStep = currentTime - _lastCmdTime;

  // Set last time method was called to current time
  _lastCmdTime = currentTime;

  // Get command
  return getCmdStep(setPoint, procVar, float (timeStep) / 1E6);
}

// Get command with specified time step
float TimedPID::getCmdStep(float setPoint, float procVar, float timeStep)
{
  // Calculate error terms
  float error = setPoint - procVar;
  _errorIntegral += (error + _errorPrevious) / 2 * timeStep;
  float errorDerivative = (error - _errorPrevious) / timeStep;

  // Set last error to current error
  _errorPrevious = error;

  // Calculate command
  float cmd = _Kp * error + _Ki * _errorIntegral + _Kd * errorDerivative;

  // return bound command
  return boundCmd(cmd);
}

// Reset the PID error terms
void TimedPID::reset()
{
  _errorPrevious = 0;
  _errorIntegral = 0;

  _lastCmdTime = micros();
}

// Set the maximum command range
void TimedPID::setCmdRange(float cmdMin, float cmdMax)
{
  _cmdMin = cmdMin;
  _cmdMax = cmdMax;
  _boundRange = true;
}

// Set the PID gains
void TimedPID::setGains(float Kp, float Ki, float Kd)
{
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
}
