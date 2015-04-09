################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Util/MessageThread.cpp \
../src/Util/XSocket.cpp \
../src/Util/XThread.cpp 

OBJS += \
./src/Util/MessageThread.o \
./src/Util/XSocket.o \
./src/Util/XThread.o 

CPP_DEPS += \
./src/Util/MessageThread.d \
./src/Util/XSocket.d \
./src/Util/XThread.d 


# Each subdirectory must supply rules for building sources it contributes
src/Util/%.o: ../src/Util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/xercesc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


