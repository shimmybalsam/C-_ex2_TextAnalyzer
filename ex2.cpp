#include <iostream>
#include "TextAnalyzer.h"
#include <unordered_map>

#define NOT_ENOUGH_ARGS "Not enough input files given"
#define WHITESPACE " "
#define BEST_AUTHOR "Best matching author is "
#define OPEN_FILE_ERR "error opening file."
#define SCORE " score "
#define MIN_ARGS 4
#define ERR_RETURN 1

using namespace std;

/**
 * main function runs the program
 * @param argc num of args
 * @param argv list of args, as in the files of frequent words, unknown text and then list of known
 * @return 0 if program runs correctly, 1 otherwise.
 */
int main(int argc, char*argv[])
{
    if (argc < MIN_ARGS)
    {
        cerr << NOT_ENOUGH_ARGS << std::endl;
        return ERR_RETURN;
    }
    double best_score = 0;
    string best_title = argv[3];
    TextAnalyzer t = TextAnalyzer();
    int v = t.vectorizeFreq(argv[1]);
    if (v == 1)
    {
        cerr << OPEN_FILE_ERR << endl;
        return ERR_RETURN;
    }
    unordered_map<string, int> unknown_map = t.mapFile(argv[2]);
    for (int i = 3; i < argc; i ++)
    {
        string filename = argv[i];
        unordered_map<string, int> file_map = t.mapFile(filename);
        if (file_map.empty())
        {
            cerr << OPEN_FILE_ERR << endl;
            return ERR_RETURN;
        }
        double score = t.dist(file_map, unknown_map);
        cout <<  filename << WHITESPACE << score << endl;
        if (score >= best_score)
        {
            best_score = score;
            best_title = filename;
        }
    }
    cout << BEST_AUTHOR << best_title << SCORE << best_score << endl;
    return 0;
}