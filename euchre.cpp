#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    // checks for 12 arguments
    if (argc != 12)
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    string pack_filename = argv[1];
    string shuffle_decision = argv[2];
    int points_to_win = atoi(argv[3]);
    string player_name_1 = argv[4];
    string player_type_1 = argv[5];
    string player_name_2 = argv[6];
    string player_type_2 = argv[7];
    string player_name_3 = argv[8];
    string player_type_3 = argv[9];
    string player_name_4 = argv[10];
    string player_type_4 = argv[11];

    ifstream input_file;
    input_file.open((pack_filename).c_str());

    // if input_file is open, if not print error message
    if (!input_file.is_open())
    {
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }

    // if points_to_win is not 1-100 inclusive, print error message
    if (!(points_to_win >= 1 && points_to_win <= 100))
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    // if shuffle_decision is not present, print error message
    if (shuffle_decision != "shuffle" && shuffle_decision != "noshuffle")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    // if player type is not simple or human, print error message
    if (player_type_1 != "Simple" && player_type_1 != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    }

    if (player_type_2 != "Simple" && player_type_2 != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    }

    if (player_type_3 != "Simple" && player_type_3 != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    }
    if (player_type_4 != "Simple" && player_type_4 != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    }

    return 0;
}