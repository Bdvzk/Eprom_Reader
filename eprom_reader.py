import serial
import time

# --- CONFIGURATION ---

PORT = ''
BAUD = 115200
FILE_NAME = "eprom.bin"
EPROM_SIZE = 32768

def read_eprom():
    try:
        # Initializing connection via Native Port
        ser = serial.Serial(PORT, BAUD, timeout=5)
        ser.dtr = True 
        time.sleep(1) 
        ser.reset_input_buffer()
        ser.write(b'R')
        ser.flush()
        
        print("Waiting for data...")
        raw_data = ser.read(EPROM_SIZE)
        
        print(f"Received: {len(raw_data)} bytes")
        
        if len(raw_data) > 0:
            with open(FILE_NAME, "wb") as f:
                f.write(raw_data)
            print(f"Done: {FILE_NAME}")
        else:
            print("Error: No data received")
            
        ser.close()
    except Exception as e:
        print(f"Critical Error: {e}")

if __name__ == "__main__":
    read_eprom()