# TurtleScreen Interface for BoxTurtle AFC

This project uses a Lilygo T3 OLED long screen to display real-time information from the BoxTurtle AFC system and to interact with it via a touchscreen interface. Designed for easy setup and portability, this project provides a dedicated Access Point (AP) for configuring network details and connecting to your printer endpoint.

## Features
- **Real-time Display**: Shows essential BoxTurtle AFC data on the OLED screen.
- **Interactive Control**: Touchscreen interface powered by LVGL for smooth user interactions.
- **Configurable via Wi-Fi**: Access Point (AP) mode for easy setup and configuration.
- **Over-the-Air (OTA) Updates**: Easily update firmware via a web interface.

## Getting Started

### Hardware Requirements
- Lilygo T3 OLED Long Screen - https://www.lilygo.cc/products/t-display-s3-long
- 3D-printed adapter (STL files included in the repository for printing)

### Software Requirements
- PlatformIO (recommended for compiling and flashing the firmware)
- LVGL (UI library for embedded systems)

### Setup Instructions

1. **Flash the Firmware**: Clone this repository, then use PlatformIO to flash the firmware to your Lilygo T3 OLED screen.

2. **Connect to the Setup Access Point**:
   - After flashing, the device will start in AP mode.
   - Connect to the Wi-Fi network **"DeviceSetupAP"**.
   - Password: **setup1234**

3. **Configure the Printer Endpoint**:
   - Once connected to the AP, open a browser and follow the instructions to set up the printer endpoint. This endpoint allows the device to retrieve BoxTurtle AFC data.

4. **Updating the Firmware**:
   - To perform Over-the-Air (OTA) firmware updates, navigate to:
     ```
     http://<printer_ip_address>/update
     ```
   - Replace `<printer_ip_address>` with the actual IP address of your printer.
   - Upload the new firmware file here for seamless updates.

### License
This project is licensed under the GNU General Public License (GPL), enabling you to freely use, modify, and distribute the code.

### Additional Resources
- **STL Files**: Adapter STL files for 3D printing are available in the `STL` directory.
- **GitHub Repository**: Find the latest code, issues, and documentation at [TurtleScreen GitHub](https://github.com/sbtoonz/TurtleScreen/tree/main).
