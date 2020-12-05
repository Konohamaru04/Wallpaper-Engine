#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

int fps;
std::string loaded;

void filesCheker();
bool is_file_exist_frame();
bool is_file_exist_loop();
bool is_file_exist_settings();
void menu();
void selectvideo();
void mainProcess();
void frameCreatorFile();
void loophandlerFile();
void settingsFile();
void cleanup();
int filesChekerManual();
void settings();
void applySettings();
int fetchSettings();
void setFPS();
void logo();
void license(); 
void clearData();
void readLines();
void frameManager();
void selectVideoMenu();
void processingMenu();
void loadFromExisting();
string post(int lineNO);
string fetchLoaded();
void eraseSubStr(std::string & mainStr, const std::string & toErase);

void frameManager() {
    if(system("framemanager"))
    {
        cout<<""<<endl;
    }
}

int main()
{
    std::cout<<"Loading...";
    applySettings();
    //loophandlerFile();
    //frameCreatorFile();
    menu();
    return 0;
}

void menu()
{
    int menuHandler;
    int filchk = 0;
    while (1)
    {
        filesCheker();
        system("CLS");
        logo();
        cout<<"\t\t\t\t\t\tFPS: "<<fps<<endl;
        cout<<"Active: "<<loaded<<endl<<endl;
        cout<<"\t[1] Select Video"<<endl;
        cout<<"\t[2] Process"<<endl;
        cout<<"\t[3] Check Files"<<endl;
        cout<<"\t[4] Settings"<<endl;
        cout<<"\t[5] License\n"<<endl;
        cout<<"\t[6] Exit\n"<<endl;

        if(fps<22)
        {
            cout<<"\tWarning !!! FPS is set to less than 22."<<endl;
        }
        else if(fps>45)
        {
            cout<<"\tWarning !!! FPS is set to greater than 45."<<endl;
        }
        else
        {
            cout<<"";
        }
        
        cout<<">>>> ";
        cin>>menuHandler;

        switch (menuHandler)
        {
        case 1: selectVideoMenu();
                break;
        case 2: processingMenu();
                break;
        case 3: filesChekerManual();
                break;
        case 4: settings();
        case 5: license();
        case 6: cout<< "Closing app ... "<<endl;
                //cleanup();
                exit(0);
                break;
        default: cout<<"Invalid Input !"<<endl;
            break;
        }
    }
}

void selectvideo()
{
    if(system("frameCreator"))
    {
        cout<<""<<endl;
    }
}

void mainProcess()
{
    //string FPS = std::to_string(fps);

    std::stringstream ss;
    ss<<fps;
    std::string FPS = ss.str();
    
    string loophandler = "loophandler " + FPS + " \"" + loaded + "\"";

    if(system(loophandler.c_str()))
    {
        cout<<""<<endl;
    }
}

