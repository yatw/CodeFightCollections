#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>
#include <cstring>
#include <algorithm>
using namespace std;



int printrecord(std::map <std::string, std::map<std::string, std::vector<std::string>>> projects){

    for(auto elem : projects)
    {
       std::cout << "--" << elem.first << "\n";
       for (auto subp: elem.second){
            std::cout << "----" << subp.first << "\n";
            for (auto i = subp.second.begin(); i != subp.second.end(); ++i){
                std::cout << "------" << *i << endl;;
            }
       }

    }
}


std::map <std::string, std::map<std::string, std::vector<std::string>>> record(std::vector<std::string> calls){
    // make a map that keep track of all the projects

    std::map <std::string, std::map<std::string, std::vector<std::string>>> projects;

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
            std::map <std::string, std::vector<std::string>> subprojects;  // inside the project, add subproject
            std::vector <std::string> methods;  // inside the subproject add methods

            methods.push_back(method_name);
            subprojects.insert(std::make_pair(subproject_name,methods));
            projects.insert(std::make_pair(project_name,subprojects));
        }else{
            // already in projects, update subdirectory

            // check if the subdirectory exist in the project folder
            if (projects[project_name].find(subproject_name) == projects[project_name].end()){
                // if the subdirectory not exist in the project folder
                // add it in
                std::vector <std::string> methods;  // inside the subproject add methods
                methods.push_back(method_name);
                projects[project_name].insert(std::make_pair(subproject_name,methods));

            }else{
                // if the subdirectory already exist in the project folder
                // add in the new method
                projects[project_name][subproject_name].push_back(method_name);
            }
        }
    }
    return projects;
}

int countAPI(std::vector<std::string> calls) {

    std::map <std::string, std::map<std::string, std::vector<std::string>>> projects = record(calls);
    printrecord(projects);

    return 0;
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
