# Unix Shell Script: install_and_run_flasher.sh
#!/bin/bash

# Install Python packages needed for the ESP flasher
pip install esptool pyserial

# Run the flasher Python script
python3 flasher.py