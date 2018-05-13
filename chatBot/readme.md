Problem: Given a currentConversation (vector of string), 
from a vector of conversations (vector<vector<string>>), find the conversation with most words matched currentConversation 
Complete the currentConversation by appending all words after the last matching words from conversation.

Complication: 

(1)Need to keep track of how many unique matching words 
for each conversation that match the words in currentConversation.

(2)Determine the last matching words in the most match conversation.

Solution:

(1) Use a map with keys as each conversation according to their orders,
values as a vector of matched words from conversation.

(2) The last item in the vector is the last matching words

Comment:
Passed 9/10 of the tests, couldn't pass that 1 hidden test, should be some
edge cases I could not think of. But the overall requirement is done.