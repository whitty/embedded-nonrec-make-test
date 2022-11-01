# This directory represents a combined component with
# linux-hosted and bare-metal code coexisting.

# Code in this directory is compiled for host, linux-target and
# bare-metal target.

# Executables in this directory compile for host and linux-target
# - master is the "application executuable" - ie the product that
#   runs on the linux-target
#
# - _integrated is a test executable - it should run on host and
#   linux-target, and and will run using `make test`
#
# the stm32 directory has a bare-metal target to do the work on the
# subsidiary microcontroller
#
# the algorithm directory contains library code shared between
# bare-metal and other target - that implement generic application
# algorithms that apply across multiple targets.

SUBDIRS := algorithm
stm32_SUBDIRS := stm32

TARGETS := master _integrated
TESTS := _integrated

master_DEPS := master.o common.o $(d)/algorithm/$(OBJDIR)/libalgorithm.a

_integrated_DEPS := _integrated.o
