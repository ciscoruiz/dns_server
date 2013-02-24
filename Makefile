VIEWER=@

# synthesizer.db/synthesizer.Executable.cc (35)
OBJECT_NAME=server

# synthesizer.db/synthesizer.SourceContainer.cc (134)
# include makefile.x.env

# synthesizer.db/synthesizer.SourceContainer.cc (154)

# Programas usandos habitualmente
#
AS=/usr/bin/as
LD=/usr/bin/ld

AR=/usr/bin/ar
AR_FLAGS=cr

# Se indica de forma independiente para dar la posibilidad de
# eliminar su valor.
USER_CPP_FLAG_RTTI=

LIBS=-lrt
LD_FLAGS=

CC=gcc
CPP=g++
LINKER=$(CPP)
LINKER_OUTPUT_INDICATOR=-o

CC_USE_AR=true
CC_NEED_CHMOD=false

CPP_FLAGS = -D__linux__ -D_REENTRANT -DLINUX -Wreturn-type -D DEBUG -g -finline-functions

LIBRARY_EXTENSION=.a

# synthesizer.db/synthesizer.SourceContainer.cc (157)
# include $(BASEPJ)/tune_project.x.config

# synthesizer.db/synthesizer.SourceContainer.cc (165)
# include makefile.x.config

# synthesizer.db/synthesizer.SourceContainer.cc (224)
OBJECT_LIST= rfc1035.db/Debug.X/rfc1035.AnswerSection.o \
	rfc1035.db/Debug.X/rfc1035.Header.o \
	rfc1035.db/Debug.X/rfc1035.Query.o \
	rfc1035.db/Debug.X/rfc1035.QuestionSection.o \
	rfc1035.db/Debug.X/rfc1035.Response.o \
	Debug.X/server.Application.o \
	Debug.X/server.DataBlock.o \
	Debug.X/server.DatagramSocket.o \
	Debug.X/server.Exception.o \
	Debug.X/server.Logger.o \
	Debug.X/server.Resolver.o \
	Debug.X/server.functions.o \
	Debug.X/server.main.o

# synthesizer.db/synthesizer.SourceContainer.cc (291)
.PHONY : all
all : ../Debug.X Debug.X rfc1035.db/Debug.X $(OBJECT_NAME) 

# synthesizer.db/synthesizer.Structure.cc (205)
.PHONY : clean
clean : 
	@echo eliminado Debug.X ...
	@find . -name "Debug.X" -exec rm -rf {} \; -depth -print
	@rm -f $(OBJECT_NAME)

# synthesizer.db/synthesizer.SourceContainer.cc (432)
%.X: 
	@if [ ! -d $@ ] ; then mkdir $@; fi ;

# synthesizer.db/synthesizer.Executable.cc (47)
$(OBJECT_NAME) : $(USER_LIBS) $(OBJECT_LIST)
	@echo; echo Generando ejecutable $@ ...
	$(VIEWER)$(LINKER) $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(LINKER_OUTPUT_INDICATOR) $(OBJECT_NAME) $(OBJECT_LIST) $(USER_LIBS) $(SYSTEM_LIBS) $(LD_FLAGS) $(LIBS)

# synthesizer.db/synthesizer.Executable.cc (53)
rfc1035.db/Debug.X/rfc1035.AnswerSection.o : rfc1035.db/rfc1035.AnswerSection.cc \
	include/dns.server.functions.h \
	include/dns.server.Logger.h \
	include/dns.server.DataBlock.h \
	include/dns.server.Exception.h \
	include/dns.server.defines.h \
	rfc1035.db/include/dns.server.rfc1035.MessageBody.h \
	rfc1035.db/include/dns.server.rfc1035.AnswerSection.h \
	rfc1035.db/include/dns.server.rfc1035.QuestionSection.h
	@printf "%s$(GMAKE_EOL)" rfc1035.db/rfc1035.AnswerSection.cc
	$(VIEWER)$(CPP) -c rfc1035.db/rfc1035.AnswerSection.cc -Iinclude -Irfc1035.db/include  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
rfc1035.db/Debug.X/rfc1035.Header.o : rfc1035.db/rfc1035.Header.cc \
	include/dns.server.functions.h \
	include/dns.server.DataBlock.h \
	include/dns.server.autoenum.h \
	include/dns.server.Exception.h \
	include/dns.server.defines.h \
	rfc1035.db/include/dns.server.rfc1035.MessageBody.h \
	rfc1035.db/include/dns.server.rfc1035.Header.h
	@printf "%s$(GMAKE_EOL)" rfc1035.db/rfc1035.Header.cc
	$(VIEWER)$(CPP) -c rfc1035.db/rfc1035.Header.cc -Iinclude -Irfc1035.db/include  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
rfc1035.db/Debug.X/rfc1035.Query.o : rfc1035.db/rfc1035.Query.cc \
	include/dns.server.functions.h \
	include/dns.server.Logger.h \
	include/dns.server.DataBlock.h \
	include/dns.server.autoenum.h \
	include/dns.server.Exception.h \
	include/dns.server.defines.h \
	rfc1035.db/include/dns.server.rfc1035.Query.h \
	rfc1035.db/include/dns.server.rfc1035.MessageBody.h \
	rfc1035.db/include/dns.server.rfc1035.Header.h \
	rfc1035.db/include/dns.server.rfc1035.QuestionSection.h
	@printf "%s$(GMAKE_EOL)" rfc1035.db/rfc1035.Query.cc
	$(VIEWER)$(CPP) -c rfc1035.db/rfc1035.Query.cc -Iinclude -Irfc1035.db/include  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
