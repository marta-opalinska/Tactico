# Tactico Framework Evaluation Protocol

# Tactico framework introduction

- What it is
- For who it is intended
- Main features

# Getting Started

Hardware Used for the evaluation

build-in LED as a ERM motor dirven by PWM 

Pre-creted Hardware Layerd file - not main point of focus

Framework resources: Git repository, documentation, git README

# Evaluation Tasks


| Actuator    | Rated Voltage | Overdrive Voltage | Resonant Frequency (LRA) | Connection Type      |
| ----------- | ------------- | ----------------- | ------------------------ | -------------------- |
| LRA_1       | 2.2           | 2.5               | 170                      | DRV2605LEVM Driver 0 |
| ERM_1       | 2.0           | 2.5               | -                        | DRV2605LEVM Driver 1 |
| LRA_2       | 2.2           | 2.5               | 170                      | DRV2605LEVM Driver 2 |
| ERM_2 (LED) | 1.0           | 1.0               | -                        | GPIO 22              |


You have the above actuators. 
You would like to create a haptic device out if them. 
Your device should have two Actions - "right" and "left".
Action "right" should trigger the following activations:
Action "left" should trigger the following activations:

