import os
import ctypes
import time
import msvcrt
import sys

def play():
    fps=int(sys.argv[1])
    path= sys.argv[2]
    print(f'Processing: "{os.path.basename(path)}" @{fps} [ Press "ESC" to stop ]')
    total_frames = len(os.listdir(f"{os.getcwd()}/{path}"))
    current_frame = 1

    while True:
        if current_frame != total_frames:
            ctypes.windll.user32.SystemParametersInfoW(20, 0, f"{os.getcwd()}/{path}/frame{current_frame}.jpg", 0)
            time.sleep(1/fps)
            current_frame += 1
        else:
            current_frame = 0
        if msvcrt.kbhit():
            if ord(msvcrt.getch()) == 27:
                break

if __name__ == "__main__":
    play()

