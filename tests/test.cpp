#include <gtest.h>
#include "TList.h"

TEST(TListTest, DefaultConstructor) {
  TList<int> list;
  EXPECT_EQ(list.GetSize(), 0);
  EXPECT_TRUE(list.IsEmpty());
  EXPECT_FALSE(list.IsFull());
  EXPECT_EQ(list.GetHead(), nullptr);
  EXPECT_EQ(list.GetTail(), nullptr);
}

TEST(TListTest, CopyConstructor) {
  TList<int> list1;
  list1.PushBack(1);
  list1.PushBack(2);
  list1.PushBack(3);

  TList<int> list2(list1);
  EXPECT_EQ(list2.GetSize(), 3);
  EXPECT_FALSE(list2.IsEmpty());

  EXPECT_EQ(list2.PopFront(), 1);
  EXPECT_EQ(list2.PopFront(), 2);
  EXPECT_EQ(list2.PopFront(), 3);
  EXPECT_EQ(list1.GetSize(), 3);
}

TEST(TListTest, MoveConstructor) {
  TList<int> list1;
  list1.PushBack(1);
  list1.PushBack(2);
  list1.PushBack(3);

  TList<int> list2(std::move(list1));
  EXPECT_EQ(list2.GetSize(), 3);
  EXPECT_EQ(list1.GetSize(), 0);
  EXPECT_EQ(list1.GetHead(), nullptr);
  EXPECT_EQ(list1.GetTail(), nullptr);

  EXPECT_EQ(list2.PopFront(), 1);
  EXPECT_EQ(list2.PopFront(), 2);
  EXPECT_EQ(list2.PopFront(), 3);
}

TEST(TListTest, PushFrontAndPopFront) {
  TList<int> list;
  list.PushFront(3);
  list.PushFront(2);
  list.PushFront(1);

  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 3);
  EXPECT_TRUE(list.IsEmpty());
}

TEST(TListTest, PushBackAndPopBack) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list.PopBack(), 3);
  EXPECT_EQ(list.PopBack(), 2);
  EXPECT_EQ(list.PopBack(), 1);
  EXPECT_TRUE(list.IsEmpty());
}

TEST(TListTest, PushFrontBackMixed) {
  TList<int> list;
  list.PushFront(2);
  list.PushBack(3);
  list.PushFront(1);
  list.PushBack(4);

  EXPECT_EQ(list.GetSize(), 4);
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopBack(), 4);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopBack(), 3);
  EXPECT_TRUE(list.IsEmpty());
}

TEST(TListTest, PopEmptyList) {
  TList<int> list;
  EXPECT_THROW(list.PopFront(), const char*);
  EXPECT_THROW(list.PopBack(), const char*);
}

TEST(TListTest, InsertAfter) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(3);

  auto head = list.GetHead();
  list.InsertAfter(head, 2);

  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 3);
}

TEST(TListTest, InsertAfterTail) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);

  auto tail = list.GetTail();
  list.InsertAfter(tail, 3);

  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list.PopBack(), 3);
  EXPECT_EQ(list.PopBack(), 2);
  EXPECT_EQ(list.PopBack(), 1);
}

TEST(TListTest, InsertBefore) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(3);

  auto tail = list.GetTail();
  list.InsertBefore(tail, 2);

  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 3);
}

TEST(TListTest, InsertBeforeHead) {
  TList<int> list;
  list.PushBack(2);
  list.PushBack(3);

  auto head = list.GetHead();
  list.InsertBefore(head, 1);

  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 3);
}

TEST(TListTest, InsertInvalidNode) {
  TList<int> list;
  list.PushBack(1);

  EXPECT_THROW(list.InsertAfter(nullptr, 2), const char*);
  EXPECT_THROW(list.InsertBefore(nullptr, 2), const char*);
}

TEST(TListTest, Remove) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  auto node = list.GetHead()->next;
  list.Remove(node);

  EXPECT_EQ(list.GetSize(), 2);
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopFront(), 3);
}

TEST(TListTest, RemoveHead) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  auto head = list.GetHead();
  list.Remove(head);

  EXPECT_EQ(list.GetSize(), 2);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 3);
}

TEST(TListTest, RemoveTail) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  auto tail = list.GetTail();
  list.Remove(tail);

  EXPECT_EQ(list.GetSize(), 2);
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopFront(), 2);
}

TEST(TListTest, RemoveInvalidNode) {
  TList<int> list;
  list.PushBack(1);

  EXPECT_THROW(list.Remove(nullptr), const char*);
}

TEST(TListTest, Clear) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  EXPECT_EQ(list.GetSize(), 3);
  list.Clear();
  EXPECT_EQ(list.GetSize(), 0);
  EXPECT_TRUE(list.IsEmpty());
  EXPECT_EQ(list.GetHead(), nullptr);
  EXPECT_EQ(list.GetTail(), nullptr);
}

