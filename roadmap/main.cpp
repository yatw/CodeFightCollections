#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <stdio.h>  //for printf
#include <algorithm> //for find
using namespace std;

struct pinfo{

    vector<string> workers;
    string startday, dueday;
};

map <string, pinfo> projects;

bool in_between(string startday, string dueday, string date){
    // "2017-02-01","2017-03-01"

    // convert string to char*
    vector<char> vs(startday.length() + 1);
    strcpy(&vs[0], startday.c_str());
    char* startday_s = &vs[0];

    int startday_year = atoi(strtok(startday_s, "-"));
    int startday_month = atoi(strtok(NULL, "-"));
    int startday_day = atoi(strtok(NULL, "-"));


    vector<char> vd(dueday.length() + 1);
    strcpy(&vd[0], dueday.c_str());
    char* dueday_s = &vd[0];

    int dueday_year = atoi(strtok(dueday_s, "-"));
    int dueday_month = atoi(strtok(NULL, "-"));
    int dueday_day = atoi(strtok(NULL, "-"));


    vector<char> ve(date.length() + 1);
    strcpy(&ve[0], date.c_str());
    char* date_s = &ve[0];

    int date_year = atoi(strtok(date_s, "-"));
    int date_month = atoi(strtok(NULL, "-"));
    int date_day = atoi(strtok(NULL, "-"));


    //check if the date is before startday
    if (date_year < startday_year){
        return false;
    }else if (date_year == startday_year){

        if (date_month < startday_month){
            return false;
        }else if (date_month == startday_month){

            if (date_day < startday_day){
                return false;
            }
        }

    }// else date_year > startday_year, the date is NOT before the startday, but continue to check if it is after the dueday



    //check if the date is after dueday
    if (date_year > dueday_year){
        return false;
    }else if (date_year == dueday_year){

        if (date_month > dueday_month){
            return false;
        }else if (date_month == dueday_month){

            if (date_day > dueday_day){
                return false;
            }
        }

    }


    return true;
}

vector<vector<string>> roadmap(vector<vector<string>> tasks, vector<vector<string>> queries) {

    vector<vector<string>> result;

    // store all the task into a project datastructure
    for (int i = 0; i < tasks.size(); i++){

        vector<string> task = tasks[i];

        pinfo p;
        p.startday = task[1];
        p.dueday = task[2];
         // loop through the list of workers
        for (int ii = 3; ii < task.size(); ii++){
            p.workers.push_back(task[ii]);
        }
        projects.insert(make_pair(task[0],p));
    }



    // find result from the data structure
    for (int i = 0; i < queries.size(); i++){ // each query is one worker

        vector<string> w; // the result of 1 worker

        vector<string> query = queries[i];

        string worker = query[0];
        string date = query[1];

        // go through each project, and find if that worker is working on it
        for (auto p: projects){


            if(find(p.second.workers.begin(), p.second.workers.end(), worker) != p.second.workers.end()) {

            // if that worker is associated with this project
            // check if the date is in between the startday and dueday
                if (in_between(p.second.startday, p.second.dueday, date)){
                    w.push_back(p.first);
                }
            }
        }

        result.push_back(w);
    }

    return result;
}



int main()
{
    vector<vector<string>> tasks = {{"A","2017-02-01","2017-03-01","Sam","Evan","Troy"}, {"B","2017-01-16","2017-02-15","Troy"}, {"C","2017-02-13","2017-03-13","Sam","Evan"}};
    vector<vector<string>> queries = {{"Evan","2017-03-10"},{"Troy","2017-02-04"}};
    vector<vector<string>> result = roadmap(tasks, queries);

    for (auto r: result){
        for (auto re: r){
            cout << re << endl;
        }
        cout << "------------------" << endl;
    }
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
