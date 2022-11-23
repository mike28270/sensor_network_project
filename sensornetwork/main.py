import cv2
import serial
import matplotlib.colors as mcolors # https://matplotlib.org/stable/gallery/color/named_colors.html
from detection import gestureDetection
from sn_mysql import connectMysql


def main():
    finger_cnt_temp = 0
    LED_COLOR = {
        0: "0 0 0",
        1: "255 0 0",
        2: "0 255 0",
        3: "0 0 255",
        4: "255 255 255",
        5: "125 125 125"
    }

    conn_mysql = connectMysql(
        host = "34.91.33.123",
        port = "3306",
        username = "admin",
        password = "admin",
        database = "sensornetwork"
        )

    conn_serial = serial.Serial(
        port = '/dev/cu.usbmodem142401', 
        baudrate = 9600
        )

    detection = gestureDetection(
        min_det_score=0.7,
        min_track_score=0.5
        )

    while True:
        image, finger_cnt = detection.process()
        image = cv2.resize(image, (0, 0), fx = 0.80, fy = 0.80)

        # Send color code to LED
        conn_serial.write(f'{LED_COLOR[finger_cnt]}\n'.encode())

        # Receive RGB LED color code
        data_read = conn_serial.readline()

        # Insert RGB color code to a table in the DB
        if data_read.decode() != '\n':
            r, g, b = data_read.decode().split(" ")
            conn_mysql.insertLED(1, r)
            conn_mysql.insertLED(2, b)
            conn_mysql.insertLED(3, g)
        
        if finger_cnt !=  finger_cnt_temp:
            conn_mysql.insertFinger(finger_cnt)
            
        finger_cnt_temp = finger_cnt

        # Show image
        cv2.imshow("Frame", image)

        # Press 'q' to stop the program.
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    detection.releaseCamera()

if __name__ == "__main__":
    main()
