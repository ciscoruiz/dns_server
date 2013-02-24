# 
# Archivo generado automaticamente con SmartTools.Generate Version 11.10.05.5/Evo-X/iMT/O/Linux 2.6 (i686)
# Componente: rfc1035.db
# Documento Configuracion:
#   /home/cisco/Develop/tools/SmartTools/v11/10.05//data/config.xml version 11.10.05.02
# 
# synthesizer.db/synthesizer.Structure.cc (122)
# include $(BASEPJ)/project.x.config

EXTERNAL_TEST=0
VIEWER=@

# synthesizer.db/synthesizer.LogicalGroup.cc (35)
OBJECT_NAME=$(OBJECT_LIST)

# synthesizer.db/synthesizer.SourceContainer.cc (131)
OTHER_USER_RULES=$(GMAKE_HOME)/data/empty.include

# synthesizer.db/synthesizer.SourceContainer.cc (134)
# include ../makefile.x.env

# synthesizer.db/synthesizer.SourceContainer.cc (154)
include $(GMAKE_CONFIG)/this.include
include $(GMAKE_CONFIG)/cppcompiler/$(GMAKE_CPPCOMPILER)/this.include
include $(GMAKE_CONFIG)/cppcompiler/$(GMAKE_CPPCOMPILER)/release/$(GMAKE_RELEASE).include
include $(GMAKE_CONFIG)/cppcompiler/$(GMAKE_CPPCOMPILER)/threading/$(GMAKE_THREADING).include
include $(GMAKE_CONFIG)/cppcompiler/$(GMAKE_CPPCOMPILER)/tidtools/$(GMAKE_TIDTOOLS).include
include $(GMAKE_CONFIG)/cppcompiler/$(GMAKE_CPPCOMPILER)/library/$(GMAKE_LIBRARY).include
include $(GMAKE_CONFIG)/xml/$(GMAKE_XML).include
include $(GMAKE_CONFIG)/ssl/$(GMAKE_SSL).include
include $(GMAKE_CONFIG)/ldap/$(GMAKE_LDAP).include
include $(GMAKE_CONFIG)/asn1/$(GMAKE_ASN1).include
include $(GMAKE_CONFIG)/rdbms/$(GMAKE_RDBMS).include
include $(GMAKE_CONFIG)/ss7/$(GMAKE_SS7).include
include $(GMAKE_CONFIG)/soap/$(GMAKE_SOAP).include

# synthesizer.db/synthesizer.SourceContainer.cc (157)
# include $(BASEPJ)/tune_project.x.config

# synthesizer.db/synthesizer.SourceContainer.cc (165)
# include ../makefile.x.config

# synthesizer.db/synthesizer.SourceContainer.cc (224)
OBJECT_LIST=$(OTHER_USER_OBJECTS) \
	.$(GMAKE_TARGET).X/rfc1035.AnswerSection.o \
	.$(GMAKE_TARGET).X/rfc1035.Header.o \
	.$(GMAKE_TARGET).X/rfc1035.Query.o \
	.$(GMAKE_TARGET).X/rfc1035.QuestionSection.o \
	.$(GMAKE_TARGET).X/rfc1035.Response.o

# synthesizer.db/synthesizer.SourceContainer.cc (291)
all : ../.$(GMAKE_TARGET).X .$(GMAKE_TARGET).X $(OTHER_USER_DEPENDENCES)  \
	$(OBJECT_NAME)

# synthesizer.db/synthesizer.Structure.cc (205)
.PHONY : clobber
clobber : 
	@echo eliminado .$(GMAKE_TARGET).X ...
	@find . -name ".$(GMAKE_TARGET).X" -exec rm -rf {} \; -depth -print
	@rm -f $(OBJECT_NAME)

# synthesizer.db/synthesizer.SourceContainer.cc (432)
%.X: 
	@if [ ! -d $@ ] ; then mkdir $@; fi ;

# synthesizer.db/synthesizer.Command.cc (82)
.$(GMAKE_TARGET).X/rfc1035.AnswerSection.o : rfc1035.AnswerSection.cc \
	$(MYPJ)/server.p/include/dns.server.functions.h \
	$(MYPJ)/server.p/include/dns.server.Logger.h \
	$(MYPJ)/server.p/include/dns.server.DataBlock.h \
	$(MYPJ)/server.p/include/dns.server.Exception.h \
	$(MYPJ)/server.p/include/dns.server.defines.h \
	include/dns.server.rfc1035.MessageBody.h \
	include/dns.server.rfc1035.AnswerSection.h \
	include/dns.server.rfc1035.QuestionSection.h
	@printf "%s$(GMAKE_EOL)" rfc1035.AnswerSection.cc
	$(VIEWER)$(CPP) -c rfc1035.AnswerSection.cc -I$(MYPJ)/server.p/include -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
