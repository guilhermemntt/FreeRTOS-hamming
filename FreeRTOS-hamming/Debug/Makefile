################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../FreeRTOS


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../FreeRTOS/checksum.c \
../FreeRTOS/croutine.c \
../FreeRTOS/event_groups.c \
../FreeRTOS/heap_3.c \
../FreeRTOS/list.c \
../FreeRTOS/port.c \
../FreeRTOS/queue.c \
../FreeRTOS/stream_buffer.c \
../FreeRTOS/tasks.c \
../FreeRTOS/timers.c \
../main.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
FreeRTOS/checksum.o \
FreeRTOS/croutine.o \
FreeRTOS/event_groups.o \
FreeRTOS/heap_3.o \
FreeRTOS/list.o \
FreeRTOS/port.o \
FreeRTOS/queue.o \
FreeRTOS/stream_buffer.o \
FreeRTOS/tasks.o \
FreeRTOS/timers.o \
main.o

OBJS_AS_ARGS +=  \
FreeRTOS/checksum.o \
FreeRTOS/croutine.o \
FreeRTOS/event_groups.o \
FreeRTOS/heap_3.o \
FreeRTOS/list.o \
FreeRTOS/port.o \
FreeRTOS/queue.o \
FreeRTOS/stream_buffer.o \
FreeRTOS/tasks.o \
FreeRTOS/timers.o \
main.o

C_DEPS +=  \
FreeRTOS/checksum.d \
FreeRTOS/croutine.d \
FreeRTOS/event_groups.d \
FreeRTOS/heap_3.d \
FreeRTOS/list.d \
FreeRTOS/port.d \
FreeRTOS/queue.d \
FreeRTOS/stream_buffer.d \
FreeRTOS/tasks.d \
FreeRTOS/timers.d \
main.d

C_DEPS_AS_ARGS +=  \
FreeRTOS/checksum.d \
FreeRTOS/croutine.d \
FreeRTOS/event_groups.d \
FreeRTOS/heap_3.d \
FreeRTOS/list.d \
FreeRTOS/port.d \
FreeRTOS/queue.d \
FreeRTOS/stream_buffer.d \
FreeRTOS/tasks.d \
FreeRTOS/timers.d \
main.d

OUTPUT_FILE_PATH +=FreeRTOS-hamming.elf

OUTPUT_FILE_PATH_AS_ARGS +=FreeRTOS-hamming.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler























FreeRTOS/%.o: ../FreeRTOS/%.c
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega328p" -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 5.4.0
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="FreeRTOS-hamming.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega328p"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "FreeRTOS-hamming.elf" "FreeRTOS-hamming.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "FreeRTOS-hamming.elf" "FreeRTOS-hamming.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "FreeRTOS-hamming.elf" > "FreeRTOS-hamming.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "FreeRTOS-hamming.elf" "FreeRTOS-hamming.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "FreeRTOS-hamming.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "FreeRTOS-hamming.elf" "FreeRTOS-hamming.a" "FreeRTOS-hamming.hex" "FreeRTOS-hamming.lss" "FreeRTOS-hamming.eep" "FreeRTOS-hamming.map" "FreeRTOS-hamming.srec" "FreeRTOS-hamming.usersignatures"
	