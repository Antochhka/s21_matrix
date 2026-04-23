CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
AR = ar
ARFLAGS = rcs
LDFLAGS = -lcheck -lm -lrt -pthread -lsubunit
CORE_DIR=core
SOURCES=$(wildcard $(CORE_DIR)/*.c)
OBJECTS=$(SOURCES:.c=.o)
LIBRARY=s21_matrix.a
TESTS=test_matrix

LDFLAGS += -lcheck -lm -lrt -pthread -lsubunit

TEST_SOURCES = $(wildcard tests/*.c)

# Object files for tests
TEST_OBJS = $(TEST_SOURCES:.c=.o)

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

$(CORE_DIR)/%.o: $(CORE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJS) $(LIBRARY)
	$(CC) $(CFLAGS) -o $(TESTS) $(TEST_OBJS) $(LIBRARY) $(LDFLAGS)
tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
# Добавим новую переменную для тестового исполняемого файла с gcov флагами
GCOV_TESTS=gcov_test_matrix

# Цель для сборки тестов с gcov флагами
gcov_test: CFLAGS += $(GCOV_FLAGS)
gcov_test: LDFLAGS += $(GCOV_FLAGS)
gcov_test: clean $(LIBRARY) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(GCOV_TESTS) $(TEST_OBJS) $(LIBRARY) $(LDFLAGS)
	rm -f $(TEST_OBJS)

# Цель отчёта gcov
gcov_report: gcov_test clean
	./$(GCOV_TESTS)
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '/usr/*' 'tests/*' --ignore-errors unused --output-file coverage_filtered.info
	genhtml coverage_filtered.info --output-directory gcov_report
	@echo "Отчёт gcov сгенерирован в gcov_report"

valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TESTS)

format:
	clang-format -i $(CORE_DIR)/*.c tests/*.c

clean:
	rm -f $(OBJECTS) $(LIBRARY) $(TEST_OBJS) $(TESTS) $(CORE_DIR)/*.gcno  $(CORE_DIR)/*.gcda tests/*.gcno tests/*.gcda


.PHONY: all clean test