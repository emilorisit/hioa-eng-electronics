HIOA Electronics Project

Overview

This repository contains an electronics engineering project developed during my studies at OsloMet (formerly HIOA). The project focuses on designing and implementing a boat control system, showcasing skills in Arduino programming, hardware integration, and project management.

Project Features

GPS Integration: Real-time speed calculation in knots using the TinyGPS++ library.

Fuel Sensor Monitoring: Calculates fuel consumption and efficiency (nautical miles per liter).

Android Communication: Utilizes AndroidAccessory for communication with mobile devices.

Timers and Interrupts: Efficient handling of hardware timers for accurate pulse counting.

Repository Structure

HIOA-Electronics-Project/
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
└── LICENSE                       # License for the repository

Technologies Used

Arduino: Core platform for hardware programming.

TinyGPS++: GPS parsing and processing library.

AndroidAccessory: USB communication with Android devices.

Eagle CAD: PCB design and schematics.

Fritzing: Circuit visualization.

Highlights

Real-Time Data Processing: Accurate GPS data parsing and fuel monitoring.

Hardware and Software Integration: Seamless communication between sensors, microcontrollers, and Android devices.

Project Documentation: Comprehensive reports and planning materials for effective project management.

Usage

Clone the repository:

git clone https://github.com/yourusername/hioa-eng-electronics.git

Navigate to the code folder for the desired feature (e.g., gpsknots) and upload the .ino file to an Arduino-compatible microcontroller.

Refer to the documentation for setup instructions and project details.

License

This project is licensed under the MIT License. See the LICENSE file for more details.

Disclaimer

This is a legacy project developed during my early engineering studies. While functional, the code and design reflect the tools and knowledge available at the time.

Contact

Feel free to reach out with any questions or suggestions:

Name: Emil Niclas Hofseth

Email: 150952943+emilorisit@users.noreply.github.com

LinkedIn: [Your LinkedIn Profile](https://www.linkedin.com/in/emilniclas/)
