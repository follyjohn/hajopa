using namespace std;
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <string>

void LPSArray(std::string pattern, int M, std::vector<int> lps)
{

    int len = 0;

    lps[0] = 0;
    int i = 1;
    while (i < M)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {

            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(std::string pattern, std::string txt)
{
    int M = pattern.length();
    int N = txt.length();

    std::vector<int> lps(M);

    LPSArray(pattern, M, lps);

    int i = 0;
    int j = 0;
    int count = 0;
    vector<int> indexes;
    while ((N - i) >= (M - j))
    {
        if (pattern[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            count++;
            j = lps[j - 1];
        }

        else if (i < N && pattern[j] != txt[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return count;
}
