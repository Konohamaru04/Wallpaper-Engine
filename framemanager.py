from glob import glob
import os

files = glob(os.path.join("frames/", "*", ""))

os.remove("frames_data.we")

file1 = open("frames_data.we","a")

for n in files:
    n = n.replace('\\', '/', 1)
    n = n.replace('\\', '')
    file1.write(f"{n}\n")
    #print(n)

file1.close()