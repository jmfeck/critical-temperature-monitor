# Critical Temperature Monitor

**Note:** This project was developed as part of a university course assignment in 2015/2016.  
It is archived here for historical and portfolio purposes.

> ⚡ Important: Documentation and code comments have been translated to English for better accessibility.

## Project Description

This project implements a critical temperature monitoring system using:

- Arduino Mega 2560
- Ethernet Shield
- Temperature Sensor (connected to pin A0)
- 16x2 LCD Display
- Physical control buttons (increase, decrease, activate monitoring)
- Status indicator LEDs

The system allows the user to adjust the critical temperature threshold (`tempSet`) directly through physical buttons.  
When the measured temperature (`tempData`) exceeds this threshold, an alert is triggered:

- An email and push notification are sent.
- A new row is automatically logged in a Google Sheets spreadsheet.

These actions are managed via the free **PushingBox** service, which received HTTP requests from the Arduino and forwarded them securely via HTTPS to the final services.

> ⚠️ Note: At the time, the Arduino Mega 2560 with Ethernet Shield did not natively support HTTPS connections. PushingBox was used as an intermediary to enable secure forwarding.

> ⚠️ Additional note: The PushingBox service may no longer be active today (or not working properly).  
> To replicate the project nowadays, it is recommended to use alternatives such as:
> - Custom Webhooks
> - IFTTT automations
> - Direct database integrations

This project was designed as a **proof of concept**, demonstrating how to integrate simple hardware with free cloud services for real-time monitoring.

## Hardware Used

- Arduino Mega 2560
- Ethernet Shield
- Temperature Sensor (e.g., LM35)
- 16x2 LCD Display (connected to pins 33–43)
- Physical buttons
- Indicator LEDs
- Cables and Breadboard
- Internet connection (via Ethernet cable)

## Project Structure

- `src/` — Main project code (`critical_temperature_monitor.ino`)
- `extras/` — Older development versions and tests (not fully recovered)
- `docs/` — Project documents (proposal, final report, presentation, schematics)
- `images/` — Hardware photos and screenshots

## How to Run

1. Open the `critical_temperature_monitor.ino` file in the Arduino IDE.
2. Set your PushingBox `DeviceID` in the code (search for `YOUR_DEVICE_ID`).
3. Upload the code to the Arduino Mega.
4. Connect the Arduino to the internet using the Ethernet Shield.
5. Adjust the critical temperature threshold using the physical buttons (`+` and `-`).
6. Press the OK button to activate monitoring.

When the temperature exceeds the set threshold, the system will automatically send an alert.

## Requirements

- Arduino IDE (compatible with Arduino Mega 2560)
- Functional Ethernet Shield
- PushingBox account (or alternative service)
- Network access to the Internet

---

Project archived preserving its original content and historical purpose.
