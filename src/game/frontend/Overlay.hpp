#pragma once

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
}