#pragma once

namespace YimMenu::Rendering
{
	// Base for a single widget in a Grid. Mirrors stand-reference's
	// src/Menu/GridItem.hpp/.cpp: a retained-mode leaf node whose
	// position/size is assigned once by its owning Grid's layout pass, and
	// whose virtual Draw() issues the actual draw calls (via GridRenderer)
	// every frame - no rebuilding of the widget itself per frame.
	class GridItem
	{
	public:
		explicit GridItem(float height) :
		    m_Height(height)
		{
		}

		virtual ~GridItem() = default;

		// Solid-colour/background draws (PrimitiveBatch pass).
		virtual void Draw() = 0;

		// Text draws (SpriteBatch pass, a separate batch type/pipeline
		// state from Draw() above - see GridRenderer::DrawImpl). Default
		// no-op: most items have no text of their own.
		virtual void DrawText()
		{
		}

		void SetPosition(float x, float y, float width)
		{
			m_X = x;
			m_Y = y;
			m_Width = width;
		}

		float GetHeight() const
		{
			return m_Height;
		}

	protected:
		float m_X{};
		float m_Y{};
		float m_Width{};
		float m_Height{};
	};
}
