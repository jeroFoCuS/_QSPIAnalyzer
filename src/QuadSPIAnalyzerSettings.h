#ifndef QUADSPI_ANALYZER_SETTINGS
#define QUADSPI_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>
#include <QuadSPITypes.h>

/**
 * @brief Our QuadSPI Analyzer Settings class
 * 
 * Inherits most of its fun tions from the AnalyzerSettings class form the SDK.
 * Here, we have to define all the channels, integer values, enums or any other
 * configurable parameter that our analyzer will need to use.
 * 
 */
class QuadSPIAnalyzerSettings : public AnalyzerSettings
{
public:
	QuadSPIAnalyzerSettings();
	virtual ~QuadSPIAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	//Parameters/objects that our analyzer use. This is to said, the channels, const values, etc...
	Channel mClockChannel;
	Channel mEnableChannel;
	Channel mD0Channel;
	Channel mD1Channel;
	Channel mD2Channel;
	Channel mD3Channel;
	
	BitState mEnableActiveState;
	BitState mClockInactiveState;

	AnalyzerEnums::ShiftOrder mShiftOrder;
	AnalyzerEnums::QSpiMode mQuadSpiMode;
	
	U32	mBytesPerTransfer;
	U8 	mAddressByteLength;
	U8  mDummyCycles;
	

protected:
	//Interface objects for every parameter that our analyzer will need to use
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mClockChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mEnableChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mD0ChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mD1ChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mD2ChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mD3ChannelInterface;

	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mEnableActiveStateInterface;
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mClockInactiveStateInterface;
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mShiftOrderInterface;
	
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mBytesPerTransferInterface;
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mAddressByteLengthInterface; 
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mDummyCyclesInterface; 
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mQuadSpiModeInterface; 

};

#endif //QUADSPI_ANALYZER_SETTINGS
