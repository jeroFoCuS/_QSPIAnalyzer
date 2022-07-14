#ifndef QUADSPI_ANALYZER_RESULTS
#define QUADSPI_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class QuadSPIAnalyzer;
class QuadSPIAnalyzerSettings;

class QuadSPIAnalyzerResults : public AnalyzerResults
{
public:
	QuadSPIAnalyzerResults( QuadSPIAnalyzer* analyzer, QuadSPIAnalyzerSettings* settings );
	virtual ~QuadSPIAnalyzerResults();

	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );

protected: //functions

protected:  //vars
	QuadSPIAnalyzerSettings* mSettings;
	QuadSPIAnalyzer* mAnalyzer;
};

#endif //QUADSPI_ANALYZER_RESULTS
