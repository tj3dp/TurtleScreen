import tkinter as tk
from tkinter import filedialog, messagebox, ttk
import subprocess
import serial.tools.list_ports
import threading

def open_file(variable):
    """Open a dialog to select a file and update the given variable."""
    file_path = filedialog.askopenfilename(
        filetypes=[("BIN Files", "*.bin")], title="Select a file"
    )
    if file_path:
        variable.set(file_path)

def refresh_ports():
    """Refresh the list of available COM ports."""
    ports = serial.tools.list_ports.comports()
    com_ports = [port.device for port in ports]
    com_port_dropdown["menu"].delete(0, "end")
    for port in com_ports:
        com_port_dropdown["menu"].add_command(
            label=port, command=tk._setit(selected_port, port)
        )
    if com_ports:
        selected_port.set(com_ports[0])  # Set the first available port by default
    else:
        selected_port.set("No ports available")

def start_flash():
    """Start the flashing process in a separate thread."""
    threading.Thread(target=flash_file, daemon=True).start()

def flash_file():
    """Flash the ESP32 using esptool.py."""
    bootloader_path = bootloader_file.get()
    firmware_path = firmware_file.get()
    partitions_path = partitions_file.get()
    com_port = selected_port.get()
    chip_type_selected = chip_type.get()

    if not bootloader_path:
        messagebox.showerror("Error", "Please select the bootloader file!")
        return
    if not firmware_path:
        messagebox.showerror("Error", "Please select the firmware file!")
        return
    if not partitions_path:
        messagebox.showerror("Error", "Please select the partitions file!")
        return
    if not com_port or com_port == "No ports available":
        messagebox.showerror("Error", "Please select a valid COM port!")
        return

    # Disable buttons and show progress bar
    flash_button.config(state="disabled")
    exit_button.config(state="disabled")
    progress_bar.grid(row=7, column=0, columnspan=3, pady=10)
    progress_bar.start(10)  # Start the progress animation
    output_text.delete("1.0", tk.END)  # Clear previous output

    try:
        # Construct the esptool.py flashing command using findings from PlatformIO
        command = (
            f"esptool.py --chip {chip_type_selected} --port {com_port} --baud 921600 "
            f"--before default_reset --after hard_reset "
            f"write_flash -z --flash_mode dio --flash_freq 80m --flash_size 16MB "
            f"0x00000000 {bootloader_path} "
            f"0x00008000 {partitions_path} "
            f"0x00010000 {firmware_path}"
        )
        process = subprocess.run(command, shell=True, capture_output=True, text=True)

        # Show verbose output
        output_text.insert(tk.END, process.stdout + "\n" + process.stderr)

        if process.returncode == 0:
            messagebox.showinfo("Success", "File flashed successfully!")
        else:
            messagebox.showerror("Error", f"Failed to flash file. See output for details.")
    except Exception as e:
        messagebox.showerror("Error", f"An unexpected error occurred:\n{e}")
    finally:
        # Re-enable buttons and hide progress bar
        flash_button.config(state="normal")
        exit_button.config(state="normal")
        progress_bar.stop()
        progress_bar.grid_remove()

def quit_app():
    """Exit the application."""
    root.destroy()

# Create the main window
root = tk.Tk()
root.title("ESP32-S3 Flasher")

# Variables to store file paths
bootloader_file = tk.StringVar()
firmware_file = tk.StringVar()
partitions_file = tk.StringVar()
selected_port = tk.StringVar()
chip_type = tk.StringVar(value="esp32s3")  # Default chip type

# Bootloader selection
tk.Label(root, text="Bootloader:").grid(row=0, column=0, padx=10, pady=5, sticky="w")
tk.Entry(root, textvariable=bootloader_file, width=40, state="readonly").grid(row=0, column=1, padx=10, pady=5)
tk.Button(root, text="Select", command=lambda: open_file(bootloader_file)).grid(row=0, column=2, padx=10, pady=5)

# Firmware selection
tk.Label(root, text="Firmware:").grid(row=1, column=0, padx=10, pady=5, sticky="w")
tk.Entry(root, textvariable=firmware_file, width=40, state="readonly").grid(row=1, column=1, padx=10, pady=5)
tk.Button(root, text="Select", command=lambda: open_file(firmware_file)).grid(row=1, column=2, padx=10, pady=5)

# Partitions selection
tk.Label(root, text="Partitions:").grid(row=2, column=0, padx=10, pady=5, sticky="w")
tk.Entry(root, textvariable=partitions_file, width=40, state="readonly").grid(row=2, column=1, padx=10, pady=5)
tk.Button(root, text="Select", command=lambda: open_file(partitions_file)).grid(row=2, column=2, padx=10, pady=5)

# Chip type selection
tk.Label(root, text="Chip Type:").grid(row=3, column=0, padx=10, pady=5, sticky="w")
chip_dropdown = tk.OptionMenu(root, chip_type, "esp32", "esp32s3", "esp8266")
chip_dropdown.grid(row=3, column=1, padx=10, pady=5, sticky="w")

# COM port selection
tk.Label(root, text="COM Port:").grid(row=4, column=0, padx=10, pady=5, sticky="w")
com_port_dropdown = tk.OptionMenu(root, selected_port, "No ports available")
com_port_dropdown.grid(row=4, column=1, padx=10, pady=5, sticky="w")
tk.Button(root, text="Refresh Ports", command=refresh_ports).grid(row=4, column=2, padx=10, pady=5)

# Action buttons
flash_button = tk.Button(root, text="Flash File", command=start_flash)
flash_button.grid(row=6, column=1, pady=20)
exit_button = tk.Button(root, text="Exit", command=quit_app)
exit_button.grid(row=6, column=2, pady=20)

# Progress bar
progress_bar = ttk.Progressbar(root, mode="indeterminate")
progress_bar.grid(row=7, column=0, columnspan=3, pady=10)
progress_bar.grid_remove()  # Hide it initially

# Output Text Box for Verbose Output
output_text = tk.Text(root, height=10, width=80, state="normal")
output_text.grid(row=8, column=0, columnspan=3, padx=10, pady=10)

# Refresh the COM ports on startup
refresh_ports()

# Run the main event loop
root.mainloop()