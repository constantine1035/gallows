#include "gallows.h"
#include "gtest/gtest.h"

// Тест для функции gallows(), проверяющий, что она возвращает корректное слово
TEST(GallowsTest, CheckCorrectWord) {
    // Перенаправляем стандартный ввод
    std::istringstream input("a\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\n");
    std::streambuf* original_cin = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    // Захватываем стандартный вывод
    testing::internal::CaptureStdout();

    // Запускаем функцию
    gallows();

    // Восстанавливаем стандартный ввод
    std::cin.rdbuf(original_cin);

    // Получаем захваченный вывод
    std::string output = testing::internal::GetCapturedStdout();

    // Проверяем, что вывод содержит "Correct word:"
    ASSERT_TRUE(output.find("Correct word:") != std::string::npos);

    // Проверяем, что вывод содержит "Mistake:"
    ASSERT_TRUE(output.find("Mistakes:") != std::string::npos);
}

// Тест для функции gallows(), проверяющий, что она возвращает корректное слово
TEST(GallowsTest, CheckMistakes) {
    // Перенаправляем стандартный ввод
    std::istringstream input("a\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\n");
    std::streambuf* original_cin = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    // Захватываем стандартный вывод
    testing::internal::CaptureStdout();

    // Запускаем функцию
    gallows();

    // Восстанавливаем стандартный ввод
    std::cin.rdbuf(original_cin);

    // Получаем захваченный вывод
    std::string output = testing::internal::GetCapturedStdout();

    // Проверяем, что вывод содержит "Mistakes:"
    ASSERT_TRUE(output.find("Mistakes:") != std::string::npos);
}

// Тест для функции gallows(), проверяющий обработку одной правильной буквы
TEST(GallowsTest, CheckCorrectLetter) {
    // TBD
}

// Тест для функции gallows(), проверяющий обработку ошибочной буквы
TEST(GallowsTest, CheckIncorrectLetter) {
    // TBD
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
