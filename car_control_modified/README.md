# PS2 Joystick Control via Arduino

The essential part of  a robotic car is to make it move. Arduino is an easy tool to make it done.

The robotic car contains four DC motors, which would be driven by a driver board and would be controlled via arduino.

For the robotic car, I chose the driver board made by MOBIUS TECH, which uses TB6612FNG to drive motors. And to install the driver board, I just need to plug it onto an arduino UNO board. The driver board have 4 sockets and it can control all four motors, what we need to do is to program the arduino board well.

In order to send movement commands to the car, a PS2 joystick would be used as well. Therefore, the `ps2x.lib` would be included in the arduino file.

I modified the source control code given by MOBIUS tech and add some new features to make it move as I want. Here is the link for their Github page:  https://github.com/MoebiusTech/-mecanum-robot-kit-for-Arduino-stm32

