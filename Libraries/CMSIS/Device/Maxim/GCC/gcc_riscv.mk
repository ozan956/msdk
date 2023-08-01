################################################################################
 # Copyright (C) 2023 Maxim Integrated Products, Inc., All Rights Reserved.
 #
 # Permission is hereby granted, free of charge, to any person obtaining a
 # copy of this software and associated documentation files (the "Software"),
 # to deal in the Software without restriction, including without limitation
 # the rights to use, copy, modify, merge, publish, distribute, sublicense,
 # and/or sell copies of the Software, and to permit persons to whom the
 # Software is furnished to do so, subject to the following conditions:
 #
 # The above copyright notice and this permission notice shall be included
 # in all copies or substantial portions of the Software.
 #
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 # OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 # MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 # IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 # OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 # ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 # OTHER DEALINGS IN THE SOFTWARE.
 #
 # Except as contained in this notice, the name of Maxim Integrated
 # Products, Inc. shall not be used except as stated in the Maxim Integrated
 # Products, Inc. Branding Policy.
 #
 # The mere transfer of this software does not imply any licenses
 # of trade secrets, proprietary technology, copyrights, patents,
 # trademarks, maskwork rights, or any other form of intellectual
 # property whatsoever. Maxim Integrated Products, Inc. retains all
 # ownership rights.
 #
 ###############################################################################

# The build directory
ifeq "$(BUILD_DIR)" ""
BUILD_DIR=$(CURDIR)/buildrv
endif

# Make sure VPATH has the location of any absolute paths given to SRCS
# This allows users to specify SRCS += /absolute/path/to/file.c to add a single file to the build
# without also having to add VPATH += /absolute/path/to
# This is necessary because we create our object file definitions with OBJS_NOPATH.
VPATH += $(sort $(abspath $(dir $(SRCS))))

# Create output object file names
SRCS_NOPATH := $(foreach NAME,$(SRCS),$(basename $(notdir $(NAME))).c)
OBJS_NOPATH := $(SRCS_NOPATH:.c=.o)
OBJS        := $(OBJS_NOPATH:%.o=$(BUILD_DIR)/%.o)

################################################################################

# Detect target OS
# windows : native windows
# windows_msys : MSYS2 on windows
# windows_cygwin : Cygwin on windows (legacy config from old sdk)
# linux : Any linux distro
# macos : MacOS
ifeq "$(_OS)" ""

ifeq "$(OS)" "Windows_NT"
_OS = windows

UNAME_RESULT := $(shell uname -s 2>&1)
# MSYS2 may be present on Windows.  In this case,
# linux utilities should be used.  However, the OS environment
# variable will still be set to Windows_NT since we configure
# MSYS2 to inherit from Windows by default.
# Here we'll attempt to call uname (only present on MSYS2)
# while routing stderr -> stdout to avoid throwing an error 
# if uname can't be found.
ifneq ($(findstring CYGWIN, $(UNAME_RESULT)), )
CYGWIN=True
_OS = windows_cygwin
endif

ifneq ($(findstring MSYS, $(UNAME_RESULT)), )
MSYS=True
_OS = windows_msys
endif

else # OS

UNAME_RESULT := $(shell uname -s)
ifeq "$(UNAME_RESULT)" "Linux"
_OS = linux
endif
ifeq "$(UNAME_RESULT)" "Darwin"
_OS = macos
endif

endif

endif

################################################################################
# Goals

# The default goal, which causes the example to be built.
.DEFAULT_GOAL :=
.PHONY: all
all: $(BUILD_DIR)
all: ${BUILD_DIR}/${PROJECT}.elf
all: $(BUILD_DIR)/project_defines.h

# Goal to build for release without debug
.PHONY: release
release: $(BUILD_DIR)
release: ${BUILD_DIR}/${PROJECT}.elf
release: ${BUILD_DIR}/${PROJECT}.srec
release: ${BUILD_DIR}/${PROJECT}.hex
release: ${BUILD_DIR}/${PROJECT}.bin
release: ${BUILD_DIR}/${PROJECT}.dasm

# The goal to build as a library
.PHONY: lib
lib: $(BUILD_DIR)
lib: ${BUILD_DIR}/${PROJECT}.a

# The goal to create the target directory.
.PHONY: mkbuildir
mkbuildir: $(BUILD_DIR)
$(BUILD_DIR):
	@echo -  MKDIR $(BUILD_DIR)
ifeq "$(_OS)" "windows"
# Make run on native Windows will yield C:/-like paths, but the mkdir commands needs
# paths with backslashes.
	@if not exist ${subst /,\,${BUILD_DIR}} mkdir ${subst /,\,${BUILD_DIR}}
