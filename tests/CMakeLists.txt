# GTest
enable_testing()  # Включаем поддержку тестирования в CMake

# Добавляем исполняемый файл тестов
add_executable(test_gallows test.cpp gallows.cpp)

# Добавляем библиотеку Google Test
add_library(gtest STATIC
        ../contrib/gtest/googletest/src/gtest-all.cc)

# Включаем директории заголовочных файлов для Google Test
target_include_directories(gtest
        PUBLIC ../contrib/gtest/googletest/include
        PUBLIC ../contrib/gtest/googletest)

# Линкуем библиотеки с тестами и gtest
target_link_libraries(test_gallows
        gtest
        pthread)

# Добавляем тест в систему тестирования CMake
add_test(test_gallows test_gallows)

