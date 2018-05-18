#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>  //for printf
using namespace std;

struct pinfo{

    vector<string> workers;
    string startday, dueday;
};

map <string, pinfo> projects;

vector<vector<string>> roadmap(vector<vector<string>> tasks, vector<vector<string>> queries) {

    vector<vector<string>> result;


    for (int i = 0; i < tasks.size(); i++){

        vector<string> task = tasks[i];

        pinfo p;
        p.startday = task[1];
        p.dueday = task[2];



         // loop through the list of workers
        for (int ii = 3; ii < task.size(); ii++){
            p.workers.push_back(task[ii]);
        }

        projects.insert(make_pair(task[0], p));

    }
/***
    for (auto p : projects){
        cout << p.first << endl;
        cout << p.second.startday << endl;
        cout << p.second.dueday << endl;
        for (auto w : p.second.workers){
            cout << w << endl;
        }


    }
    ***/
    return result;
}



int main()
{
    vector<vector<string>> tasks = {{"A","2017-02-01","2017-03-01","Sam","Evan","Troy"}, {"B","2017-01-16","2017-02-15","Troy"}, {"C","2017-02-13","2017-03-13","Sam","Evan"}};
    vector<vector<string>> queries = {{"Evan","2017-03-10"},{"Troy","2017-02-04"}};
    roadmap(tasks, queries);
    return 0;
}


/***
tasks: [["A","2017-02-01","2017-03-01","Sam","Evan","Troy"],
 ["B","2017-01-16","2017-02-15","Troy"],
 ["C","2017-02-13","2017-03-13","Sam","Evan"]]
queries: [["Evan","2017-03-10"],
 ["Troy","2017-02-04"]]

 [["C"],
 ["B","A"]]
 ***/
