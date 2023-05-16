#pragma once
#include "Example.hpp"
#include "Core/IManager.hpp"

namespace UpPower
{
	class GraphicEngine: public IManager<GraphicEngine>
	{
	public:
		virtual void DoInit();
		virtual void DoUpdate();
		virtual void DoDestroy();
	
	private:
		Example* m_pExample;
	};
}