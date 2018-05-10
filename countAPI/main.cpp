#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>
#include <cstring>
#include <algorithm>
using namespace std;

struct folder
{
    map<string, folder> subfolders;
    map<string, int> methods;
    int methods_count;
};

std::map<string, folder> projects; //datastructure to store the folders



int record(std::vector<std::string> calls){
    // make a map that keep track of all the projects

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

            folder subproject;
            subproject.methods.insert(make_pair(method_name, 1 ));
            subproject.methods_count = 1;

            folder project;
            project.methods_count = 1;
            project.subfolders.insert(make_pair(subproject_name, subproject));

            projects.insert(make_pair(project_name,project));
        }else{

            // if project already in projects
            // check subproject exist
            if (projects[project_name].subfolders.find(subproject_name) == projects[project_name].subfolders.end()){
                // subproject not in project folder
                // add subproject and methods
                folder subproject;
                subproject.methods_count = 1;
                subproject.methods.insert(make_pair(method_name, 1 ));

                projects[project_name].methods_count++;
                projects[project_name].subfolders.insert(make_pair(subproject_name, subproject ));

            }else{
                // subproject exists in project folder
                // check if that methods in the subproject folder

                if (projects[project_name].subfolders[subproject_name].methods.find(method_name) == projects[project_name].subfolders[subproject_name].methods.end()){
                    // method doesn't exist
                    projects[project_name].subfolders[subproject_name].methods.insert(make_pair(method_name, 1));

                }else{

                    projects[project_name].subfolders[subproject_name].methods[method_name]++;
                }
                projects[project_name].subfolders[subproject_name].methods_count++;
                projects[project_name].methods_count++;

            }


        }
    }
    return 0;
}

std::vector<std::string> countAPI(std::vector<std::string> calls) {

    record(calls);
    std::vector<std::string> result;

    for(auto project : projects)
    {
       std::cout << "--" << project.first << " (" << project.second.methods_count <<  ")" << endl;

       for (auto subproject: project.second.subfolders){
            std::cout << "----" << subproject.first << " ("  << subproject.second.methods_count <<  ")" <<  endl;
            for (auto method : subproject.second.methods){
                std::cout << "------" << method.first << "  (" << method.second  << ")" << endl;;
            }
       }


    }




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
