#include <iostream>

//подключаем макросы catch2
#include <catch2/catch_test_macros.hpp>
#include <cstdint>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear(); 
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }  //                     1

    unsigned long Size() { return m_size; } //                   2

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()  //                                             3
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};


//проверяемая функция
List begin;



//юнит-тест
TEST_CASE("List begin")
{
    CHECK(begin.PopFront() == 0);
    CHECK(begin.PopBack() == 0);
    
        begin.PushFront(1);
        begin.PushFront(23);
        begin.PushFront(7);
        begin.PushBack(10);
        begin.PushBack(4);
        begin.PushBack(2);
       // CHECK(begin.Size() == 6);
       // CHECK(begin.Empty() == false);
        CHECK(begin.PopFront() == 7);
        CHECK(begin.PopFront() == 23);
        CHECK(begin.PopBack() == 2);
        CHECK(begin.PopBack() == 4);
       // CHECK(begin.Size() == 2);
       // begin.Clear();
      //  CHECK(begin.Size() == 0);
       // CHECK(begin.Empty() == true);
    
}