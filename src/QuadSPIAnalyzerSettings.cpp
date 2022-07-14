#include "QuadSPIAnalyzerSettings.h"
#include <AnalyzerHelpers.h>
#include <sstream>
#include <cstring>


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
	mAddressByteLength(3)
	

{
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
	mQuadSpiModeInterface->SetTitleAndTooltip( "Significant bit", "" );
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

		ss << i << "bytes";
		mBytesPerTransferInterface->AddNumber(i, ss.str().c_str(), "");
	}
	mBytesPerTransferInterface->SetNumber(mBytesPerTransfer);

	mAddressByteLengthInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mAddressByteLengthInterface->SetTitleAndTooltip( "Address length (bytes)", "" );
	for (U32 i = 1; i < 5; i++)
	{
		std::stringstream ss;

		ss << i << "bytes";
		mBytesPerTransferInterface->AddNumber(i, ss.str().c_str(), "");
	}
	mAddressByteLengthInterface->SetNumber(mAddressByteLength);

	mDummyCyclesInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mDummyCyclesInterface->SetTitleAndTooltip( "Number of dummy cycles", "Dummy cycles between the end of the adress and the start of the data" );
	for (U32 i = 0; i < 16; i++)
	{
		std::stringstream ss;

		ss << i << "cycles";
		mDummyCyclesInterface->AddNumber(i, ss.str().c_str(), "");
	}
	mDummyCyclesInterface->SetNumber(mDummyCycles);

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

	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	AddChannel( mClockChannel, "Serial", false );
	AddChannel( mEnableChannel, "Serial", false );
	AddChannel( mD0Channel, "Serial", false );
	AddChannel( mD1Channel, "Serial", false );
	AddChannel( mD2Channel, "Serial", false );
	AddChannel( mD3Channel, "Serial", false );
}

QuadSPIAnalyzerSettings::~QuadSPIAnalyzerSettings()
{
}

bool QuadSPIAnalyzerSettings::SetSettingsFromInterfaces()
{
	mInputChannel = mInputChannelInterface->GetChannel();
	mBitRate = mBitRateInterface->GetInteger();

	ClearChannels();
	AddChannel( mInputChannel, "QuadSPI", true );

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
