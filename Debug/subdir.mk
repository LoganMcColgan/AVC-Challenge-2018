################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AVCBasicMove.cpp \
../AVCImageProcessing.cpp \
../AVCMovements.cpp \
../AVCNetwork.cpp \
../AVCTest.cpp \
../read.cpp 

O_SRCS += \
../read.o 

OBJS += \
./AVCBasicMove.o \
./AVCImageProcessing.o \
./AVCMovements.o \
./AVCNetwork.o \
./AVCTest.o \
./read.o 

CPP_DEPS += \
./AVCBasicMove.d \
./AVCImageProcessing.d \
./AVCMovements.d \
./AVCNetwork.d \
./AVCTest.d \
./read.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


