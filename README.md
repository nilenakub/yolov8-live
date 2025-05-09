Using TACO Dataset (http://tacodataset.org/) to train an object detecting model with bounding boxes & labels (best.pt)

in the example (test.py) , we use camera to detect Clear Plastic Bottle & Plastic Bottle cap, calculate the bounding boxes Height/Width in pixels, turn pixels into real world measurement (mm), send data to Arduino via pySerial

in Arduino (MotorisedThingSerial.ino) We take the float data, convert into distances, and order the stepper motor to rotate forward and back, while simulating the blade with LED


