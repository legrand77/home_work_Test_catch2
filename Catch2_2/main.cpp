#include "catch2/extras/catch_amalgamated.hpp"
#include "my_list.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <cstdint>
#include <iostream>


//проверяемая функция
List begin;

//юнит-тест
TEST_CASE("List begin")
{
    REQUIRE_THROWS_WITH(begin.PopFront(), "list is empty");


        begin.PushFront(1);
        begin.PushFront(23);
        begin.PushFront(7);
        begin.PushBack(10);
        begin.PushBack(4);
        begin.PushBack(2);
        CHECK(begin.PopFront() == 7);
        CHECK(begin.PopFront() == 23);
        CHECK(begin.PopBack() == 2);
        CHECK(begin.PopBack() == 4);   
}