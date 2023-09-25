// ---------------------------------------------------------------------------

#pragma hdrstop

#pragma package(smart_init)
#if DEF_TGSPF052
// Файл RshApi.cpp включается директивой #include, чтобы содержащиеся в нем определения методов и функций
// были скомпилированы, иначе возникнут проблемы при линковке.
//
// В крупных проектах может быть удобнее сделать файл-обертку rshsdkwrapper.cpp, внутри которого прописать
// #include <RshApi.cpp>
// и сделать его частью проекта.
//
#include "TGSPF052.h"
#include "TProtocol.h"
#include "unTExtFunction.h"
// #include <RshApi.cpp>

// GSPF052::GSPF052(TIniFile* _ini)
TGSPF052::TGSPF052(TGlobalSettings* _globalSettings, int &_err) {
	try {
		gspfGlobalSettings = _globalSettings;
		_err = -99;
		isStartedGSPF052 = false;
		rshClient = new RshDllClient();
		// // Служебное имя устройства, с которым будет работать программа.
		BoardName = "GSPF052PCI";
		// //Номер устройства. Если в системе установлено несколько одинаковых устройств, можно выбрать, к какому из них подключаться. Нумерация начинается с 1.
		DeviceID = 1;
		// // Частота дискретизации
		SampleFreq = 10000000.0;
		// // Частота генерируемого синуса в Герцах
		SignalFreq = 2000.0;
		// // Амплитуда генерируемого синуса в вольтах
		SignalAmplitude = 2.0;
		// // Язык вывода ошибок. (В случае проблем с кодировкой выбирайте английский язык)
		ErrorLanguage = RSH_LANGUAGE_RUSSIAN;
		// //const RSH_LANGUAGE ErrorLanguage = RSH_LANGUAGE_ENGLISH;
		// //1МОм согласованная нагрузка. L Данная константа используется при расчете выходного напряжения генератора.
		OutR = 1000000.0f;

		// ini = _ini;
		// Строка для вывода в протокол
		AnsiString Str;
		// Статус выполнения операции. RSH_API_SUCCESS в случае успеха, либо код ошибки
		U32 st = RSH_API_SUCCESS;
		// Указатель на объект с интерфейсом IRshDevice, который используется для доступа к устройству.
		rshDevice = 0;
		// //Класс для загрузки библиотеки абстракции.
		// RshDllClient Client;

		// //===================== ПОЛУЧЕНИЕ СПИСКА ЗАРЕГИСТРИРОВАННЫХ БИБЛИОТЕК =====================
		// //В данном примере результаты этого вызова не используются,
		// //так как мы заранее знаем имя библиотеки (константа BoardName)
		// toProtocol(
		// "так как мы заранее знаем имя библиотеки (константа BoardName):");
		// + BoardName);
		// std::vector<std::string> *allDevices;
		// st = Client.GetRegisteredList(allDevices);
		// if(st == RSH_API_SUCCESS)
		// {
		// pr("List of registered device libraries:");
		// for(std::vector<std::string>::iterator *it = allDevices.begin();
		// it != allDevices.end(); ++it)
		// {
		// toProtocol((AnsiString)*it);
		// }
		// }
		// toProtocol("----------");
#ifndef VIRTGPSF052
		// ===================== ЗАГРУЗКА КЛАССА ДЛЯ РАБОТЫ С УСТРОЙСТВОМ ИЗ БИБЛИОТЕКИ =====================
		// Инициализируем интерфейсный ключ.
		RshDllInterfaceKey DevKey(BoardName, (void**)&rshDevice);
		// Получаем экземляр класса устройства.
		toProtocol("Loading device interface from dynamic library... ");
		st = rshClient->GetDeviceInterface(DevKey);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "Client.GetDeviceInterface(DevKey)");
			_err = -1;
			// toProtocol("ERROR Client.GetDeviceInterface(DevKey)");
			CloseCard("Client.GetDeviceInterface(DevKey)");
		}
		else
			toProtocol("Success!");

		// После успешного выполнения вызова Client.GetDeviceInterface()
		// указатель device ссылается на инстанцированный объект,
		// который можно использовать для управления устройством

		// ===================== ИНФОРМАЦИЯ ОБ ИСПОЛЬЗУЕМЫХ БИБЛИОТЕКАХ =====================
		RSH_S8P libname = 0;
		st = rshDevice->Get(RSH_GET_LIBRARY_FILENAME, &libname);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Get(RSH_GET_LIBRARY_FILENAME)");
			_err = -2;
			// toProtocol(" ERROR device->Get(RSH_GET_LIBRARY_FILENAME)");
			CloseCard("device->Get(RSH_GET_LIBRARY_FILENAME)");
		}
		else
			toProtocol(AnsiString("Library Name: ") + (char*)(libname.data));

		RSH_S8P libVersion = 0;
		st = rshDevice->Get(RSH_GET_LIBRARY_VERSION_STR, &libVersion);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Get(RSH_GET_LIBRARY_VERSION_STR)");
			_err - 3;
			CloseCard("device->Get(RSH_GET_LIBRARY_VERSION_STR)");
		}
		else
			toProtocol(AnsiString("Library Version: ") + (char*)(libVersion.data));

		RSH_S8P libCoreName = 0;
		st = rshDevice->Get(RSH_GET_CORELIB_FILENAME, &libCoreName);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Get(RSH_GET_CORELIB_FILENAME)");
			_err = -4;
			CloseCard("device->Get(RSH_GET_CORELIB_FILENAME)");
			throw(Exception("Не смогли открыть ГСПФ!!! RSH_GET_CORELIB_FILENAME err=" + IntToStr(_err)));
		}
		else
			toProtocol(AnsiString("Core Library Name: ") + (char*)(libCoreName.data));

		RSH_S8P libCoreVersion = 0;
		st = rshDevice->Get(RSH_GET_CORELIB_VERSION_STR, &libCoreVersion);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Get(RSH_GET_CORELIB_VERSION_STR)");
			_err - 5;
			CloseCard("device->Get(RSH_GET_CORELIB_VERSION_STR)");
			throw(Exception("Не смогли открыть ГСПФ!!! RSH_GET_CORELIB_VERSION_STR err=" + IntToStr(_err)));
		}
		else
			toProtocol(AnsiString("Core Library Version: ") + (char*)(libCoreVersion.data));

		// ============================= ПРОВЕРКА СОВМЕСТИМОСТИ =============================
		RSH_U32 caps = RSH_CAPS_SOFT_GENERATION_IS_AVAILABLE;
		// Проверим, поддерживает ли плата генерацию аналогового сигнала.
		st = rshDevice->Get(RSH_GET_DEVICE_IS_CAPABLE, &caps);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Get(RSH_GET_DEVICE_IS_CAPABLE)");
			_err = -6;
			CloseCard("device->Get(RSH_GET_DEVICE_IS_CAPABLE)");
			throw(Exception("Не смогли открыть ГСПФ!!! Get(RSH_GET_DEVICE_IS_CAPABLE err=" + IntToStr(_err)));
		}
		// ========================= ПОДКЛЮЧЕНИЕ К УСТРОЙСТВУ ====================================
		// Создаем ключ, по которому будет выполняться подключение (в данном случае
		// используется базовый адрес)
		RshDeviceKey connectKey(DeviceID);

		// Подключаемся к устройству
		toProtocol("Connecting to device (it may take some time)... ");
		st = rshDevice->Connect(&connectKey);
		if (st != RSH_API_SUCCESS) {
			_err = -61;
			CloseCard("device->Connect()");
			throw(Exception("Не смогли открыть ГСПФ!!! Connect err=" + IntToStr(_err)));
			// Close(Client, st,"device->Connect()");
		}
		else
			toProtocol("Success!");
		// Полное (точное) имя устройства и заводской номер доступны только после подключения к устройству
		RSH_S8P fullDeviceName = 0;
		st = rshDevice->Get(RSH_GET_DEVICE_NAME_VERBOSE, &fullDeviceName);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Get(RSH_GET_DEVICE_NAME_VERBOSE)");
			_err = -7;
			CloseCard("device->Get(RSH_GET_DEVICE_NAME_VERBOSE)");
			throw(Exception("Не смогли открыть ГСПФ!!! RSH_GET_DEVICE_NAME_VERBOSE err=" + IntToStr(_err)));
		}
		else {
			toProtocol((AnsiString)"The name of the connected device: " + (char *)fullDeviceName.data);
			// toProtocol(Str);
		}
		RSH_U32 serialNumber = 0;
		st = rshDevice->Get(RSH_GET_DEVICE_SERIAL_NUMBER, &serialNumber);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Get(RSH_GET_DEVICE_SERIAL_NUMBER)");
			_err = -8;
			CloseCard("device->Get(RSH_GET_DEVICE_SERIAL_NUMBER)");
			throw(Exception("Не смогли открыть ГСПФ!!! RSH_GET_DEVICE_SERIAL_NUMBER err=" + IntToStr(_err)));
		}
		else
			toProtocol("Serial number of the connected device:  " + (AnsiString)(serialNumber.data));
		// ========================= ДОПОЛНИТЕЛЬНЫЕ ОСОБЕННОСТИ УСТРОЙСТВА ====================================

		toProtocol("----------");
		toProtocol("Additional device features: ");

		// Разрядность ЦАПа
		RSH_U32 DACResolution = 0;
		st = rshDevice->Get(RSH_GET_DEVICE_DATA_BITS, &DACResolution);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Get(RSH_GET_DEVICE_DATA_BITS)");
			_err = -9;
			CloseCard("device->Get(RSH_GET_DEVICE_DATA_BITS)");
			throw(Exception("Не смогли открыть ГСПФ!!! RSH_GET_DEVICE_DATA_BITS err=" + IntToStr(_err)));
		}
		toProtocol((AnsiString)"DAC resolution: " + (DACResolution.data) + "bits");

		// Минимальная частота дискретизации
		RSH_DOUBLE DACMinFreq = 0.0;
		rshDevice->Get(RSH_GET_DEVICE_MIN_FREQUENCY, &DACMinFreq);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Get(RSH_GET_DEVICE_MIN_FREQUENCY)");
			_err = -10;
			CloseCard("device->Get(RSH_GET_DEVICE_MIN_FREQUENCY)");
			throw(Exception("Не смогли открыть ГСПФ!!! RSH_GET_DEVICE_MIN_FREQUENCY err=" + IntToStr(_err)));
		}
		toProtocol((AnsiString)"Minimum frequency: " + FloatToStr(DACMinFreq.data) + "Hz");

		// Максимальная частота дискретизации
		RSH_DOUBLE DACMaxFreq = 0.0;
		rshDevice->Get(RSH_GET_DEVICE_MAX_FREQUENCY, &DACMaxFreq);
		if (st != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Get(RSH_GET_DEVICE_MAX_FREQUENCY)");
			_err = -11;
			CloseCard("device->Get(RSH_GET_DEVICE_MAX_FREQUENCY)");
			throw(Exception("Не смогли открыть ГСПФ!!! RSH_GET_DEVICE_MAX_FREQUENCY err=" + IntToStr(_err)));
		}
		toProtocol((AnsiString)"Maximum frequency: " + FloatToStr(DACMaxFreq.data) + "Hz");

		// Максимальная амплитуда в вольтах
		RSH_DOUBLE DACRealMaxAmp;
		rshDevice->Get(RSH_GET_DEVICE_OUTPUT_RANGE_VOLTS, &DACRealMaxAmp);
		toProtocol((AnsiString)"Maximum out amplitude: " + FloatToStr(DACRealMaxAmp.data) + "V");

		// Расчет значения максимальной амплитуды в зависимости от сопротивления нагрузки
		DACMaxAmp = 0.0;
		DACMaxAmp = OutR * (DACRealMaxAmp.data / (OutR + 50.0));
		toProtocol((AnsiString)"Maximum out amplitude for current output resist: " + FloatToStr(DACMaxAmp) + "V");

		// ========================= ИНИЦИАЛИЗАЦИЯ ====================================

		// //Структура инициализации
		// Запуск генерациии - программный
		gspfPar.startType = RshInitGSPF::Program;

		// Ослабление не используется
		gspfPar.attenuator = RshInitGSPF::AttenuationOff;

		// Включаем циклическое проигрывание сигнала.
		// Альтернатива - прямое управление флагами управляющего слова:
		// gspfPar.control |= RshInitGSPF::PlayLoop;
		gspfPar.control |= RshInitGSPF::PlayLoop; // SetPlayModeLoop();
		// вырубаем синтезатор, ибо глючит
		gspfPar.control |= RshInitGSPF::SynthesizerOff;
		// Частота дискретизации
		gspfPar.frequency = SampleFreq;
		// Инициализация параметров
		st = rshDevice->Init(&gspfPar, 1);
		if (st != RSH_API_SUCCESS) {
			_err = -99;
			CloseCard("device->Init(&gspfPar)");
			throw(Exception("Не смогли открыть ГСПФ!!! device->Init err=" + IntToStr(_err)));
			return;
		}
		else {
			//
		}

		// todo как перевести параметры в строку?
		// а нафига?
		// AnsiString StrA = "Initialization parameters: " + gspfPar.;
		// toProtocol(StrA);
