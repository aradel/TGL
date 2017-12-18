#ifndef COMMAND_LIST_HPP
#define COMMAND_LIST_HPP
#include "../TGL.hpp"
#include <d3d12.h>
#include <memory>
namespace TGL 
{
	struct ViewPort;
	class PipelineState;
	class CommandList 
	{
	public:
		virtual void Release() = 0;
		virtual void StartRecording() = 0;
		virtual void StopRecording() = 0;

		virtual void ClearRenderTarget(uint8 r, uint8 g, uint8 b) = 0;

		virtual void SetViewPort(const TGL::ViewPort& viewPort) = 0;
		virtual bool SetPipelineState(const TGL::PipelineState& pipeline) = 0;
	};
	
	typedef std::shared_ptr<CommandList> CommandListPtr;

	class CommandListD3D12 : public CommandList
	{
		private:
			enum State { NotRecording = 0, Recording = 1 };
			__declspec(align(4)) LONG state = State::NotRecording;
		public:
			ID3D12CommandAllocator* pCmdAllocator = nullptr;
			ID3D12GraphicsCommandList* pCmdList = nullptr;
		public:
			void Release() override;
			void StartRecording() override;
			void StopRecording() override;

			void ClearRenderTarget(uint8 r, uint8 g, uint8 b) override;
			
			void SetViewPort(const TGL::ViewPort& viewPort) override;
			bool SetPipelineState(const TGL::PipelineState& pipeline) override;

	};
}
#endif