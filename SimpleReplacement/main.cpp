//
//  main.cpp
//  SimpleReplacement
//
//  Created by Constantine on 15.10.2020.
//  Copyright © 2020 Kostyansa. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>

const std::string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::map<char, double> ALPHABET_DISRIBUTION = {
    {'E', 0.1270},
    {'T', 0.0906},
    {'A', 0.0817},
    {'O', 0.0751},
    {'I', 0.0697},
    {'N', 0.0675},
    {'S', 0.0633},
    {'H', 0.0609},
    {'R', 0.0599},
    {'D', 0.0425},
    {'L', 0.0403},
    {'C', 0.0278},
    {'U', 0.0276},
    {'M', 0.0241},
    {'W', 0.0236},
    {'F', 0.0223},
    {'G', 0.0202},
    {'Y', 0.0197},
    {'P', 0.0193},
    {'B', 0.0149},
    {'V', 0.0098},
    {'K', 0.0077},
    {'J', 0.0015},
    {'X', 0.0015},
    {'Q', 0.0010},
    {'Z', 0.0007}
};
std::string ALPHABET_ORDERED_BY_PROBABILITIES = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

std::map<char, char> buildReplacementMap(const std::string& alphabet, const std::string& key){
    if (key.size() != 26) {
        throw std::invalid_argument("Key lenght is not valid");
    }
    std::map<char, char> replacement_map;
    for (char i = 0; i < 26; i++) {
        replacement_map.insert(std::make_pair(ALPHABET[i], key[i]));
    }
    return replacement_map;
}

std::map<char, double> buildProbabilityDistribution(std::string message){
    std::map<char, int> count;
    std::map<char, double> distribution;
    for (int i = 0; i < 26; i++) {
        count.insert(std::make_pair(ALPHABET[i], 0));
    }
    for (int i = 0; i < message.size(); i++) {
        (*count.find(message[i])).second += 1;
    }
    
    int sum = 0;
    for (auto itr : count) {
        sum += itr.second;
    }
    for (int i = 0; i < 26; i++) {
        distribution.insert(std::make_pair(ALPHABET[i],
                                           (double) (*count.find(ALPHABET[i])).second/sum
                                           ));
    }
    return distribution;
}

std::string Encrypt(const std::string& message, const std::string& key){
    std::stringstream ss;
    std::map<char, char> replacement_map = buildReplacementMap(ALPHABET, key);
    for (int i = 0; i < message.size(); i++) {
        auto symbol = replacement_map.find(message[i]);
        ss << symbol -> second;
    }
    return ss.str();
}

std::string Decrypt(const std::string& message, const std::string& key){
    std::stringstream ss;
    std::map<char, char> replacement_map = buildReplacementMap(key, ALPHABET);
    for (int i = 0; i < message.size(); i++) {
        auto symbol = replacement_map.find(message[i]);
        ss << symbol -> second;
    }
    return ss.str();
}

std::string SimpleProbability(std::string message){
    std::map<char, double> message_distribution = buildProbabilityDistribution(message);
    std::vector<std::pair<char, double>> alphabet_to_sort(26, std::make_pair(0, 0));
    for (auto itr : message_distribution) {
        alphabet_to_sort.push_back(itr);
    }
    sort(alphabet_to_sort.begin(), alphabet_to_sort.end(), [](std::pair<char, double> a, std::pair<char, double> b) -> bool {return b.second - a.second;});
    std::stringstream alphabet;
    for (auto itr : alphabet_to_sort) {
        alphabet << itr.first;
    }
    return Decrypt(message, alphabet.str());
}

std::vector<std::string> Analyze(std::string message){
    std::vector<std::string> results;
    results.push_back(SimpleProbability(message));
    return results;
}

int main(int argc, const char * argv[]) {
    int n;
    std::cout << "This is a program to encrypt/decrypt and analyze messages with Simple Substitution ciphers" << std::endl;
    bool finished = false;
    do {
        std::cout << "Input 1 to Encrypt message" << std::endl;
        std::cout << "Input 2 to Decrypt message" << std::endl;
        std::cout << "Input 3 to Analyze message with simple symbol probability analysis" << std::endl;
        std::cout << "Input 4 to exit" << std::endl;
        std::cin >> n;
        switch (n) {
            case 1:{
                std::cout << "Input message" << std::endl;
                std::string message;
                std::cin.ignore();
                std::getline(std::cin, message);
                std::transform(message.begin(), message.end(), message.begin(), ::toupper);
                std::cout << "Input key(26 symbol alphabet)" << std::endl;
                std::string key;
                std::cin >> key;
                std::transform(key.begin(), key.end(), key.begin(), ::toupper);
                std::string encrypted = Encrypt(message, key);
                std::cout << encrypted << std::endl;
                break;
            }
            case 2:{
                std::cout << "Input message: " << std::endl;
                std::string message;
                std::cin.ignore();
                std::getline(std::cin, message);
                std::transform(message.begin(), message.end(), message.begin(), ::toupper);
                std::cout << "Input key(26 symbol alphabet)" << std::endl;
                std::string key;
                std::cin >> key;
                std::transform(key.begin(), key.end(), key.begin(), ::toupper);
                std::string decrypted = Decrypt(message, key);
                std::cout << decrypted << std::endl;
                break;
            }
            case 3:{
                std::cout << "Input message: " << std::endl;
                std::string message;
                std::cin.ignore();
                std::getline(std::cin, message);
                std::transform(message.begin(), message.end(), message.begin(), ::toupper);
                std::vector<std::string> possible = Analyze(message);
                std::cout << "Possible variants:" << std::endl;
                for (auto itr : possible) {
                    std::cout << itr << std::endl;
                }
                break;
            }
            case 4:{
                finished = true;
                break;
            }
            default:{
                std::cout << "Invalid command" << std::endl;
            }
        }
    } while (!finished);
    return 0;
}
