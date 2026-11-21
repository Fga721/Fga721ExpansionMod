#pragma once

namespace Sexy
{
	class PopAnimListener
	{
	public:
		virtual ~PopAnimListener() {}
		virtual void PopAnimPlaySample(std::string theSampleName, int thePan, double theVolume, double theNumSteps) {}
		virtual void PopAnimStopped(int theId) {}
		virtual void PopAnimCommand(int theId, std::string theCommand, std::string theParam) {}
		virtual bool PopAnimCommand(int theId, void* theSpriteInst, std::string theCommand, std::string theParam) {}
	};
}