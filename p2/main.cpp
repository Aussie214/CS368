///////////////////////////////////////////////////////////////////////////////
// File Name:      main.cpp
//
// Author:         Gerald
// CS email:       gerald@cs.wisc.edu
//
// Description:    The main program for a2.
//
// IMPORTANT NOTE: THIS FILE SHOULD NOT BE MODIFIED.
///////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "a2.hpp"

/**
 * @brief The program execution begins here.
 * @param argc The number of command-line arguments.
 * @param argv The command line arguments.
 * @return 0 for normal program termination, -1 for abnormal termination.
 */
int main(int argc, char *argv[]) {
    // Check if the program is given 3 command line arguments
    // including the program name.
    if (argc != 3) {
        std::cerr << "USAGE: ./a.out <ReviewScoresFile> <ReviewsFile>"
                  << std::endl;
        return -1;
    }

    // Open the input file containing the raw data.
    std::ifstream rawReviewScoresInputFile(argv[1]);
    if (!rawReviewScoresInputFile.is_open()) {
        std::cerr << "Input file " << argv[1] << " cannot be opened."
                  << std::endl;
        return -1;
    }

    // Open an output file for storing the clean data.
    std::ofstream cleanReviewScoresOutputFile("cleanReviewScores.txt");
    if (!cleanReviewScoresOutputFile.is_open()) {
        std::cerr << "Output file cleanReviewScores.txt cannot be opened."
                  << std::endl;
        return -1;
    }

    // A set to store the stopwords.
    std::unordered_set<std::string> stopwords;

    // Open the input file containing the stopwords.
    std::ifstream stopwordsFile("stopwords.txt");
    if (!stopwordsFile.is_open()) {
        std::cerr << "Input file stopwords.txt cannot be opened." << std::endl;
        return -1;
    }

    // Read a collections of stopwords from the stopwords file
    // and store it in a set.
    fillStopWords(stopwordsFile, stopwords);

    // Clean the raw data and store it in an output file.
    cleanData(rawReviewScoresInputFile, cleanReviewScoresOutputFile, stopwords);

    // A map from each word to a pair consisting of the total rating for this
    // word and the total number of times this word has occurred in the reviews.
    std::unordered_map<std::string, std::pair<long, long> > dictionary;

    // Open an input file containing the clean data.
    std::ifstream clearReviewScoresInputFile("cleanReviewScores.txt");
    if (!clearReviewScoresInputFile.is_open()) {
        std::cerr << "Input file cleanReviewScores.txt cannot be opened."
                  << std::endl;
        return -1;
    }

    // Create a mapping between the words and their associated values.
    fillDictionary(clearReviewScoresInputFile, dictionary);

    // Open the file with the raw reviews.
    std::ifstream rawReviewsInputFile(argv[2]);
    if (!rawReviewsInputFile.is_open()) {
        std::cerr << "Input file " << argv[2] << " cannot be opened."
                  << std::endl;
        return -1;
    }

    // Open an output file for storing the clean reviews.
    std::ofstream cleanReviewsOutputFile("cleanReviews.txt");
    if (!cleanReviewsOutputFile.is_open()) {
        std::cerr << "Output file cleanReview.txt cannot be opened."
                  << std::endl;
        return -1;
    }

    // Clean the raw reviews and store them in an output file.
    cleanData(rawReviewsInputFile, cleanReviewsOutputFile, stopwords);


    // Open the input file containing the clean reviews.
    std::ifstream cleanReviewsInputFile("cleanReviews.txt");
    if (!cleanReviewsInputFile.is_open()) {
        std::cerr << "Input file cleanReviews.txt cannot be opened."
                  << std::endl;
        return -1;
    }

    // Open an output file for storing the scores for each review.
    std::ofstream scoresOutputFile("rawReviewsPredicted.txt");
    if (!scoresOutputFile.is_open()) {
        std::cerr << "Output file rawReviewsPredicted.txt cannot be opened." << std::endl;
        return -1;
    }

    // Rate the reviews and write the scores to an output file.
    scoreReviews(cleanReviewsInputFile, dictionary, scoresOutputFile);

    // Normal program termination.
    return 0;
}
