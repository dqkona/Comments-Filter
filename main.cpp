#include <iostream>
#include "SuffixAutomaton.h"

using namespace std;

int main()
{
    srand(time(0)); // set the seed
    generate_comment("jane.txt", MLN);

    SuffixAutomaton automaton;
    automaton.construct("jane.txt");

    //automaton.addComment("youfaggot");
    if (automaton.contains("youfaggot"))
    {
        cout << "please do not use mature language" << endl;
    }
    else
    {
        cout << "everything is ok with this user's comments" << endl;
    }

    vector<string> curses;
    curses.push_back("faggot");
    curses.push_back("moron");
    return 0;
}
