# 🐭 MicroMouse Project

A comprehensive micromouse robot implementation featuring ESP32-based hardware control, maze-solving algorithms, and multi-communication protocols for autonomous maze navigation.

## 📋 Project Overview

This project implements a complete micromouse solution capable of autonomously navigating and solving mazes. The system combines embedded hardware control with sophisticated pathfinding algorithms to create an intelligent robotic mouse that can learn and optimize its route through unknown mazes.

## 🏗️ System Architecture

### Hardware Components
- **Main Controller**: ESP32 microcontroller
- **Secondary Controller**: Arduino Nano for sensor processing
- **Sensors**: 4x IR distance sensors for wall detection
- **Motors**: Dual DC motors with encoders for precise movement
- **Communication**: I2C bus between controllers, Bluetooth for debugging

### Software Components
- **Embedded Control**: C++ firmware for ESP32 and Arduino Nano
- **Maze Algorithms**: Python-based pathfinding and optimization algorithms
- **Simulation Environment**: MMS (Micromouse Simulator) for algorithm testing
- **Communication**: Multi-protocol support (I2C, Bluetooth, Serial)

## 📁 Project Structure

```
micromouse-main/
├── Algorithm/                          # Maze-solving algorithms
│   ├── maze_runner.py                 # Main maze navigation algorithm
│   └── Micro Master/                  # Advanced algorithm implementation
│       ├── API.py                     # Maze simulator API interface
│       ├── location.py                # Location and cell management
│       ├── main.py                    # Main algorithm controller
│       └── state.py                   # State management
├── mms_simulation_algorithm/          # MMS Simulation implementation
│   ├── asd2copylothelp.cpp           # C++ algorithm for MMS simulator
│   └── asd2copylothelp.exe           # Compiled executable
├── Mouse 1/                           # Primary mouse implementation
│   ├── esp.cpp                        # ESP32 main controller code
│   └── nano.cpp                       # Arduino Nano sensor code
├── I2C_encoder/                       # I2C encoder communication
│   ├── ESP32_master.cpp              # ESP32 as I2C master
│   └── Slave_Nano.cpp                # Nano as I2C slave
├── I2C_Infra/                        # I2C infrared sensor handling
│   ├── ESP32.cpp                     # ESP32 IR sensor controller
│   └── Nano.cpp                      # Nano IR sensor interface
├── I2C Send Read/                    # I2C communication protocols
│   ├── esp.cpp                       # ESP32 I2C implementation
│   ├── nano.cpp                      # Nano I2C implementation
│   └── working blue infra i2c/       # Working Bluetooth + IR + I2C code
├── Bluetooth/                        # Bluetooth communication
│   └── code.cpp                      # Bluetooth implementation
├── wire try codes/                   # I2C communication experiments
│   ├── wire 1/, wire 2/, wire 3/     # Different I2C implementations
│   └── not working/                  # Debug/test code
└── esp32.cpp                         # Main ESP32 implementation
```

## 🤖 Key Features

### 1. Autonomous Maze Navigation
- **Wall Detection**: 4 IR sensors for real-time wall detection
- **Position Tracking**: Encoder-based odometry for precise positioning
- **Maze Mapping**: Dynamic maze discovery and mapping
- **Path Optimization**: Multiple algorithms for finding optimal routes

### 2. Advanced Algorithms
- **Flood Fill Algorithm**: Classic micromouse pathfinding
- **Wall Following**: Backup navigation strategy
- **Dead-end Detection**: Smart backtracking capabilities
- **Route Optimization**: Multiple-run optimization for speed competitions

### 3. Multi-Controller Architecture
- **ESP32 Master**: Main processing, motor control, decision making
- **Arduino Nano Slave**: Dedicated sensor processing and I2C communication
- **Distributed Processing**: Optimized workload distribution

### 4. Communication Systems
- **I2C Protocol**: Fast inter-controller communication
- **Bluetooth**: Wireless debugging and monitoring
- **Serial Communication**: Development and debugging interface

### 5. Motor Control System
- **PWM Control**: Precise speed regulation
- **PID Control**: Smooth acceleration and positioning
- **Encoder Feedback**: Closed-loop position control
- **Differential Drive**: Independent wheel control for turning

## 🚀 Getting Started