else
	@mkdir -p ${BUILD_DIR}
endif

# The goal to clean out all the build products.
.PHONY: clean
clean:
	@echo -  RMDIR $(BUILD_DIR)
ifneq "$(_OS)" "windows"
	@rm -rf ${BUILD_DIR} ${wildcard *~}
else
	@if exist ${subst /,\,${BUILD_DIR}} rmdir /s /q ${subst /,\,${BUILD_DIR}}
endif

${BUILD_DIR}/${PROJECT}.elf: ${LIBS} ${OBJS} ${LINKERFILE}
${BUILD_DIR}/${PROJECT}.a: ${OBJS}

# Create a goal to exercise the library build dependencies
.PHONY: FORCE
FORCE:

# Include the automatically generated dependency files.
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${BUILD_DIR}/*.d} __dummy__
endif

################################################################################
# Get the operating system name.  If this is Cygwin, the .d files will be
# munged to convert c: into /cygdrive/c so that "make" will be happy with the
# auto-generated dependencies. Also if this is Cygwin, file paths for ARM GCC
# will be converted from /cygdrive/c to C:.
################################################################################

# Set the toolchain prefix.  Top-level makefiles can specify RISCV_PREFIX or
# PREFIX directly.  RISCV_PREFIX is given to improve dual-core projects
ifeq "$(RISCV_PREFIX)" ""
PREFIX ?= riscv-none-elf
else
PREFIX ?= $(RISCV_PREFIX)
endif

# Set absolute path to tools if TOOL_DIR is specified
ifneq "$(TOOL_DIR)" ""
PREFIX=$(TOOL_DIR)/$(PREFIX)
endif

# The command for calling the assembler
AS=${PREFIX}-as
# The command for calling the library archiver.
AR=${PREFIX}-ar
# The command for calling the linker.
LD=${PREFIX}-gcc
# The command for calling the compiler.
CC=${PREFIX}-gcc
CXX=${PREFIX}-g++
# The command for extracting images from the linked executables.
OBJCOPY=${PREFIX}-objcopy
OBJDUMP=${PREFIX}-objdump

# Discover if we are using GCC > 4.8.0
GCCVERSIONGTEQ4 := 1
# GCCVERSIONGTEQ4 := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \> 4)
# ifeq "$(GCCVERSIONGTEQ4)" "0"
# GCCVERSIONGTEQ4 := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 4)
	
# ifeq "$(GCCVERSIONGTEQ4)" "1"
# GCCVERSIONGTEQ4 := $(shell expr `$(CC) -dumpversion | cut -f2 -d.` \>= 8)
# endif

# endif

# Set -march, which defines the instruction set the compiler is allowed to use
# -march=[BASE][EXTENSION][EXTRAS]
# Options for the [BASE] of the -march string are:
# - RV32I: A load-store ISA with 32 (32-bit) general purpose integer registers
# - RV32E: RV32 "embedded" with 16 (32-bit) integer registers
# - RV64I: 64-bit version of RV32I with 32 (64-bit) general purpose integer registers
# Options for EXTENSIONS can be one or all (combined in order):
# - M: Integer multiplication and division
# - A: Atomic instructions
# - F: Single precision floating-point
# - D: Double precision floating point
# - C: Compressed instructions
# EXTRAS are additional options available per the compiler.  I'm not sure if there is a
# comprehensive list of these anywhere.  Try "gcc -dumpspecs" *******************************************************************************
ifeq "$(PREFIX)" "riscv-none-elf"
# With the upgrade to riscv-none-elf came a new ISA spec
# See https://groups.google.com/a/groups.riscv.org/g/sw-dev/c/aE1ZeHHCYf4
# BASE = RV32I
# EXTENSION = M
# EXTRAS = _zicsr_zifencei as recommended above
MARCH ?= rv32im_zicsr_zifencei
endif

# Default option (riscv-none-embed)
ifeq "$(RISCV_NOT_COMPRESSED)" ""
# The RISCV_NOT_COMPRESSED option is a legacy option that I'm not even sure anyone uses...
# but it has existed since the beginning to make the default builds use the compressed
# instruction set.
MARCH ?= rv32imc
else
MARCH ?= rv32im
endif
# *******************************************************************************
# Set -mabi, which defines the instruction set the linker is allowed to link
# against, calling convention, and layout of data in memory
MABI ?= ilp32

# *******************************************************************************
# Set default optimization flags
ifeq "$(MXC_OPTIMIZE_CFLAGS)" ""
# Default is optimize for size
MXC_OPTIMIZE_CFLAGS = -Os
endif

# The flags passed to the assembler.
AFLAGS += -march=$(MARCH)
ifneq "$(HEAP_SIZE)" ""
AFLAGS+=-D__HEAP_SIZE=$(HEAP_SIZE)
endif
ifneq "$(STACK_SIZE)" ""
AFLAGS+=-D__STACK_SIZE=$(STACK_SIZE)
endif
AFLAGS+=$(PROJ_AFLAGS)

# The flags passed to the compiler.
CFLAGS+= \
         -march=$(MARCH)		 \
	     -mabi=$(MABI)           \
	     -ffunction-sections     \
	     -fdata-sections         \
	     -MD                     \
	     -Wall                   \
	     -Wno-format             \
	     $(MXC_OPTIMIZE_CFLAGS)  \
	     -c

# fno-isolate-erroneous-paths-dereference disables the check for pointers with the value of 0
#  add this below when riscv-none-embed version is past 4.8 -fno-isolate-erroneous-paths-dereference
ifeq "$(GCCVERSIONGTEQ4)" "1"
CFLAGS += -fno-isolate-erroneous-paths-dereference
endif

ifneq "$(TARGET)" ""
CFLAGS+=-DTARGET=$(TARGET)
endif

ifneq "$(TARGET_REV)" ""
CFLAGS+=-DTARGET_REV=$(TARGET_REV)
endif

# Exclude debug for 'release' builds
ifneq (${MAKECMDGOALS},release)
ifneq (${DEBUG},0)
CFLAGS+=-g3 -ggdb -DDEBUG
CXX_FLAGS+=-g3 -ggdb -DDEBUG
endif
endif

CFLAGS+=$(PROJ_CFLAGS)
CXX += $(CFLAGS)
CXXFLAGS += \
	-fno-rtti				\
	-fno-exceptions			\
	-std=c++11				\

# NOTE(JC): I'm leaving this commented because it's weird.  We used
# to pass the linker **all** of the available extensions and no -mabi
# option...  I don't think that was correct.  I have updated LDFLAGS
# to match what we give the compiler but I will leave this relic for
# future civilizations
# ----
# ifeq "$(RISCV_NOT_COMPRESSED)" ""
# LDFLAGS=-march=rv32imafdc
# else
# LDFLAGS=-march=rv32imafd 
# endif
# ----

# The flags passed to the linker
LDFLAGS+=-Xlinker --gc-sections       \
      -nostartfiles 	\
	  -march=$(MARCH) 	\
	  -mabi=$(MABI)		\
      -Xlinker -Map -Xlinker ${BUILD_DIR}/$(PROJECT).map
LDFLAGS+=$(PROJ_LDFLAGS)

# Include math library
STD_LIBS=-lc_nano -lm

# Determine if any C++ files are in the project sources, and add libraries as appropriate
ifneq "$(findstring .cpp, ${SRCS})" ""
STD_LIBS+=-lsupc++ -lstdc++
endif

# Finally, resolve any newlib system calls with libnosys
STD_LIBS+=-lnosys

PROJ_LIBS:=$(addprefix -l, $(PROJ_LIBS))

ifeq "$(CYGWIN)" "True"
fixpath=$(shell echo $(1) | sed -r 's/\/cygdrive\/([A-Na-n])/\U\1:/g' )
else
fixpath=$(1)
endif

# Add the include file paths to AFLAGS and CFLAGS.
AFLAGS+=${patsubst %,-I%,$(call fixpath,$(IPATH))}
CFLAGS+=${patsubst %,-I%,$(call fixpath,$(IPATH))}
CXXFLAGS+=${patsubst %,-I%,$(call fixpath,$(IPATH))}
LDFLAGS+=${patsubst %,-L%,$(call fixpath,$(LIBPATH))}

# Add an option for stripping unneeded symbols from archive files
STRIP_LIBRARIES ?= 0
# The command for stripping objects.
STRIP = $(PREFIX)-strip

################################################################################
# The rule for building the object file from each C source file.
${BUILD_DIR}/%.o: %.c $(PROJECTMK)
ifneq "${ECLIPSE}" ""
	@echo ${CC} ${CFLAGS} -o $(call fixpath,${@}) $(call fixpath,${<}) | sed 's/-I\/\(.\)\//-I\1:\//g'
else
ifneq "${VERBOSE}" ""
	@echo ${CC} ${CFLAGS} -o ${@} ${<}
else
	@echo -  CC    ${<}
endif
endif

	@${CC} ${CFLAGS} -o ${@} ${<}

ifeq "$(CYGWIN)" "True"
	@sed -i -r -e 's/([A-Na-n]):/\/cygdrive\/\L\1/g' -e 's/\\([A-Za-z])/\/\1/g' ${@:.o=.d}
endif

# The rule to build an object file from a C++ source file
${BUILD_DIR}/%.o: %.cpp $(PROJECTMK)
ifneq "${ECLIPSE}" ""
	@echo ${CXX} ${CXXFLAGS} -o $(call fixpath,${@}) $(call fixpath,${<}) | sed 's/-I\/\(.\)\//-I\1:\//g'
else
ifneq "${VERBOSE}" ""
	@echo ${CXX} ${CXXFLAGS} -o ${@} ${<}
else
	@echo -  CXX    ${<}
endif
endif

	@${CXX} ${CXXFLAGS} -o ${@} ${<}

ifeq "$(CYGWIN)" "True"
	@sed -i -r -e 's/([A-Na-n]):/\/cygdrive\/\L\1/g' -e 's/\\([A-Za-z])/\/\1/g' ${@:.o=.d}
endif

# The rule for building the object file from each assembly source file.
${BUILD_DIR}/%.o: %.S $(PROJECTMK)
ifneq "${VERBOSE}" ""
	@echo ${CC} ${AFLAGS} -o ${@} -c ${<}
else
	@echo -  AS    ${<}
endif

	@${CC} ${AFLAGS} -o ${@} -c ${<}

ifeq "$(CYGWIN)" "True"
	@sed -i -r -e 's/([A-Na-n]):/\/cygdrive\/\L\1/g' -e 's/\\([A-Za-z])/\/\1/g' ${@:.o=.d}
endif

# The rule for creating an object library.
${BUILD_DIR}/%.a: $(PROJECTMK)
ifeq "$(_OS)" "windows_msys"
	@echo -cr ${@} ${^}                          \
	| sed -r -e 's/ \/([A-Za-z])\// \1:\//g' > ${BUILD_DIR}/ar_args.txt
else
	@echo -cr ${@} ${^} > ${BUILD_DIR}/ar_args.txt
endif

ifneq "$(VERBOSE)" ""
	@echo ${AR} -cr ${@} ${^}
else
	@echo -  AR    ${@}
endif
	@${AR} @${BUILD_DIR}/ar_args.txt

ifeq ($(STRIP_LIBRARIES),1)
ifneq "$(ECLIPSE)" ""
	@echo ${STRIP} $(call fixpath,${@}) | sed 's/-I\/\(.\)\//-I\1:\//g'
else

ifneq "$(VERBOSE)" ""
	@echo ${STRIP} --strip-unneeded ${@}
else
	@echo -  STRIP ${@}
endif # VERBOSE

endif # ECLIPSE

	@${STRIP} --strip-unneeded ${@}

endif # STRIP_LIBRARIES

# The rule for building the object file from binary source file.
# Resulting object will have the following symbols
# _binary_<file_name>_bin_start
# _binary_<file_name>_bin_end
# _binary_<file_name>_bin_size
${BUILD_DIR}/%.o: %.bin $(PROJECTMK)
ifneq "$(VERBOSE)" ""
	echo ${OBJCOPY} -I binary -B arm -O elf32-littlearm --rename-section    \
	    .data=.text ${<} ${@}
else
	echo -  CP    ${<}
endif

	@${OBJCOPY} -I binary -B arm -O elf32-littlearm --rename-section            \
	.data=.text ${<} ${@}

ifeq "$(CYGWIN)" "True"
	@sed -i -r -e 's/([A-Na-n]):/\/cygdrive\/\L\1/g' -e 's/\\([A-Za-z])/\/\1/g' ${@:.o=.d}
endif

# The rule for linking the application.
${BUILD_DIR}/%.elf: $(PROJECTMK)
# This rule parses the linker arguments into a text file to work around issues
# with string length limits on the command line
ifeq "$(_OS)" "windows_msys"
# MSYS2 will create /c/-like paths, but GCC needs C:/-like paths on Windows.
# So the only difference between this command and the "standard" command for
# creating ln_args.txt is the sed call to perform the path replacement.
	@echo -T ${LINKERFILE}                                       \
	      --entry ${ENTRY}                                                       \
	      ${LDFLAGS}                                             \
	      -o ${@}                                                \
	      $(filter %.o, ${^})                                    \
	      -Xlinker --start-group                                                 \
	      $(filter %.a, ${^})                                    \
	      ${PROJ_LIBS}                                                           \
	      ${STD_LIBS}                                                            \
	      -Xlinker --end-group                                                   \
		  | sed -r -e 's/\/([A-Za-z])\//\1:\//g'    \
	      > ${BUILD_DIR}/ln_args.txt
else
	@echo -T ${LINKERFILE}                                       \
	      --entry ${ENTRY}                                                       \
	      ${LDFLAGS}                                             \
	      -o ${@}                                                \
	      $(filter %.o, ${^})                                    \
	      -Xlinker --start-group                                                 \
	      $(filter %.a, ${^})                                    \
	      ${PROJ_LIBS}                                                           \
	      ${STD_LIBS}                                                            \
	      -Xlinker --end-group                                                   \
	      > ${BUILD_DIR}/ln_args.txt
endif

ifneq "$(VERBOSE)" ""
	@echo ${LD} -T ${LINKERFILE}                          \
	        --entry ${ENTRY}                                             \
	        ${LDFLAGS}                                   \
	        -o ${@}                                      \
	        $(filter %.o, ${^})                          \
	        -Xlinker --start-group                                       \
	        $(filter %.a, ${^})                          \
	        ${PROJ_LIBS}                                                 \
	        ${STD_LIBS}                                                  \
	        -Xlinker --end-group
else
	@echo -  LD    ${@}
endif

	@${LD} @${BUILD_DIR}/ln_args.txt

# Create S-Record output file
%.srec: %.elf
ifneq "$(VERBOSE)" ""
	@echo ${OBJCOPY} -O srec ${<} ${@}
else
	@echo Creating ${@}
endif

	@$(OBJCOPY) -O srec $< ${@}

# Create Intex Hex output file
%.hex: %.elf
ifneq "$(VERBOSE)" ""
	@echo ${OBJCOPY} -O ihex ${<} ${@}
else
	@echo Creating ${@}
endif

	@$(OBJCOPY) -O ihex $< ${@}

# Create binary output file
%.bin: %.elf
ifneq "$(VERBOSE)" ""
	@echo ${OBJCOPY} -O binary ${<} ${@}
else
	@echo Creating ${@}
endif

	@$(OBJCOPY) -O binary $< ${@}

# Create disassembly file
%.dasm: %.elf
ifneq "$(VERBOSE)" ""
	@echo $(OBJDUMP) -S ${<} ${@}
else
	@echo Creating ${@}
endif

	@$(OBJDUMP) -S $< > ${@}

################################################################################
.PHONY: debug
debug:
	@echo CYGWIN = ${CYGWIN}
	@echo
	@echo CC = ${CC}
	@echo
	@echo AS = ${AS}
	@echo
	@echo LD = ${LD}
	@echo
	@echo TARGET = ${TARGET}
	@echo
	@echo BOARD = ${BOARD}
	@echo
	@echo BUILD_DIR = ${BUILD_DIR}
	@echo
	@echo SRCS = ${SRCS}
	@echo
	@echo SRCS_NOPATH = ${SRCS_NOPATH}
	@echo
	@echo OBJS_NOPATH = ${OBJS_NOPATH}
	@echo
	@echo OBJS = ${OBJS}
	@echo
	@echo LIBS = ${LIBS}
	@echo
	@echo VPATH = ${VPATH}
	@echo
	@echo IPATH = ${IPATH}
	@echo
	@echo CFLAGS = ${CFLAGS}
	@echo
	@echo AFLAGS = ${AFLAGS}
	@echo
	@echo LDFLAGS = ${LDFLAGS}

################################################################################
# Add a rule for generating a header file containing compiler definitions
# that come from the build system and compiler itself.  This generates a
# "project_defines.h" header file inside the build directory that can be
# force included by VS Code to improve the intellisense engine.
$(BUILD_DIR)/_empty_tmp_file.c: | $(BUILD_DIR)
	@echo "// Temp file used to detect compiler defs at build time.  Safely ignore/delete" > $(BUILD_DIR)/_empty_tmp_file.c

.PHONY: project_defines
project_defines: $(BUILD_DIR)/project_defines.h
$(BUILD_DIR)/project_defines.h: $(BUILD_DIR)/_empty_tmp_file.c | $(BUILD_DIR)
	@echo "- Detecting compiler definitions"
	@echo "// This is a generated file that's used to detect definitions that have been set by the compiler and build system." > $@
	@$(CC) -E -P -dD $(BUILD_DIR)/_empty_tmp_file.c $(filter-out -MD,$(CFLAGS)) >> $@
