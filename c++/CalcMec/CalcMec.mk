##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=CalcMec
ConfigurationName      :=Release
WorkspacePath          :=/home/alan/Dropbox/git/calc_mec/c++
ProjectPath            :=/home/alan/Dropbox/git/calc_mec/c++/CalcMec
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Alan
Date                   :=03/20/18
CodeLitePath           :=/home/alan/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="CalcMec.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS := -lboost_iostreams -lboost_system -lboost_filesystem -lboost_thread -march=native -O2 -DNDEBUG -std=c++14 -Wall -DARMA_NO_DEBUG $(Preprocessors)
CFLAGS   :=  -O2 -Wall  $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/GeraGrafico.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/ParserXML.cpp$(ObjectSuffix) $(IntermediateDirectory)/FuncoesMec.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/GeraGrafico.cpp$(ObjectSuffix): GeraGrafico.cpp $(IntermediateDirectory)/GeraGrafico.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alan/Dropbox/git/calc_mec/c++/CalcMec/GeraGrafico.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GeraGrafico.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GeraGrafico.cpp$(DependSuffix): GeraGrafico.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GeraGrafico.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GeraGrafico.cpp$(DependSuffix) -MM GeraGrafico.cpp

$(IntermediateDirectory)/GeraGrafico.cpp$(PreprocessSuffix): GeraGrafico.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GeraGrafico.cpp$(PreprocessSuffix) GeraGrafico.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alan/Dropbox/git/calc_mec/c++/CalcMec/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/ParserXML.cpp$(ObjectSuffix): ParserXML.cpp $(IntermediateDirectory)/ParserXML.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alan/Dropbox/git/calc_mec/c++/CalcMec/ParserXML.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ParserXML.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ParserXML.cpp$(DependSuffix): ParserXML.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ParserXML.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ParserXML.cpp$(DependSuffix) -MM ParserXML.cpp

$(IntermediateDirectory)/ParserXML.cpp$(PreprocessSuffix): ParserXML.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ParserXML.cpp$(PreprocessSuffix) ParserXML.cpp

$(IntermediateDirectory)/FuncoesMec.cpp$(ObjectSuffix): FuncoesMec.cpp $(IntermediateDirectory)/FuncoesMec.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/alan/Dropbox/git/calc_mec/c++/CalcMec/FuncoesMec.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FuncoesMec.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FuncoesMec.cpp$(DependSuffix): FuncoesMec.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FuncoesMec.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FuncoesMec.cpp$(DependSuffix) -MM FuncoesMec.cpp

$(IntermediateDirectory)/FuncoesMec.cpp$(PreprocessSuffix): FuncoesMec.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FuncoesMec.cpp$(PreprocessSuffix) FuncoesMec.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


