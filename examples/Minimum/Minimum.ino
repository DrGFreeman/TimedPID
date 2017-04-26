/*
Minimum.ino
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
This example shows the minimum code lines to declare, setup and get the command
from the PID controller.
*/

#include <TimedPID.h>

/* Create a TimedPID object instance.
Kp, Ki, Kd are floats representing the proportional, integral and derivative
gains respectively. */
TimedPID pid(Kp, Ki, Kd);

void setup() {
  /* Optional: Set min and max PID command values.
  minValue and maxValue arguments are floats representing the min and max
  command values that the PID controller can produce.
  Uncomment the following line to use this option. */
  // pid.setCmdRange(minValue, maxValue);
}

void loop() {
  /* Get the PID command
  cmd is a variable to store the PID command.
  setPoint is the desired "target" value for the controlled process variable.
  procVar is the current value of the process variable being controlled.

  getCmd() method uses unit time step. */
  float cmd = pid.getCmd(setPoint, procVar);

  /* Alternatively, use getCmdAutoStep() method to have the PID controller
  automatically calculate the time step between calls to the method. */
  // float cmd = pid.getCmdAutoStep(setPoint, procVar);

  /* Alternatively, use getCmdStep() method to have the PID controller use the
  time step defined by timeStep. */
  // float cmd = pid.getCmdStep(setPoint, procVar, timeStep);
}
