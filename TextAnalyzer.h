//
// Created by Shimmy on 12/27/2018.
//

#ifndef EX2_TEXTANALYZER_H
#define EX2_TEXTANALYZER_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>

using namespace std;

/**
 * TextAnalyzer class. This class represents the databases and function through which we can
 * calculate a text's author.
 */
class TextAnalyzer
{
public:

    /**
     * adds all frequent words into a vector
     * @param frequent filename of frequent words
     */
    int vectorizeFreq(string frequent);

    /**
     *  maps file to occurences of each frequent word
     * @param filename name of current file to be mapped
     * @return an unordered map of frequent word occurences in file
     */
    unordered_map<string, int> mapFile(string filename);

    /**
     * calculates the distance between 2 texts
     * @param f map of file who's author is known
     * @param unknown map of file who's author is unknown
     * @return calculated distance
     */
    double dist(unordered_map<string, int> &f, unordered_map<string, int> &unknown) const;

    /**
     * calculates the norm of a text
     * @param file map of frequent words count in given file
     * @return calculated norm
     */
    double norm(unordered_map<string, int> &file) const;


private:
    vector<string> _freq; /** vector of frequent words*/
};

#endif //EX2_TEXTANALYZER_H