### Prerequisites
- **Hardware**: ESP32, Arduino Nano, IR sensors, motors with encoders
- **Software**: Arduino IDE, Python 3.x
- **Libraries**: Wire.h, BluetoothSerial.h, QuickPID.h, TimerEvent.h

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/HalaszAkos/MicroMouse.git
   cd MicroMouse
   ```

2. **Hardware Setup**:
   - Connect ESP32 as I2C master (pins 3, 1)
   - Connect Arduino Nano as I2C slave
   - Wire 4 IR sensors to Nano analog pins
   - Connect motors to ESP32 PWM pins
   - Connect encoders to ESP32 interrupt pins

3. **Upload Firmware**:
   - Upload `Mouse 1/esp.cpp` to ESP32
   - Upload `Mouse 1/nano.cpp` to Arduino Nano

4. **Algorithm Testing**:
   ```bash
   cd Algorithm
   python maze_runner.py
   ```

5. **MMS Simulation Testing**:
   ```bash
   cd mms_simulation_algorithm
   ./asd2copylothelp.exe
   ```

### Pin Configuration

#### ESP32 Connections:
- **Motors**: GPIO 2, 4, 12, 15 (direction control)
- **PWM**: Channels 0-3 (speed control)
- **Encoders**: GPIO 13, 14 (interrupt pins)
- **I2C**: GPIO 3 (SDA), GPIO 1 (SCL)

#### Arduino Nano Connections:
- **IR Sensors**: A0-A3 (analog inputs)
- **I2C**: A4 (SDA), A5 (SCL)

## 🧪 Algorithm Details

### Maze-Solving Strategy
1. **Exploration Phase**: Map unknown maze using wall-following
2. **Flood Fill**: Calculate distances to goal from every cell
3. **Path Planning**: Find optimal route using distance matrix
4. **Speed Runs**: Execute optimized path at maximum speed

### Key Classes and Functions
- `Cell`: Represents maze cell with walls and visit status
- `matrix()`: Calculates Manhattan distance to goal
- `flood_fill()`: Implements flood fill pathfinding
- `dead_end`: Handles dead-end detection and backtracking

## 🖥️ MMS Simulation Environment

### What is MMS?
**MMS (Micromouse Simulator)** is a powerful simulation environment that makes it easy to write and test maze-solving code without a physical robot.

### Key Features:
- **Virtual Testing**: Test how your robot would behave in a real maze
- **Algorithm Visualization**: Visualize what your robot is thinking
- **Wall Mapping**: Show known/unknown walls in real-time
- **Cell Customization**: Set colors and display ASCII text on cells
- **Crash Simulation**: Simulate crash-and-reset scenarios
- **Custom Mazes**: Test algorithms on custom maze files
- **Language Agnostic**: Write code in any programming language

### Getting Started with MMS:
1. **Download MMS**: https://github.com/mackorone/mms
2. **Compile Algorithm**: Use the provided C++ implementation
3. **Run Simulation**: Execute the algorithm in the MMS environment
4. **Analyze Results**: Visualize pathfinding and optimization

### Included Implementation:
- **C++ Algorithm**: `mms_simulation_algorithm/asd2copylothelp.cpp`
- **Executable**: Pre-compiled version for immediate testing
- **Compatible**: Works with standard MMS simulator interface

For more information about Micromouse competitions, see the [Micromouse Wikipedia page](https://en.wikipedia.org/wiki/Micromouse).

## 🔧 Configuration Options

### Motor Parameters
```cpp
#define PWM_START 93    // Starting PWM value
#define PWM_FREQ 500    // PWM frequency
#define PWM_RES 8       // PWM resolution
```

### Algorithm Parameters
```python
MAZE_WIDTH = 16         # Standard micromouse maze size
MAZE_HEIGHT = 16        # Standard micromouse maze size
```

## 📊 Performance Features

- **Real-time Processing**: Sub-millisecond sensor reading and processing
- **Adaptive Speed**: Dynamic speed adjustment based on maze complexity
- **Memory Efficient**: Optimized data structures for embedded systems
- **Robust Navigation**: Multiple fallback strategies for reliable operation

## 🐛 Debugging and Monitoring

### Bluetooth Interface
- Real-time sensor data streaming
- Motor status monitoring
- Algorithm state visualization
- Remote parameter adjustment

### Serial Output
- Detailed logging of navigation decisions
- Sensor calibration data
- Performance metrics

## 🏁 Competition Features

- **Multiple Run Support**: Learn maze, then optimize for speed
- **Configurable Goal**: Support for different target areas
- **Time Optimization**: Minimize total solve time
- **Reliability**: Robust error handling and recovery

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Classic micromouse algorithms and strategies
- ESP32 and Arduino communities
- Micromouse competition standards and rules

## 📞 Contact

**Halász Ákos** - [GitHub Profile](https://github.com/HalaszAkos)

Project Link: [https://github.com/HalaszAkos/MicroMouse](https://github.com/HalaszAkos/MicroMouse)

---

*Built with ❤️ for autonomous robotics and maze-solving competitions*

## Suggestions for a good README

Every project is different, so consider which of these sections apply to yours. The sections used in the template are suggestions for most open source projects. Also keep in mind that while a README can be too long and detailed, too long is better than too short. If you think your README is too long, consider utilizing another form of documentation rather than cutting out information.

## Name
Choose a self-explaining name for your project.

## Description
Let people know what your project can do specifically. Provide context and add a link to any reference visitors might be unfamiliar with. A list of Features or a Background subsection can also be added here. If there are alternatives to your project, this is a good place to list differentiating factors.

## Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

## Visuals
Depending on what you are making, it can be a good idea to include screenshots or even a video (you'll frequently see GIFs rather than actual videos). Tools like ttygif can help, but check out Asciinema for a more sophisticated method.

## Installation
Within a particular ecosystem, there may be a common way of installing things, such as using Yarn, NuGet, or Homebrew. However, consider the possibility that whoever is reading your README is a novice and would like more guidance. Listing specific steps helps remove ambiguity and gets people to using your project as quickly as possible. If it only runs in a specific context like a particular programming language version or operating system or has dependencies that have to be installed manually, also add a Requirements subsection.

## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.

## Support
Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc.

## Roadmap
If you have ideas for releases in the future, it is a good idea to list them in the README.

## Contributing
State if you are open to contributions and what your requirements are for accepting them.

For people who want to make changes to your project, it's helpful to have some documentation on how to get started. Perhaps there is a script that they should run or some environment variables that they need to set. Make these steps explicit. These instructions could also be useful to your future self.

You can also document commands to lint the code or run tests. These steps help to ensure high code quality and reduce the likelihood that the changes inadvertently break something. Having instructions for running tests is especially helpful if it requires external setup, such as starting a Selenium server for testing in a browser.

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## License
For open source projects, say how it is licensed.

## Project status
If you have run out of energy or time for your project, put a note at the top of the README saying that development has slowed down or stopped completely. Someone may choose to fork your project or volunteer to step in as a maintainer or owner, allowing your project to keep going. You can also make an explicit request for maintainers.
