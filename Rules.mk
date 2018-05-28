SUBDIRS := integrated \
	test

# all sub-directories should be able to include from this level
INCLUDES_$(d) := $(d)

INHERIT_DIR_VARS := INCLUDES
