#pragma once
#include <imgui.h>

namespace YimMenu
{
	class Overlay
	{
	public:
		static void Draw();
	};

	enum class OverlayPosition
	{
		TopLeft = 0,
		TopRight,
		BottomLeft,
		BottomRight,
		Free
	};

	inline ImVec4 g_OverlayTextColor = ImVec4(1.f, 0.f, 0.f, 1.f); // default red
}