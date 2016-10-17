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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/60843d1b/catch.o \
	${OBJECTDIR}/_ext/511e4115/ksp_math.o \
	${OBJECTDIR}/_ext/511e4115/parts.o \
	${OBJECTDIR}/_ext/217750e/rocket.o \
	${OBJECTDIR}/_ext/d2aa2781/test_ksp_math.o \
	${OBJECTDIR}/_ext/d2aa2781/test_rocket.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ksp_utils_nb.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ksp_utils_nb.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ksp_utils_nb ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/60843d1b/catch.o: ../../catch/catch.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/60843d1b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/60843d1b/catch.o ../../catch/catch.cpp

${OBJECTDIR}/_ext/511e4115/ksp_math.o: ../src/ksp_math.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/ksp_math.o ../src/ksp_math.cpp

${OBJECTDIR}/_ext/511e4115/parts.o: ../src/parts.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/parts.o ../src/parts.cpp

${OBJECTDIR}/_ext/217750e/rocket.o: ../src/rocket/rocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217750e
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/217750e/rocket.o ../src/rocket/rocket.cpp

${OBJECTDIR}/_ext/d2aa2781/test_ksp_math.o: ../test/test_ksp_math.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2aa2781
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2aa2781/test_ksp_math.o ../test/test_ksp_math.cpp

${OBJECTDIR}/_ext/d2aa2781/test_rocket.o: ../test/test_rocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/d2aa2781
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d2aa2781/test_rocket.o ../test/test_rocket.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ksp_utils_nb.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
