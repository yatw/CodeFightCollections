/*

If you have a task that you need to complete on a regular basis, you can set it up in Asana as a recurring task. One option is to schedule the task to repeat every k weeks on specified days of the week.

It would be useful to be able to view the first n dates for which the task is scheduled. Given the first date for which the task is scheduled, return an array of the first n dates.

In this task, you'll likely need month lengths and weekday names, provided here:

    Month lengths from January to December: 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31.
        During leap years February has 29 days.

    Names of weekdays: "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday".

    January 1, 2015 was a Thursday.

Example

For firstDate = "01/01/2015", k = 2, daysOfTheWeek = ["Monday", "Thursday"] and n = 4, the output should be

recurringTask(firstDate, k, daysOfTheWeek, n) =
    ["01/01/2015", "05/01/2015", "15/01/2015", "19/01/2015"]

firstDate falls on a Thursday. The first Monday after it is "05/01/2015". Since k = 2, the next two days for which the task is scheduled are Thursday, January 15, and Monday, January 19.

Input/Output

    [time limit] 500ms (cpp)

    [input] string firstDate

    A string in the format "dd/mm/yyyy", representing some date either in the past, or in the future. It is guaranteed that the date is between 1900 and 3999, both inclusive.

    [input] integer k

    A positive integer.

    Constraints:
    1 ≤ k ≤ 20.

    [input] array.string daysOfTheWeek

    Array containing from 1 to 7 distinct elements, inclusive, each of which equals a weekday name. Weekdays appear in the same order they are given in the description.
    It's guaranteed that the day of the week on which the firstDate falls is present in this list.

    Constraints:
    1 ≤ daysOfTheWeek.length ≤ 7.

    [input] integer n

    Constraints:
    1 ≤ n ≤ 15.

    [output] array.string

    Array containing the first n dates (including the first one) on which the task is scheduled in the chronological order.



*/


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h> /// atoi
#include <map>
#include <vector>
#include <iomanip>
using namespace std;

vector<int> strtoint(string given_date){

    char cmonth[3];
    char cdate[3];
    char cyear[5];
    char cyear_last2digit[3];

    int ii = 0;
    for (int i = 0; i < 10; i++){
        /// firstDate[2] and firstDate[5] == '/'
        /// date format 09/12/2016  =  December 9, 2016
        if (i < 2)            { cdate[ii]  = given_date[i]; }
        if (i > 2 && i < 5)   { cmonth[ii] = given_date[i]; }
        if (i > 5 && i < 11)  { cyear[ii]  = given_date[i]; }
        ii++;
        if (i == 2 || i == 5){ii = 0;} // reset ii to 0 when it hit "/"
    }

    cyear_last2digit[0] = cyear[2];
    cyear_last2digit[1] = cyear[3];

    int date = atoi(cdate);  /// atoi char list to int
    int month = atoi(cmonth);
    int year = atoi(cyear);
    int yy = atoi(cyear_last2digit);
    return vector<int> {date, month, year, yy};
}

int GiveCenteryCode(int year){

    if (year >= 1700 && year <= 1799){ return 5;}
    if (year >= 1800 && year <= 1899){ return 3;}
    if (year >= 1900 && year <= 1999){ return 1;}
    if (year >= 2000 && year <= 2099){ return 0;}
}


int GiveMonthCode(int month){

    map<int, int> Month_code;
    Month_code[1] = 5;
    Month_code[2] = 1;
    Month_code[3] = 1;
    Month_code[4] = 4;
    Month_code[5] = 6;
    Month_code[6] = 2;
    Month_code[7] = 4;
    Month_code[8] = 0;
    Month_code[9] = 3;
    Month_code[10] = 5;
    Month_code[11] = 1;
    Month_code[12] = 3;

    return Month_code[month];

}

string GiveDay(int day){

    map<int, string> Day_code;
    Day_code[0] = "Sunday";
    Day_code[1] = "Monday";
    Day_code[2] = "Tuesday";
    Day_code[3] = "Wednesday";
    Day_code[4] = "Thursday";
    Day_code[5] = "Friday";
    Day_code[6] = "Saturday";
    //Day_code[7] = "Sunday";

    return Day_code[day];
}


string DateToDay(string given_date){

    vector<int> date_in_int = strtoint(given_date); // strtoint return a vector that contains (date month year yy)

    int date = date_in_int[0];
    int month= date_in_int[1];
    int year = date_in_int[2];
    int yy   = date_in_int[3];

    /// FORMULA to find day
    /// remainder of (  (yy + yy/4 + 1 + century + month + dd) /7 )   <- yy/4  if not whole, always round down

    int centery_code = GiveCenteryCode(year);
    int month_code = GiveMonthCode(month);
/*
    cout << yy << endl;
    cout << yy/4 << endl;
    cout << centery_code << endl;
    cout << month_code << endl;
    cout << date << endl;
*/
    int day_code = (yy + yy/4 + 1 + centery_code + month_code + date)% 7 ;
    return GiveDay(day_code);  // GiveDay takes the day_code and return the day in string


}


