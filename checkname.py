from ultralytics import YOLO
import cv2
import torch
import serial
import time

model = YOLO("best.pt")  # Load a custom model (best.pt) trained on the custom dataset
model.to('cuda')  # Move the model to GPU
model.names

print(model.names)