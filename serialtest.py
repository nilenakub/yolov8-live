import serial
import time
import struct

# Setting Serial Communications
SerialObj = serial.Serial('COM4', timeout=1)  # Set Comms, include timeout
SerialObj.baudrate = 9600  # set Baud rate to 9600

time.sleep(2)  # Wait for 2 seconds to establish the connection

float_value = 2.02
packed_data = struct.pack('f', float_value)  # Pack the float into bytes

SerialObj.write(packed_data)  # Send the packed bytes

print(f"Sent: {float_value}")

SerialObj.close()  # Close the serial port