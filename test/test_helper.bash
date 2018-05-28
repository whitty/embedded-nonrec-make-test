TOP() {
  dirname "$BATS_TEST_DIRNAME"
}

OBJDIR() {
  echo "obj/${BUILD_MODE:-debug}"
}

disturb() {
  touch -c "$1"
}

do_make() {
  make -C $(TOP) "$@"
}

build_clean_baseline() {
  echo "$BATS_TEST_DIRNAME"
  echo " -- setup preliminary build --"
  # ensure we are built
  do_make tree
  # and we don't need to make any more
  do_make -q tree
  echo "-- setup done --"
}
