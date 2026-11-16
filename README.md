# ROS 2 Vision-Based Autonomous Line Following Robot

**Florida State University | EEL 4930 – Autonomous Robots | Summer 2024**

## Project Overview

The objective of this project was to develop an autonomous mobile robot capable of following a predetermined path using computer vision and ROS 2.

As part of a team project, I developed a zone-based image processing and reactive navigation algorithm in C++. The algorithm was implemented and successfully demonstrated on a physical differential-drive robot.

## Hardware and Software

- Raspberry Pi 4
- Arduino Mega 2560
- RGB camera (640 × 480 resolution)
- DC motors and wheel encoders
- Differential-drive mobile robot
- ROS 2
- C++
- OpenCV
- Linux
- UART serial communication

The Raspberry Pi was responsible for image processing and navigation, while the Arduino managed motor control and encoder feedback. Wheel velocity commands were transmitted from the Raspberry Pi to the Arduino through a UART serial interface.

## Algorithm

### Image Processing and Zone Structure

The camera provides a 640 × 480 RGB image containing 307,200 pixels, each represented by three individual color values. To reduce computational overhead, the algorithm processes subsets of the image referred to as zones.

The lower half of the image is divided into five equally sized zones, each measuring 128 × 240 pixels. The lower half was selected because it captures the portion of the path closest to the robot, allowing the robot to make navigation decisions based on its immediate surroundings.

Processing only these zones reduces the number of pixels examined per processed frame by 50%. Additionally, the algorithm processes every fifteenth received image.

### Black Pixel and Line Detection

Although OpenCV was used for accessing image data in the original project, the line detection algorithm was implemented manually in C++ by iterating through the raw RGB image buffer.

A pixel is classified as black if all three of its RGB values fall below a predefined intensity threshold. A counter records the number of black pixels within each zone.

If the number of black pixels exceeds a user-defined threshold, the zone is classified as containing a portion of the line and assigned a binary value of 1. Otherwise, it is assigned a value of 0. This threshold was based on the proportion of black pixels within a zone and refined through experimental testing.

The resulting five-element binary representation describes the position of the line relative to the robot.

### Navigation and Motor Control

The navigation algorithm determines the appropriate movement based on the five-zone classification.

| Zone Pattern (Example) | Robot Action |
|---|---|
| 00100 | Move forward |
| 11111 | Continue straight through an intersection |
| 11100 | Turn left |
| 00111 | Turn right |
| 00000 | Stop |
| Unrecognized pattern | Reverse and turn slightly |

When turning, the robot rotates its wheels in opposite directions. If an unrecognized pattern is encountered, the robot reverses while slightly adjusting its orientation in an attempt to recover.

The resulting wheel velocity commands are transmitted to the Arduino Mega over UART at 9600 baud.

## Implementation Highlights

- Custom C++ image processing and line detection.
- ROS 2 subscriber and callback architecture.
- Direct RGB image buffer indexing.
- Region-of-interest processing and frame decimation.
- Experimental threshold tuning.
- Rule-based reactive navigation and recovery behavior.
- Linux serial port configuration using POSIX system calls and `termios`.
- Hardware integration between an embedded Linux computer and a microcontroller.

## Results

The algorithm was successfully tested on a physical robot, which completed the designated course in both directions and achieved the fastest course completion time among all robots in the class.

I attribute much of this performance to the simplicity of the line following algorithm and its relatively low computational overhead.

The algorithm demonstrated reliable line tracking, particularly at lower operating speeds. Although the robot occasionally encountered difficulties navigating sharp corners at higher speeds, its reverse-and-turn recovery behavior frequently allowed it to correct its orientation without operator intervention.

## Future Improvements

With the additional computer vision knowledge I have gained while pursuing my graduate degree in Robotics and Autonomous Systems, I would be interested in revisiting this project and implementing more sophisticated image processing and line tracking techniques.

Potential improvements include:

- Canny edge detection for extracting line boundaries.
- Estimation of the line's position and orientation relative to the robot.
- Continuous steering control for smoother navigation.
- Improved line reacquisition and recovery behavior.

While these techniques could improve tracking accuracy and produce smoother robot movement, they could also introduce additional computational overhead. I would be interested in experimentally comparing these approaches against the original algorithm to determine whether both smoother line tracking and faster course completion could be achieved.

## Repository Scope

This repository preserves my original C++ implementation from Summer 2024 for documentation and portfolio purposes. The complete ROS 2 workspace and associated Arduino firmware are not included.
