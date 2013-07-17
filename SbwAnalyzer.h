#ifndef SBW_ANALYZER_H
#define SBW_ANALYZER_H

#include <Analyzer.h>
#include "SbwAnalyzerResults.h"
#include "SbwSimulationDataGenerator.h"

enum JtagState {
    JtagReset,
    JtagIdle,
    
    JtagSelectDR,
    JtagCaptureDR,
    JtagShiftDR,
    JtagExit1DR,
    JtagPauseDR,
    JtagExit2DR,
    JtagUpdateDR,

    JtagSelectIR,
    JtagCaptureIR,
    JtagShiftIR,
    JtagExit1IR,
    JtagPauseIR,
    JtagExit2IR,
    JtagUpdateIR
};

class SbwAnalyzerSettings;
class SbwAnalyzer : public Analyzer2
{
public:
	SbwAnalyzer();
	virtual ~SbwAnalyzer();
	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //functions
	void Setup();
    void ProcessStep();
    U64 FlipWord(U64 word, U32 bits);
	
protected:  //vars
	std::auto_ptr< SbwAnalyzerSettings > mSettings;
	std::auto_ptr< SbwAnalyzerResults > mResults;
	bool mSimulationInitilized;
	SbwSimulationDataGenerator mSimulationDataGenerator;

	AnalyzerChannelData* mTCK; 
	AnalyzerChannelData* mTMS;
	AnalyzerChannelData* mTDI;
	AnalyzerChannelData* mTDO;
	AnalyzerChannelData* mTRST;

	U64 mCurrentSample, mFirstSample;

    enum JtagState mState;
    U64 mDataIn, mDataOut;
    U32 mBits;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //SBW_ANALYZER_H