#endif
		_err = 0;
	}
	catch (Exception *ex) {
		TLog::ErrFullSaveLog(ex);
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
}

// ---------------------------------------------------------------------------
TGSPF052::~TGSPF052(void) {
	//
}

int TGSPF052::FormSignal(int _valueFrec, double _valueAmpl) {
	int err = -101;
	AnsiString msg = "";
	// ========================= ФОРМИРОВАНИЕ СИГНАЛА (СИНУС) ====================================
	// Статус выполнения операции. RSH_API_SUCCESS - 0 в случае успеха, либо код ошибки
	U32 status = RSH_API_SUCCESS;

	// Размер буфера для сигнала в отсчетах
	// надо делать кратным частоте сигнала
	const U32 bSize = 100000;

	// Инициализируем буфер для данных
	RSH_BUFFER_S16 buffer(bSize);

	// теперь будем присылать частоту напрямую извне
	SignalFreq = _valueFrec;
	// ini->ReadFloat("SignalFrequencies", str, 1000.0);
	SignalAmplitude = _valueAmpl;
#ifndef VIRTGPSF052
	// проверим, не получилось ли значение для амплитуды равным 0
	if (RSH_CMPDOUBLE(DACMaxAmp, 0.0)) {
		// Close(Client, RSH_API_PARAMETER_INVALID, "RSH_CMPDOUBLE(DACMaxAmp, 0.0)");
		err = -1;
		CloseCard("RSH_CMPDOUBLE(DACMaxAmp, 0.0)");
		return err;
	}

	// Коэффициент для пересчета из вольт в МЗР
	double amplitudeCoef = SignalAmplitude / DACMaxAmp;

	// Заполняем буфер данными
	int old_size = buffer.PSize();
	// buffer.reserve(sz);
	for (U32 i = 0; i < buffer.PSize(); ++i) {
		S16 value = static_cast<S16>(amplitudeCoef * 32768 * sin(i * (2 * 3.1415926 * SignalFreq) / gspfPar.frequency));
		buffer.PushBack(value);
	}
	// Если нужно использовать только часть буфера, можно указать размер
	// (не выделяя память заново)
	// todo обрезаем до цикличной части     //понятное дело, что он слегка округляет
	U32 new_size = (int) gspfPar.frequency / SignalFreq;
	if (new_size % 2 != 0) // новый размер буфера должен быть четным!
			new_size++;
	if (new_size < bSize)
		buffer.SetSize(new_size);
	else {
		msg = "Не хватает размера буфера для цикличного графика синуса - попробуйте снизить частоту";
		toProtocol(msg);
		TExtFunction::ShowBigModalMessage(msg, clRed);
	}
	// new_size должен быть меньше или равен buffer.PSize()
	// Отправляем буфер в устройство
	status = rshDevice->GetData(&buffer);
	if (status != RSH_API_SUCCESS) {
		err = -2;
		msg = "Ошибка Отправляем буфер в устройство!!! \n";
		TExtFunction::ShowBigModalMessage(msg, clRed);
		// Close(Client, st, "device->GetData(&buffer)");
		CloseCard("device->GetData(&buffer)");
		return err;
	}
#endif
	err = 0;
	return err;
}

