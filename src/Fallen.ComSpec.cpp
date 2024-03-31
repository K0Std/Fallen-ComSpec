#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <color.hpp>
#include "Fallen_COMSPEC.hpp"
using namespace std;
void Start(){
    auto Console = conhost::Shell();
    conhost::Install_DIR = filesystem::current_path().string();
    string Command = "";
    while (true){
        cout << dye::purple("FallenCOMSPEC: ");
        cout << dye::light_aqua(filesystem::current_path().string() + "\n");
        cout << dye::green("$ ");
        getline(cin,Command);
        if (Command == ""){
            continue;
        }
        if (strstr(Command.c_str(),"\t") && !(strstr(Command.c_str(),"\\"))){
            Command.erase(Command.find("\t"),Command.find("\t"));
            Console.AutoComplete(conhost::ConvertToUppercase(Command));
            continue;
        }
        if (strstr(Command.c_str(),"\t") && strstr(Command.c_str(),"\\")){
            Console.PathAutoComplete();
            continue;
        }else if (strstr(conhost::ConvertToUppercase(Command.c_str()).c_str(),"CD ")){
            string New_Path = Command;
            New_Path.erase(0,3);
            filesystem::current_path(New_Path);
            continue;
        }else if (strstr(Command.c_str(),"/?")){
            vector<string> Args;
            conhost::Split(Command,Args,' ');
            string CMD_Name = Args[0];
            Console.Generate_CMD_HELP(CMD_Name);
            continue;
        }else if (strstr(conhost::ConvertToUppercase(Command.c_str()).c_str(),"NETUTILS")){
            vector<string> NetUtilsARGV;
            conhost::Split(Command,NetUtilsARGV,' ');
            Console.NetUtils(NetUtilsARGV);
            continue;
        }else if (strstr(conhost::ConvertToUppercase(Command.c_str()).c_str(),"CHDIR ")){
            string New_Path = Command;
            New_Path.erase(0,6);
            filesystem::current_path(New_Path);
            continue;
        }else if (Command == "exit"){
            break;
        }else{
            Console.Eval(Command);
            continue;
        }
    };
    };
int main(int argc,char* argv[]){
    system("title FALLEN COMSPEC");
    Start();
    return 0;
};
