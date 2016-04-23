################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/socket/common_Socket.cpp \
../src/socket/common_SocketException.cpp 

OBJS += \
./src/socket/common_Socket.o \
./src/socket/common_SocketException.o 

CPP_DEPS += \
./src/socket/common_Socket.d \
./src/socket/common_SocketException.d 


# Each subdirectory must supply rules for building sources it contributes
src/socket/%.o: ../src/socket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