// ---------------------------------------------------------------------------
int TGSPF052::StartGSPF052() {
	int err = -99;
	AnsiString msg;
	// Статус выполнения операции. RSH_API_SUCCESS в случае успеха, либо код ошибки
	U32 status = RSH_API_SUCCESS;
#ifndef VIRTGPSF052
	// Запускаем проигрывание данных
	status = rshDevice->Start();
	if (status != RSH_API_SUCCESS) {
		// Close(Client, st, "device->Start()");
		err = -1;
		msg = "device->Start()";
		toProtocol(msg);
		TExtFunction::ShowBigModalMessage(msg, clRed);
		CloseCard(msg.c_str());
	}
	else {
		isStartedGSPF052 = true;
		err = 0;
	}
#else
	err=0;
#endif
	return err;
}

// ---------------------------------------------------------------------------
int TGSPF052::WaitInterrupt() {
	int err = -99;
	// Статус выполнения операции. RSH_API_SUCCESS в случае успеха, либо код ошибки
	U32 status = RSH_API_SUCCESS;
	toProtocol("Waiting for interrupt after buffer generation completion...");
#ifndef VIRTGPSF052
	// Ожидание прерывания (происходит каждый раз при завершении проигрывания буфера)
	status = rshDevice->Get(RSH_GET_WAIT_BUFFER_READY_EVENT);
	if (status != RSH_API_SUCCESS) {
		// Close(Client, st, "device->Get(RSH_GET_WAIT_BUFFER_READY_EVENT)");
		CloseCard("device->Get(RSH_GET_WAIT_BUFFER_READY_EVENT)");
		err = -1;
	}
	else {
		err = 0;
		toProtocol("Interrupt has taken place!");
		// Close(Client, RSH_API_SUCCESS);
	}
#else
	err=0;
#endif
	return err;
}