TEST(TListTest, ClearEmptyList) {
  TList<int> list;
  list.Clear();
  EXPECT_TRUE(list.IsEmpty());
}

TEST(TListTest, AssignmentOperator) {
  TList<int> list1;
  list1.PushBack(1);
  list1.PushBack(2);
  list1.PushBack(3);

  TList<int> list2;
  list2 = list1;

  EXPECT_EQ(list2.GetSize(), 3);
  EXPECT_EQ(list2.PopFront(), 1);
  EXPECT_EQ(list2.PopFront(), 2);
  EXPECT_EQ(list2.PopFront(), 3);
  EXPECT_EQ(list1.GetSize(), 3);
}

TEST(TListTest, MoveAssignmentOperator) {
  TList<int> list1;
  list1.PushBack(1);
  list1.PushBack(2);
  list1.PushBack(3);

  TList<int> list2;
  list2 = std::move(list1);

  EXPECT_EQ(list2.GetSize(), 3);
  EXPECT_EQ(list1.GetSize(), 0);

  EXPECT_EQ(list2.PopFront(), 1);
  EXPECT_EQ(list2.PopFront(), 2);
  EXPECT_EQ(list2.PopFront(), 3);
}

TEST(TListTest, SelfAssignment) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  list = list;

  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list.PopFront(), 1);
  EXPECT_EQ(list.PopFront(), 2);
  EXPECT_EQ(list.PopFront(), 3);
}

TEST(TListTest, EqualityOperator) {
  TList<int> list1;
  list1.PushBack(1);
  list1.PushBack(2);
  list1.PushBack(3);

  TList<int> list2;
  list2.PushBack(1);
  list2.PushBack(2);
  list2.PushBack(3);

  TList<int> list3;
  list3.PushBack(3);
  list3.PushBack(2);
  list3.PushBack(1);

  TList<int> list4;
  list4.PushBack(1);
  list4.PushBack(2);

  EXPECT_TRUE(list1 == list2);
  EXPECT_FALSE(list1 == list3);
  EXPECT_FALSE(list1 == list4);
  EXPECT_TRUE(list1 != list3);
  EXPECT_TRUE(list1 != list4);
}

TEST(TListTest, IndexOperator) {
  TList<int> list;
  list.PushBack(10);
  list.PushBack(20);
  list.PushBack(30);

  EXPECT_EQ(list[0], 10);
  EXPECT_EQ(list[1], 20);
  EXPECT_EQ(list[2], 30);
  EXPECT_THROW(list[3], const char*);
}

TEST(TListTest, ConstIndexOperator) {
  const TList<int> list = []() {
    TList<int> temp;
    temp.PushBack(10);
    temp.PushBack(20);
    temp.PushBack(30);
    return temp;
  }();

  EXPECT_EQ(list[0], 10);
  EXPECT_EQ(list[1], 20);
  EXPECT_EQ(list[2], 30);
  EXPECT_THROW(list[3], const char*);
}

TEST(TListTest, ConcatenationOperator) {
  TList<int> list1;
  list1.PushBack(1);
  list1.PushBack(2);

  TList<int> list2;
  list2.PushBack(3);
  list2.PushBack(4);

  TList<int> result = list1 + list2;

  EXPECT_EQ(result.GetSize(), 4);
  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 2);
  EXPECT_EQ(result[2], 3);
  EXPECT_EQ(result[3], 4);

  EXPECT_EQ(list1.GetSize(), 2);
  EXPECT_EQ(list2.GetSize(), 2);
}

TEST(TListTest, Iterators) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = list.begin(); it != list.end(); it = it->next) {
    EXPECT_EQ(it->data, expected[i++]);
  }
}

TEST(TListTest, ConstIterators) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  const TList<int> &constList = list;
  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = constList.begin(); it != constList.end(); it = it->next) {
    EXPECT_EQ(it->data, expected[i++]);
  }
}

TEST(TListTest, CountOccurrences) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(1);
  list.PushBack(3);
  list.PushBack(1);
  list.PushBack(4);

  EXPECT_EQ(list.CountOccurrences(1), 3);
  EXPECT_EQ(list.CountOccurrences(2), 1);
  EXPECT_EQ(list.CountOccurrences(5), 0);
}

TEST(TListTest, FindOccurrences) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(1);
  list.PushBack(3);
  list.PushBack(1);

  auto occurrences = list.FindOccurrences(1);
  EXPECT_EQ(occurrences.GetSize(), 3);

  for (auto it = occurrences.begin(); it != occurrences.end(); it = it->next) {
    EXPECT_EQ(it->data->data, 1);
  }

  auto occIt = occurrences.begin();
  auto listIt = list.begin();
  while (listIt != list.end()) {
    if (listIt->data == 1) {
      EXPECT_EQ(listIt, occIt->data);
      occIt = occIt->next;
    }
    listIt = listIt->next;
  }
}

