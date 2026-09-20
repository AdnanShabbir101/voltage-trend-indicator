# Voltage Trend Indicator

An Arduino-based real-time voltage monitoring algorithm that analyzes the rate of change of an analog input signal and provides intuitive visual feedback using LEDs. The project samples an input voltage, compares it with the previous reading, and determines whether the signal is increasing, decreasing, or remaining stable. At the same time, a third LED dynamically adjusts its brightness according to the instantaneous input voltage using PWM.

# 🎥Project Demonstration

[Watch the project in action] (https://youtu.be/MkwFP2X_znk)

---

## Features

- Real-time voltage trend detection using custom differential sampling.
- Blue LED indicates increasing voltage.
- Red LED indicates decreasing voltage.
- Automatic stable-state detection when neither LED glows for negligible voltage changes.
- White LED brightness scales proportionally with input voltage.
- Non-blocking timing using `millis()` instead of `delay()`.
- Configurable sampling interval and voltage-change threshold.
- Entirely implemented in native Arduino C/C++.
- No external libraries required.

## 🛠️ How It Works

The Arduino continuously reads an analog voltage through pin `A0` and converts the 10-bit ADC value (`0–1023`) into a corresponding voltage (`0–5V`).

Every `200 ms`, the program:

1. Reads the current input voltage.
2. Calculates the voltage difference (`ΔV`) between the current and previous sample.
3. Compares the voltage change against a predefined threshold (`±0.05V`).
4. Determines the direction of change:
   - **Blue LED ON** → Voltage increasing
   - **Red LED ON** → Voltage decreasing
   - **Both OFF** → Voltage approximately constant
5. Updates the brightness of the White LED using PWM based on the current analog input value.
6. Outputs diagnostic data via Serial Monitor for debugging and analysis.

This approach allows the system to simultaneously display both the **magnitude** and **trend** of an analog signal.

## Pin Configuration

| Component | Arduino Pin |
|------------|------------|
| Analog Input | A0 |
| Red LED | 8 |
| White LED (PWM) | 6 |
| Blue LED | 12 |

## Use Cases

### Human-Machine Interface (HMI)
Provides a lightweight visual interface where users can instantly identify whether an analog signal is rising, falling, or remaining stable without interpreting numerical data.

### Sensor Trend Monitoring
Monitor sensors whose outputs change over time, such as:
- Temperature sensors
- Light-dependent resistors (LDRs)
- Pressure sensors
- Gas sensors

The LEDs provide immediate visual feedback on whether the measured quantity is increasing or decreasing.

### Educational Demonstrations
Useful for Understanding:
- Analog-to-Digital Conversion (ADC)
- Pulse Width Modulation (PWM)
- Signal sampling
- Rate-of-change analysis

### Real-Time Process Monitoring
Can serve as a simple indicator system for:
- Battery charging/discharging behavior
- Voltage stability testing
- System diagnostics
- Control-system prototyping

### Sensor Characterization
Helps visualize how quickly a sensor responds to environmental changes by observing trend indications in real time.

---

## Code-Specific Attributes

### 0. Differential Sampling Logic
Instead of relying on absolute voltage values, the algorithm compares consecutive samples:

```cpp
change = current_volts - prev_volts;
```

This allows the system to detect signal trends rather than just signal magnitude.

### 1. Threshold-Based Noise Rejection

```cpp
if(change > 0.05)
```

A threshold of `±0.05V` prevents minor ADC fluctuations and electrical noise from triggering false trend indications.

### 2. Non-Blocking Timing

```cpp
if(curr_time - prev_time >= interval)
```

Using `millis()` enables periodic sampling without halting the execution of the program, making the design suitable for real-time embedded applications.

### 3. Custom Trend Detection

The entire trend-analysis algorithm is implemented manually without external libraries, providing a clear and transparent implementation of rate-of-change detection.

### 4. PWM-Based Analog Visualization

```cpp
analogWrite(greenPin, (255.0/1023.0) * readVal);
```

The White LED acts as a visual analog meter whose brightness directly reflects the current input voltage.

### 5. Resource-Efficient Design

- Constant memory usage
- No dynamic allocation
- Minimal computational overhead
- Suitable for low-resource microcontrollers

### 6. Adjustable Parameters

The following values can be tuned depending on the application:

```cpp
const long interval = 200;
```

- Sampling interval

```cpp
if(change > 0.05)
```

- Trend sensitivity threshold

**These parameters allow the system to be optimized for both slow-changing and rapidly varying signals.**

## 🧑‍💻Technical Highlights

- Pure Arduino C/C++ implementation.
- Custom rate-of-change detection algorithm.
- Simultaneous trend indication and signal-level visualization.
- Noise-tolerant threshold logic.
- Real-time, non-blocking architecture.
- Serial debugging support.
- No third-party dependencies.

## 💯Repository Goals

This project demonstrates how fundamental signal-processing concepts can be implemented on an Arduino using only built-in functionality. By combining ADC sampling, time-based measurements, differential analysis, threshold filtering, and PWM control, the system provides a compact example of real-time embedded data processing without relying on external libraries.

---

**A lightweight embedded system that visualizes both the direction and magnitude of voltage changes using custom rate-of-change analysis, LED trend indicators, and PWM-based signal representation.**
