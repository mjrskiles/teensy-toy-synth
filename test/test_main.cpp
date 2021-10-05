//
// Created by mjrsk on 10/4/2021.
//
#include <unity.h>
#include "../include/utils/JengaStack.h"

uint8_t test_stack[JENGA_STACK_SIZE_MAX];
JengaStack jengaStack = JengaStack();

void test_push() {
    jengaStack.push(10);
    TEST_ASSERT_EQUAL(1, jengaStack.size());
    jengaStack.push(11);
    TEST_ASSERT_EQUAL(2, jengaStack.size());
    jengaStack.push(12);
    TEST_ASSERT_EQUAL(3, jengaStack.size());
    jengaStack.push(13);
    TEST_ASSERT_EQUAL(4, jengaStack.size());
    jengaStack.push(14);
    TEST_ASSERT_EQUAL(5, jengaStack.size());
    jengaStack.push(15);
    TEST_ASSERT_EQUAL(6, jengaStack.size());
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_push);
}

void loop() {
    // do tests;
    UNITY_END();
}
