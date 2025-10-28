#include <beat_pattern.h>
#include <unity.h>

struct s_test {
  beat_pattern pattern_mtx[4][4];
} s1;

void setUp(void) {}

void tearDown(void) {}

void test_pattern_cycle(void) {
  TEST_ASSERT_EQUAL(0x1, cycle_beat(s1.pattern_mtx[0][0], 0));
  // TEST_ASSERT_BITS_HIGH(0x2, cycle_beat(s1.pattern_mtx[0][0], 0));
}

void test_pattern_cycle2(void) {
  beat_pattern test = 0;
  test = cycle_beat(test, 0);
  test = cycle_beat(test, 0);
  TEST_ASSERT_EQUAL(0x3, test);
}

int main(int argc, char *argv[]) {
  UNITY_BEGIN();
  RUN_TEST(test_pattern_cycle);
  RUN_TEST(test_pattern_cycle2);
  UNITY_END();

  return 0;
}
