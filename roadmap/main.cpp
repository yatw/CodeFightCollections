#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <stdio.h>  //for printf
#include <algorithm> //for find
#include <queue>          // std::priority_queue
#include <functional>
using namespace std;

struct pinfo{

    vector<string> workers;
    string startday, dueday;
};

struct Compare
{

    map <string, pinfo> p;

    Compare( map <string, pinfo>*  projects){
        p = *projects;
    }

    bool operator() (string date1, string date2)
    {
        // compare two date, return true if lhs < rhs

        string d1 = p[date1].dueday;
        string d2 = p[date2].dueday;

        // convert string to char*
        vector<char> v1(d1.length() + 1);
        strcpy(&v1[0], d1.c_str());
        char* date1_s = &v1[0];

        int date1_y = atoi(strtok(date1_s, "-"));
        int date1_m = atoi(strtok(NULL, "-"));
        int date1_d = atoi(strtok(NULL, "-"));

        vector<char> v2(d2.length() + 1);
        strcpy(&v2[0], d2.c_str());
        char* date2_s = &v2[0];

        int date2_y = atoi(strtok(date2_s, "-"));
        int date2_m = atoi(strtok(NULL, "-"));
        int date2_d = atoi(strtok(NULL, "-"));

        if (date1_y > date1_y){
            return true;
        }else if (date1_y == date2_y){

            if (date1_m > date2_m){
                return true;
            }else if (date1_m == date2_m){

                if (date1_d > date2_d || date1_d == date2_d){
                    return true;
                }
            }
        }
        return false;
    }
};




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


    map <string, pinfo> projects;
    map <string, vector<string>> workingon;

    vector<vector<string>> result;

    // store all the task into a project data structure
    for (int i = 0; i < tasks.size(); i++){

        vector<string> task = tasks[i];
        string task_name = task[0];

        pinfo p;
        p.startday = task[1];
        p.dueday = task[2];
         // loop through the list of workers
        for (int ii = 3; ii < task.size(); ii++){

            string worker_name = task[ii];
            p.workers.push_back(worker_name);

            // also keep another map keep tracks of the project they working on
            if (workingon.find(worker_name) != workingon.end()){
                workingon[worker_name].push_back(task_name);
            }else{
                vector<string> t;
                t.push_back(task_name);
                workingon.insert(make_pair(worker_name,t));
            }

        }
        projects.insert(make_pair(task_name,p));
    }



    // find result from the data structure
    for (int i = 0; i < queries.size(); i++){
            // each query is one worker
        vector<string> query = queries[i];
        string worker = query[0];
        string date = query[1];

        priority_queue<string, std::vector<string>, Compare> q(&projects); // store all the projects in order

        // loop through all the projects this worker working on
        for (auto p :workingon[worker]){
            // p is just the name of each project

            if (in_between(projects[p].startday, projects[p].dueday, date)){
                q.push(p);
            }
        }

        // after getting all the projects in order, put them in a vector
        vector<string> w;
        while (!q.empty()) {
          w.push_back(q.top());
          q.pop();
        }



        result.push_back(w);
    }

    return result;
}



int main()
{
    vector<vector<string>> tasks = {{"LNWBN","2017-08-13","2017-12-24","Corey","Kyle","Kaleb","Reuben"}, {"NSXEN","2017-08-20","2017-09-18","Kai"}, {"DNMDC","2017-06-19","2017-08-07","Kaleb","Kai","Kyle","Reuben"}, {"UYWEQ","2017-04-23","2017-07-18","Corey","Kyle","Reuben","Kai"}, {"LIVNH","2017-11-01","2017-12-24","Kaleb","Kai"}};
    vector<vector<string>> queries = {{"Corey","2017-10-21"},{"Reuben","2017-03-16"},{"Kaleb","2017-11-22"},{"Kaleb","2017-03-22"},{"Reuben","2017-10-06"}};
    vector<vector<string>> result = roadmap(tasks, queries);

    for (auto e : result){
        for (auto r: e){
            cout << r << endl;
        }
        cout << "------------" << endl;
    }


    return 0;
}


/***
tasks: [["LNWBN","2017-08-13","2017-12-24","Corey","Kyle","Kaleb","Reuben"],
 ["NSXEN","2017-08-20","2017-09-18","Kai"],
 ["DNMDC","2017-06-19","2017-08-07","Kaleb","Kai","Kyle","Reuben"],
 ["UYWEQ","2017-04-23","2017-07-18","Corey","Kyle","Reuben","Kai"],
 ["LIVNH","2017-11-01","2017-12-24","Kaleb","Kai"]]
queries: [["Corey","2017-10-21"],
 ["Reuben","2017-03-16"],
 ["Kaleb","2017-11-22"],
 ["Kaleb","2017-03-22"],
 ["Reuben","2017-10-06"]]
 ***/