// ---------------------------------------------------------------------------
int TGSPF052::StopGSPF052() {
	int err = -99;
#ifndef VIRTGPSF052
	// Статус выполнения операции. RSH_API_SUCCESS в случае успеха, либо код ошибки
	U32 status = RSH_API_SUCCESS;
	if (isStartedGSPF052 && rshDevice) {
		// Останавливаем проигрывание данных
		isStartedGSPF052 = false;
		status = rshDevice->Stop();
		if (status != RSH_API_SUCCESS) {
			// Close(Client, st, "device->Stop()");
			err = -1;
			CloseCard("device->Stop()");
		}
		else {
			err = 0;
		}
	}
	else {
		err = 1;
	}
#else
	err = 0;
#endif
	return err;
}

// ---------------------------------------------------------------------------
// Функция выводит сообщение об ошибке и завершает работу платы
int TGSPF052::CloseCard(AnsiString desc) {
	int err = -99;
	AnsiString msg;
	toProtocol("----------");
	if (desc != "ok") {
		msg = "Error on " + desc + " call.";
		toProtocol(msg);
		TExtFunction::ShowBigModalMessage(msg, clRed);
	}
	else
		toProtocol("GSPF normal close");
#ifndef VIRTGPSF052
	// RshError::PrintError(st, ErrorLanguage, true); //todo проверить куда выводит
	// Вызов Free() выгружает все загруженные классом RshDllClient библиотеки.
	try {
		rshClient->Free();
		rshClient = NULL;
		err = 0;
		// pr("Press 'Enter' key to end up the program.");
		// cin.ignore();
	}
	catch (Exception *ex) {
		// TLog::ErrFullSaveLog(ex);
		err = -3;
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
#else
	err = 0;
#endif
	return err;
	// return (unsigned int) st;
}

// ---------------------------------------------------------------------------
// Вывод сообщения в протокол
void TGSPF052::toProtocol(AnsiString _msg) {
	AnsiString a;
	a = "GSPF052: ";
	a += _msg;
	TProtocol::ProtocolSave(a);
}

// ---------------------------------------------------------------------------
// Обновление частоты дискретизации
void TGSPF052::SetSampleFreq(double _SampleFreq) {
#ifndef VIRTGPSF052
	// Обновим частоту дискретизации
	try {
		gspfPar.frequency = _SampleFreq;
		// Инициализация параметров
		U32 st = RSH_API_SUCCESS;
		st = rshDevice->Init(&gspfPar, 1);
		if (st != RSH_API_SUCCESS) {
			CloseCard("device->Init(&gspfPar)");
			return;
		}
	}
	catch (Exception *ex) {
		TLog::ErrFullSaveLog(ex);
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
#else
	return;
#endif
}
// ---------------------------------------------------------------------------
#endif
