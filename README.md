# TimedPID
A simple PID controller for the Arduino IDE featuring different time step calculation options.

Version 1.0.0  
[![Build Status](https://travis-ci.org/DrGFreeman/TimedPID.svg?branch=master)](https://travis-ci.org/DrGFreeman/TimedPID)  
By Julien de la Bruère-Terreault (drgfreeman@tuta.io)

## Summary

This library for the Arduino IDE provides a simple [Proportional - Integral - Derivative (PID) controller](https://en.wikipedia.org/wiki/PID_controller). The controller features three options for time step calculation (the time step is used for integral and derivative error terms calculation):

1. Non-specified (unit) time step (`getCmd()` method)
1. Auto time step calculation (uses time between calls to `getCmdAutoStep()` method)
1. Defined time step (passed as argument to `getCmdStep()` method)

## Examples
Two example sketches are provided with the library:
* _Minimum.ino_  
This example shows the minimum code lines to declare, setup and get the command from the PID controller.

* _DemoTimedPID.ino_  
This example shows how to use the library with a defined time step. It includes a fake mechanical system simulation to demonstrate how the PID controls the force to apply on a mass object subject to inertial and drag forces to have the mass object achieve a desired speed function.

## Library Reference
* `TimedPID(float Kp = 1.0, float Ki = 0.0, float Kd = 0.0)`  
Constructor: `Kp`, `Ki` and `Kd` are the proportional, integral and derivative gains respectively.

* `float getCmd(float setPoint, float procVar)`  
Returns the system command. `setPoint` is the desired "target" value for the process variable being controlled. `procVar` is the current value of the process variable being controlled. This method uses unit time step for integral and derivative error terms calculation.

* `float getCmdAutoStep(float setPoint, float procVar)`  
Similar to `getCmd` method except this method automatically calculates the time step based on the time between two calls to this method. The calculated time step is in seconds units.

* `float getCmdStep(float setPoint, float procVar, float timeStep)`  
Similar to `getCmdAutoStep` method except the time step is passed to the method via the `timeStep` argument. The time step can be in any units.

* `void reset()`  
Resets the PID error terms. The method also resets to the current time the time variable used by the `getCmdAutoStep` to calculate the time step.

* `void setCmdRange(float cmdMin, float cmdMax)`  
Sets the min and max command values that can be returned by the `getCmd`, `getCmdAutoStep` and `getCmdStep` methods to the range defined by the arguments `cmdMin` and `cmdMax`. Unless this method is called, the command range will not be limited.

* `void setGains(float Kp, float Ki, float Kd)`  
Sets the PID controller gains. `Kp`, `Ki` and `Kd` are the proportional, integral and derivative gains respectively.

## Version history

* 1.0.0 (2017-04-25) Initial release
