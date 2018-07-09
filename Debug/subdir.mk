################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../config.cpp \
../main.cpp \
../mempool.cpp \
../message.cpp \
../network.cpp \
../server.cpp \
../session.cpp \
../session_mgr.cpp \
../testclient.cpp \
../timer.cpp \
../tinystr.cpp \
../tinyxml.cpp \
../tinyxmlerror.cpp \
../tinyxmlparser.cpp 

OBJS += \
./config.o \
./main.o \
./mempool.o \
./message.o \
./network.o \
./server.o \
./session.o \
./session_mgr.o \
./testclient.o \
./timer.o \
./tinystr.o \
./tinyxml.o \
./tinyxmlerror.o \
./tinyxmlparser.o 

CPP_DEPS += \
./config.d \
./main.d \
./mempool.d \
./message.d \
./network.d \
./server.d \
./session.d \
./session_mgr.d \
./testclient.d \
./timer.d \
./tinystr.d \
./tinyxml.d \
./tinyxmlerror.d \
./tinyxmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


