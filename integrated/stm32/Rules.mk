TARGETS := slave

slave_DEPS := slave.o $(parent_dir)/algorithm/$(OBJDIR)/libalgorithm.a

INCLUDES_$(d) := $(INCLUDES_$(parent_dir)) $(parent_dir)
