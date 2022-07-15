#include "QuadSPIAnalyzerSettings.h"
#include <AnalyzerHelpers.h>
#include <sstream>
#include <cstring>

/**
 * @brief Construct a new QuadSpi Analyzer Settings:: Spi Analyzer Settings object
 * 
 * We need to define the default values of the diferent parameters of the analyzer
 * such as channels, integer values, etc...
 * 
 * Fuerhtermore, we need to configure the interface for said objects.
 * 
 */
QuadSPIAnalyzerSettings::QuadSPIAnalyzerSettings()
:	mClockChannel( UNDEFINED_CHANNEL ),
	mEnableChannel( UNDEFINED_CHANNEL ),
	mD0Channel( UNDEFINED_CHANNEL ),
	mD1Channel( UNDEFINED_CHANNEL ),
	mD2Channel( UNDEFINED_CHANNEL ),
	mD3Channel( UNDEFINED_CHANNEL ),

	mEnableActiveState(BIT_LOW),
	mClockInactiveState(BIT_LOW),
	mShiftOrder(AnalyzerEnums::MsbFirst),
	mQuadSpiMode(AnalyzerEnums::RAW),

	mBytesPerTransfer(1),
	mAddressByteLength(3),
	mDummyCycles(4)
{
	//We configure the parameters and options that each interface object will display in the GUI
	mClockChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mClockChannelInterface->SetTitleAndTooltip( "Clock", "Clock (CLK)" );
	mClockChannelInterface->SetChannel( mClockChannel );

	mEnableChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mEnableChannelInterface->SetTitleAndTooltip( "Enable", "Enable (CS Chip Select)" );
	mEnableChannelInterface->SetChannel( mEnableChannel );

	mD0ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mD0ChannelInterface->SetTitleAndTooltip( "D0", "Data pin 0" );
	mD0ChannelInterface->SetChannel( mD0Channel );

	mD1ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mD1ChannelInterface->SetTitleAndTooltip( "D1", "Data pin 1" );
	mD1ChannelInterface->SetChannel( mD1Channel );

	mD2ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mD2ChannelInterface->SetTitleAndTooltip( "D2", "Data pin 2" );
	mD2ChannelInterface->SetChannel( mD2Channel );

	mD3ChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mD3ChannelInterface->SetTitleAndTooltip( "D3", "Data pin 3" );
	mD3ChannelInterface->SetChannel( mD3Channel );

	mEnableActiveStateInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mEnableActiveStateInterface->SetTitleAndTooltip( "Enable logic", "" );
	mEnableActiveStateInterface->AddNumber(BIT_LOW, "Enable line is Active Low (standar)", "");
	mEnableActiveStateInterface->AddNumber(BIT_HIGH, "Enable line is Active High", "");
	mEnableActiveStateInterface->SetNumber(mEnableActiveState);

	mClockInactiveStateInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mClockInactiveStateInterface->SetTitleAndTooltip( "Clock logic ", "" );
	mClockInactiveStateInterface->AddNumber(BIT_LOW, "Clock is Low when inactive (CPOL = 0)", "(CPOL) Clock Polarity = 0 and (CPHA) Clock Phase = 0");
	mClockInactiveStateInterface->AddNumber(BIT_HIGH, "Clock is High when inactive (CPOL = 1)", "(CPOL) Clock Polarity = 1 and (CPHA) Clock Phase = 1");
	mClockInactiveStateInterface->SetNumber(mClockInactiveState);

	mShiftOrderInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mShiftOrderInterface->SetTitleAndTooltip( "Significant bit", "" );
	mShiftOrderInterface->AddNumber(AnalyzerEnums::MsbFirst, "Most singificant bit first", "");
	mShiftOrderInterface->AddNumber(AnalyzerEnums::LsbFirst, "Less significant bit first", "");
	mShiftOrderInterface->SetNumber(mShiftOrder);

	mQuadSpiModeInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mQuadSpiModeInterface->SetTitleAndTooltip( "Quad SPI mode", "" );
	mQuadSpiModeInterface->AddNumber(AnalyzerEnums::QuadSPI, "Opcode and adress send in line D0", "");
	mQuadSpiModeInterface->AddNumber(AnalyzerEnums::QuadIO, "Opcode send in line D0", "");
	mQuadSpiModeInterface->AddNumber(AnalyzerEnums::QPI, "All data send over the four data lines", "");
	mQuadSpiModeInterface->AddNumber(AnalyzerEnums::RAW, "Reads raw data in D0-3", "");
	mQuadSpiModeInterface->SetNumber(mQuadSpiMode);

	mBytesPerTransferInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mBytesPerTransferInterface->SetTitleAndTooltip( "Data word lenght", "" );
	for (U32 i = 1; i < 9; i++)
	{
		std::stringstream ss;

		ss << i << " bytes";
		mBytesPerTransferInterface->AddNumber(i, ss.str().c_str(), "");
	}
	mBytesPerTransferInterface->SetNumber(mBytesPerTransfer);

	mAddressByteLengthInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mAddressByteLengthInterface->SetTitleAndTooltip( "Address length (bytes)", "" );
	for (U32 i = 1; i < 5; i++)
	{
		std::stringstream ss;

		ss << i << " bytes";
		mAddressByteLengthInterface->AddNumber(i, ss.str().c_str(), "");
	}
	mAddressByteLengthInterface->SetNumber(mAddressByteLength);

	mDummyCyclesInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mDummyCyclesInterface->SetTitleAndTooltip( "Number of dummy cycles", "Dummy cycles between the end of the adress and the start of the data" );
	for (U32 i = 0; i < 16; i++)
	{
		std::stringstream ss;

		ss << i << " cycles";
		mDummyCyclesInterface->AddNumber(i, ss.str().c_str(), "");
	}
	mDummyCyclesInterface->SetNumber(mDummyCycles);


	//We add said interface objects to de GUI
	AddInterface(mClockChannelInterface.get());
	AddInterface(mEnableChannelInterface.get());
	AddInterface(mD0ChannelInterface.get());
	AddInterface(mD1ChannelInterface.get());
	AddInterface(mD2ChannelInterface.get());
	AddInterface(mD3ChannelInterface.get());
	AddInterface(mEnableActiveStateInterface.get());
	AddInterface(mClockInactiveStateInterface.get());
	AddInterface(mShiftOrderInterface.get());
	AddInterface(mQuadSpiModeInterface.get());
	AddInterface(mBytesPerTransferInterface.get());
	AddInterface(mAddressByteLengthInterface.get());
	AddInterface(mDummyCyclesInterface.get());

	//Specifiying export options
	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	//Specify to the SDK which channels are in use
	ClearChannels();
	AddChannel( mClockChannel, "CLOCK", false ); //false since we specified UNDEFINED_CHANNEL as a default.
	AddChannel( mEnableChannel, "Enable", false );
	AddChannel( mD0Channel, "D0", false );
	AddChannel( mD1Channel, "D1", false );
	AddChannel( mD2Channel, "D2", false );
	AddChannel( mD3Channel, "D3", false );
}

