PROJECT_NAME=MeasurementSeries

CFLAGS=-Wall -Werror -ggdb -O0 -Iproduct

SHARED_SOURCES=product/$(PROJECT_NAME).cpp

MAIN_SOURCES=product/main.cpp \
			 product/menu.cpp \
             $(SHARED_SOURCES)

TEST_SOURCES=test/$(PROJECT_NAME)Test.cpp \
             $(SHARED_SOURCES)

TEST_LIBS=-lgtest -lgtest_main -lpthread

GCC=g++

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(MAIN_SOURCES) Makefile product/*.h
	@$(GCC) $(CFLAGS) $(MAIN_SOURCES) -o $@

$(PROJECT_NAME)Test: $(TEST_SOURCES) Makefile product/*.h
	@$(GCC) $(CFLAGS) $(TEST_SOURCES) -o $@ $(TEST_LIBS) -Itest

clean:
	@rm -rf $(PROJECT_NAME)Test $(PROJECT_NAME)

test: $(PROJECT_NAME)Test
	@./$(PROJECT_NAME)Test
