#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

int createFiles();
int filesCheker();
bool is_file_exist_frame();
bool is_file_exist_loop();
void menu();
void selectvideo();
void mainProcess();

int main()
{
    int createFile = createFiles();
    menu();
    return 0;
}

void menu()
{
    int menuHandler;
    while (1)
    {
        cout<<"\t\tCheap Wallpaper Engine\n"<<endl;
        cout<<"\t1] Select Video"<<endl;
        cout<<"\t2] Process\n"<<endl;
        cout<<"\t3] Exit\n"<<endl;
        
        cout<<">>>> ";
        cin>>menuHandler;

        switch (menuHandler)
        {
        case 1: selectvideo();
                break;
        case 2: mainProcess();
                break;
        case 3: cout<< "Closing app ... "<<endl;
                exit(0);
                break;
        default: cout<<"Invalid Parameter !"<<endl;
            break;
        }
    }
}

int createFiles()
{
    ofstream frameCreator;
    frameCreator.open("frameCreator.py");
    frameCreator<<"import ctypes"<<endl;
    frameCreator<<"import time"<<endl;
    frameCreator<<"import cv2"<<endl;
    frameCreator<<"import os"<<endl;
    frameCreator<<"import sys"<<endl;
    frameCreator<<"def create_frames(video, frames):"<<endl;
    frameCreator<<"    if video.isOpened() == False:"<<endl;
    frameCreator<<"        print(\"Error opening video.\")"<<endl;
    frameCreator<<"        input()"<<endl;
    frameCreator<<"        return False"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"    total_frames = int(video.get(cv2.CAP_PROP_FRAME_COUNT))"<<endl;
    frameCreator<<"    fps = video.get(cv2.CAP_PROP_FPS)"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"    if frames == None or frames == \"\":"<<endl;
    frameCreator<<"        frames = total_frames"<<endl;
    frameCreator<<"    elif frames > total_frames:"<<endl;
    frameCreator<<"        print(\"The amount of frames needs to be less than the total amount in the video.\")"<<endl;
    frameCreator<<"        input()"<<endl;
    frameCreator<<"        return False"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"    success, image = video.read()"<<endl;
    frameCreator<<"    for i in range(frames):"<<endl;
    frameCreator<<"        cv2.imwrite(f\"frames/frame{i+1}.jpg\", image)"<<endl;
    frameCreator<<"        success, image = video.read()"<<endl;
    frameCreator<<"        sys.stdout.write(f\"\\r{int((i+1)/frames*100)}% complete\")"<<endl;
    frameCreator<<"        sys.stdout.flush()"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"    print(\"\")"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"def create_folder():"<<endl;
    frameCreator<<"    if not os.path.exists(f\"{os.getcwd()}/frames\"):"<<endl;
    frameCreator<<"        os.makedirs(f\"{os.getcwd()}/frames\")"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"def main():"<<endl;
    frameCreator<<"    path = input(\"Enter the path of the video: \")"<<endl;
    frameCreator<<"    video = cv2.VideoCapture(path)"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"    while True:"<<endl;
    frameCreator<<"        try:"<<endl;
    frameCreator<<"            frames = input(\"Enter the number of frames you want shown (leave blank if you want the entire video): \")"<<endl;
    frameCreator<<"            if frames != \"\":"<<endl;
    frameCreator<<"                frames = int(frames)"<<endl;
    frameCreator<<"            break"<<endl;
    frameCreator<<"        except:"<<endl;
    frameCreator<<"            print(\"That isn't a valid number!\")"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"    create_folder()"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"    os.system(\"cls\")"<<endl;
    frameCreator<<"    create_frames(video, frames)"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"if __name__ == \"__main__\":"<<endl;
    frameCreator<<"    main()"<<endl;
    frameCreator<<""<<endl;
    frameCreator.close();

    ofstream loophandler;
    loophandler.open("loophandler.py");
    loophandler<<"import os"<<endl;
    loophandler<<"import ctypes"<<endl;
    loophandler<<"import time"<<endl;
    loophandler<<""<<endl;
    loophandler<<"def play(fps=30):"<<endl;
    loophandler<<"    print(\"Playing! (press Ctrl + C to stop)\")"<<endl;
    loophandler<<"    total_frames = len(os.listdir(f\"{os.getcwd()}/frames\"))"<<endl;
    loophandler<<"    current_frame = 1"<<endl;
    loophandler<<""<<endl;
    loophandler<<"    while True:"<<endl;
    loophandler<<"        if current_frame != total_frames:"<<endl;
    loophandler<<"            ctypes.windll.user32.SystemParametersInfoW(20, 0, f\"{os.getcwd()}/frames/frame{current_frame}.jpg\", 0)"<<endl;
    loophandler<<"            time.sleep(1/fps)"<<endl;
    loophandler<<"            current_frame += 1"<<endl;
    loophandler<<"        else:"<<endl;
    loophandler<<"            current_frame = 0"<<endl;
    loophandler<<""<<endl;
    loophandler<<"if __name__ == \"__main__\":"<<endl;
    loophandler<<"    play()"<<endl;
    loophandler<<""<<endl;
    loophandler.close();

    int files = filesCheker();

    if(files == 11)
    {
        return 0;
    }
    else if(files == 10)
    {
        return 1;
    }
    else if(files == 01)
    {
        return 2;
    }

}

void selectvideo()
{
    if(system("python frameCreator.py"))
    {
        cout<<"success"<<endl;
    }
    //system("python frameCreator.py");
}

void mainProcess()
{
    if(system("python loophandler.py"))
    {
        cout<<"success"<<endl;
    }
   // system("python loophandler.py");
}

int filesCheker()
{
    bool frame;
    bool loop;
loop =  is_file_exist_loop();
frame = is_file_exist_frame();

if(loop&&frame)
{
    return 11;
}
else if(loop&&!frame)
{
    return 10;
}
else if(!loop&&frame)
{
    return 01;
}

}
bool is_file_exist_loop()
{
    std::ifstream infile("loophandler.py");
    return infile.good();
}

bool is_file_exist_frame()
{
    std::ifstream infile("frameCreator.py");
    return infile.good();
}