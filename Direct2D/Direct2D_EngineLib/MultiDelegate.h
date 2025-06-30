#pragma once
#include <vector>
#include <functional>

template<typename... Args>
class MultiDelegate {
	struct Slot
	{
		void* instance;						// �ݹ� ���п� ������
		std::function<void(Args...)> func;	// �ݹ� �Լ� ����Ʈ
	};
	std::vector<Slot> slots;

public:
	// Add Function
	void AddListener(void* instance, const std::function<void(Args...)>& f)
	{
		slots.push_back({ instance, f });
	}

	// Remove Function (����� instacne Ȱ��)
	void Remove(void* instance)
	{
		slots.erase(std::remove_if(slots.begin(), slots.end(),
			[instance](const Slot& s) { return s.instance == instance; }),
			slots.end());
	}

	// Claer Functions
	void Clear() { slots.clear(); }

	// ��ϵ� Functions Call
	void Invoke(Args... args) const
	{
		// instance ����ִ��� �˻� ���� x
		// ����Ʈ ������ ������ �ٲ���, Handle ID�� ������� ������Դϴ�
		for (const auto& s : slots)
			if (s.func) s.func(args...);
	}
};
