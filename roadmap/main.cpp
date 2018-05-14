#include <iostream>
#include <vector>
#include <stdio.h>  //for printf
using namespace std;


vector<vector<string>> roadmap(vector<vector<string>> tasks, vector<vector<string>> queries) {

    vector<vector<string>> result;

    for (int i = 0; i < queries.size(); i++){
        vector<string> working_on = {};
        result.insert(working_on);

    }
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
