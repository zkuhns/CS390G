#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void populate_dictionary(std::vector < std::string >* dictionary, std::string filename) {
    std::ifstream input;
    std::string line;
    input.open(filename.c_str());

    while (getline(input, line)) {
        dictionary->push_back(line);
    }

    input.close();
}

int minimum(int value1, int value2, int value3) {
    int min = value1;
    if (min > value2) {
        min = value2;
    }
    if (min > value3) {
        min = value3;
    }
    return min;
    //return std::min(std::min(value1, value2), value3);
}

int levenshtein(std::string string_one, std::string string_two) {
    std::vector< std::vector<int> > matrix (string_one.size()+1, std::vector<int> (string_two.size()+1, 0));

    for (int i = 1; i <= string_one.size(); i++)
        matrix[i][0] = i;
    for (int i = 1; i <= string_two.size(); i++)
        matrix[0][i] = i;

    int cost;
    for (int j = 1; j <= string_two.size(); j++) {
        for (int i = 1; i <= string_one.size(); i++) {
            if (string_one[i-1] == string_two[j-1]) {
                cost = 0;
            } else {
                cost = 1;
            }
            matrix[i][j] = minimum(matrix[i-1][j] + 1,
                                   matrix[i][j-1] + 1,
                                   matrix[i-1][j-1] + cost);
        }
    }

    return matrix[string_one.size()][string_two.size()];
}

int main() {
    std::string word = "testington";
    std::string closest_word;
    int smallest_distance = 100;

    std::vector < std::string > dictionary;

    populate_dictionary(&dictionary, "dictionary.txt");

    #pragma omp parallel
    {
        #pragma omp for
        for (unsigned int i = 0; i < dictionary.size(); i++) {
            int distance = levenshtein(word, dictionary[i]);
            if (distance < smallest_distance) {
                smallest_distance = distance;
                closest_word = dictionary[i];
            }
        }
    }

    std::cout << smallest_distance << std::endl;
    std::cout << closest_word << std::endl;
}
