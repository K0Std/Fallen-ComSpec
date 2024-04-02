#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <color.hpp>
#include "headers/Fallen_COMSPEC.hpp"
using namespace std;
void Start(){
    auto Console = conhost::Shell();
    auto DefaultTab = console_tabs::tab("Default",0,"Default.history");
    console_tabs::ActiveTab = DefaultTab;
    conhost::Install_DIR = filesystem::current_path().string();
    string Command = "";
    while (true){
        cout << dye::purple("FallenCOMSPEC: ");
        cout << dye::light_aqua(filesystem::current_path().string() + "\n");
        cout << dye::green("$ ");
        getline(cin,Command);
        Console.DumpHistory(Command,console_tabs::ActiveTab.HistoryFile);
        Console.Eval(Command);
    };
    };
int main(int argc,char* argv[]){
    system("title FALLEN COMSPEC");
    Start();
    return 0;
};
