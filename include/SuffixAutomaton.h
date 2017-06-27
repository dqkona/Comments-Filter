#ifndef SUFFIXAUTOMATON_H
#define SUFFIXAUTOMATON_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

#define MLN_100 10000000
#define MLN 1000000
#define MIN_CHAR 97
#define MAX_CHAR 122
#define CHAR_COUNT MAX_CHAR - MIN_CHAR + 1 // 122(max char) - 97(min char) + 1

typedef std::vector<std::pair<char, int>>::const_iterator PairIterator;
using namespace std;

// helper functions
void generate_comment(string file_name, int com_size /* comment size */);

struct State
{
    int len;
    int link;
    vector< pair<char, int> > next;

    int getLink(char c);
    void setLink(char c, int a);

    friend ostream& operator<<(ostream &out, State &_state)
    {
        for (PairIterator iter = _state.next.begin(); iter != _state.next.end(); iter++)
        {
            out << "(" << _state.len << "," << iter->first << ") => " << iter->second << endl;
        }
        return out;
    }

};

class SuffixAutomaton
{
    public:
        SuffixAutomaton();
        ~SuffixAutomaton();
        void construct(string file_name); // constructs the Suffix Automaton with the data from <file_name> file
        bool contains(string word);
        bool contains(vector<string> words);
        void addComment(string word);

    private:
        void sa_init(); // init the Suffix Automata
        void sa_extend (char c); // extend for the current symbol

    public:

    private:
        vector<State> st; // states of the tree
        int sz; // current size
        int last;
        int total_links;
        int furthest;
};

#endif // SUFFIXAUTOMATON_H
