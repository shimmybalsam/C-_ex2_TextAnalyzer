//
// Created by Shimmy on 12/27/2018.
//

#include "TextAnalyzer.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <map>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <unordered_map>

#define OPEN_FILE_ERR "error opening file."

using namespace std;

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class TextAnalyzer.
// --------------------------------------------------------------------------------------

/** the following functions are all implementations of the functions declared in TextAnalyzer.h,
 * as such all documentation of functions are same as in TextAnalyzer.h.
 */

int TextAnalyzer::vectorizeFreq(string frequent)
{
    ifstream f(frequent);
    if (f.is_open())
    {
        string word;
        while (!f.eof())
        {
            f >> word;
            _freq.push_back(word);
        }
        f.close();
        return 0;
    }
    else
    {
        return 1;
    }
}

unordered_map<string, int> TextAnalyzer::mapFile(string filename)
{
    unordered_map<string, int> m;
    ifstream f(filename);
    if (f.is_open())
    {
        for (auto i = _freq.begin(); i != _freq.end(); i++)
        {
            m[*i] = 0;
        }
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        boost::char_separator<char> sep{", !\":;\n"};
        string line;
        while (!f.eof())
        {
            getline(f, line);
            boost::algorithm::to_lower(line);
            tokenizer tok{line, sep};
            for (const auto &t : tok)
            {
                auto it = find(_freq.begin(), _freq.end(), t);
                if (it != _freq.end())
                {
                    m[*it]++;
                }
            }
        }
        f.close();
    }
    return m;
}

double TextAnalyzer::norm(unordered_map<string, int> &file) const
{
    double sum = 0;
    for (auto i = file.begin(); i != file.end(); ++i)
    {
        sum += pow(i->second, 2);
    }
    return sqrt(sum);
}

double TextAnalyzer::dist(unordered_map<string, int> &f, unordered_map<string, int> &unknown) const
{
    double unknown_norm = norm(unknown);
    double known_norm = norm(f);
    if (known_norm == 0 or unknown_norm == 0)
    {
        return 0;
    }
    double mult = 0;
    for (auto i = f.begin(); i != f.end(); ++i)
    {
        mult += i->second * unknown[i->first];
    }
    return mult / (unknown_norm * known_norm);
}

