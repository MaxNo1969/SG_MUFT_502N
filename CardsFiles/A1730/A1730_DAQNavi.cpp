// ---------------------------------------------------------------------------
#pragma hdrstop
//#ifdef A1730_DAQNaviR
#include "A1730_DAQNavi.h"
#include <SysUtils.hpp>
#include "unTUtils.h"
#include "unTExtFunction.h"
#include "unSQLDbModule.h"
#pragma package(smart_init)

#ifdef VIRT1730
BYTE input[4];
BYTE output[4];
#endif
// ---------------------------------------------------------------------------
A1730_DAQNavi::A1730_DAQNavi(int &_DevNum,int &_codeErr)
{
/*
	_codeErr=0;
	int oldDevNum=_DevNum;
#ifndef VIRT1730
	DeviceInformation devInfo(_DevNum);
	instantDiCtrl = AdxInstantDiCtrlCreate();
	instantDoCtrl = AdxInstantDoCtrlCreate();
	//devInfo.DeviceNumber=2;
	AnsiString strInfo="";
	_codeErr = instantDiCtrl->setSelectedDevice(devInfo);
	_codeErr = instantDoCtrl->setSelectedDevice(devInfo);
	//if (BioFailed(_codeErr)){
	if (_codeErr<0){
	//instantDiCtrl->Cleanup();
	//instantDoCtrl->Cleanup();
	//instantDiCtrl->Dispose();
	//instantDoCtrl->Dispose();
	//instantDiCtrl=NULL;
	//instantDoCtrl=NULL;
	for (int i = 0; i < 16; i++) {
		devInfo.DeviceNumber=i;
		//DeviceInformation devInfo2(i);
		//instantDiCtrl = AdxInstantDiCtrlCreate();
		//instantDoCtrl = AdxInstantDoCtrlCreate();
		_codeErr = instantDiCtrl->setSelectedDevice(devInfo);
		_codeErr = instantDoCtrl->setSelectedDevice(devInfo);
		//instantDiCtrl->
	  if (_codeErr<0) {
		 //instantDiCtrl->Dispose();
		 //instantDoCtrl->Dispose();
		 //instantDiCtrl=NULL;
		 //instantDoCtrl=NULL;
	  }else{
		  //int TSqlDBModule::UpdIntSql(AnsiString _tableName, AnsiString _fieldName,int _fieldValue, AnsiString _where);
		  _DevNum=i;
		  SqlDBModule->UpdIntSql("PCIE1730Params","Devnum",i,"Devnum="+IntToStr(oldDevNum));
		  //serg
		  break;
	  }
	}

		//TExtFunction::ShowBigModalMessage("A1730_DAQNavi::A1730_DAQNavi: не смогли открыть плату Advantech1730", clRed);
		//throw(Exception("A1730_DAQNavi::A1730_DAQNavi: не смогли открыть плату Advantech1730"));
	}
	//_codeErr = instantDoCtrl->setSelectedDevice(devInfo);
	if (BioFailed(_codeErr)){
	//throw(Exception("A1730_DAQNavi::A1730_DAQNavi: не смогли открыть плату Advantech1730"));
	TExtFunction::ShowBigModalMessage("A1730_DAQNavi::A1730_DAQNavi: не смогли открыть плату Advantech1730", clRed);
	}
#endif
*/
}

// ---------------------------------------------------------------------------
A1730_DAQNavi::~A1730_DAQNavi(void)
{
/*
#ifndef VIRT1730
	if (instantDiCtrl!=NULL) {
	 instantDiCtrl->Cleanup();
	 instantDoCtrl->Cleanup();
	 instantDiCtrl->Dispose();
	 instantDoCtrl->Dispose();
	}
#endif
*/
}

// ---------------------------------------------------------------------------
DWORD A1730_DAQNavi::Read(void)
{
/*
	BYTE buf[4];
	DWORD v=0;
#ifndef VIRT1730
	ErrorCode errorcode = instantDiCtrl->Read(0, 4, buf);
	if (errorcode != Success){
	  TExtFunction::ShowBigModalMessage("A1730_DAQNavi::Read: не могу прочитать плату", clRed);
	  v=-1;
	  return (v);
	   //	throw(Exception("A1730_DAQNavi::Read: не могу прочитать плату"));
	}
	v = buf[0] + (buf[1] << 8) + (buf[2] << 16) + (buf[3] << 24);
#else
	v = input[0] + (input[1] << 8) + (input[2] << 16) + (input[3] << 24);
#endif
	return (v);
	*/
}

// ---------------------------------------------------------------------------
DWORD A1730_DAQNavi::ReadOut(void)
{
/*
	BYTE buf[4];
	DWORD v=0;
#ifndef VIRT1730
	ErrorCode errorcode = instantDoCtrl->Read(0, buf[0]);
	if (errorcode != Success){
		//throw(Exception("A1730_DAQNavi::Read: не могу прочитать плату"));
		TExtFunction::ShowBigModalMessage("A1730_DAQNavi::Read: не могу прочитать плату", clRed);
	  v=-1;
	  return (v);
	}
	v = buf[0] + (buf[1] << 8) + (buf[2] << 16) + (buf[3] << 24);
#else
	v = output[0] + (output[1] << 8) + (output[2] << 16) + (output[3] << 24);
#endif
	return (v);
	*/
}

// ---------------------------------------------------------------------------
void A1730_DAQNavi::Write(DWORD _v)
{
/*
#ifndef VIRT1730
	BYTE buf[4];
	buf[0] = _v & 0xFF;
	buf[1] = _v >> 8 & 0xFF;
	buf[2] = _v >> 16 & 0xFF;
	buf[3] = _v >> 24 & 0xFF;
	ErrorCode errorcode = instantDoCtrl->Write(0, 4, buf);
	if (errorcode != Success){
		//throw(Exception("A1730_DAQNavi::Write: не могу записать на плату"));
	   TExtFunction::ShowBigModalMessage("A1730_DAQNavi::Write: не могу записать на плату", clRed);
	}
#else
	output[0] = _v & 0xFF;
	output[1] = _v >> 8 & 0xFF;
	output[2] = _v >> 16 & 0xFF;
	output[3] = _v >> 24 & 0xFF;
#endif
*/
}
// ---------------------------------------------------------------------------
//#endif
