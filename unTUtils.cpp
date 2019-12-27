// ---------------------------------------------------------------------------

#pragma hdrstop

#include "unTUtils.h"
//

#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.Series.hpp>
#include <System.IOUtils.hpp>

#include <IOUtils.hpp>

// ---------------------------------------------------------------------------

// #pragma package(smart_init)
// #pragma link "Series"
// ---------------------------------------------------------------------------

TLog::TLog() {
	setlocale(LC_ALL, "Russian");
	// applPath = ExtractFilePath(Application->ExeName);
};

TLog::~TLog(void) {
	// delete Log;
};

int TLog::SaveStrMsgLog(AnsiString _Msg) {
	int err = -1;
	// ofstream pFileLog;
	int logFileHandle = -1; ;
	try {
		try {
			// вычисляем время с датой
			setlocale(LC_ALL, "Russian");
			TDateTime currentDT;
			AnsiString strCurrentDT = FormatDateTime("yyyy.mm.dd hh:mm:ss", currentDT.CurrentDateTime());
			AnsiString strCurrentD = FormatDateTime("yyyy_mm_dd", currentDT.CurrentDateTime());
			strCurrentDT = strCurrentDT + " ;" + _Msg + "\n";
			AnsiString applPath = ExtractFilePath(Application->ExeName);
			if (!DirectoryExists(applPath + "\\LOGs\\")) {
				CreateDir(applPath + "\\LOGs\\");
			}
			else {
				//
			}
			AnsiString nameLog = applPath + "\\LOGs\\errLog_" + strCurrentD + ".log";
			// pFileLog.open(strLog.c_str());
			// pFileLog.
			// pFileLog << strCurrentDT.c_str();
			// logFile=FileCreate(strLog);
			if (!FileExists(nameLog)) {
				// logFileHandle = FileCreate(nameLog, FILE_ALL_ACCESS, FILE_SHARE_WRITE);
				logFileHandle = FileCreate(nameLog, FILE_WRITE_DATA, FILE_SHARE_WRITE);
			}
			else {
				logFileHandle = FileOpen(nameLog, fmOpenRead | fmOpenWrite | fmShareDenyNone);
			}
			// ползем на конец файла
			FileSeek(logFileHandle, 0, 2);
			err = FileWrite(logFileHandle, strCurrentDT.c_str(), strCurrentDT.Length());
			FileClose(logFileHandle);
			logFileHandle = 0;
			err = 0;
		}
		catch (Exception *ex) {
			err = -2;
			// TLog::SaveStrLog(ex->Message);
			MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);

		}
	}
	__finally {
		if (logFileHandle > 0) {
			FileClose(logFileHandle);
		}
		else {
			//
		}
	}
	// pFileLog.close();
	return err;
};

TLog::SaveStrTxtFile(AnsiString _fullNameFile, AnsiString _msg) {
	int err = -1;
	// ofstream pFileLog;
	int txtFileHandle = -1;
	try {
		try {
			// Обращаемся к функции записи  в файл
			setlocale(LC_ALL, "Russian");
			AnsiString pathSave = ExtractFileDir(_fullNameFile);
			if (DirectoryExists(pathSave)) {
				CreateDir(pathSave);
			}
			else {
				//
			}
			if (!FileExists(_fullNameFile)) {
				txtFileHandle = FileCreate(_fullNameFile, FILE_WRITE_DATA, FILE_SHARE_WRITE);
			}
			else {
				txtFileHandle = FileOpen(_fullNameFile, fmOpenRead | fmOpenWrite | fmShareDenyNone);
			}
			err = FileWrite(txtFileHandle, _msg.c_str(), _msg.Length());
			FileSeek(txtFileHandle, 0, 2);
			FileClose(txtFileHandle);
			txtFileHandle = 0;
			err = 0;
		}
		catch (Exception *ex) {
			err = -2;
			TLog::ErrFullSaveLog(ex);
			MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);

		}
	}
	__finally {
		if (txtFileHandle > 0) {
			FileClose(txtFileHandle);
		}
		else {
			//
		}
	}
	// pFileLog.close();
	return err;
}

