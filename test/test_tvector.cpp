#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(v1);

	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int n = 5;
	TDynamicVector<int> v1(n);
	for (int i = 0; i < n; i++)
		v1[i] = 2;
	
	TDynamicVector<int> v2(v1);

	v2[0] = 10;

	ASSERT_EQ(v1[0], 2);
	ASSERT_EQ(v2[0], 10);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	
	ASSERT_ANY_THROW(v.at(-1) = 0);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);

	ASSERT_ANY_THROW(v.at(10) = 0);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(5);

	ASSERT_NO_THROW(v = v);

}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);

	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);

	v1 = v2;
	ASSERT_EQ(v1.size(), v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);

	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	
	ASSERT_EQ(v1==v2, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{

	TDynamicVector<int> v1(5);


	ASSERT_EQ(v1 == v1, true);
  
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{

	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);

	ASSERT_EQ(v1 == v2, false);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	
	int scal = 1;
	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 2;
	v2[1] = 2;

	v1 = v1 + scal;

	ASSERT_EQ(v1 == v2, true);
	
	
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{

	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	TDynamicVector<int> res(2);

	double scal = 1.0;
	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 0;
	v2[1] = 0;

	v1 = v1 - scal;

	ASSERT_EQ(v1 == v2, true);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);

	double scal = 2.0;
	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 2;
	v2[1] = 2;

	v1 = v1 * scal;

	ASSERT_EQ(v1 == v2, true);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 2;
	v2[1] = 2;

	ASSERT_NO_THROW(v1 + v2);
	
	
}

TEST(TDynamicVector, correctly_do_move) {
	TDynamicVector<int> v1(5);
	int* old_pMem = v1.get_pMem();
	TDynamicVector<int> v2(std::move(v1));

	
	EXPECT_EQ(v1.size(), 0);
	EXPECT_EQ(v2.size(), 5);

	EXPECT_EQ(v1.get_pMem(), nullptr);
	EXPECT_EQ(v2.get_pMem(), old_pMem);
}

TEST(TDynamicVector, correctly_do_move_operator) {
	TDynamicVector<int> v1(5);
	int* old_pMem = v1.get_pMem();
	TDynamicVector<int> v2 = std::move(v1);

	EXPECT_EQ(v1.size(), 0);
	EXPECT_EQ(v2.size(), 5);

	EXPECT_EQ(v1.get_pMem(), nullptr);
	EXPECT_EQ(v2.get_pMem(), old_pMem);

}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(1);

	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 2;


	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 2;
	v2[1] = 2;

	ASSERT_NO_THROW(v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(1);
	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 2;

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 2;
	v2[1] = 2;

	ASSERT_NO_THROW(v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(5);

	
	ASSERT_ANY_THROW(v1 * v2);
}

