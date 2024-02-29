// ---------------------------------------------------------------------------

#pragma hdrstop
#include <stdio.h>
//#include <time.h>

#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.Series.hpp>
#include <System.IOUtils.hpp>
//#include <IOUtils.hpp>

#include "unTUtils.h"
#include "TProtocol.h"
#include "unTExtFunction.h"


// ---------------------------------------------------------------------------

// #pragma package(smart_init)
// #pragma link "Series"
// ---------------------------------------------------------------------------

TLog::TLog() {
	setlocale(LC_ALL, "Russian");
};

TLog::~TLog(void) {
};


int TLog::SaveChTxtDoubleFile(AnsiString _fullFileName, double *_data,int _dataSize,int _countCh) {
	int err = -1;
	AnsiString str;
	AnsiString dataStr;
	// ofstream pFileLog;
	int binFileHandle = -1;
	try {

		// dataStr = new AnsiString[_vectSize];
		try {
			// Обращаемся к функции записи  в файл
			setlocale(LC_ALL, "Russian");
			// AnsiString applPath = ExtractFilePath(Application->ExeName);
			// AnsiString nameLog = applPath + "\\\\LOGs\\" + _fileName;
			// if (!DirectoryExists(applPath + "\\LOGs\\")) {
			// CreateDir(applPath + "\\LOGs\\");
			// }else{
			// //
			// }
			if (!FileExists(_fullFileName)) {
				binFileHandle = FileCreate(_fullFileName, FILE_WRITE_DATA, FILE_SHARE_WRITE);
			}
			else {
				// binFileHandle = FileOpen(_fullFileName, fmOpenRead | fmOpenWrite | fmShareDenyNone);
			}
			FileSeek(binFileHandle, 0, 2);
			// -------------------------
			dataStr = "";
			int ii = 0;
			for (ii = 0; ii < _countCh; ii++) {
				dataStr += "CH_";
				dataStr += IntToStr(ii);
				dataStr += "_";
				dataStr += IntToStr((int)(_dataSize/_countCh));
				dataStr +=  ";";
			}
			dataStr += "\n";
			// -------------
			ii = 0;
			while (ii < _dataSize) {
				str = FloatToStrF(_data[ii], ffFixed, 6, 6);
				if ((ii+1) % _countCh != 0) {
					dataStr += FloatToStrF(_data[ii], ffFixed, 6, 6) + ";";
				}
				else {
					dataStr += FloatToStrF(_data[ii], ffFixed, 6, 6) + "\n";
				}
				ii++;
			}
			// sz = dataStr[0].Length();
			err = FileWrite(binFileHandle, dataStr.c_str(), dataStr.Length());
			FileClose(binFileHandle);
			binFileHandle = 0;
			err = 0;
			// другой вариант  использовать в стиле C
			// #include <stdio.h>
			// #include <time.h>

			// FILE *f = fopen("c:\\file.bin", "wb");
			// fprintf(f, " file : %s %c %d %I64 %f %7.2f", "строка :", 'c', 12345, time(0), 1.2, -34.23);
			// fclose(f);
		}

		catch (Exception *ex) {
			err = -2;
            AnsiString tmpStr = "Ошибка при записи файла \""+_fullFileName+"\"";
			TProtocol::ProtocolSave(tmpStr);
			TExtFunction::ShowBigModalMessage(tmpStr, clRed);

		}
	}
	__finally {
		if (binFileHandle > 0) {
			FileClose(binFileHandle);
		}
		else {
			//
		}
	}
	// pFileLog.close();
	return err;
}
// ----------------------------------------------------------------------------
int TLog::LoadTxtChDoubleFile(AnsiString _fullFileName, TLCardData *_lCardData, int _frec,int _countCh) {
	int err = -1;
	AnsiString str;
	int countCharBuffer = 128;
	AnsiString tmpStr;
	AnsiString strDouble;
	AnsiString strZ = "";
	int iFileLength = 0;
	int binFileHandle = -1;
	try {
		// dataStr = new AnsiString[_vectSize];
		try {
			// // Обращаемся к функции чтения из файла
			// setlocale(LC_ALL, "Russian");
			// // AnsiString applPath = ExtractFilePath(Application->ExeName);
			// AnsiString nameLog = "d:\\Work\\GP_MuftN\\SavedResult\\2018_02_14_13_45_24_49500_1_SG_D_FHZ.csv";
			// _fullFileName=nameLog;
			if (!FileExists(_fullFileName)) {
				binFileHandle = -2; // FileCreate(_fullFileName, FILE_WRITE_DATA, FILE_SHARE_WRITE);
				// throw;
				tmpStr = "Не найден файл: \n" + _fullFileName;
				TProtocol::ProtocolSave(tmpStr);
				TExtFunction::ShowBigModalMessage(tmpStr, clRed);
				err = -11;
				return err;
			}
			else {
				binFileHandle = FileOpen(_fullFileName, fmOpenRead | fmShareDenyNone);
				if (binFileHandle < 0) {
					tmpStr = "Не удалось открыть!: \n" + _fullFileName;
					TProtocol::ProtocolSave(tmpStr);
					TExtFunction::ShowBigModalMessage(tmpStr, clRed);
					err = binFileHandle;
					return err;
				}
				else {
					//
				}
				// узнаем размер и вернемся в начало
				iFileLength = FileSeek(binFileHandle, 0, 2);
				FileSeek(binFileHandle, 0, 0);
				// вычитываем полностью
				countCharBuffer = iFileLength;
				std::unique_ptr<char>charBuffer(new char[countCharBuffer]);
				FileRead(binFileHandle, charBuffer.get(), countCharBuffer);
				FileClose(binFileHandle);
				binFileHandle = 0;
				int beginRead = 0;
				// выкинули первую строку
				while (beginRead < countCharBuffer) {
					strZ = charBuffer.get()[beginRead];
					beginRead++;
					if (strZ == "\n") {
						break;
					}
					else {
						//
					}
				}
				strZ = "";
				int d = 0;
				for (int i = 0; i < _countCh; i++) {
					 _lCardData->vecMeasure.clear();
					_lCardData->vecMeasuresData[_frec].vecSensorsData[i].clear();
				}
				while (beginRead < countCharBuffer) {
					strZ = charBuffer.get()[beginRead];
					beginRead++;
					if (strZ == ";" || strZ == "\n")
					{
						if(strDouble != "" && strDouble != "\r")
						{
							int ch = d % _countCh;
							double dd;
							dd = StrToFloat(strDouble);
							_lCardData->vecMeasure.push_back(dd);
							_lCardData->vecMeasuresData[_frec].vecSensorsData[ch].push_back(dd);
						// _lCardData->vecMeasure[i]=StrToFloat(strDouble);
						}
						strDouble = "";
						d++;
					}
					else
					{
						strDouble += strZ;
					}
				}
			}
			err = 0;
		}

		catch (Exception *ex) {
			err = -2;
			tmpStr = "TLog::LoadTxtChDoubleFile: " + ex->Message;
			TProtocol::ProtocolSave(tmpStr);
			TExtFunction::ShowBigModalMessage(tmpStr, clRed);
		}
	}
	__finally {
		if (binFileHandle > 0) {
			FileClose(binFileHandle);
		}
		else {
			//
		}
	}
	// pFileLog.close();
	return err;
}

