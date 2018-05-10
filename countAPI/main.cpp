#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>
#include <cstring>
#include <algorithm>
using namespace std;




int printrecord(std::map <std::string, std::map<std::string, std::map<std::string,int>>> projects){

    for(auto project : projects)
    {
       std::cout << "--" << project.first << "\n";
       for (auto subproject: project.second){
            std::cout << "----" << subproject.first << "\n";
            for (auto method : subproject.second){
                std::cout << "------" << method.first << " " << method.second << endl;;
            }
       }

    }
}


std::map <std::string, std::map<std::string, std::map<std::string,int>>> record(std::vector<std::string> calls){
    // make a map that keep track of all the projects

    std::map <std::string, std::map<std::string, std::map<std::string,int>>> projects;

    for (int i = 0; i < calls.size(); i++){

        // convert string to char*
        std::vector<char> v(calls[i].length() + 1);
        std::strcpy(&v[0], calls[i].c_str());
        char* directory = &v[0];

        char* project_name = strtok(directory, "/");
        char* subproject_name = strtok(NULL, "/");
        char* method_name = strtok(NULL, "/");

        if ( projects.find(project_name) == projects.end()){
            // not in the projects, add it in
            std::map <std::string,  std::map <std::string, int>> subprojects;  // inside the project, add subproject
            std::map <std::string, int> methods;  // inside the subproject add methods

            methods.insert(std::make_pair(method_name, 1));
            subprojects.insert(std::make_pair(subproject_name,methods));
            projects.insert(std::make_pair(project_name,subprojects));
        }else{
            // already in projects, update subdirectory

            // check if the subdirectory exist in the project folder
            if (projects[project_name].find(subproject_name) == projects[project_name].end()){
                // if the subdirectory not exist in the project folder
                // add it in
                std::map <std::string, int> methods;   // inside the subproject add methods
                methods.insert(std::make_pair(method_name, 1));
                projects[project_name].insert(std::make_pair(subproject_name,methods));

            }else{
                // if the subdirectory already exist in the project folder
                // check if the method already in subdirectory
                if (projects[project_name][subproject_name].find(method_name) == projects[project_name][subproject_name].end()){
                    // method not in subdirectory

                    projects[project_name][subproject_name].insert(std::make_pair(method_name, 1));
                }else{
                    // method already in subdirectory
                    // update
                    projects[project_name][subproject_name][method_name]++;
                }

            }
        }
    }
    return projects;
}

std::vector<std::string> countAPI(std::vector<std::string> calls) {

    std::map <std::string, std::map<std::string, std::map<std::string,int>>> projects = record(calls);
    printrecord(projects);
    std::vector<std::string> result;
    //std::map <std::string, int> countfolder;
/*
    for(auto project : projects){
        int methods_in_project = 0;

        for (auto subproject: project.second){
            int methods_in_sub = 0;

            for (auto method = subproject.second.begin(); method != subproject.second.end(); ++method){
                methods_in_sub++;
            }
            countfolder.insert(std::make_pair(subproject.first,methods_in_sub));
            methods_in_project += methods_in_sub;
        }
        countfolder.insert(std::make_pair(project.first,methods_in_project));
    }
*/



    return result;
 }


int main()
{

    std::vector<std::string> calls;
    calls.push_back ("/project1/subproject1/method1");
    calls.push_back ("/project2/subproject1/method1");
    calls.push_back ("/project1/subproject1/method1");
    calls.push_back ("/project1/subproject2/method1");
    calls.push_back ("/project1/subproject1/method2");
    calls.push_back ("/project1/subproject2/method1");
    calls.push_back ("/project2/subproject1/method1");
    calls.push_back ("/project1/subproject2/method1");



    countAPI(calls);
    return 0;
}
/***

Expected Output:

["--project1 (6)",
 "----subproject1 (3)",
 "------method1 (2)",
 "------method2 (1)",
 "----subproject2 (3)",
 "------method1 (3)",
 "--project2 (2)",
 "----subproject1 (2)",
 "------method1 (2)"]
 ***/
