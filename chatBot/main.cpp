#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // to use find

using namespace std;


vector<string> chatBot(vector<vector<string>> conversations, vector<string> currentConversation) {


    map<int, vector<string>> match_words; // conversation number map-> a list of matched words>

    for (int i = 0; i < conversations.size(); i++){  // for each conversation

        match_words.insert(make_pair(i, vector<string>{}));

        for (int ii = 0; ii < conversations[i].size(); ii++){  // for each word in the conversation

            // if that word is in the currentConversation and have not been matched
            if (find(currentConversation.begin(), currentConversation.end(), conversations[i][ii]) != currentConversation.end()
                 && find(match_words[i].begin(), match_words[i].end(), conversations[i][ii]) == match_words[i].end()
               ){

                match_words[i].push_back(conversations[i][ii]);
            }
        }
    }

    int most_match = 0; // the conversation number that has the most match
    // if 2 conversation has the same match, use the smaller number
    int match_count = 0;
    for (int i = 0; i < match_words.size(); i++){

        if ( match_words[i].size() > match_count){
            most_match = i;
            match_count = match_words[i].size();  // the size is the number of match
        }
     }


    // insert the words from the conversation to currentConversation
    if (match_count != 0){

        string last_matching_word = match_words[most_match][match_count-1];
        bool insert_word = false;
        for (int i = 0; i < conversations[most_match].size(); i++){

            if (insert_word){
                currentConversation.push_back(conversations[most_match][i]);
            }

            if (conversations[most_match][i] == last_matching_word){
                insert_word = true;
            }
        }
    }

    return currentConversation;
}






int main()
{
    vector<string> currentConversation = {"hello", "john", "do", "you", "have", "a", "favorite", "city", "to", "live", "in", "yes", "it", "is"};

    vector<vector<string>> conversations = {

        {"where", "are", "you", "live", "i", "live", "in", "new", "york"},
        {"are", "you", "going", "somewhere", "tonight", "no", "i", "am", "too", "tired", "today"},
        {"hello", "what", "is", "your", "name", "my", "name", "is", "john"},



    };

    chatBot(conversations,currentConversation );

    return 0;
}


/***
conversations = [
    ["where", "are", "you", "live", "i", "live", "in", "new", "york"],
    ["are", "you", "going", "somewhere", "tonight", "no", "i", "am", "too", "tired", "today"],
    ["hello", "what", "is", "your", "name", "my", "name", "is", "john"]]

and currentConversation = ["hello", "john", "do", "you", "have", "a", "favorite", "city", "to", "live", "in", "yes", "it", "is"], the output should be
chatBot(conversations, currentConversation) = ["hello", "john", "do", "you", "have", "a", "favorite", "city", "to", "live", "in", "yes", "it", "is", "new", "york"].

***/
