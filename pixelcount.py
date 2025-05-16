import cv2
import matplotlib.pyplot as plt

try:
    # Take Image from Webcam
    cap = cv2.VideoCapture(0)  # Open the webcam (0 for default camera, 1 for external camera)
    if not cap.isOpened():
        raise IOError("Cannot open webcam")

    ret, frame = cap.read()
    if not ret:
        raise IOError("Cannot read frame")

    cap.release()  # Release the webcam

    # Convert the frame from BGR to RGB (Matplotlib uses RGB)
    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # Display the image using Matplotlib
    plt.imshow(frame_rgb)
    plt.title("Webcam Feed")
    plt.xlabel("Pixel Column")
    plt.ylabel("Pixel Row")
    plt.show()

except IOError as e:
    print(f"IOError: {e}")
except Exception as e:
    print(f"An error occurred: {e}")