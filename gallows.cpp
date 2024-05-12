#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <ctime>

std::vector<std::string> words = {
        "car", "dog", "house", "cat", "book", "pen", "chair", "table", "computer",
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
        "swimming", "tennis", "hockey", "baseball", "football"
};

std::string get_current_word(const std::vector<char>& ready) {
    return std::string(ready.begin(), ready.end());
}

std::string get_current_mistakes(const std::vector<char>& mistakes) {
    return std::string(mistakes.begin(), mistakes.end());
}

std::string get_play_screen(const std::string& input, const std::vector<char>& ready, const std::vector<char>& mistakes) {
    return "Guess the letter: " + input + "\nCurrent word: " + get_current_word(ready) + "\nCurrent mistakes: " + get_current_mistakes(mistakes);
}

bool find_mistake(const char& letter, const std::vector<char>& mistakes) {
    return std::find(mistakes.begin(), mistakes.end(), letter) != mistakes.end();
}

void process_input(const std::string& guess, std::vector<char>& ready, std::vector<char>& mistakes, int& number_correct, int& number_mistakes, const std::string& word) {
    if (word.find(guess[0]) != std::string::npos) {
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == guess[0] && ready[i] != guess[0]) {
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
    bool is_end = false;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
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
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                ++number_entered;
                if (number_entered == 1) {
                    text.setString(get_play_screen(" ", ready, mistakes));
                    continue;
                }
                if (event.text.unicode == '\n' && is_end) { // Check for Enter key
                    is_end = false;
                    word = words[std::rand() % words.size()]; // Generate new word
                    number_mistakes = 0;
                    number_correct = 0;
                    number_entered = 0;
                    mistakes.clear();
                    ready.assign(word.size(), '.');
                    text.setString(get_play_screen(" ", ready, mistakes));
                    continue;
                }
                if (event.text.unicode == 27) { // Check for Escape key
                    window.close();
                    return;
                }
                if (96 < event.text.unicode && event.text.unicode < 123) {
                    std::string inputText = "";
                    inputText += static_cast<char>(event.text.unicode);
                    text.setString(get_play_screen(inputText, ready, mistakes));
                    process_input(inputText, ready, mistakes, number_correct, number_mistakes, word);
                    text.setString(get_play_screen(inputText, ready, mistakes));
                    if (number_correct == word.size()) {
                        text.setString("\t\t\tGame won!\nCorrect word: " + word + "\nPress Enter to restart");
                        is_end = true;
                        break;
                    }
                    if (number_mistakes > 5) {
                        text.setString("\t\t\tGame over\nCorrect word: " + word + "\nPress Enter to restart");
                        is_end = true;
                        break;
                    }
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
        window.clear();
        window.draw(text);
        window.display();
    }
}
