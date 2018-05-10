#include <iostream> // cout
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <cstring>
#include <sstream>

using namespace std;

struct folder
{
    map<string, folder> subfolders;
    vector<string> subfolders_order;
    map<string, int> methods;
    vector<string> methods_order;
    int methods_count;
};

map<string, folder> projects; //datastructure to store the folders
vector<string> projects_order;



int record(vector<string> calls){
    // make a map that keep track of all the projects

    for (int i = 0; i < calls.size(); i++){

        // convert string to char*
        vector<char> v(calls[i].length() + 1);
        strcpy(&v[0], calls[i].c_str());
        char* directory = &v[0];

        char* project_name = strtok(directory, "/");
        char* subproject_name = strtok(NULL, "/");
        char* method_name = strtok(NULL, "/");


        if ( projects.find(project_name) == projects.end()){
            // not in the projects, add it in

            folder subproject;
            subproject.methods.insert(make_pair(method_name, 1 ));
            subproject.methods_count = 1;
            subproject.methods_order.push_back(method_name);

            folder project;
            project.methods_count = 1;
            project.subfolders.insert(make_pair(subproject_name, subproject));
            project.subfolders_order.push_back(subproject_name);

            projects.insert(make_pair(project_name,project));
            projects_order.push_back(project_name);
        }else{

            // if project already in projects
            // check subproject exist
            if (projects[project_name].subfolders.find(subproject_name) == projects[project_name].subfolders.end()){
                // subproject not in project folder
                // add subproject and methods
                folder subproject;
                subproject.methods_count = 1;
                subproject.methods.insert(make_pair(method_name, 1 ));
                subproject.subfolders_order.push_back(method_name);
                subproject.methods_order.push_back(method_name);

                projects[project_name].methods_count++;
                projects[project_name].subfolders.insert(make_pair(subproject_name, subproject ));
                projects[project_name].subfolders_order.push_back(subproject_name);

            }else{
                // subproject exists in project folder
                // check if that methods in the subproject folder

                if (projects[project_name].subfolders[subproject_name].methods.find(method_name) == projects[project_name].subfolders[subproject_name].methods.end()){
                    // method doesn't exist
                    projects[project_name].subfolders[subproject_name].methods.insert(make_pair(method_name, 1));
                    projects[project_name].subfolders[subproject_name].methods_order.push_back(method_name);

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

vector<string> countAPI(vector<string> calls) {

    record(calls);
    vector<string> result;

    string temp;
    for (auto project: projects_order){
        ostringstream c;
        c << projects[project].methods_count;
        temp = "--" + project + " (" + c.str() + ")";
        result.push_back(temp);
        cout << temp << endl;


       for (auto subproject: projects[project].subfolders_order){

            ostringstream c1;
            c1 << projects[project].subfolders[subproject].methods_count;
            temp = "----" + subproject +  " (" +  c1.str() + ")";
            result.push_back(temp);
            cout << temp <<  endl;

                for (auto method : projects[project].subfolders[subproject].methods_order){

                    ostringstream c2;
                    c2 << projects[project].subfolders[subproject].methods[method];
                    temp = "------" + method +  " (" + c2.str() +  ")";
                    result.push_back(temp);
                    cout << temp << endl;;
                }

       }
    }
    return result;
 }


int main()
{

    vector<std::string> calls;
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

calls: ["/project1/subproject1/method1",
 "/project2/subproject1/method1",
 "/project1/subproject1/method1",
 "/project1/subproject2/method1",
 "/project1/subproject1/method2",
 "/project1/subproject2/method1",
 "/project2/subproject1/method1",
 "/project1/subproject2/method1"]

["--project1 (6)",
 "----subproject1 (3)",
 "------method1 (2)",
 "----subproject2 (3)",
 "------method1 (3)",
 "--project2 (2)",
 "----subproject1 (2)",
 "------method1 (2)"]

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

