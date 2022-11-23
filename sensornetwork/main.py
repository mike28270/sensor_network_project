import cv2
import serial
import mediapipe as mp
import mysql.connector

class connectMysql:
    def __init__(self, host, port, username, password, database):
        self.conn = mysql.connector.connect(
            host=host, port=port,
            user=username, password=password,
            database=database
            )
        self.mycursor = self.conn.cursor()

    def insertLED(self, id, value):
        query = f"INSERT INTO LED (did, date, time, value) VALUES ('{id}', CURRENT_DATE(), CURRENT_TIME(), {value})"
        self.mycursor.execute(query)
        self.conn.commit()
        return query

class gestureDetection:
    def __init__(
        self, 
        cam=0,
        tipIds=[4,8,12,16,20], 
        min_det_score=0.5,
        min_track_score=0.5
        ):
        self.tipIds = tipIds
        self.mp_draw = mp.solutions.drawing_utils
        self.mp_hand = mp.solutions.hands
        self.cap = cv2.VideoCapture(cam)
        self.min_det_score = min_det_score
        self.min_track_score = min_track_score
        self.hands = self.mp_hand.Hands(min_detection_confidence=min_det_score,min_tracking_confidence=min_track_score) 
        #self.ser = connectSerial
        self.ser = serial.Serial('/dev/cu.usbmodem141401', 9600)
        print(self.ser)

    def drawLabel(self, image, value, unit):
        cv2.rectangle(image, (20, 300), (270, 425), (0, 255, 0), cv2.FILLED)
        cv2.putText(image, value, (45, 375), cv2.FONT_HERSHEY_SIMPLEX,
            2, (255, 0, 0), 5)
        cv2.putText(image, unit, (100, 375), cv2.FONT_HERSHEY_SIMPLEX,
            2, (255, 0, 0), 5)

    def releaseCamera(self):
        self.cap.release()

    def detOneHandKeypoints(self, image):
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        # image.flags.writeable=False  # Maybe don't need this
        results = self.hands.process(image) # A NamedTuple object with the following fields
        # image.flags.writeable=True  # Maybe don't need this
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)  # Maybe don't need this
        lmList = []
        if results.multi_hand_landmarks:
            for hand_landmark in results.multi_hand_landmarks:
                myHands = results.multi_hand_landmarks[0]
                for id, lm in enumerate(myHands.landmark):
                    h, w, c = image.shape
                    cx, cy = int(lm.x*w), int(lm.y*h)
                    lmList.append([id,cx,cy])
                self.mp_draw.draw_landmarks(image, hand_landmark, self.mp_hand.HAND_CONNECTIONS)
        return image, lmList

    def detFinger(self, keypoints):
        fingers = []
        if len(keypoints)!=0:
            # Check x for thumb and little finger
            if keypoints[self.tipIds[0]][1] > keypoints[self.tipIds[0]-1][1]:  
                fingers.append(1)
            else:
                fingers.append(0)
            # Check y for every finger whether the tip is lower than 2nd point or not.
            for id in range(1,5):
                if keypoints[self.tipIds[id]][2] < keypoints[self.tipIds[id]-2][2]:  
                    fingers.append(1)
                else:
                    fingers.append(0)
            # finger_cnt = fingers.count(1)
            # print(finger_cnt)
        return fingers.count(1)

    def process(self):
        ret, image = self.cap.read()
        # frame captures without errors...
        if ret:
            image, keypoints = self.detOneHandKeypoints(image)
            finger_cnt = self.detFinger(keypoints)
        return image, finger_cnt

def main():
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
        port = '/dev/cu.usbmodem141401', 
        baudrate = 9600
        )

    detection = gestureDetection(
        min_det_score=0.7,
        min_track_score=0.5
        )

    while True:
        image, finger_cnt = detection.process()
        image = cv2.resize(image, (0, 0), fx = 0.80, fy = 0.80)

        # Draw label on the image
        detection.drawLabel(image, f"{finger_cnt}", "LED")

        # Send color code to LED
        conn_serial.write(f'{LED_COLOR[finger_cnt]}\n'.encode())

        # Receive RGB LED color code
        data_read = conn_serial.readline()

        # Insert Table to the DB
        if data_read.decode() != '\n':
            r, g, b = data_read.decode().split(" ")
            conn_mysql.insertLED(1, r)
            conn_mysql.insertLED(2, b)
            conn_mysql.insertLED(3, g)

        # Show image
        cv2.imshow("Frame", image)

        # Press 'q' to stop the program.
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    detection.releaseCamera()

if __name__ == "__main__":
    main()
