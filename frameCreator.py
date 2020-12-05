import ctypes
import time
import cv2
import os
import sys
from tqdm import tqdm
import tkinter as tk
from tkinter import filedialog

def create_frames(video, frames, pathVid):
    if video.isOpened() == False:
        print("Error opening video.")
        input()
        return False

    total_frames = int(video.get(cv2.CAP_PROP_FRAME_COUNT))
    fps = video.get(cv2.CAP_PROP_FPS)

    if frames == None or frames == "":
        frames = total_frames
    elif frames > total_frames:
        print("The amount of frames needs to be less than the total amount in the video.")
        input()
        return False

    success, image = video.read()
    for i in tqdm(range(frames)):
        cv2.imwrite(f"frames/{pathVid}/frame{i+1}.jpg", image)
        success, image = video.read()
        sys.stdout.flush()

    print("")

def create_folder(pathVid):
    if not os.path.exists(f"{os.getcwd()}/frames/{pathVid}"):
        os.makedirs(f"{os.getcwd()}/frames/{pathVid}")

def main():
    root = tk.Tk()
    root.withdraw()
    path = filedialog.askopenfilename()
    fileName = os.path.basename(path).replace(".mp4", "")
    print(f"Processing: {fileName}")
    video = cv2.VideoCapture(path)

    while True:
        try:
            frames = ""
            if frames != "":
                frames = int(frames)
            break
        except:
            print("That isn't a valid number!")

    create_folder(fileName)

    create_frames(video, frames, fileName)

if __name__ == "__main__":
    main()

