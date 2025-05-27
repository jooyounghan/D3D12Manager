#pragma once
#include "D3D12DllHelper.h"
#include "D3D12AppHelper.h"

namespace Utilities
{
	template<typename T, UINT Capacity>
	class LockfreeRingBuffer
	{
	public:
		LockfreeRingBuffer() = default;
		~LockfreeRingBuffer() = default;

	public:
		bool Push(const T& item);
		bool Pop(T* out);
		bool TryNPop(UINT count, T* out);

	private:
		struct Slot
		{
			volatile LONG status = 0;
			T data;
		};

		volatile LONG m_head = 0;
		volatile LONG m_tail = 0;
		Slot m_ringBuffer[Capacity];
	};

	template<typename T, UINT Capacity>
	inline bool LockfreeRingBuffer<T, Capacity>::Push(const T& item)
	{
		while (true)
		{
			LONG head = m_head;
			LONG tail = m_tail;
			LONG count = head - tail;
			if (count >= Capacity) return false;

			if (InterlockedCompareExchange(&m_head, head + 1, head) == head)
			{
				LONG index = head % Capacity;
				Slot& slot = m_ringBuffer[index];
				slot.data = item;
				InterlockedCompareExchange(&slot.status, 1, 0);
				return true;
			}
			YieldProcessor();
		}
	}

	template<typename T, UINT Capacity>
	inline bool LockfreeRingBuffer<T, Capacity>::Pop(T* out)
	{
		while (true)
		{
			LONG head = m_head;
			LONG tail = m_tail;
			if (tail >= head) return false;

			if (InterlockedCompareExchange(&m_tail, tail + 1, tail) == tail)
			{
				LONG index = tail % Capacity;
				while (InterlockedCompareExchange(&m_ringBuffer[index].status, 0, 1) == 0)
				{
					YieldProcessor();
				}

				*out = m_ringBuffer[index].data;
				return true;
			}

			YieldProcessor();
		}
	}

	template<typename T, UINT Capacity>
	inline bool LockfreeRingBuffer<T, Capacity>::TryNPop(UINT count, T* out)
	{
		for (UINT spinCount = 0; spinCount < count; ++spinCount)
		{
			LONG head = m_head;
			LONG tail = m_tail;
			if (tail >= head) break;

			if (InterlockedCompareExchange(&m_tail, tail + 1, tail) == tail)
			{
				LONG index = tail % Capacity;
				while (InterlockedCompareExchange(&m_ringBuffer[index].status, 0, 1) == 0)
				{
					YieldProcessor();
				}

				*out = m_ringBuffer[index].data;
				return true;
			}

			YieldProcessor();
		}
		return false;
	}
}

