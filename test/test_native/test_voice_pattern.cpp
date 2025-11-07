#include <BeatPattern.hpp>
#include <unity.h>

struct s_test {
  BeatPattern pattern_mtx[4][4];
} s1;

void setUp(void) {}

void tearDown(void) {}

void test_pattern_cycle(void) {
  s1.pattern_mtx[0][0].cycleBeat(0);
  TEST_ASSERT_EQUAL(0x1, s1.pattern_mtx[0][0].get());
  // TEST_ASSERT_BITS_HIGH(0x2, cycle_beat(s1.pattern_mtx[0][0], 0));
}

void test_pattern_cycle_around(void) {
  s1.pattern_mtx[0][0].cycleBeat(0); // 2
  // TEST_ASSERT_EQUAL(0x2, s1.pattern_mtx[0][0].get());
  s1.pattern_mtx[0][0].cycleBeat(0); // 3
  // TEST_ASSERT_EQUAL(0x3, s1.pattern_mtx[0][0].get());
  s1.pattern_mtx[0][0].cycleBeat(0); // 0
  TEST_ASSERT_EQUAL(0x0, s1.pattern_mtx[0][0].get());
}

int main(int argc, char *argv[]) {
  UNITY_BEGIN();
  RUN_TEST(test_pattern_cycle);
  RUN_TEST(test_pattern_cycle_around);
  UNITY_END();

  return 0;
}