bool is_leap_year(int year){

    if (year%4   != 0){return false;}   ///If it is not divisible by 4, like 1997, it is not a leap year
    if (year%100 != 0){return true;}    ///If a year is divisible by 4, but not 100, like 2012, it is a leap year.
    if (year%400 != 0){return false;}   ///If a year is divisible by 100, but not 400, like 1900, then it is not a leap year.
                                        ///If a year is divisible by both, then it is a leap year.
    return true;
}
int month_length(int month, int year){

    map<int, int> Month_day;
    Month_day[1] = 31;
    Month_day[2] = 28;
    Month_day[3] = 31;
    Month_day[4] = 30;
    Month_day[5] = 31;
    Month_day[6] = 30;
    Month_day[7] = 31;
    Month_day[8] = 31;
    Month_day[9] = 30;
    Month_day[10] = 31;
    Month_day[11] = 30;
    Month_day[12] = 31;

    if (month == 2 && is_leap_year(year)){
        return 29;
    }
    return Month_day[month];
}


int days_till(string day1, string day2)
{
    /// count days from day1 to day2
    map<string, int> Day;

    Day["Sunday"]    = 0;
    Day["Monday"]    = 1;
    Day["Tuesday"]   = 2;
    Day["Wednesday"] = 3;
    Day["Thursday"]  = 4;
    Day["Friday"]    = 5;
    Day["Saturday"]  = 6;

    if ((Day[day2] - Day[day1] ) > 0 ){return (Day[day2] - Day[day1]);} /// if it is within the same week
    if ((Day[day2] - Day[day1] ) < 0 ){ return (7 - Day[day1] + Day[day2])  ;}

    return 7;
}


string determine_new_date(int first_date, int first_month, int first_year, int day_distance){

    int days_in_month = month_length(first_month ,first_year);

    int date = first_date + day_distance;
    int month = first_month;
    int year = first_year;
    if (date > days_in_month)
    {
        date = date - days_in_month;
        month++;
        if (month > 12)
        {
            month = 1;
            year++;
        }
    }

    stringstream s;
    s << setfill('0') << setw(2) << date  << "/" << setfill('0') << setw(2) << month << "/" << year;
    string str = s.str() ;
    return str;
}

vector<string> recurringTask(string firstDate, int k, vector<std::string> daysOfTheWeek, int n)
{

    vector<int> date_in_int = strtoint(firstDate); // strtoint return a vector that contains (date month year yy)

    int first_date = date_in_int[0];
    int first_month= date_in_int[1];
    int first_year = date_in_int[2];
    int first_yy   = date_in_int[3];


    map<string,string> day_of_firstdate;   /// 12/12/2016 Monday
    for (int index = 0; index < daysOfTheWeek.size() ; index++)   /// determine the day of the firstdate
    {
        if (DateToDay(firstDate) == daysOfTheWeek[index])
        {
            day_of_firstdate[firstDate] = daysOfTheWeek[index];
            daysOfTheWeek.erase(daysOfTheWeek.begin()+index);  /// remove the day of the firstdate from the vector
        }
    }

    for (int index = 0; index < daysOfTheWeek.size() ; index++)   /// run another for loop to determine other date
    {
        int day_distance =  days_till(day_of_firstdate[firstDate],daysOfTheWeek[index]  ) ;
        string new_date = determine_new_date(first_date, first_month,first_year, day_distance);
        day_of_firstdate[new_date] = daysOfTheWeek[index];
    }



    vector<string> taskday;
    int i = 0;
    int week = 0;
    while (i < n){
        for(auto it = day_of_firstdate.cbegin(); it != day_of_firstdate.cend(); ++it)
        {
            vector<int> v = strtoint(it->first);
            int add_days = (k*7)*week ;
            taskday.push_back(determine_new_date(v[0],v[1],v[2], add_days));
            i++;
        }
        week++;
    }

    for (int i = 0; i < taskday.size(); i++){
        cout << taskday[i] << endl;
    }

    return taskday;

}

int main()
{
    string firstDate = "22/02/2020";
    int k = 1;
    vector<string> daysOfTheWeek {"Saturday"};

    int n = 2;




    recurringTask(firstDate, k, daysOfTheWeek, n);
    ///["01/01/2015", "05/01/2015", "15/01/2015", "19/01/2015"]


}

