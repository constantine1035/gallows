#include "gallows.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>

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

std::string get_current_word(const std::vector<char>& ready) {
    std::string word;
    for (auto i : ready) {
        word += i;
    }
    return word;
}

std::string get_current_mistakes(const std::vector<char>& mistakes) {
    std::string output;
    for (auto i : mistakes) {
        output += i;
        output += ' ';
    }
    return output;
}

std::string get_play_screen(std::string input, const std::vector<char>& ready, const std::vector<char>& mistakes) {
    return "Guess the letter: " + input + "\nCurrent word: " + get_current_word(ready) + "\nCurrent mistakes: " + get_current_mistakes(mistakes);
}

bool find_mistake(const char& letter, const std::vector<char>& mistakes) {
    for (auto i : mistakes) {
        if (i == letter) {
            return true;
        }
    }
    return false;
}

void process_input(std::string guess, std::vector<char>& ready, std::vector<char>& mistakes, int& number_correct, int& number_mistakes, const std::string& word) {
    if (word.find(guess[0]) != std::string::npos) {
        for (int i = 0; i < word.size(); ++i) {
            if (word[i] == guess[0]) {
                ready[i] = guess[0];
                ++number_correct;
            }
        }
    } else {
        if (!find_mistake(guess[0], mistakes)) {
            mistakes.push_back(guess[0]);
            ++number_mistakes;
        }
    }
}

void gallows() {
    std::srand(std::time(nullptr));
    std::string word = words[std::rand() % words.size()];
    int number_mistakes = 0;
    int number_correct = 0;
    int number_entered = 0;
    std::vector<char> mistakes;
    std::vector<char> ready(word.size(), '.');
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    sf::Text text;
    sf::Font font;
    font.loadFromFile("../../light-arial.ttf");
    text.setString("Game started\n\nPress any button");
    text.setPosition(200, 200);
    text.setFont(font);
    text.setCharacterSize(24);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                ++number_entered;
                if (number_entered == 1) {
                    text.setString(get_play_screen(" ", ready, mistakes));
                    continue;
                }
                if (96 < event.text.unicode && event.text.unicode < 123) {
                    std::string inputText = "";
                    inputText += static_cast<char>(event.text.unicode);
                    text.setString(get_play_screen(inputText, ready, mistakes));
                    process_input(inputText, ready, mistakes, number_correct, number_mistakes, word);
                    text.setString(get_play_screen(inputText, ready, mistakes));
                    if (number_correct == word.size()) {
                        text.setString("    Game won!\nCorrect word: " + word);
                        break;
                    }
                    if (number_mistakes > 5) {
                        text.setString("    Game over\nCorrect word: " + word);
                        break;
                    }
                }
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }
}