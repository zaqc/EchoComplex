/*
 * DataFile.cpp
 *
 *  Created on: Jan 14, 2015
 *      Author: zaqc
 */

#include "DataFile.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include "../Util/XThread.h"
//----------------------------------------------------------------------------

namespace usm {

//============================================================================
//	DataBlock
//============================================================================
void DataBlock::Write(FILE *aFile) {
	fwrite(&m_FilePos, sizeof(__int64_t ), 1, aFile);
	fwrite(&m_RealSize, sizeof(__int32_t ), 1, aFile);
	fwrite(&m_ZippedSize, sizeof(__int32_t ), 1, aFile);
	fwrite(&m_Position, sizeof(__int32_t ), 1, aFile);
	fwrite(&m_FrameCount, sizeof(__int32_t ), 1, aFile);
}
//----------------------------------------------------------------------------

void DataBlock::Read(FILE *aFile) {
	fread(&m_FilePos, sizeof(__int64_t ), 1, aFile);
	fread(&m_RealSize, sizeof(__int32_t ), 1, aFile);
	fread(&m_ZippedSize, sizeof(__int32_t ), 1, aFile);
	fread(&m_Position, sizeof(__int32_t ), 1, aFile);
	fread(&m_FrameCount, sizeof(__int32_t ), 1, aFile);
}
//----------------------------------------------------------------------------

bool DataBlock::PositionInBlock(int aFrame) {
	return aFrame >= m_Position && aFrame < m_Position + m_FrameCount;
}
//----------------------------------------------------------------------------

//============================================================================
//	DataBlockIndex
//============================================================================
DataBlockIndex::DataBlockIndex() :
		m_Lock() {
	m_FrameCount = 0;
}
//----------------------------------------------------------------------------

DataBlockIndex::~DataBlockIndex() {
}
//----------------------------------------------------------------------------

void DataBlockIndex::Add(DataBlock *aDB) {

}
//----------------------------------------------------------------------------

DataBlock * DataBlockIndex::FindDataBlock(int aFrame) {

	DataBlock *ret = NULL;
	m_Lock.Lock();
	for (std::vector<DataBlock*>::iterator i = m_DataBlock.begin();
			i != m_DataBlock.end(); i++) {
		if ((*i)->PositionInBlock(aFrame)) {
			ret = *i;
			break;
		}
	}
	m_Lock.Unlock();

	return ret;
}
//----------------------------------------------------------------------------

//============================================================================
//	DataFile
//============================================================================
DataFile::DataFile() {
	m_File = NULL;
}
//----------------------------------------------------------------------------

DataFile::~DataFile() {
}
//----------------------------------------------------------------------------

void DataFile::Open(void) {
	m_File = fopen("/home/zaqc/my_file_stdio.tst", "w+");
}
//----------------------------------------------------------------------------

void DataFile::Close(void) {
	fclose(m_File);
}
//----------------------------------------------------------------------------

void DataFile::WriteData(DataBlock &aDB, char *aBuf, int aSize) {
}
//----------------------------------------------------------------------------

void DataFile::ReadData(DataBlock &aDB, char *aBuf, int &aSize) {

}
//----------------------------------------------------------------------------

} /* namespace usm */
