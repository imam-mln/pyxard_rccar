# Import Library yang dibutuhkan
from cvzone.HandTrackingModule import HandDetector
import cv2
import serial

# Menangkap gambar frame per second
cap = cv2.VideoCapture(0)

# Deteksi tangan
detector = HandDetector(detectionCon=0.5, maxHands=1)

# Koneksi bluetooth
ser = serial.Serial("COM6", 9600, timeout=1)

while True:
   # Membaca gambar yang ditangkap
   success, img = cap.read()
   
   # Mendeteksi tangan dari gambar
   hands, img = detector.findHands(img)
   hands = detector.findHands(img, draw=False)
   
   if hands:
      # Mengambil ndarray index 0
      hand = hands[0]
      # Membaca dan mengambil data ndarray hand
      handType = hand["type"]
      lmList = hand["lmList"]

      if lmList:
            # Membaca jari dari gambar tangan
            fingers = detector.fingersUp(hand)

            if fingers == [1,1,1,1,1] and handType == "Right": # Maju (Forward)
               ser.write(b'F')
               print(">>> MAJU <<<")   
            elif fingers == [0,1,1,1,1] and handType == "Right": # Mundur (Backward)
               ser.write(b'B')
               print(">>> MUNDUR <<<")
            elif fingers == [1,0,0,0,0] and handType == "Right": # Belok Kiri (Left)
               ser.write(b'L')
               print(">>> BELOK KIRI <<<")
            elif fingers == [0,0,0,0,1] and handType == "Right": # Belok Kanan (Right)
               ser.write(b'R')
               print(">>> BELOK KANAN <<<")
            elif fingers == [0,0,0,0,0] and handType == "Right": # Berhenti (Stop)
               ser.write(b'S')
               print(">>> BERHENTI <<<")

   # Menampilkan teks pada frame
   img = cv2.putText(img, 'Use Your Right Hand!', (10,30), cv2.FONT_HERSHEY_SIMPLEX, 
                  0.8, (255, 0, 0), 2, cv2.LINE_AA)
   
   # Menampilkan gambar
   cv2.imshow("Hand Gesture", img)
   if cv2.waitKey(1) & 0xFF == ord('q'):
      break
   
ser.close()
cap.release()
cv2.destroyAllWindows()