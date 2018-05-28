#!/usr/bin/env bats

load test_helper

setup() {
  build_clean_baseline
}

@test "Disturbing source means we need to recompile" {
  disturb $(TOP)/integrated/_integrated.cpp
  run do_make -q tree
  [ "$status" -eq 1 ]
}

@test "Disturbing binary source means we need to recompile and link" {
  # Should not need to build
  run do_make -q $(TOP)/integrated/$(OBJDIR)/_integrated
  [ "$status" -eq 0 ]
  run do_make -q $(TOP)/integrated/$(OBJDIR)/_integrated.o
  [ "$status" -eq 0 ]

  disturb $(TOP)/integrated/_integrated.cpp
  run do_make -q $(TOP)/integrated/$(OBJDIR)/_integrated.o
  [ "$status" -eq 1 ]
  run do_make -q $(TOP)/integrated/$(OBJDIR)/_integrated
  [ "$status" -eq 1 ]
}
