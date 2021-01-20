CC = gcc
TARGET    := $(notdir $(CURDIR))
BUILD     := build
OUT       := out
SOURCES   := src
INCLUDES  := include


#----------------------------------------------------------------------
# Languages Standard
#----------------------------------------------------------------------
C_STANDARD   := -std=c11

#----------------------------------------------------------------------
# Defined Symbols
#----------------------------------------------------------------------
DEFINES += -DDEBUG
DEFINES += -DENABLE_LOGGING

#----------------------------------------------------------------------
# Sources & Files
#----------------------------------------------------------------------
OUTPUT    := $(CURDIR)/$(OUT)/$(TARGET)
SYMBOLS   := $(CURDIR)/$(BUILD)/$(TARGET).out

CSOURCES   := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))

OBJS       := $(patsubst %,$(BUILD)/%.o,$(basename $(CSOURCES)))
DEPS       := $(patsubst %,$(BUILD)/%.d,$(basename $(CSOURCES)))

INCLUDE    += $(addprefix -I,$(foreach dir,$(INCLUDES), $(wildcard $(dir))))
INCLUDE    += $(addprefix -I,$(foreach dir,$(LIBRARIES),$(wildcard $(dir)/include)))

CXXFLAGS = -O3 -Wall 

.PHONY: all clean help

FLAGS := -lm

#----------------------------------------------------------------------
# Targets
#----------------------------------------------------------------------

all: compile

run: $(OUTPUT)
	@$<

compile: ${SOURCES}/*.c
	@mkdir -p $(OUT)
	$(CC) $(FLAGS) -g ${SOURCES}/*.c -o ${OUT}/${TARGET}

clean:
	@$(RM) -r $(BUILD) $(OUT)

help:
	@echo available targets: all compile run clean