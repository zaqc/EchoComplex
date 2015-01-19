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

	void Write(FILE *aFile) {
		fwrite(this, sizeof(DataBlock), 1, aFile);
	}

	void Read(FILE *aFile) {
		fread(this, sizeof(DataBlock), 1, aFile);
	}

	bool PositionInBlock(int aFrame) {
		return aFrame >= m_Position && aFrame < m_Position + m_FrameCount;
	}
};
//----------------------------------------------------------------------------

struct DataFileHeader {
	char m_Header[3];
	char m_Version[5];
	__int32_t m_HardwareID;	// код аппарата
	__int32_t m_TripID;		// ID проезда
	__int32_t m_SessionID;	// ID сессии
	time_t m_DataTime;		// Дата начала проезда

	__int64_t m_IndexOffset;

	char m_TripCaption[128];

	void Write(FILE *aFile) {
		fwrite(this, sizeof(DataFileHeader), 1, aFile);
	}

	void Read(FILE *aFile) {
		fread(this, sizeof(DataFileHeader), 1, aFile);
	}
};
//----------------------------------------------------------------------------

struct TripPoint {
	__int32_t m_DirectionID;
	__int32_t m_WayID;
	__int32_t m_Km;
	__int32_t m_M;
	__int32_t m_StationID;
	__int32_t m_Switcher;

	void Write(FILE *aFile) {
		fwrite(this, sizeof(TripPoint), 1, aFile);
	}

	void Read(FILE *aFile) {
		fread(this, sizeof(TripPoint), 1, aFile);
	}
};
//----------------------------------------------------------------------------

struct CorrectionMarker {
	__int64_t m_MasterFrame;
	time_t m_Now;
	TripPoint m_TripPoint;	// Точка на маршруте перед корректировкой
	__int32_t m_IncDec;		// На увеличение = 1
	__int32_t m_ROR;		// Правая справа = 1
	__int32_t m_Cot;		// Котлом=1

	void Write(FILE *aFile) {
		fwrite(this, sizeof(CorrectionMarker), 1, aFile);
	}

	void Read(FILE *aFile) {
		fread(this, sizeof(CorrectionMarker), 1, aFile);
	}
};
//----------------------------------------------------------------------------

struct TextMarker {
	__int64_t m_MasterFrame;
	time_t m_Now;
	int m_DeletedFlag;	// состояние корректировки (Deleted/Modified)
	int m_TextSize;
	char *m_Text;

	void Write(FILE *aFile) {
		fwrite(this, sizeof(TextMarker) - sizeof(char*), 1, aFile);
		if (0 != m_TextSize)
			fwrite(m_Text, m_TextSize, 1, aFile);
	}

	void Read(FILE *aFile) {
		fread(this, sizeof(TextMarker) - sizeof(char*), 1, aFile);
		if (0 != m_TextSize) {
			m_Text = new char[m_TextSize];
			fread(m_Text, m_TextSize, 1, aFile);
		}
	}
};
//----------------------------------------------------------------------------

class DataFileIndex {
protected:
	int m_FrameCount;
	XLock m_Lock;
	std::vector<DataBlock*> m_DataBlock;
	std::vector<CorrectionMarker*> m_CorrectionMarker;
	std::vector<TextMarker*> m_TextMarker;
public:
	DataFileIndex();
	virtual ~DataFileIndex();

	void Write(FILE *aFile);
	void Read(FILE *aFile);

	void AddDataBlock(DataBlock *aDB);
	DataBlock * FindDataBlock(int aFrame);
};
//----------------------------------------------------------------------------

class DataFile {
protected:
	FILE *m_File;
	DataFileIndex m_Index;
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