rfc1035.db/Debug.X/rfc1035.QuestionSection.o : rfc1035.db/rfc1035.QuestionSection.cc \
	include/dns.server.functions.h \
	include/dns.server.Logger.h \
	include/dns.server.DataBlock.h \
	include/dns.server.Exception.h \
	include/dns.server.defines.h \
	rfc1035.db/include/dns.server.rfc1035.MessageBody.h \
	rfc1035.db/include/dns.server.rfc1035.QuestionSection.h
	@printf "%s$(GMAKE_EOL)" rfc1035.db/rfc1035.QuestionSection.cc
	$(VIEWER)$(CPP) -c rfc1035.db/rfc1035.QuestionSection.cc -Iinclude -Irfc1035.db/include  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
rfc1035.db/Debug.X/rfc1035.Response.o : rfc1035.db/rfc1035.Response.cc \
	rfc1035.db/include/dns.server.rfc1035.Response.h \
	include/dns.server.Logger.h \
	include/dns.server.DataBlock.h \
	include/dns.server.autoenum.h \
	include/dns.server.Exception.h \
	include/dns.server.defines.h \
	rfc1035.db/include/dns.server.rfc1035.MessageBody.h \
	rfc1035.db/include/dns.server.rfc1035.AnswerSection.h \
	rfc1035.db/include/dns.server.rfc1035.Header.h \
	rfc1035.db/include/dns.server.rfc1035.QuestionSection.h
	@printf "%s$(GMAKE_EOL)" rfc1035.db/rfc1035.Response.cc
	$(VIEWER)$(CPP) -c rfc1035.db/rfc1035.Response.cc -Irfc1035.db/include -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
Debug.X/server.Application.o : server.Application.cc \
	rfc1035.db/include/dns.server.rfc1035.Response.h \
	include/dns.server.Logger.h \
	include/dns.server.DataBlock.h \
	include/dns.server.Application.h \
	include/dns.server.autoenum.h \
	include/dns.server.Exception.h \
	include/dns.server.DatagramSocket.h \
	include/dns.server.defines.h \
	rfc1035.db/include/dns.server.rfc1035.Query.h \
	rfc1035.db/include/dns.server.rfc1035.MessageBody.h \
	rfc1035.db/include/dns.server.rfc1035.AnswerSection.h \
	include/dns.server.SingleList.h \
	include/dns.server.Resolver.h \
	rfc1035.db/include/dns.server.rfc1035.Header.h \
	rfc1035.db/include/dns.server.rfc1035.QuestionSection.h
	@printf "%s$(GMAKE_EOL)" server.Application.cc
	$(VIEWER)$(CPP) -c server.Application.cc -Irfc1035.db/include -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
Debug.X/server.DataBlock.o : server.DataBlock.cc \
	include/dns.server.functions.h \
	include/dns.server.DataBlock.h \
	include/dns.server.Exception.h \
	include/dns.server.defines.h
	@printf "%s$(GMAKE_EOL)" server.DataBlock.cc
	$(VIEWER)$(CPP) -c server.DataBlock.cc -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
Debug.X/server.DatagramSocket.o : server.DatagramSocket.cc \
	include/dns.server.functions.h \
	include/dns.server.Logger.h \
	include/dns.server.DataBlock.h \
	include/dns.server.Exception.h \
	include/dns.server.DatagramSocket.h \
	include/dns.server.defines.h
	@printf "%s$(GMAKE_EOL)" server.DatagramSocket.cc
	$(VIEWER)$(CPP) -c server.DatagramSocket.cc -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
Debug.X/server.Exception.o : server.Exception.cc \
	include/dns.server.Logger.h \
	include/dns.server.Exception.h
	@printf "%s$(GMAKE_EOL)" server.Exception.cc
	$(VIEWER)$(CPP) -c server.Exception.cc -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
Debug.X/server.Logger.o : server.Logger.cc \
	include/dns.server.functions.h \
	include/dns.server.Logger.h \
	include/dns.server.DataBlock.h \
	include/dns.server.Exception.h \
	include/dns.server.defines.h
	@printf "%s$(GMAKE_EOL)" server.Logger.cc
	$(VIEWER)$(CPP) -c server.Logger.cc -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
Debug.X/server.Resolver.o : server.Resolver.cc \
	include/dns.server.functions.h \
	include/dns.server.Logger.h \
	include/dns.server.Exception.h \
	include/dns.server.defines.h \
	include/dns.server.SingleList.h \
	include/dns.server.Resolver.h
	@printf "%s$(GMAKE_EOL)" server.Resolver.cc
	$(VIEWER)$(CPP) -c server.Resolver.cc -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
Debug.X/server.functions.o : server.functions.cc \
	include/dns.server.functions.h \
	include/dns.server.DataBlock.h \
	include/dns.server.Exception.h \
	include/dns.server.defines.h
	@printf "%s$(GMAKE_EOL)" server.functions.cc
	$(VIEWER)$(CPP) -c server.functions.cc -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
Debug.X/server.main.o : server.main.cc \
	include/dns.server.Application.h \
	include/dns.server.Exception.h
	@printf "%s$(GMAKE_EOL)" server.main.cc
	$(VIEWER)$(CPP) -c server.main.cc -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


FORCE:

