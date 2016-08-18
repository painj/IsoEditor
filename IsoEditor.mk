##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=IsoEditor
ConfigurationName      :=Debug
WorkspacePath          :=/home/pain/src/IsoWS
ProjectPath            :=/home/pain/src/IsoWS/IsoEditor
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Pain
Date                   :=17/08/16
CodeLitePath           :=/home/pain/.codelite
LinkerName             :=/usr/bin/clang++
SharedObjectLinkerName :=/usr/bin/clang++ -shared -fPIC
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
OutputFile             :=./$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="IsoEditor.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)/usr/local/include $(IncludeSwitch)/usr/local/include/SDL2 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)SDL2 $(LibrarySwitch)SDL2main $(LibrarySwitch)SDL2_image $(LibrarySwitch)SDL2 $(LibrarySwitch)SDL2main $(LibrarySwitch)SDL2_image $(LibrarySwitch)SDL2_ttf 
ArLibs                 :=  "SDL2" "SDL2main" "SDL2_image" "SDL2" "SDL2main" "SDL2_image" "SDL2_ttf" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local/lib $(LibraryPathSwitch)/usr/local/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/clang++
CC       := /usr/bin/clang
CXXFLAGS := -O0 -W -std=c++11 -g -O0 -std=c++11 -Wall $(Preprocessors)
CFLAGS   := -std=c++11 -g -O0 -std=c++11 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/layout.cpp$(ObjectSuffix) $(IntermediateDirectory)/editor.cpp$(ObjectSuffix) $(IntermediateDirectory)/clickcontrol.cpp$(ObjectSuffix) 



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
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pain/src/IsoWS/IsoEditor/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)main.cpp

$(IntermediateDirectory)/layout.cpp$(ObjectSuffix): layout.cpp $(IntermediateDirectory)/layout.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pain/src/IsoWS/IsoEditor/layout.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/layout.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/layout.cpp$(DependSuffix): layout.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/layout.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/layout.cpp$(DependSuffix) -MM layout.cpp

$(IntermediateDirectory)/layout.cpp$(PreprocessSuffix): layout.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/layout.cpp$(PreprocessSuffix)layout.cpp

$(IntermediateDirectory)/editor.cpp$(ObjectSuffix): editor.cpp $(IntermediateDirectory)/editor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pain/src/IsoWS/IsoEditor/editor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/editor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/editor.cpp$(DependSuffix): editor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/editor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/editor.cpp$(DependSuffix) -MM editor.cpp

$(IntermediateDirectory)/editor.cpp$(PreprocessSuffix): editor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/editor.cpp$(PreprocessSuffix)editor.cpp

$(IntermediateDirectory)/clickcontrol.cpp$(ObjectSuffix): clickcontrol.cpp $(IntermediateDirectory)/clickcontrol.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/pain/src/IsoWS/IsoEditor/clickcontrol.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/clickcontrol.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/clickcontrol.cpp$(DependSuffix): clickcontrol.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/clickcontrol.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/clickcontrol.cpp$(DependSuffix) -MM clickcontrol.cpp

$(IntermediateDirectory)/clickcontrol.cpp$(PreprocessSuffix): clickcontrol.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/clickcontrol.cpp$(PreprocessSuffix)clickcontrol.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


