#include <iostream>
#include <vector>
#include <string>
#include <sstream>   // for turning int to str
#include <map>
#include <set>
#include <algorithm> // for transform
using namespace std;



vector<int> reduce_fraction(int x, int y){

    int i = 2;
    while(i <= min(x,y)){
        if (x%i == 0 && y%i == 0){
            return reduce_fraction(x/i,y/i);
        }
        i++;
    }

    return vector<int> {x,y};

}

string check_first_criterion(vector<vector<string>> messages){
    /// first test, check if the messages is more than 5 words

    string result;
    int total = messages.size();
    int less_than_five_words = 0;

    for (int i = 0 ; i < total; i++){
        string sentence = messages[i][0];
        int words_number = 0;

        for (int ii = 0; ii < sentence.size(); ii++){
            if (sentence[ii] == ' ' ){
                words_number++;
            }
        }
        if (words_number > 0){ words_number++;}  ///words number = space + 1

        if (words_number < 5){
            less_than_five_words++;
        }
    }

    int percentage = (less_than_five_words*1.0/total) * 100;
    if (percentage < 90)
        {
            return "passed";
        }else{
            vector<int> answer = reduce_fraction(less_than_five_words,total);
            stringstream r;
            r << "failed: " << answer[0] << "/" << answer[1];
            string result = r.str();
            return result;
        }
}


string check_second_criterion(vector<vector<string>> messages){
    ///second test, check if the repeat/total percentage > 50

    map<string,int> message_total; /// user, total of message
    map<string,int> repeated_total;  ///user, number of repeated message
    int user_total = 0;  /// user total is the size of message_total
    int total = messages.size();

    for (int i=0; i < total; i++){   /// this for loop count how many message each user receive
        string user = messages[i][1];
        string message = messages[i][0];

        bool already_in_map = false;
        for (auto E: message_total){
            if (user == E.first){
                already_in_map = true;
            }
        }
        if (already_in_map){
            message_total[user]++;
        }else{
            message_total[user] = 1;
            user_total++;
        }
    }

    map<string,string> counted_message;  /// message,user
    for (int i=0; i < total; i++){ /// this for loop count how many repeated message each user received
        string user = messages[i][1];
        string message = messages[i][0];

        int repeat = 0;
        for (int ii = 0; ii < total; ii++){
            if ( messages[ii][1] == user){        /// if messages are the same
                if ( messages[ii][0] == message){ /// if users are the same
                        repeat++;
                }
            }
        }
        if (repeat == 1){repeat =0;}  /// if a message only occurs once, there is no repeat
        repeated_total[user] = repeat;  /// map don't count repeat
    }

    vector<string> failed_user;
    for (int i = 0; i < user_total; i++){
        string user = messages[i][1];
        string message = messages[i][0];

        int percentage = (((repeated_total[user])*1.0)/message_total[user])*100;
        if (percentage > 50){
            failed_user.push_back(user);  // vector use push_back()
        }
    }


    if (failed_user.size() == 0){
        return "passed";
    }else{
        stringstream r;
        r << "failed:";
        for (int i = 0; i < failed_user.size(); i++){
            r << " " << failed_user[i];
        }
        string result = r.str() ;
        return result;
    }
}


string check_third_criterion(vector<vector<string>> messages){

    string result = " ";
    int message_total = messages.size();
    map<string,int> repeated_message;

    for (int i = 0; i < messages.size(); i++){
        string message = messages[i][0];
        int repeat = 0;
        for (int ii = 0; ii < messages.size(); ii++){
            if (messages[ii][0] == message){
                repeat++;
            }
        }

        if (repeat == 1){repeat = 0;}
        if (repeat > 0){
            repeated_message[message] = repeat;
        }
    }

    vector<string> problem_message;
    for (auto E: repeated_message){
        int repeat = E.second;
        int percentae = ((repeat*1.0)/message_total)*100;
        if (percentae > 50){
            problem_message.push_back(E.first);
        }
    }

    if (problem_message.size() == 0){
        return "passed";
    }else{
        stringstream r;
        r << "failed:" ;
        for (int i = 0 ; i< problem_message.size(); i++){
            r << " " << problem_message[i];
        }
        string result = r.str();
        return result;
    }
}


