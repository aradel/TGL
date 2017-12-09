#ifndef TIMER_H
#define TIMER_H
namespace TGL 
{	
	class Timer 
	{
		struct TimeVar;
		private:
			TimeVar* pVar;
		public:
			Timer();
			~Timer();
		public:
			void Pause() noexcept;
			void Start() noexcept;
			void Tick() noexcept;
			float GetDeltaTime() const noexcept;
	};

}

#endif