# Smart RFID-Based Locking System

## Project Overview
The Smart RFID-Based Locking System is a low-cost electronic access control prototype developed using RFID technology and an Arduino microcontroller. The system identifies authorized RFID cards and tags and controls a servo-based locking mechanism accordingly.

## Objectives
- To develop an RFID-based authentication system.
- To allow access only to authorized RFID credentials.
- To automate the locking and unlocking mechanism.
- To provide visual and audio feedback to users.
- To develop an economical offline security prototype.

## Hardware Components
- Arduino Uno R3
- RC522 RFID Reader Module
- RFID Card and RFID Tag
- SG90 Servo Motor
- 16×2 I2C LCD Display
- Green LED
- Red LED
- Buzzer
- 220Ω Resistors
- Breadboard and Jumper Wires

## Software Requirements
- Arduino IDE
- Embedded C/C++ Programming
- MFRC522 Library
- Servo Library
- LiquidCrystal I2C Library

## Working Principle
1. The RFID reader scans the presented card or tag.
2. The Arduino reads its unique identification number (UID).
3. The UID is compared with the predefined authorized credentials.
4. If the credential is authorized, the servo motor unlocks the mechanism.
5. The LCD and green LED indicate successful authentication.
6. If the credential is unauthorized, access is denied and the red LED and buzzer provide feedback.
7. The servo automatically returns to its locking position after the predefined time.

## Key Features
- RFID-based access authentication
- Multiple authorized credentials
- Unauthorized access rejection
- Automatic servo-based locking
- LCD status display
- LED and buzzer notifications
- Offline operation

## Future Scope
- ESP32-based Wi-Fi connectivity
- Firebase cloud database integration
- Mobile application monitoring
- Advanced RFID authentication
- Improved mechanical locking mechanism

## Project Type
Academic Mini Project – Electronics and Telecommunication Engineering

## Developed By
Student Project Team

## License
This project is developed for educational and academic purposes.
