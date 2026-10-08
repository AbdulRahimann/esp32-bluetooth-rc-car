# esp32-bluetooth-rc-car
A Bluetooth-controlled RC car powered by an ESP32 microcontroller and L298N motor driver, featuring multi-level PWM speed control via smartphone.

# ESP32 Bluetooth RC Car

A remote-controlled smart car powered by an ESP32 microcontroller and an L298N dual H-bridge motor driver. It features wireless control via Bluetooth Classic with multi-level PWM speed regulation using modern ESP32 Arduino Core 3.x APIs.

---

## Features

- **Bluetooth Classic Serial Control**: Pairs seamlessly with Android Bluetooth RC controller apps.
- **Dynamic PWM Speed Control**: 11 granular speed levels ranging from duty cycle 100 to 255 (max).
- **Full Differential Drive**: Complete directional movement (Forward, Backward, Left, Right, Stop).
- **Modern ESP32 Core 3.x Support**: Uses the updated `ledcAttach()` and `ledcWrite()` PWM architecture.

---

## Hardware Components

| Component | Description / Spec | Quantity |
| :--- | :--- | :--- |
| **ESP32 NodeMCU Development Board** | 30-pin or 38-pin with Bluetooth Classic | 1 |
| **L298N Motor Driver Module** | Dual H-Bridge motor controller | 1 |
| **TT Gear DC Motors + Wheels** | 3V–6V DC geared motors | 2 or 4 |
| **Power Source** | 2x 18650 Li-ion batteries (7.4V) or 3x (11.1V) | 1 pack |
| **Robot Chassis** | 2WD or 4WD acrylic chassis | 1 |
| **Jumper Wires & Switch** | Male-to-Female, Male-to-Male | As needed |

---

## Pinout & Wiring Connections

### 1. ESP32 to L298N Motor Driver

| ESP32 Pin | L298N Pin | Function |
| :--- | :--- | :--- |
| **GPIO 5** | **ENA** | Left Motor PWM Speed Control (Remove jumper) |
| **GPIO 22** | **IN1** | Left Motor Direction 1 |
| **GPIO 21** | **IN2** | Left Motor Direction 2 |
| **GPIO 19** | **IN3** | Right Motor Direction 1 |
| **GPIO 18** | **IN4** | Right Motor Direction 2 |
| **GPIO 23** | **ENB** | Right Motor PWM Speed Control (Remove jumper) |

> **Important**: Remove the black jumpers on the L298N `ENA` and `ENB` pins so the ESP32 can feed PWM signals directly.

### 2. Power Supply & Ground Sharing

- **Battery (+) (7.4V – 12V)** &rarr; L298N **12V terminal**
- **Battery (-)** &rarr; L298N **GND** and ESP32 **GND** (**Common Ground is required**)
- **L298N 5V Out** &rarr; ESP32 **VIN** / **5V pin** (if using onboard 5V regulator)

---

## Bluetooth Command Protocol

The car listens on Serial Bluetooth under the broadcast name **`GAGAN CAR`**.

### Movement Commands
| Command | Action | Left Motor (IN1, IN2) | Right Motor (IN3, IN4) |
| :--- | :--- | :--- | :--- |
| `'F'` | Forward | HIGH, LOW | LOW, HIGH |
| `'B'` | Backward | LOW, HIGH | HIGH, LOW |
| `'L'` | Turn Left | HIGH, LOW | HIGH, LOW |
| `'R'` | Turn Right | LOW, HIGH | LOW, HIGH |
| `'S'` | Stop Car | LOW, LOW | LOW, LOW |

### Speed Commands (PWM Duty Cycle: 0 - 255)
| Character | Speed Duty Cycle | Character | Speed Duty Cycle |
| :--- | :--- | :--- | :--- |
| `'0'` | 100 | `'6'` | 180 |
| `'1'` | 110 | `'7'` | 200 |
| `'2'` | 120 | `'8'` | 220 |
| `'3'` | 130 | `'9'` | 240 |
| `'4'` | 140 | `'q'` | 255 (Max) |
| `'5'` | 150 | - | - |

---

## Getting Started

### 1. Software Prerequisites
- [Arduino IDE](https://www.arduino.cc/en/software) (version 2.x recommended)
- **ESP32 Board Package**: Install via Arduino Board Manager (`esp32` by Espressif Systems, version 3.0.0 or higher).

### 2. Uploading the Code
1. Clone or download this repository.
2. Open the `.ino` sketch in Arduino IDE.
3. Select your board under **Tools > Board > ESP32 Arduino > ESP32 Dev Module**.
4. Select the matching COM port under **Tools > Port**.
5. Click **Upload**.

### 3. Pairing and Operation
1. Power on the robot chassis.
2. On your Android smartphone, turn on Bluetooth and scan for new devices.
3. Pair with **`GAGAN CAR`** (Default PIN is usually `1234` or `0000`, if prompted).
4. Open a Bluetooth RC controller app (such as *Bluetooth RC Controller* by mi社 or *Serial Bluetooth Terminal*).
5. Configure controls to match the character commands above and drive!

---

## Troubleshooting

- **Motors Hum but Do Not Spin**: Battery voltage may be too low, or initial PWM speed (`Speed = 100`) may be below the stall torque threshold of your motors. Increase speed to `'6'` (180) or higher.
- **Car Turns in Wrong Direction**: Invert the motor wires at the L298N screw terminals or swap the digital pins in the code.
- **Bluetooth Disconnects When Moving**: High motor current draw causes voltage drops resetting the ESP32. Use separate battery power for motors and logic, or add a decoupling capacitor across the ESP32 power pins.

---

## License

This project is licensed under the [MIT License](LICENSE).
