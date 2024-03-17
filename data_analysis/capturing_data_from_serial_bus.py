import serial
import time
import threading

ser = serial.Serial('COM12', 115200)

end = False
def logging():
    global ser, end
    try:
        with open('./sources/bang_bang_control_motor.csv', 'w') as file:
            while not end:
                file.write(ser.readline().decode('utf-8'))
    finally:
        ser.close()
def sending_data():
    global ser, end
    for i in range(0, 400, 50):
        print(f"Sent {i}")
        ser.write(f"{i}".encode('utf-8'))
        time.sleep(5)
    end = True

logging_thread = threading.Thread(target=logging)
data_sending_thread = threading.Thread(target=sending_data)

logging_thread.start()
data_sending_thread.start()

logging_thread.join()
data_sending_thread.join()