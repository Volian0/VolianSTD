//
// Created by volian on 12/26/21.
//

#include "unique_ptr.hpp"

[[nodiscard]] auto test_unique_ptr() noexcept -> int
{
	volian::UniquePtr<int> ptr1;
	if (ptr1.get() != nullptr)
	{
		return 1;
	}
	volian::UniquePtr<int> ptr2{new int};
	if (ptr2.get() == nullptr)
	{
		return 2;
	}
	*ptr2 = 420;
	if (*ptr2 != 420)
	{
		return 3;
	}
	ptr2.swap(ptr1);
	if (ptr1.get() == nullptr || ptr2.get() != nullptr || *ptr1 != 420)
	{
		return 4;
	}
	ptr2 = static_cast<volian::UniquePtr<int>&&>(ptr1);
	auto ptr3{static_cast<volian::UniquePtr<int>&&>(ptr2)};
	if (ptr3.get() == nullptr || ptr1.get() != nullptr || ptr2.get() != nullptr || *ptr3 != 420)
	{
		return 5;
	}
	if (!ptr3 || ptr1 || ptr2)
	{
		return 6;
	}
	auto int_ptr{ptr3.release()};
	if (ptr3 || int_ptr == nullptr || *int_ptr != 420)
	{
		return 7;
	}
	ptr1.reset(int_ptr);
	if (!ptr1 || *ptr1 != 420)
	{
		return 8;
	}
	struct Object
	{
		int variable1;
		int variable2;
	};
	volian::UniquePtr<Object> ptr4{new Object{47,99}};
	ptr4->variable1 = 91;
	if (ptr4->variable1 != 91 || ptr4->variable2 != 99)
	{
		return 9;
	}
	//ptr1 = ptr2;
	//auto ptr5 = ptr2;
	return 0;
}