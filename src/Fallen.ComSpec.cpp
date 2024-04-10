#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "headers/color.hpp"
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
        system("whoami > .uid");
        ifstream file;
        string Content;
        file.open(".uid");
        while (getline(file,Content)){
            if (Content == "root")
            {
                cout << dye::light_red("# ");
                break;
            } else {
                cout << dye::light_green("$ ");
                break;
            }
        }
        getline(cin,Command);
        Console.DumpHistory(Command,console_tabs::ActiveTab.HistoryFile);
        Console.Eval(Command);
    };
    };
int main(int argc,char* argv[]){
    Start();
    return 0;
};