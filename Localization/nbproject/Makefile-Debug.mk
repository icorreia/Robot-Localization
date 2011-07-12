#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=
AS=as.exe

# Macros
CND_PLATFORM=MinGW_1-Windows
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1363287317/MeanAndSDCalcs.o \
	${OBJECTDIR}/_ext/1363287317/Algorithms.o \
	${OBJECTDIR}/_ext/1363287317/Localizer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/MinGW_1-Windows/localization.exe

dist/Debug/MinGW_1-Windows/localization.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/MinGW_1-Windows
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/localization ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1363287317/MeanAndSDCalcs.o: ../C\ Files/MeanAndSDCalcs.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1363287317
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1363287317/MeanAndSDCalcs.o ../C\ Files/MeanAndSDCalcs.cpp

${OBJECTDIR}/_ext/1363287317/Algorithms.o: ../C\ Files/Algorithms.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1363287317
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1363287317/Algorithms.o ../C\ Files/Algorithms.cpp

${OBJECTDIR}/_ext/1363287317/Localizer.o: ../C\ Files/Localizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1363287317
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1363287317/Localizer.o ../C\ Files/Localizer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/MinGW_1-Windows/localization.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
