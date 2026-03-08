# Smart IoT Gas Leakage Detection Robot

A mobile robotic platform designed for industrial safety. This robot detects hazardous gas leaks (LPG, Smoke, Methane) and transmits real-time alerts via Bluetooth/IoT while allowing manual navigation.

## 🚀 Features
- **Dual Mode:** Supports Bluetooth Joystick control and Autonomous Obstacle Avoidance.
- **Gas Monitoring:** Real-time MQ-2 sensor data processing.
- **Safety Protocol:** Automatic "Hard-Stop" and audible alarm when gas levels exceed safety limits.
- **Visual Feedback:** 16x2 I2C/Parallel LCD display for local monitoring.

## 🛠️ Hardware Stack
| Component | Purpose |
| :--- | :--- |
| **Arduino Uno** | Main Microcontroller |
| **MQ-2** | Gas & Smoke Sensor |
| **HC-SR04** | Ultrasonic Distance Sensor |
| **HC-05** | Bluetooth Communication Module |
| **L293D** | Dual H-Bridge Motor Driver |
| **16x2 LCD** | Status Display |

## 🔌 Connection Pinout
- **Motors:** IN1(D2), IN2(D3), IN3(D4), IN4(D5)
- **HC-05:** TX(D10), RX(D11)
- **HC-SR04:** Trig(D7), Echo(D8)
- **MQ-2:** Analog Pin A0
- **Buzzer:** Digital Pin D13

## 📲 Usage
1. Upload the code to your Arduino.
2. Open any **Bluetooth Terminal** app on your smartphone.
3. Connect to "HC-05".
4. Send 'F', 'B', 'L', 'R' for movement and 'S' to stop.
5. If gas is detected, the robot will ignore your commands and sound the alarm.
