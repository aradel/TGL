#ifndef COMMAND_LIST_HPP
#define COMMAND_LIST_HPP
#include <d3d12.h>
#include "../TGL.hpp"

namespace TGL 
{
	struct Viewport;
	class PipelineState;
	class CommandList 
	{
		virtual void SetViewport(const TGL::Viewport& viewport) = 0;
		virtual bool SetPipelineState(const TGL::PipelineState& pipeline) = 0;
	};
}
#endif