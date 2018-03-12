SUBDIRS := \
	$(if $(CPU),cpu/$(CPU)) \
	$(if $(PLATFORM),platform/$(PLATFORM)) \
	$(if $(OS),os/$(OS)) \

# This component builds for stm32f0
OPT_IN_PLATFORMS := stm32f0

TARGETS := libplatform.a

libplatform.a_DEPS := \
	$(d)/cpu/$(CPU)/$(OBJDIR)/lib$(CPU).a \
	$(d)/platform/$(PLATFORM)/$(OBJDIR)/lib$(PLATFORM).a \
	$(d)/os/$(OS)/$(OBJDIR)/lib$(OS).a