TEST(TListTest, FindOccurrencesEmptyResult) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  auto occurrences = list.FindOccurrences(4);
  EXPECT_EQ(occurrences.GetSize(), 0);
  EXPECT_TRUE(occurrences.IsEmpty());
}

TEST(TListIOTest, OutputOperator) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  std::stringstream ss;
  ss << list;
  EXPECT_EQ(ss.str(), "[1, 2, 3]");
}

TEST(TListIOTest, InputOperator) {
  TList<int> list;
  std::stringstream ss("5\n10 20 30 40 50");
  ss >> list;

  EXPECT_EQ(list.GetSize(), 5);
  EXPECT_EQ(list[0], 10);
  EXPECT_EQ(list[1], 20);
  EXPECT_EQ(list[2], 30);
  EXPECT_EQ(list[3], 40);
  EXPECT_EQ(list[4], 50);
}

TEST(TListIOTest, InputOperatorOverwrites) {
  TList<int> list;
  list.PushBack(100);
  list.PushBack(200);

  std::stringstream ss("3\n1 2 3");
  ss >> list;

  EXPECT_EQ(list.GetSize(), 3);
  EXPECT_EQ(list[0], 1);
  EXPECT_EQ(list[1], 2);
  EXPECT_EQ(list[2], 3);
}

TEST(TListTemplateTest, WithDouble) {
  TList<double> list;
  list.PushBack(1.5);
  list.PushBack(2.7);
  list.PushBack(3.14);

  EXPECT_DOUBLE_EQ(list[0], 1.5);
  EXPECT_DOUBLE_EQ(list[1], 2.7);
  EXPECT_DOUBLE_EQ(list[2], 3.14);
  EXPECT_EQ(list.GetSize(), 3);
}

TEST(TListTemplateTest, WithString) {
  TList<std::string> list;
  list.PushBack("Hello");
  list.PushBack("World");
  list.PushBack("!");

  EXPECT_EQ(list[0], "Hello");
  EXPECT_EQ(list[1], "World");
  EXPECT_EQ(list[2], "!");
  EXPECT_EQ(list.GetSize(), 3);
}

TEST(TListTemplateTest, WithCustomStruct) {
  struct Point {
    int x, y;

    Point(int x_, int y_) : x(x_), y(y_) {}

    bool operator==(const Point &other) const {
      return x == other.x && y == other.y;
    }
  };

  TList<Point> list;
  list.PushBack(Point(1, 2));
  list.PushBack(Point(3, 4));

  EXPECT_EQ(list[0].x, 1);
  EXPECT_EQ(list[0].y, 2);
  EXPECT_EQ(list[1].x, 3);
  EXPECT_EQ(list[1].y, 4);
  EXPECT_EQ(list.GetSize(), 2);
}

TEST(TListEdgeCaseTest, LargeNumberOfElements) {
  TList<int> list;
  const int COUNT = 1000;

  for (int i = 0; i < COUNT; ++i) {
    list.PushBack(i);
  }

  EXPECT_EQ(list.GetSize(), COUNT);

  for (int i = 0; i < COUNT; ++i) {
    EXPECT_EQ(list[i], i);
  }

  for (int i = 0; i < COUNT; ++i) {
    list.PopFront();
  }

  EXPECT_TRUE(list.IsEmpty());
}

TEST(TListEdgeCaseTest, SingleElementList) {
  TList<int> list;
  list.PushBack(42);

  EXPECT_EQ(list.GetSize(), 1);
  EXPECT_EQ(list.GetHead(), list.GetTail());
  EXPECT_EQ(list.PopFront(), 42);
  EXPECT_TRUE(list.IsEmpty());

  list.PushFront(100);
  EXPECT_EQ(list.GetSize(), 1);
  EXPECT_EQ(list.GetHead(), list.GetTail());
  EXPECT_EQ(list.PopBack(), 100);
  EXPECT_TRUE(list.IsEmpty());
}

TEST(TListEdgeCaseTest, RemoveAllElements) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  auto node1 = list.GetHead();
  auto node2 = node1->next;
  auto node3 = list.GetTail();

  list.Remove(node2);
  EXPECT_EQ(list.GetSize(), 2);

  list.Remove(node1);
  EXPECT_EQ(list.GetSize(), 1);

  list.Remove(node3);
  EXPECT_EQ(list.GetSize(), 0);
  EXPECT_TRUE(list.IsEmpty());
}

TEST(TListEdgeCaseTest, IteratorRangeBasedFor) {
  TList<int> list;
  list.PushBack(1);
  list.PushBack(2);
  list.PushBack(3);

  int sum = 0;
  for (auto it = list.begin(); it != list.end(); it = it->next) {
    sum += it->data;
  }
  EXPECT_EQ(sum, 6);
}