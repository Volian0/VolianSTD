//
// Created by volian on 12/25/21.
//

#ifndef VOLIANSTD_UNIQUE_PTR_HPP
#define VOLIANSTD_UNIQUE_PTR_HPP

namespace volian
{

	template<typename T>
	class UniquePtr
	{
	public:
		constexpr explicit UniquePtr() noexcept
			: m_ptr{nullptr}
		{}

		constexpr explicit UniquePtr(T *t_ptr) noexcept
			: m_ptr{t_ptr}
		{}

		virtual ~UniquePtr() noexcept
		{
			delete m_ptr;
		}

		UniquePtr(const UniquePtr &) = delete;

		auto operator=(const UniquePtr &) -> UniquePtr & = delete;

		constexpr UniquePtr(UniquePtr &&t_unique_ptr) noexcept
			: m_ptr{t_unique_ptr.release()}
		{}

		auto operator=(UniquePtr &&t_unique_ptr) noexcept -> UniquePtr &
		{
			if (this != &t_unique_ptr)
			{
				reset(t_unique_ptr.release());
			}
			return *this;
		}

		[[nodiscard]] constexpr auto release() noexcept -> T *
		{
			const auto ptr{m_ptr};
			m_ptr = nullptr;
			return ptr;
		}

		auto reset(T *t_ptr = nullptr) noexcept -> void
		{
			delete m_ptr;
			m_ptr = t_ptr;
		}

		constexpr auto swap(UniquePtr &t_unique_ptr) noexcept -> void
		{
			const auto ptr{m_ptr};
			m_ptr = t_unique_ptr.m_ptr;
			t_unique_ptr.m_ptr = ptr;
		}

		[[nodiscard]] constexpr auto get() const noexcept -> T *
		{
			return m_ptr;
		}

		[[nodiscard]] constexpr explicit operator bool() const noexcept
		{
			return m_ptr;
		}

		[[nodiscard]] constexpr auto operator->() const noexcept -> T *
		{
			return m_ptr;
		}

		[[nodiscard]] constexpr auto operator*() const noexcept -> T &
		{
			return *m_ptr;
		}

	private:
		T *m_ptr;
	};

}

#endif //VOLIANSTD_UNIQUE_PTR_HPP
