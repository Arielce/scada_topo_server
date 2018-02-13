.SUFFIXES: .idl .cpp .o


PROGRAM = test_graph

OBJECTS = CModel.o\
	  CGraph.o\
	  test.o\
          CPropertyReader.o\
          CPropertyReaderImpl.o \
          CTopoAlg.o \
          CScadaAlg.o \
          CUDataValue.o \
          CModelRtLoader.o\
          CModelLoaderFactory.o\
          CGraphManager.o \
          CModelContainer.o \
          CRtModelContainer.o \
          CConfigurationInfo.o
OBJ_EXT =


CC	= `makeopts.sh cc`
CCFLAGS = `makeopts.sh ccflag pi_inc` -I/home/d5000/qt484/include/QtCore -I/home/d5000/qt484/include/QtXml -I/home/d5000/qt484/include
LDFLAGS = `makeopts.sh ldflag` -L/home/d5000/qt484/lib
LIBS	= `makeopts.sh syslib pub odb_api pi_app_lib` -lQtCore -lQtXml
#LIBS	= `makeopts.sh syslib pub sam odb_api corba_lib cwrap pi_app_lib` -ldb_commit_client -lsave_sql -lsca_common -lm -lrte -lcomm
# Valid LIBS args: syslib odb_api sam para msg marshal_lib corba_lib odb_net socket $(DATABASE)_lib`
BIN_PATH = `makeopts.sh bin_path`

.idl.cpp:
	@echo	$(IDL_CC) $<
	@	$(IDL_CC) $<


.cpp.o:
	@echo	$(CC) $(CCFLAGS) $<
	@	$(CC) $(CCFLAGS) $<

$(PROGRAM): $(OBJECTS) $(OBJ_EXT)
	@echo	$(CC) -o $(PROGRAM)  $(OBJECTS) $(OBJ_EXT) $(LDFLAGS) $(LIBS) 
	@	$(CC) -o $(PROGRAM)  $(OBJECTS) $(OBJ_EXT) $(LDFLAGS) $(LIBS) 
	@echo	cp -pf $(PROGRAM) $(BIN_PATH)
	@	cp -pf $(PROGRAM) $(BIN_PATH)


# optional part

RM 	= rm -f

clean:
	$(RM) $(PROGRAM) $(OBJECTS)

cleano:
	$(RM) $(OBJECTS)

cleanp:
	$(RM) $(PROGRAM)

