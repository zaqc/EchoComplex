################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Server/ServerItem.cpp \
../src/Server/ServerThread.cpp 

OBJS += \
./src/Server/ServerItem.o \
./src/Server/ServerThread.o 

CPP_DEPS += \
./src/Server/ServerItem.d \
./src/Server/ServerThread.d 


# Each subdirectory must supply rules for building sources it contributes
src/Server/%.o: ../src/Server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


