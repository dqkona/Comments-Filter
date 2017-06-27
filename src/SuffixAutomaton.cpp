#include "SuffixAutomaton.h"

void generate_comment(string file_name, int com_size /* comment size */)
{
    ofstream write_data(file_name);
    for (int i = 0; i < com_size; i++)
    {
        int random = rand() % (122 - 97 + 1) + 97;
        char ch = random;
        write_data.write(&ch, 1);
    }
    write_data.close();
}

int State::getLink(char c)
{
    for (int i = 0; i < next.size(); i++)
    {
        if (next.at(i).first == c)
            return next.at(i).second;
    }
    return -1;
}

void State::setLink(char c, int a)
{
    for (int i = 0; i < next.size(); i++)
    {
        if (next.at(i).first == c)
        {
            next.at(i).second = a;
        }
    }
}

SuffixAutomaton::SuffixAutomaton()
{
    total_links = 0;
    sa_init();
}

SuffixAutomaton::~SuffixAutomaton()
{
    //dtor
}

void SuffixAutomaton::construct(string file_name)
{
    ifstream data;

    // open file
    data.open(file_name, ios::binary);

    if (!data.is_open())
    {
        cout << "file not open" << endl;
        return;
    }

    char c;

    //for (int i = 0; i < MLN_100; i++)
    while (data.get(c))
    {
        //int random = rand() % (122 - 97 + 1) + 97;
        //c = random;
        sa_extend(c);
    }
    data.close();
}

void SuffixAutomaton::sa_init()
{
    sz = last = 0;
    st.push_back(State());
    st[0].len = 0;
    st[0].link = -1;
    ++sz;
}

void SuffixAutomaton::sa_extend (char c)
{
    int cur = sz++;
    st.push_back(State());
    furthest = cur;
    st[cur].len = st[last].len + 1;
    int p;
    for (p = last; p != -1 && (st[p].getLink(c) == -1); p = st[p].link)
    {
        st[p].next.push_back(make_pair(c, cur));
        total_links++;
    }

    if (p == -1)
    {
        st[cur].link = 0;
        //cout << *st[cur];
    }

    else
    {
        //int q = st[p].next[c - MIN_CHAR];
        int q = st[p].getLink(c);
        if (st[p].len + 1 == st[q].len)
        {
            st[cur].link = q;
        }
        else
        {
            int clone = sz++;
            st.push_back(State());
            st[clone].len = st[p].len + 1;
            //st[clone].next = st[q].next;
            //copy(std::begin(st[q].next), end(st[q].next), begin(st[clone].next));
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;

            // links increase with the number of links of state 'q'
            total_links += st[q].next.size();
            //for (; p != -1 && st[p].next[c] == q; p = st[p].link)
            for (; p != -1 && st[p].getLink(c) == q; p = st[p].link)
            {
                //st[p].next[c - MIN_CHAR] = clone;
                st[p].setLink(c, clone);
            }


            st[q].link = st[cur].link = clone;
            //cout << *st[clone] << endl;
        }
    }
    last = cur;
}

// checks if <word> is a substring in the tree
bool SuffixAutomaton::contains(string word)
{
    State *curr = &st[0]; // current state
    for (int i = 0; i < word.length(); i++)
    {
        if (curr->getLink(word[i]) == -1) // no link found with this char
        {
            return false;
        }
        curr = &st[curr->getLink(word[i])];
    }
    return true;
}

bool SuffixAutomaton::contains(vector<string> words)
{
    for (int i = 0; i < words.size(); i++)
    {
        State *curr = &st[0]; // current state
        string word = words.at(i);
        for (int j = 0; j < word.length(); j++)
        {
            if (curr->getLink(word[j]) != -1) // link found with this char
            {
                if (j == word.length() - 1) // link found with the last char
                {
                    return true;
                }
            }
            else // no link found
            {
                break;
            }
        }
    }
    return false;
}

void SuffixAutomaton::addComment(string word)
{
    for (int i = 0; i < word.length(); i++)
    {
        sa_extend(word[i]);
    }
}


