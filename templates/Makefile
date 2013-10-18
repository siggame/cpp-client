##First and last lines are a wrapper
##To make the rest of the file pop out as-is.
${"""\
sources = $(wildcard *.cpp) $(wildcard jsonCpp/src/*.cpp)
headers = $(wildcard *.h)
objects = $(sources:%.cpp=%.o)
CFLAGS += -g
CXXFLAGS += -g

#Uncomment this line to get a boatload of debug output.
#override CPPFLAGS += -DSHOW_WARNINGS

override CPPFLAGS += -IjsonCpp/include

all: client

client: $(objects)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^

clean:
	rm -f $(objects) client
"""}
