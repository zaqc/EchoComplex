/*
 * DataFile.cpp
 *
 *  Created on: Jan 14, 2015
 *      Author: zaqc
 */

#include "DataFile.h"
#include "../Util/XThread.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
//----------------------------------------------------------------------------

namespace usm {

//============================================================================
//	DataBlockIndex
//============================================================================
DataFileIndex::DataFileIndex() :
		m_Lock() {
	m_FrameCount = 0;
	time_t t;
	time(&t);
	tm *lt = localtime(&t);
	std::cout << asctime(lt) << std::endl;
}
//----------------------------------------------------------------------------

DataFileIndex::~DataFileIndex() {
}
//----------------------------------------------------------------------------

void DataFileIndex::AddDataBlock(DataBlock *aDB) {
	m_Lock.Lock();
	aDB->m_Position = m_FrameCount;
	m_DataBlock.push_back(aDB);
	m_FrameCount += aDB->m_FrameCount;
	m_Lock.Unlock();
}
//----------------------------------------------------------------------------

DataBlock * DataFileIndex::FindDataBlock(int aFrame) {

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
