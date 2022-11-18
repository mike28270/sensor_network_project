import cv2
from PIL import Image

#cap_api = cv2.CAP_FFMPEG
cap_api = cv2.CAP_GSTREAMER
#dev = "/dev/video0"
dev = 0
cap = cv2.VideoCapture(dev, cap_api)
print(cap.isOpened())

#while(True):
# while cap.isOpened():
#     ret, frame = cap.read()
#     cv2.imshow('frame', frame)
#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break

ret, frame = cap.read()
cv2.imshow('frame', frame)

cap.release()
cv2.destroyAllWindows()