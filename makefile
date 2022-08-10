SRCDIR := ${CURDIR}/src/
OBJDIR := ${CURDIR}/obj/
BINDIR := ${CURDIR}/bin/
COMPILE_OPTS := -std=c++11

FILES := \
	base64Converter \
	ArgsParser \
	Argument \
	InteractiveInputFunctor \
	FileInputFunctor \
	BlockConverter \
	ANSI_CODES \
	ConverterEncodeInteractiveCommand \
	ConverterEncodeFileCommand \
	ConverterDecodeCommand \
	ConverterImplementation \
	ErrorHandler

OBJS := $(addsuffix .o,$(addprefix $(OBJDIR),$(FILES)))
HEADERS := $(addsuffix .h,$(addprefix $(SRCDIR),$(filter-out base64Converter,$(FILES))))
SRCS := $(addsuffix .cpp,$(addprefix $(SRCDIR),$(FILES)))

CXX_FLAGS += $(COMPILE_OPTS)


.PHONY: all
all: tool

.PHONY: tool
tool: $(OBJS) | $(BINDIR)
	$(CXX) -o $(BINDIR)base64 $^

$(OBJDIR)%.o: $(SRCDIR)%.cpp | $(OBJDIR) $(SRCDIR)
	$(CXX) $(CXX_FLAGS) -o $@ -c $<

$(SRCDIR):
	@if ! ([ -e "$(SRCDIR)" ]); then \
		mkdir $(SRCDIR); \
	fi

$(OBJDIR):
	@if ! ([ -e "$(OBJDIR)" ]); then \
		mkdir $(OBJDIR); \
	fi

$(BINDIR):
	@if ! ([ -e "$(BINDIR)" ]); then \
		mkdir $(BINDIR); \
	fi