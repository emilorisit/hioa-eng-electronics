HIOA Electronics Project

Overview

This repository contains an electronics engineering project developed in 2013 during my studies at OsloMet (formerly HIOA). The project focuses on designing and implementing a boat control system, showcasing skills in PCB design, electrical engineering, Arduino programming, Android development, hardware integration, and project management.

Project Features

PCB Design: Custom-designed printed circuit boards (PCBs) created using Eagle CAD, showcasing hands-on electrical engineering skills.

Electrical System Design: Complete design and integration of electrical circuits for reliable system performance.

GPS Integration: Real-time speed calculation in knots using the TinyGPS++ library.

Fuel Sensor Monitoring: Calculates fuel consumption and efficiency (nautical miles per liter).

Android Communication: Utilizes AndroidAccessory for communication with mobile devices.

Timers and Interrupts: Efficient handling of hardware timers for accurate pulse counting.

Repository Structure

HIOA-Electronics-Project/
├── android/                     # Android application source code
│   └── BoatControlActivity.java  # Android app for boat control system
│
├── code/                         # Source code for Arduino
│   ├── gpsknots/                 # GPS speed monitoring
│   ├── fuelsensor_0_2/           # Fuel sensor integration
│   ├── boatcontrol_01/           # Initial boat control implementation
│   ├── boatcontrol_02/           # Advanced boat control with battery monitoring
│   └── boatcontrol_0_1/          # Basic Android communication example
│
├── documentation/                # Reports and project documentation
│   ├── project_plan.pdf          # Initial project plan
│   ├── status_meeting_1.pdf      # Status meeting notes
│   └── final_report.docx         # Final project report
│
├── design/                       # Design files
│   ├── eagle/                    # PCB schematics (Eagle CAD)
│   ├── fritzing/                 # Circuit diagrams (Fritzing)
│   ├── img/                      # Project-related images
│   └── gantt_chart.png           # Project timeline (Gantt chart)
│
├── datasheets/                   # Datasheets for components used
│   └── datasheet1.pdf
│
├── presentations/                # Presentation materials
│   └── auxiliary_control_system.pptx
│
├── README.md                     # Overview of the project (this file)

Technologies Used

Arduino: Core platform for hardware programming.

TinyGPS++: GPS parsing and processing library.

AndroidAccessory: USB communication with Android devices.

Eagle CAD: PCB design and schematics.

Fritzing: Circuit visualization.

Android Development: Java-based Android application for boat system monitoring.

Highlights

Comprehensive Engineering Work: Includes PCB design, electrical engineering, Android development, and software integration for a functional control system.

Real-Time Data Processing: Accurate GPS data parsing and fuel monitoring.

Hardware and Software Integration: Seamless communication between sensors, microcontrollers, and Android devices.

Project Documentation: Comprehensive reports and planning materials for effective project management.
