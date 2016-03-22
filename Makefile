PWD=$(shell pwd)
CGI_PATH=$(PWD)/cgi_bin
SER_BIN=httpd
CLI_BIN=demon_client
SER_SRC=httpd.c
CLI_SRC=demon_client.c
INCLUDE=.
CC=gcc
FLAGS=-o
LDFLAGS=-lpthread#static
LIB=

.PHONY:all
all:$(SER_BIN) $(CLI_BIN)

$(SER_BIN):$(SER_SRC)
	@$(CC) $(FLAGS) $@ $^ $(LDFLAGS) -gdwarf-2 -D_DEBUG_
$(CLI_BIN):$(CLI_SRC)
	@$(CC) $(FLAGS) $@ $^ $(LDFLAGS)

.PHONY:cgi
cgi:
	@for name in `echo $(CGI_PATH)`;\
	do\
	       cd $$name;\
		   make;\
		   cd -;\
	done

.PHONY:output
output:all
	@makidr -p output/htdocs/cgi_bin
	@cp httpd output
	@cp demon_client output
	@cp -rf conf output
	@cp -rf log output
	@cp start.sh output
	@cp -rf htdocs/* output/htdocs
	@for name in `echo $(CGI_PATH)`;\
	do\
	cd  $$name;\
		make output;\
		cd -;\
	done
.PHONY:clean
clean:
	@rm -rf $(SER_BIN) $(CLI_BIN) output
	@for name in `echo $(CGI_PATH)`;\
	do\
		cd $$name;\
		make clean;\
		cd -;\
	done
