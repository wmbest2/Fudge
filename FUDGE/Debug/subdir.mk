################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cppclass.cpp \
../main.cpp 

OBJS += \
./cppclass.o \
./main.o 

CPP_DEPS += \
./cppclass.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DDBG_ENABLED -I"/home/wmb001/workspace/CSC500/GenHelpers" -I"/home/wmb001/workspace/CSC500/Resolver" -I"/home/wmb001/workspace/CSC500/CppParlexser" -I"/home/wmb001/workspace/CSC500/Lexical Analyzer" -I"/home/wmb001/workspace/CSC500/Parser" -I/home/wmb001/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