.$(GMAKE_TARGET).X/rfc1035.Header.o : rfc1035.Header.cc \
	$(MYPJ)/server.p/include/dns.server.functions.h \
	$(MYPJ)/server.p/include/dns.server.DataBlock.h \
	$(MYPJ)/server.p/include/dns.server.autoenum.h \
	$(MYPJ)/server.p/include/dns.server.Exception.h \
	$(MYPJ)/server.p/include/dns.server.defines.h \
	include/dns.server.rfc1035.MessageBody.h \
	include/dns.server.rfc1035.Header.h
	@printf "%s$(GMAKE_EOL)" rfc1035.Header.cc
	$(VIEWER)$(CPP) -c rfc1035.Header.cc -I$(MYPJ)/server.p/include -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
.$(GMAKE_TARGET).X/rfc1035.Query.o : rfc1035.Query.cc \
	$(MYPJ)/server.p/include/dns.server.functions.h \
	$(MYPJ)/server.p/include/dns.server.Logger.h \
	$(MYPJ)/server.p/include/dns.server.DataBlock.h \
	$(MYPJ)/server.p/include/dns.server.autoenum.h \
	$(MYPJ)/server.p/include/dns.server.Exception.h \
	$(MYPJ)/server.p/include/dns.server.defines.h \
	include/dns.server.rfc1035.Query.h \
	include/dns.server.rfc1035.MessageBody.h \
	include/dns.server.rfc1035.Header.h \
	include/dns.server.rfc1035.QuestionSection.h
	@printf "%s$(GMAKE_EOL)" rfc1035.Query.cc
	$(VIEWER)$(CPP) -c rfc1035.Query.cc -I$(MYPJ)/server.p/include -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
.$(GMAKE_TARGET).X/rfc1035.QuestionSection.o : rfc1035.QuestionSection.cc \
	$(MYPJ)/server.p/include/dns.server.functions.h \
	$(MYPJ)/server.p/include/dns.server.Logger.h \
	$(MYPJ)/server.p/include/dns.server.DataBlock.h \
	$(MYPJ)/server.p/include/dns.server.Exception.h \
	$(MYPJ)/server.p/include/dns.server.defines.h \
	include/dns.server.rfc1035.MessageBody.h \
	include/dns.server.rfc1035.QuestionSection.h
	@printf "%s$(GMAKE_EOL)" rfc1035.QuestionSection.cc
	$(VIEWER)$(CPP) -c rfc1035.QuestionSection.cc -I$(MYPJ)/server.p/include -Iinclude  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


# synthesizer.db/synthesizer.Command.cc (82)
.$(GMAKE_TARGET).X/rfc1035.Response.o : rfc1035.Response.cc \
	include/dns.server.rfc1035.Response.h \
	$(MYPJ)/server.p/include/dns.server.Logger.h \
	$(MYPJ)/server.p/include/dns.server.DataBlock.h \
	$(MYPJ)/server.p/include/dns.server.autoenum.h \
	$(MYPJ)/server.p/include/dns.server.Exception.h \
	$(MYPJ)/server.p/include/dns.server.defines.h \
	include/dns.server.rfc1035.MessageBody.h \
	include/dns.server.rfc1035.AnswerSection.h \
	include/dns.server.rfc1035.Header.h \
	include/dns.server.rfc1035.QuestionSection.h
	@printf "%s$(GMAKE_EOL)" rfc1035.Response.cc
	$(VIEWER)$(CPP) -c rfc1035.Response.cc -Iinclude -I$(MYPJ)/server.p/include  $(USER_INCLUDES) $(SYSTEM_INCLUDES) -o $@ $(CPP_DEBUG_INDICATOR) $(CPP_FLAGS) $(USER_CPP_FLAGS) $(USER_CPP_FLAG_RTTI) -DSmartTools_10_0 


FORCE:

# synthesizer.db/synthesizer.SourceContainer.cc (355)
include $(OTHER_USER_RULES)

