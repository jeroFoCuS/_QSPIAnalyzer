#ifndef QUADSPI_ANALYZER_H
#define QUADSPI_ANALYZER_H

#include <Analyzer.h>
#include "QuadSPIAnalyzerResults.h"
#include "QuadSPISimulationDataGenerator.h"

class QuadSPIAnalyzerSettings;
class ANALYZER_EXPORT QuadSPIAnalyzer : public Analyzer2
{
public:
	QuadSPIAnalyzer();
	virtual ~QuadSPIAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< QuadSPIAnalyzerSettings > mSettings;
	std::auto_ptr< QuadSPIAnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	QuadSPISimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //QUADSPI_ANALYZER_H