QuadSPIAnalyzerSettings::~QuadSPIAnalyzerSettings()
{
}

/**
 * @brief Changes the values of our interface objets to the settings specified by the user
 * 
 * @return true: the user's settings are accepted.
 * @return false: The user's settings are rejected.
 */
bool QuadSPIAnalyzerSettings::SetSettingsFromInterfaces()
{
	Channel clock = mClockChannelInterface->GetChannel();
	Channel enable = mEnableChannelInterface->GetChannel();
	Channel d0 = mD0ChannelInterface->GetChannel();
	Channel d1 = mD1ChannelInterface->GetChannel();
	Channel d2 = mD2ChannelInterface->GetChannel();
	Channel d3 = mD3ChannelInterface->GetChannel();

	std::vector<Channel> channels;
	channels.push_back(clock);
	channels.push_back(enable);
	channels.push_back(d0);
	channels.push_back(d1);
	channels.push_back(d2);
	channels.push_back(d3);

	if( AnalyzerHelpers::DoChannelsOverlap(&channels[0], channels.size() ) == true)
	{
		SetErrorText( "Channels overlap, please set diferent channels for each input");
		return false;
	}

	//See if every channel has to be mandatory. For example, as long as we have a clk maybe enable can be not deffined.
	if( (d0 == UNDEFINED_CHANNEL) || (d1 == UNDEFINED_CHANNEL) || (d2 == UNDEFINED_CHANNEL) || (d3 == UNDEFINED_CHANNEL) || (clock == UNDEFINED_CHANNEL)  || (enable == UNDEFINED_CHANNEL)  )
	{
		SetErrorText( "Please select an input for every channel");
		return false;
	}

	 mClockChannel 	= mClockChannelInterface->GetChannel();
	 mEnableChannel = mEnableChannelInterface->GetChannel();
	 mD0Channel 	= mD0ChannelInterface->GetChannel();
	 mD1Channel 	= mD1ChannelInterface->GetChannel();
	 mD2Channel 	= mD2ChannelInterface->GetChannel();
	 mD3Channel 	= mD3ChannelInterface->GetChannel();


	mBytesPerTransfer 	= U32( mBytesPerTransferInterface->GetNumber() );
	mAddressByteLength 	= U8( mAddressByteLengthInterface->GetNumber() );
	mDummyCycles 		= U8( mDummyCyclesInterface->GetNumber() );

	mQuadSpiMode 		= (AnalyzerEnums::QSpiMode) U32(mQuadSpiModeInterface->GetNumber()); 
	mShiftOrder 		= (AnalyzerEnums::ShiftOrder) U32( mShiftOrderInterface->GetNumber() );
	mClockInactiveState = (BitState) U32( mClockInactiveStateInterface->GetNumber() );
	mEnableActiveState 	= (BitState) U32( mEnableActiveStateInterface->GetNumber() );

	ClearChannels();
	AddChannel( mClockChannel, "Clock", mClockChannel != UNDEFINED_CHANNEL );
	AddChannel( mEnableChannel, "Enable", mEnableChannel != UNDEFINED_CHANNEL );
	AddChannel( mD0Channel, "D0", mD0Channel != UNDEFINED_CHANNEL );
	AddChannel( mD1Channel, "D1", mD1Channel != UNDEFINED_CHANNEL );
	AddChannel( mD2Channel, "D2", mD2Channel!= UNDEFINED_CHANNEL );
	AddChannel( mD3Channel, "D3", mD3Channel != UNDEFINED_CHANNEL );
	return true;
}

void QuadSPIAnalyzerSettings::UpdateInterfacesFromSettings()
{
	mInputChannelInterface->SetChannel( mInputChannel );
	mBitRateInterface->SetInteger( mBitRate );
}

void QuadSPIAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mInputChannel;
	text_archive >> mBitRate;

	ClearChannels();
	AddChannel( mInputChannel, "QuadSPI", true );

	UpdateInterfacesFromSettings();
}

const char* QuadSPIAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mInputChannel;
	text_archive << mBitRate;

	return SetReturnString( text_archive.GetString() );
}
