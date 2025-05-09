from ultralytics import YOLO
import cv2
import torch
import serial
import time



# Setting Serial Communications
SerialObj = serial.Serial('COM5', timeout=1)  # Set Comms, include timeout
SerialObj.baudrate = 9600  # set Baud rate to 9600
time.sleep(2)  # Wait for 2 seconds to establish the connection

# print(torch.cuda.is_available())
# print(torch.cuda.device_count())
# print(torch.cuda.get_device_name(0))

# Load Yolo Model
try:
    model = YOLO("best.pt")  # Load a custom model (best.pt) trained on the custom dataset
    model.to('cuda')  # Move the model to GPU
    model.names

# Take Image from Webcam
    cap = cv2.VideoCapture(1)  # Open the webcam (0 for default camera, 1 for external camera)
    # and predict the image
    cap.set(3, 640)  # Set the width of the frame
    cap.set(4, 480)  # Set the height of the frame

    ret, frame = cap.read()
    
    results = model.predict(frame, show=True, classes=[5, 7], conf=0.2, iou=0.2)

# Calculate Width & Height of Bounding Boxes 
    for result in results:
        boxes = result.boxes
        class_names = model.names  # Get the class names from the model
        class_ids = boxes.cls  # Get the class IDs of the detected objects
        for box in boxes:
            x, y, w, h = box.xywh[0]
            print(f"Bounding Box: x={x}, y={y}, w={w}, h={h}, class={class_names[int(box.cls[0])]}")
            x, y, w, h = int(x), int(y), int(w), int(h)
            # Convert w, h to real-world units  
            if class_names[int(box.cls[0])] == "Plastic bottle cap":  # Check if the detected object is a Bottle cap
                pixel_to_real_height_ratio = 0.55  # Example ratio, adjust based on your calibration
                real_height = h * pixel_to_real_height_ratio
                print(f"Real Height: {real_height} mm, Class: {class_names[int(box.cls[0])]}.")
                float_value = real_height
                packed_data = "{:.2f}\n".format(float_value)
                SerialObj.write(packed_data.encode('utf-8'))
                print(f"Sent: {packed_data}")
                SerialObj.flush()
                time.sleep(0.1)
                
    # # Press 'esc' to exit the webcam feed
    cap.release()  # Release the webcam
    if cv2.waitKey(0) & 0xFF == 27:  # 27 is the ASCII code for the 'esc' key
        cv2.destroyAllWindows()  # Close all OpenCV windows
    # break #remove this line
    # cv2.destroyAllWindows() #remove this line

except Exception as e:
    print(f"An error occurred: {e}")