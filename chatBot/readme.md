Problem: Given a currentConversation, find a conversation with the most
matched words from a list of conversations. Complete the currentConversation
by appending everywords from conversation after the last matching words.

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
edge cases I can't think of. But the overall requirement is done
in terms of completing the currentConvesation by evaluating a list of conversations.