void filesCheker()
{
    bool frame = true;
    bool loop = true;
    bool set;
    char anyInput;
//loop =  is_file_exist_loop();
//frame = is_file_exist_frame();
set = is_file_exist_settings();
logo();
if(loop&&frame&&set)
{
    cout<<""<<endl;
}
else if(loop&&!frame&&set)
{
    cout<< "Frame generator not found !"<<endl;
    cout<< "Do you want to create missing file ? (y/n) : ";
    cin>>anyInput;
    switch (anyInput)
    {
    case 'y' : frameCreatorFile();
                    break;
    case 'n' : filesCheker();
                    break;
    default : cout<<"Invalid Input !"<<endl;
                
    }
}
else if(!loop&&frame&&set)
{
    cout<<"Frame Processor not found !"<<endl;
    cout<< "Do you want to create missing file ? (y/n) : ";
    cin>>anyInput;
    switch (anyInput)
    {
    case 'y' : loophandlerFile();
                    break;
    case 'n' : filesCheker();
                    break;
    default : cout<<"Invalid Input !"<<endl;
                
    }
}
else if(loop&&frame&&!set)
{
    cout<<"User settings not found !"<<endl;
    cout<< "Do you want to create missing file ? (y/n) : ";
    cin>>anyInput;
    switch (anyInput)
    {
    case 'y' : settingsFile();
                    break;
    case 'n' : filesCheker();
                    break;
    default : cout<<"Invalid Input !"<<endl;
                
    }
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

bool is_file_exist_settings()
{
    std:ifstream infile("Settings.dat");
    return infile.good();
}

void frameCreatorFile()
{
    ofstream frameCreator;
    frameCreator.open("frameCreator.py");
    frameCreator<<"import ctypes"<<endl;
    frameCreator<<"import time"<<endl;
    frameCreator<<"import cv2"<<endl;
    frameCreator<<"import os"<<endl;
    frameCreator<<"import sys"<<endl;
    frameCreator<<"from tqdm import tqdm"<<endl;
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
    frameCreator<<"    for i in tqdm(range(frames)):"<<endl;
    frameCreator<<"        cv2.imwrite(f\"frames/frame{i+1}.jpg\", image)"<<endl;
    frameCreator<<"        success, image = video.read()"<<endl;
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
    frameCreator<<"    create_frames(video, frames)"<<endl;
    frameCreator<<""<<endl;
    frameCreator<<"if __name__ == \"__main__\":"<<endl;
    frameCreator<<"    main()"<<endl;
    frameCreator<<""<<endl;
    frameCreator.close();

    cout<<"Frame Generator created Successfully !"<<endl;
}

void loophandlerFile()
{
    ofstream loophandler;
    loophandler.open("loophandler.py");
    loophandler<<"import os"<<endl;
    loophandler<<"import ctypes"<<endl;
    loophandler<<"import time"<<endl;
    loophandler<<"import msvcrt"<<endl;
    loophandler<<""<<endl;
    loophandler<<"def play(fps="<<fps<<"):"<<endl;
    loophandler<<"    print(\"Processing @"<<fps<<" FPS [ Press 'ESC' to stop ]\")"<<endl;
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
    loophandler<<"        if msvcrt.kbhit():"<<endl;
    loophandler<<"            if ord(msvcrt.getch()) == 27:"<<endl;
    loophandler<<"                break"<<endl;
    loophandler<<""<<endl;
    loophandler<<"if __name__ == \"__main__\":"<<endl;
    loophandler<<"    play()"<<endl;
    loophandler<<""<<endl;
    loophandler.close();

    cout<<"Frame Processor created Successfully !"<<endl;
}

void settingsFile()
{
    cout<<"Set default FPS (between 22 - 45) : ";
    cin>>fps;
    ofstream settingsFile;
    settingsFile.open("Settings.dat");
    settingsFile<<fps;
    settingsFile.close();

    settingsFile.open("loader.dat");
    settingsFile<<fps;
    settingsFile.close();

    settingsFile.open("frames_data.we");
    settingsFile<<fps;
    settingsFile.close();
}

void cleanup()
{
    if(system("del /f loophandler.py"))
    {
        cout << "";
    }

    if(system("del /f frameCreator.py"))
    {
        cout << "";
    }
}

int filesChekerManual()
{   
    int temp;
    int var=0;
    cout<<"Frame Generator : ";
    if(is_file_exist_frame())
        cout<<"File exists"<<endl;
    else
        {
            cout<<"File doesnot exists"<<endl;
            var++;
        }

    cout<<"Frame Processor : ";
    if(is_file_exist_loop())
        cout<<"File exists"<<endl;
    else
        {
            cout<<"File doesnot exists"<<endl;
            var++;
        }
    cout<<"User Settings : ";
    if(is_file_exist_settings())
        cout<<"File exists"<<endl;
    else
        {
            cout<<"File doesnot exists"<<endl;
            var++;
        }

    if(var>3)
        filesCheker();
    cout<<"press 1 to continue : ";
    cin>>temp;
    return 0;  
}

void settings()
{   
    int switchVar;
    while (1)
    {   
        system("CLS");
        logo();
        cout<<"\t\t\t\t\t\tFPS : "<<fps<<endl;
        cout<<"\nProgram Settings :"<<endl<<endl;
        cout<<"\t\t[1] Set Frames Per Second\n";
        cout<<"\t\t[2] Clear Data\n";
        cout<<"\t\t[3] Main Menu\n";
        cout<<"\t\t    >>>> ";
        cin>>switchVar;

        switch (switchVar)
        {
        case 1 :setFPS();
                break;
        case 2 :clearData();
        case 3 :menu();
                break;
        default: cout<<"Invalid Imput!"<<endl;
        }
    }
}

void selectVideoMenu() 
{
    int switchVar;
    while (1)
    {
        system("CLS");
        logo();
        cout<<"\t\t\t\t\t\tFPS : "<<fps<<endl;
        cout<<"\nLoad video :"<<endl<<endl;
        cout<<"\t\t[1] Select new video\n";
        cout<<"\t\t[2] Select from existing data\n";
        cout<<"\t\t[3] Cancel\n";
        cout<<"\t\t    >>>> ";
        cin>>switchVar;

        switch (switchVar)
        {
        case 1 : selectvideo();
                 frameManager();
                 break;
        case 2 : loadFromExisting();
        case 3 :menu();
                break;
        default: cout<<"Invalid Imput!"<<endl;
        }

    }
    
    logo();
}

void setFPS()
{   
    cout<<"Set FPS :\n"<<endl;
    cout<<"Enter number of FPS ( between 22-45 to reduce CPU load) : ";
    cin>>fps;
    ofstream settings;
    settings.open("Settings.dat");
    settings<<fps;
    settings.close();
    applySettings();
    cout<<"FPS set to : "<<fps;
    Sleep(3000);
}


int fetchSettings()
{
    int temp;
    ifstream settings;
    settings.open("Settings.dat");
    settings>>temp;
    settings.close();
    return temp;
}

std::string fetchLoaded() {
    std::ifstream loaderFile("loader.dat");
    std::string line;

    for(int i = 1; i<= 1; i++) {
        std::getline(loaderFile, line);
    }
    return line;
}

void applySettings()
{
    fps = fetchSettings();
    loaded = fetchLoaded();
    frameManager();
}

void clearData()
{
    if(system("RD /S /Q frames"))
    {
        cout<<""<<endl;
        Sleep(3000);
    }
    else
    {
        cout << "Old Frames deleted !";
        Sleep(3000);
    }
    
}

void license()
{
    int tempk;
    system("CLS");
    system("more LICENSE");
    cout<<endl<<"Press 1 for Main menu"<<endl;
    cout<<">>>>> ";
    cin>>tempk;
    if (tempk==1)
    {
        main();
    }
}

string post(int lineNO) 
{
    std::ifstream file("frames_data.we");
    std::string line;
 
    for(int i = 1; i <= lineNO; i++) {
        std::getline(file, line);
    }
    //std::cout<<line;
    return line;
}

void setLoaded(std::string load)
{
    std::ofstream setloaded;
    setloaded.open("loader.dat");
    setloaded<<load;
    setloaded.close();
    applySettings();
}

void readLines() 
{
    std::ifstream file("frames_data.we");
    std::string str;
    int i = 1;
    while (std::getline(file, str)) {
    eraseSubStr(str, "frames/");
    std::cout <<i<<": "<< str << "\n";
    i++;
    }
}

void eraseSubStr(std::string & mainStr, const std::string & toErase)
{
    size_t pos = mainStr.find(toErase);
    if (pos != std::string::npos)
    {
        mainStr.erase(pos, toErase.length());
    }
}

void loadFromExisting() 
{
    system("CLS");
    logo();
    cout<<"\t\t\t\t\t\tFPS: "<<fps<<endl;
    cout<<"Active: "<<loaded<<endl<<endl;
    int lineNo = 1;
    readLines();
    std::cout<<"Enter index of video: ";
    std::cin>>lineNo;
    std::string loadedS = post(lineNo);
    setLoaded(loadedS);
}

void processingMenu()
{
    system("CLS");
    logo();
    cout<<"\t\t\t\t\t\tFPS: "<<fps<<endl;
    cout<<"Active: "<<loaded<<endl<<endl;
    mainProcess();
}

void logo()
{   
    system("CLS");
    cout<<"\t||DDDDD               ||  $$$$$$         CCCCC  "<<endl;
    cout<<"\t||     D  eeeee       ||  $       eeeee  C      "<<endl;
    cout<<"\t||     D  e   e   dddd||  $$$$$$  e   e  C      "<<endl;
    cout<<"\t||     D  eeee    ||  ||       $  eeee   C      "<<endl;
    cout<<"\t||DDDDD   eeeee   dddd||  $$$$$$  eeeee  CCCCC  "<<endl;
    cout<<"\t                     Instagram : amartya.deshmukh  "<<endl;
    cout<<"\t                     GitHub    : Konohamaru04   "<<endl;
    cout<<"\n                  Cheap Wallpaper Engine            "<<endl<<endl;
}
