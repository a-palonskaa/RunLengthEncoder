CC = g++
CFLAGS = -c -Wall -std=c++17 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations           \
					-Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy     \
					-Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2     \
					-Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith       \
					-Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo           \
					-Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef   \
					-Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-range                \
					-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs \
					-Wstack-protector -Wsuggest-override -Wbounds-attributes-redundant -Wlong-long  \
					-Wopenmp -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow   \
					-fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-protector -fPIE -Werror=vla
LDFLAGS =

BASE85_DIR = base85
NI_DIR     = naive_implementation
SSO_DIR    = small_sequence_optimization
MAIN_DIR   = main
BUILD_DIR  = build

SOURCES_BASE85 = text_decode_base85.cpp text_encode_base85.cpp
SOURCES_NI     = text_decode_naive_implementation.cpp text_encode_naive_implementation.cpp
SOURCES_SSO    = text_decode_sso.cpp text_encode_sso.cpp
SOURCES_MAIN   = main.cpp arg_parser.cpp

SOURCES_BASE85 := $(addprefix $(BASE85_DIR)/, $(SOURCES_BASE85))
SOURCES_NI     := $(addprefix $(NI_DIR)/, $(SOURCES_NI))
SOURCES_SSO    := $(addprefix $(SSO_DIR)/, $(SOURCES_SSO))
SOURCES_MAIN   := $(addprefix $(MAIN_DIR)/, $(SOURCES_MAIN))

SOURCES =  $(SOURCES_BASE85) $(SOURCES_NI) $(SOURCES_SSO) $(SOURCES_MAIN)
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:%.cpp=%.o))
DEPS 	= $(OBJECTS:.o=.d)

CFLAGS += -I$(MAIN_DIR)
CFLAGS += -I$(BASE85_DIR)
CFLAGS += -I$(NI_DIR)
CFLAGS += -I$(SSO_DIR)

EXECUTABLE = $(BUILD_DIR)/run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPS): $(BUILD_DIR)/%.d: %.cpp
	@mkdir -p $(@D)
	$(CC) -E $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

NODEPS = clean

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif
