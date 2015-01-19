/*
 * DataFile.h
 *
 *  Created on: Jan 14, 2015
 *      Author: zaqc
 */

#ifndef DATAFILE_DATAFILE_H_
#define DATAFILE_DATAFILE_H_

#include <stdio.h>
#include <vector>
#include "../Util/XThread.h"
//----------------------------------------------------------------------------

namespace usm {

struct DataBlock {
	__int64_t m_FilePos;
	__int32_t m_RealSize;
	__int32_t m_ZippedSize;
	__int32_t m_Position;
	__int32_t m_FrameCount;

	void Write(FILE *aFile);
	void Read(FILE *aFile);

	bool PositionInBlock(int aFrame);
};
//----------------------------------------------------------------------------

class DataBlockIndex {
protected:
	XLock m_Lock;
	std::vector<DataBlock*> m_DataBlock;
	int m_FrameCount;
public:
	DataBlockIndex();
	virtual ~DataBlockIndex();

	void Add(DataBlock *aDB);
	DataBlock * FindDataBlock(int aFrame);
};
//----------------------------------------------------------------------------

struct DataFileHeader {
	char m_Header[3];
	char m_Version[5];
	__int32_t m_HardwareID;
	__int32_t m_TripID;
	__int32_t m_SessionID;
	time_t m_DataTime;

	__int64_t m_TripEdge;
	char m_TripCaption[128];
};
//----------------------------------------------------------------------------

struct TripPoint {
	__int32_t m_DirectionID;
	__int32_t m_WayID;
	__int32_t m_Km;
	__int32_t m_M;
	__int32_t m_StationID;
	__int32_t m_Switcher;
};
//----------------------------------------------------------------------------

class TripPointIndex {
protected:
	std::vector<TripPoint> m_TripEdge;
public:
};
//----------------------------------------------------------------------------

struct CorrectionMarker {
	TripPoint m_TripPoint;	// Точка на маршруте
	__int32_t m_IncDec;		// На увеличение = 1
	__int32_t m_ROR;		// Правая справа = 1
	__int32_t m_Cot;		// Котлом=1
};
//----------------------------------------------------------------------------

class DataFile {
protected:
	FILE *m_File;
	DataBlockIndex m_BlockIndex;
public:
	DataFile();
	virtual ~DataFile();

	void Create(void);
	void Open(void);
	void Close(void);

	void WriteData(DataBlock &aDB, char *aBuf, int aSize);
	void ReadData(DataBlock &aDB, char *aBuf, int &aSize);
};
//----------------------------------------------------------------------------

class WriteCacher {

};
//----------------------------------------------------------------------------

class ReadCacher {

};
//----------------------------------------------------------------------------

} /* namespace usm */

#endif /* DATAFILE_DATAFILE_H_ */
