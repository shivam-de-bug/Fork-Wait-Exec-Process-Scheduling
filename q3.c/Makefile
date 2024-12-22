com = gcc

flags =  -O2 -Wno-unused-parameter

pro = date cal uptime main

all: date cal uptime main
main: date cal uptime

%: %.c
	$(com) $(flags) -o $@ $<

clean:
	rm -f $(pro)