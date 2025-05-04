import serial
import time
import pyautogui
import tkinter as tk
from tkinter import messagebox
from tkinter import PhotoImage

ser = None

def check_device_status():
    global ser
    try:
        ser = serial.Serial(' YOUR_COM_PORT ', 9600, timeout=1)
        time.sleep(2)  # Wait for the serial connection to initialize
        animate_text(status_label, "Device Status: Active/Connected")
        status_image.config(image=connected_image)
    except serial.SerialException as e:
        animate_text(status_label, "Device Status: Inactive/Disconnected")
        status_image.config(image=disconnected_image)
        messagebox.showerror("Error", f"Error with serial port: {e}")
    except Exception as e:
        animate_text(status_label, "Device Status: Inactive")
        status_image.config(image=disconnected_image)
        messagebox.showerror("Error", f"Unexpected error: {e}")

def scroll_up():
    pyautogui.scroll(275)
    animate_text(action_label, "Action: Scroll Up")

def scroll_down():
    pyautogui.scroll(-300)
    animate_text(action_label, "Action: Scroll Down")

def monitor_serial():
    global ser
    if ser and ser.is_open:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if line == "Scroll Up":
                scroll_up()
            elif line == "Scroll Down":
                scroll_down()
    root.after(100, monitor_serial)

def animate_text(label, new_text):
    def blink():
        current_color = label.cget("fg")
        next_color = "black" if current_color == "blue" else "blue"
        label.config(fg=next_color)
        label.after(500, blink)

    label.config(text=new_text)
    blink()

root = tk.Tk()
root.title("Device Monitor")
root.configure(bg="black")

# Set default font for the entire application
default_font = ("ADLaM Display", 12)
root.option_add("*Font", default_font)

# Set the window icon
root.iconbitmap(r"C:\Users\owenh\Downloads\designer_7yT_icon.ico")

# Set the window background color to black
root.configure(bg="black")

status_label = tk.Label(root, text="Device Status: Checking...", fg="blue", bg="black")
status_label.pack()

action_label = tk.Label(root, text="Action: None", fg="blue", bg="black")
action_label.pack()

# Load images
connected_image = PhotoImage(file=r"YOUR IMAGE PATH FOR DISCONNECT PNG")
disconnected_image = PhotoImage(file=r"YOUR IMAGE PATH FOR CONNECTED PNG")

# Create a label to display the image
status_image = tk.Label(root, bg="black")
status_image.pack()

check_device_status()
monitor_serial()

root.mainloop()

if ser and ser.is_open:
    ser.close()