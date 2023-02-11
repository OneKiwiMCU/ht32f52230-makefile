######################################
# target
######################################
TARGET = ht32f52230


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

HT32_LIB_PATH = Library/HT32F5xxxx_Driver/src/
HT32_UTL_PATH = Utilities/

######################################
# source
######################################
# C sources
C_SOURCES =  \
User/main.c \
User/ht32f5xxxx_01_it.c \
User/system_ht32f5xxxx_02.c \
$(HT32_LIB_PATH)ht32_cm0plus_misc.c \
$(HT32_LIB_PATH)ht32f5xxxx_adc.c \
$(HT32_LIB_PATH)ht32f5xxxx_bftm.c \
$(HT32_LIB_PATH)ht32f5xxxx_ckcu.c \
$(HT32_LIB_PATH)ht32f5xxxx_exti.c \
$(HT32_LIB_PATH)ht32f5xxxx_flash.c \
$(HT32_LIB_PATH)ht32f5xxxx_gpio.c \
$(HT32_LIB_PATH)ht32f5xxxx_i2c.c \
$(HT32_LIB_PATH)ht32f5xxxx_pwrcu.c \
$(HT32_LIB_PATH)ht32f5xxxx_rstcu.c \
$(HT32_LIB_PATH)ht32f5xxxx_spi.c \
$(HT32_LIB_PATH)ht32f5xxxx_tm.c \
$(HT32_LIB_PATH)ht32f5xxxx_usart.c \
$(HT32_LIB_PATH)ht32f5xxxx_wdt.c \
$(HT32_UTL_PATH)drv_systick.c \
$(HT32_UTL_PATH)drv_uart.c \
$(HT32_UTL_PATH)drv_i2c.c \
$(HT32_UTL_PATH)drv_mpq8875a.c

# ASM sources
ASM_SOURCES =  \
startup_ht32f5xxxx_gcc_01.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m0

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = \
--defsym USE_HT32_CHIP=1

# C defines
C_DEFS =  \
-DUSE_HT32_DRIVER \
-DUSE_HT32F52220_30 \
-DUSE_MEM_HT32F52230


# AS includes
AS_INCLUDES =


# C includes
C_INCLUDES =  \
-IUser \
-ILibrary/CMSIS/Include \
-ILibrary/Device/Holtek/HT32F5xxxx/Include \
-ILibrary/HT32F5xxxx_Driver/inc \
-IUtilities


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = linker.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***