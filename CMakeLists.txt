cmake_minimum_required(VERSION 3.10)
project(SudokuSolver)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 14)

# Ajouter le répertoire des fichiers d'en-tête
include_directories(include)

# Ajouter les fichiers source
add_executable(SudokuSolver main.cpp)
add_subdirectory(src)
target_link_libraries(SudokuSolver sudokuSrc)


# Activer les tests
#enable_testing()

# Ajouter Google Test
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# # Ajouter le fichier de test
# add_executable(TESTS test/test.cpp)
# target_link_libraries(TESTS md5)
# target_link_libraries(TESTS ${GTEST_LIBRARIES} pthread)

# # Ajouter un test
# add_test(NAME MD5 COMMAND TESTS)
