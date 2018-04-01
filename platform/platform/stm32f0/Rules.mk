DAYTONA := true

# This component builds for stm32f0
OPT_IN_PLATFORMS := stm32f0

# Parameters to startup_ARMCM0.S
CPPFLAGS_$(d) := -D__STACK_SIZE=0x400 -D__HEAP_SIZE=0x800
