#include "gallows.h"

std::vector<std::string> words = {"car", "dog", "house", "cat", "book", "pen", "chair", "table", "computer",
                                  "phone", "sun", "moon", "tree", "flower", "river", "mountain", "baby", "bird",
                                  "fish", "friend", "teacher", "parent", "child", "doctor", "nurse", "artist",
                                  "actor", "singer", "writer", "scientist", "engineer", "student", "employee",
                                  "boss", "coworker", "police", "firefighter", "soldier", "lawyer", "judge",
                                  "prisoner", "detective", "thief", "singer", "dancer", "composer", "chef",
                                  "waiter", "customer", "driver", "passenger", "bicycle", "bus", "train", "plane",
                                  "ship", "boat", "radio", "television", "newspaper", "magazine", "internet",
                                  "library", "school", "university", "hospital", "office", "restaurant", "zoo",
                                  "park", "beach", "garden", "farm", "store", "market", "mall", "supermarket",
                                  "gym", "bank", "church", "mosque", "temple", "synagogue", "politics", "economy",
                                  "history", "geography", "mathematics", "science", "chemistry", "biology",
                                  "physics", "art", "music", "literature", "film", "sport", "soccer", "basketball",
                                  "swimming", "tennis", "hockey", "baseball", "football"};


void gallows() {
    std::srand(std::time(nullptr));
    std::string word = words[std::rand() % words.size()];
    int number_mistakes = 0;
    int number_correct = 0;
    std::vector<char> mistakes;
    std::vector<char> ready(word.size());
    while (number_mistakes < 6) {
        std::string guess;
        std::cin >> guess;
        if (guess.size() == 1) {
            if (word.find(guess[0]) != std::string::npos) {
                for (int i = 0; i < word.size(); ++i) {
                    if (word[i] == guess[0]) {
                        ready[i] = guess[0];
                        ++number_correct;
                    }
                }
                if (number_correct == word.size()) {
                    break;
                }
                std::cout << "Correct:\n";
                for (char i : ready) {
                    std::cout << i;
                }
                std::cout << '\n';
            } else {
                mistakes.push_back(guess[0]);
                ++number_mistakes;
                std::cout << "Mistake:\n";
                for (char i : mistakes) {
                    std::cout << i << ", ";
                }
                std::cout << '\n';
            }
        }
    }
    std::cout << "Correct word:\n" << word << '\n';
}