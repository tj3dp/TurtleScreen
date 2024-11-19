REM Windows Batch Script: install_and_run_flasher.bat
@echo off

REM Set the Python path to resolve in AppData for any user
set PYTHON_PATH=%LOCALAPPDATA%\Programs\Python\Python310\python.exe

REM Uninstall incorrect serial package if installed
%PYTHON_PATH% -m pip uninstall -y serial

REM Install Python packages needed for the ESP flasher
%PYTHON_PATH% -m pip install esptool pyserial

REM Ensure Tkinter is installed
%PYTHON_PATH% -m pip install tk || (
    echo Tkinter is not installed. Please run the Python installer again and ensure that the tcl/tk option is selected.
    pause
    exit /b
)

REM Verify that pyserial is installed
%PYTHON_PATH% -m pip show pyserial || (
    echo Pyserial is not installed. Please check your Python environment.
    pause
    exit /b
)

REM Run the flasher Python script
%PYTHON_PATH% flasher.py

pause