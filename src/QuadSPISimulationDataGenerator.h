#ifndef QUADSPI_SIMULATION_DATA_GENERATOR
#define QUADSPI_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class QuadSPIAnalyzerSettings;

class QuadSPISimulationDataGenerator
{
public:
	QuadSPISimulationDataGenerator();
	~QuadSPISimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, QuadSPIAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	QuadSPIAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //QUADSPI_SIMULATION_DATA_GENERATOR