int TLog::ErrFullSaveLog(Exception *_ex) {
	int err = -1;
	AnsiString msg = "";
	try {
		msg = _ex->ClassName() + "\n";
		msg += _ex->ToString() + "\n";
		msg += _ex->Message;
		SaveStrMsgLog(msg);
		// MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
		err = 0;
	}
	catch (Exception *ex) {
		err = -2;
		SaveStrMsgLog(ex->Message);
		// MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
	return err;
}

int TLog::SaveTxtArrDoubleFile(AnsiString _fullFileName, AnsiString _str, double *_arr, int _arrSize) {
	int err = -1;
	// ofstream pFileLog;
	int binFileHandle = -1;
	try {
		try {
			// Обращаемся к функции записи  в файл
			setlocale(LC_ALL, "Russian");
			// AnsiString applPath = ExtractFilePath(Application->ExeName);
			// AnsiString nameLog = applPath + "\\\\LOGs\\" + _fileName;
			if (!FileExists(_fullFileName)) {
				binFileHandle = FileCreate(_fullFileName, FILE_WRITE_DATA, FILE_SHARE_WRITE);
			}
			else {
				binFileHandle = FileOpen(_fullFileName, fmOpenRead | fmOpenWrite | fmShareDenyNone);
			}
			FileSeek(binFileHandle, 0, 2);
			if (_str != NULL) {
				err = FileWrite(binFileHandle, _str.c_str(), _str.Length());
			}
			else {
				//
			}
			err = sizeof(double);
			err = FileWrite(binFileHandle, _arr, _arrSize*sizeof(double));
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
			TLog::ErrFullSaveLog(ex);
			MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);

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

// ----------------
TSettingsINI::TSettingsINI() {
	// AnsiString applPath = ExtractFilePath(Application->ExeName);
	AnsiString strINI = applPath + "\settings.ini";
	TIniFile *Ini = new TIniFile(strINI);
};

TSettingsINI::~TSettingsINI(void) {
	delete Ini;
};

int TLog::SaveTxtVectDoubleFile(AnsiString _fullFileName, vector<double> &_vectorData, int _vectSize) {
	int err = -1;
	int sz = 0;
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
			if (!FileExists(_fullFileName)) {
				binFileHandle = FileCreate(_fullFileName, FILE_WRITE_DATA, FILE_SHARE_WRITE);
			}
			else {
				binFileHandle = FileOpen(_fullFileName, fmOpenRead | fmOpenWrite | fmShareDenyNone);
			}
			FileSeek(binFileHandle, 0, 2);
			str = "SZ " + IntToStr(_vectSize) + "; ";
			if (str != NULL) {
				// запишем размер сенсора
				err = FileWrite(binFileHandle, str.c_str(), str.Length());
			}
			else {
				//
			}
			for (int i = 0; i < _vectSize; i++) {
				str = FloatToStrF(_vectorData[i], ffFixed, 6, 6);
				if (i < _vectSize - 1) {
					dataStr += FloatToStrF(_vectorData[i], ffFixed, 6, 6) + "; ";
				}
				else {
					dataStr += FloatToStrF(_vectorData[i], ffFixed, 6, 6) + "\n";
				}

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
			TLog::ErrFullSaveLog(ex);
			MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);

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

int TLog::SaveChTxtDoubleFile(AnsiString _fullFileName, double *_data,int _dataSize,int _countCh) {
	int err = -1;
	int sz = 0;
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
			TLog::ErrFullSaveLog(ex);
			MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);

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

int TLog::Save123TxtVectDoubleFile(AnsiString _fullFileName, vector<double> &_vectorData) {
	int err = -1;
	int sz = 0;
	AnsiString str;
	AnsiString dataStr;
	// ofstream pFileLog;
	int binFileHandle = -1;
	int _vectSize;
	try {
		// dataStr = new AnsiString[_vectSize];
		_vectSize = _vectorData.size();
		try {
			// Обращаемся к функции записи  в файл
			setlocale(LC_ALL, "Russian");
			// AnsiString applPath = ExtractFilePath(Application->ExeName);
			// AnsiString nameLog = applPath + "\\\\LOGs\\" + _fileName;
			if (!FileExists(_fullFileName)) {
				binFileHandle = FileCreate(_fullFileName, FILE_WRITE_DATA, FILE_SHARE_WRITE);
			}
			else {
				binFileHandle = FileOpen(_fullFileName, fmOpenRead | fmOpenWrite | fmShareDenyNone);
			}
			FileSeek(binFileHandle, 0, 2);
			sz = _vectSize / 3;
			for (int i = 0; i < sz; i++) {
				for (int j = 0; j < 3; j++) {
					dataStr += FloatToStrF(_vectorData[i * 3 + j], ffFixed, 6, 6) + "; ";
				}
				dataStr += "\n";
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
			TLog::ErrFullSaveLog(ex);
			MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);

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

int TLog::SaveNEWTxtVectDoubleFile(AnsiString _fullFileName, vector<double> &_vectorData, int _vectSize) {
	int err = -1;
	int sz = 0;
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
				binFileHandle = FileOpen(_fullFileName, fmOpenRead | fmOpenWrite | fmShareDenyNone);
			}
			FileSeek(binFileHandle, 0, 2);
			dataStr = "CH_0 " + IntToStr(_vectSize) + "; " + " CH_1 " + IntToStr(_vectSize) + "; " + " CH_2 " + IntToStr(_vectSize) + "\n";
			for (int i = 0; i < _vectSize; i++) {
				// str  = FloatToStrF(_vectorData1[i], ffFixed, 6, 6);
				dataStr += FloatToStrF(_vectorData[i], ffFixed, 6, 6) + ";";
				i++;
				if (i >= _vectSize)
					break;
				dataStr += FloatToStrF(_vectorData[i], ffFixed, 6, 6) + ";";
				i++;
				if (i >= _vectSize)
					break;
				dataStr += FloatToStrF(_vectorData[i], ffFixed, 6, 6) + "\n";
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
			TLog::ErrFullSaveLog(ex);
			MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);

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
	int sz = 0;
	AnsiString str;
	char* charBuffer = NULL;
	int countCharBuffer = 128;
	AnsiString tmpStr;
	AnsiString strDouble;
	AnsiString strZ = "";
	int iFileLength = 0;
	int iBytesRead = 0;
	// ofstream pFileLog;
	int binFileHandle = -1;
	int beginRead = 0;
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
				tmpStr = "Не найден: \n" + _fullFileName;
				MessageDlg(tmpStr, mtError, TMsgDlgButtons() << mbOK, NULL);
				TLog::SaveStrMsgLog(tmpStr);
				err = -11;
				return err;
			}
			else {
				binFileHandle = FileOpen(_fullFileName, fmOpenRead | fmShareDenyNone);
				if (binFileHandle < 0) {
					tmpStr = "Не удалось открыть!: \n" + _fullFileName;
					MessageDlg(tmpStr, mtError, TMsgDlgButtons() << mbOK, NULL);
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
				iBytesRead = FileRead(binFileHandle, charBuffer.get(), countCharBuffer);
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
				int i = 0;
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
			TLog::ErrFullSaveLog(ex);
			MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);

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

int TLog::LoadTubeFromFileBin(AnsiString _fullFileName, int _countZonesAll, int _wdFirstSensorsThick, int _wdCountSensorsThick, int _wdFirstSensorsCross,
	int _wdCountSensorsCross, int _wdFullSensorSize, int _wdCountLOGchX502) {
	int err = -1;
	int binFileHandle = -1;
	int iFileLength = 0;
	int iBytesRead = 0;
	char* charBuffer = NULL;
	int countCharBuffer = 128;
	// --------------- размер заголовка не более ХХ символов
	int headLength = 0; // реальная длина заголовка
	double* dlbBuffer = NULL;
	int countDlbBuf = 0;
	// сколько цифр надо вычитать
	int readInt = 0;
	int countZones = 0;
	int firstSensorThick;
	int sensorsThick;
	int firstSensorCross;
	int sensorsCross;
	int sensorSize;
	// AnsiString nameFile = applPath + "\\LOGs\\errLog_" + strCurrentD + ".log";
	AnsiString nameFile = _fullFileName;
	AnsiString strZ = "";
	AnsiString tmpStr = "";
	try {
		try {

			if (!FileExists(_fullFileName)) {
				tmpStr = "Не найден: \n" + _fullFileName;
				MessageDlg(tmpStr, mtError, TMsgDlgButtons() << mbOK, NULL);
				TLog::SaveStrMsgLog(tmpStr);
				err = -11;
				return err;
			}
			else {
				binFileHandle = FileOpen(_fullFileName, fmOpenRead);
				// binFileHandle = FileOpen(_fullFileName, fmOpenRead | fmOpenWrite | fmShareDenyNone);
				iFileLength = FileSeek(binFileHandle, 0, 2);
				FileSeek(binFileHandle, 0, 0);
				// std::tr1::shared_ptr<>
				// std::shared_ptr
				// auto ptr = std::make_shared<Foo>();
				// std::auto_ptr<char>charBuffer(new char[iFileLength + 1]);
				std::unique_ptr<char>charBuffer(new char[countCharBuffer]);
				// iBytesRead = FileRead(binFileHandle, charBuffer.get(), countCharBuffer);
				// --------------- разберем заголовок
				// ZC:ХХ FST:XX ST:XX FSC:XX SC:XX FSS:XXXX-EOH:
				// charBuffer = new char[countCharBuffer + 1];
				iBytesRead = FileRead(binFileHandle, charBuffer.get(), countCharBuffer);
				int iH = 0;
				while (iH < countCharBuffer) {
					strZ += charBuffer.get()[iH];
					iH++;
				}
				// ----- countZones
				tmpStr = strZ.SubString(4, 2);
				countZones = StrToInt(tmpStr);
				if (countZones != _countZonesAll) {
					MessageDlg("Количество зон в файле \n и в настройках не совпадают! \n В файле: " + IntToStr(countZones) + " в настройках: " +
						IntToStr(_countZonesAll), mtWarning, TMsgDlgButtons() << mbOK, NULL);
					// return err;
				}
				else {
					//
				}
				// --------------firstSensorThick
				tmpStr = strZ.SubString(11, 2);
				firstSensorThick = StrToInt(tmpStr);
				if (firstSensorThick != _wdFirstSensorsThick) {
					MessageDlg("Первый датчик толщиномера в файле \n и в настройках не совпадают! \n В файле: " + IntToStr(firstSensorThick) +
						" в настройках: " + IntToStr(_wdFirstSensorsThick) + "\n Загрузка детализации отменена!", mtError, TMsgDlgButtons() << mbOK, NULL);
					err = -2;
					return err;
				}
				else {
					//
				}
				// --------------sensorsThick
				tmpStr = strZ.SubString(17, 2);
				sensorsThick = StrToInt(tmpStr);
				if (sensorsThick != _wdCountSensorsThick) {
					MessageDlg("Число датчиков толщиномера в файле \n и в настройках не совпадают! \n В файле: " + IntToStr(sensorsThick) + " в настройках: " +
						IntToStr(_wdCountSensorsThick) + "\n Загрузка детализации отменена!", mtError, TMsgDlgButtons() << mbOK, NULL);
					err = -3;
					return err;
				}
				else {
					//
				}
				// --------------firstSensorCross
				tmpStr = strZ.SubString(24, 2);
				firstSensorCross = StrToInt(tmpStr);
				if (firstSensorCross != _wdFirstSensorsCross) {
					MessageDlg("Первый датчик поперечника в файле \n и в настройках не совпадают! \n В файле: " + IntToStr(firstSensorCross) +
						" в настройках: " + IntToStr(_wdFirstSensorsCross) + "\n Загрузка детализации отменена!", mtError, TMsgDlgButtons() << mbOK, NULL);
					err = -4;
					return err;
				}
				else {
					//
				}
				// -----sensorsCross
				tmpStr = strZ.SubString(30, 2);
				sensorsCross = StrToInt(tmpStr);
				if (sensorsCross != _wdCountSensorsCross) {
					MessageDlg("Первый датчик поперечника в файле \n и в настройках не совпадают! \n В файле: " + IntToStr(sensorsCross) + " в настройках: " +
						IntToStr(_wdCountSensorsCross) + "\n Загрузка детализации отменена!", mtError, TMsgDlgButtons() << mbOK, NULL);
					err = -5;
					return err;
				}
				else {
					//
				}
				// ---- sensorSize
				tmpStr = strZ.SubString(37, 5);
				sensorSize = StrToInt(tmpStr);
				if (sensorSize != _wdFullSensorSize) {
					MessageDlg("Размер буфера датчика в файле \n и в настройках не совпадают! \n В файле: " + IntToStr(sensorSize) + " в настройках: " +
						IntToStr(_wdFullSensorSize) + "\nЗагрузка детализации отменена!", mtError, TMsgDlgButtons() << mbOK, NULL);
					err = -6;
					return err;
				}
				else {
					//
				}
				// Длина заголовка
				headLength = strZ.Pos("-EOH:") + 4;
				// убежим в начало
				FileSeek(binFileHandle, 0, 0);
				// смещаемся на начало данных
				FileSeek(binFileHandle, headLength, 0);
				int szDbl = sizeof(double);
				// -----------размер буфера по по файлу в  double
				countDlbBuf = (int)(sensorSize * _wdCountLOGchX502);
				dlbBuffer = new double[countDlbBuf];
				// pszBuffer = PChar(AllocMem(iFileLength + 1));
				// iBytesRead = FileRead(binFileHandle, pszBuffer, iFileLength);
				// очистим зоны
				// ResetAllData(lastMsg);
				for (int i = 0; i < countZones; i++) {
					// байт читать надо countDlbBuf*szDbl - учитывать размерность double
					iBytesRead = FileRead(binFileHandle, dlbBuffer, countDlbBuf * szDbl);
					// int need = vectZones[i]->sizeZoneFull - vectZones[i]->sizeZoneReal;
					// if (need > countDlbBuf) {
					// need = countDlbBuf;
					// }
					// else {
					// need = vectZones[i]->sizeZoneFull - vectZones[i]->sizeZoneReal;
					// }
					// // int TZoneData::AddPartZone(int _firstADCdata, double* _dataADC, int _sizeADC, uint32_t* _dataDIN, int _sizeDIN)
					// vectZones[i]->AddPartZone(0, dlbBuffer, need, NULL, 0,countUsedZones,countFullZones,countZonesAll);
					err = iBytesRead;
				}
			}
			delete charBuffer;
			delete dlbBuffer;
			err = 0;
		}
		catch (Exception *ex) {
			err = -20;
			TLog::ErrFullSaveLog(ex);
			MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);

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
	return err;
}
