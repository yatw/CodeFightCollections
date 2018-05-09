#include <iostream>
#include <string>
#include <array>
#include <vector>
using namespace std;

bool plagiarismCheck(std::vector<std::string> code1, std::vector<std::string> code2) {







}



int main()
{
vector<string> code1{"def is_even_sum(a, b):",
 "    return (a + b) % 2 == 0"};
vector<string> code2{"def is_even_sum(summand_1, summand_2):",
 "    return (summand_1 + summand_2) % 2 == 0"};

 cout << plagiarismCheck(code1, code2) << endl;
     return 0;
}