bool is_a_word(string message, string spamword, int position){

    ///  a word is surrounded by space ' '
    bool head_is_space = false;
    bool tail_is_space = false;

    int spam_word_length = spamword.length();

    if (position-1 < 0)
    {
        head_is_space = true;
    }else{
        if (message[position-1] == ' '){
            head_is_space = true;
        }
    }

    if (position + spam_word_length >= message.length())
    {
        tail_is_space = true;
    }else{
        char char_after_the_word = message[position+spam_word_length];
        if (!isalpha(char_after_the_word)){
            tail_is_space = true;
        }
    }

    return (head_is_space && tail_is_space);

}

string check_fourth_criterion(vector<vector<string>> messages, vector<string> spamSignals ){

    int total_words = messages.size();
    int total_spam_word = 0;

    set<string> problem;
    for (int i =0; i < messages.size(); i++){
        bool contain_spam = false;
        string message = messages[i][0];
        transform(message.begin(), message.end(), message.begin(), ::tolower);  /// all lower case

        for (int ii = 0; ii < spamSignals.size(); ii++){
            string spam_words = spamSignals[ii];
            transform(spam_words.begin(), spam_words.end(), spam_words.begin(), ::tolower); ///all lower case

            size_t found = message.find(spam_words);
            if (found != string::npos && is_a_word(message, spam_words, found)){
                contain_spam = true;
                problem.insert(spam_words);  /// set has no duplicate
            }
        }
        if (contain_spam){total_spam_word++;}
    }


    int percentage = ((total_spam_word*1.0)/total_words)* 100;
    if (percentage < 50){
        return "passed";
    }else{
        stringstream r;
        r << "failed:" ;

        for (auto E: problem){
            r << " " << E ;
        }
        string result = r.str();
        return result;

    }


}

vector<string> spamDetection(vector<vector<string>> messages, vector<string> spamSignals) {

    string first_criterion_result = check_first_criterion(messages);
    string second_criterion_result = check_second_criterion(messages);
    string third_criterion_result = check_third_criterion(messages);
    string fourth_criterion_result = check_fourth_criterion(messages, spamSignals);

    return vector<string> {first_criterion_result, second_criterion_result, third_criterion_result, fourth_criterion_result};
}

/*
[["Jkl ABA ty","111"],
 ["Jkl aba TY","222"],
 ["Jkl abA Ty","111"],
 ["jkl Aba tY","111"],
 ["JKl ABA ty","222"],
 ["Jkl aba tY","222"],
 ["Jkl abA Ty","111"],
 ["jkl Aba tY klk TY","111"],
 ["Jkl aBa tY","222"],
 ["Jkl aBA Ty","111"],
 ["Jkl aBA TY","111"]]

spamSignals: ["ty",
 "jk",
 "ab"]*/

 /*
 messages: [["Sale today!","2837273"],
 ["Unique offer!","3873827"],
 ["Only today and only for you!","2837273"],
 ["Sale today!","2837273"],
 ["Unique offer!","3873827"]]
spamSignals: ["sale",
 "discount",
 "offer"]

 */
int main()
{
    vector<vector<string>> messages = {{"Sale today!","2837273"},
 {"Unique offer!","3873827"},
 {"Only today and only for you!","2837273"},
 {"Sale today!","2837273"},
 {"Unique offer!","3873827"}};
  /*  vector<vector<string>> messages =
    {{"Jkl ABA ty","111"},
 {"Jkl aba TY","222"},
 {"Jkl abA Ty","111"},
 {"jkl Aba tY","111"},
 {"JKl ABA ty","222"},
 {"Jkl aba tY","222"},
 {"Jkl abA Ty","111"},
 {"jkl Aba tY klk TY","111"},
 {"Jkl aBa tY","222"},
 {"Jkl aBA Ty","111"},
 {"Jkl aBA TY","111"}
 };
*/
    //vector<string> spamSignals   = {"ty","jk","ab"};
    vector<string> acciden {"asdf","sdaff","fdsa"};
    vector<string> spamSignals   = {"sale","discount","offer"};
    vector<string> x = spamDetection(messages, spamSignals);
    for (int i = 0; i < x.size(); i++){
        cout << x[i] << endl;
    }


    return 0;
}
/*


Expected Output:

["passed",
 "failed: 2837273 3873827",
 "passed",
 "failed: offer sale"]
 */
