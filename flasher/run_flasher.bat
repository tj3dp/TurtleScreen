REM Windows Batch Script: install_and_run_flasher.bat
@echo off

REM Install Python packages needed for the ESP flasher
pip install esptool pyserial

REM Run the flasher Python script
python flasher.py

pause