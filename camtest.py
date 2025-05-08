from ultralytics import YOLO
import cv2
import torch

print(torch.cuda.is_available())
print(torch.cuda.device_count())
print(torch.cuda.get_device_name(0))

# Load Yolo Model
model = YOLO("best.pt")  # Load a custom model (best.pt) trained on the custom dataset
print(model.names)
model.to('cuda')  # Move the model to GPU

