// ---------------------------------------------------------------------------

#pragma hdrstop

#include "unTExtFunction.h"
#include "unSQLDbModule.h"
#include "unTUtils.h"
#include "unFmMessage.h"
// ---------------------------------------------------------------------------
//#pragma package(smart_init)

// -------------------------
TExtFunction::TExtFunction() {

}

TExtFunction::~TExtFunction(void) {

}

// настраиваем чарты одноообразно, длинно муторно, но полезно
void TExtFunction::PrepareBarChart(int _countSensors, int _maxZones,
	TChart* _chart) {
	_chart->BackWall->Color = clBtnFace;
	_chart->BackWall->Transparent = false;
	_chart->BottomWall->Visible = false;
	_chart->Foot->AdjustFrame = false;
	_chart->Foot->Alignment = taLeftJustify;
	_chart->Foot->Visible = false;
	_chart->LeftWall->Visible = false;
	_chart->Legend->Visible = false;
	_chart->MarginBottom = 0;
	_chart->MarginLeft = 0;
	_chart->MarginRight = 5;
	_chart->MarginTop = 0;
	_chart->MarginUnits = muPixels;
	_chart->PrintProportional = false;
	_chart->SubFoot->Alignment = taLeftJustify;
	_chart->SubFoot->Visible = false;
	_chart->SubTitle->Alignment = taLeftJustify;
	_chart->SubTitle->Visible = false;
	_chart->Title->Alignment = taLeftJustify;
	// убрать прокрутку по колесу мыши
	// _chart->AllowPanning = Vcltee::Teeprocs::pmNone;
	_chart->AllowPanning = Teeprocs::pmNone;
	// _chart->Title->Text = (L"");
	_chart->Title->Visible = false;
	_chart->BottomAxis->Automatic = false;
	_chart->BottomAxis->AutomaticMaximum = false;
	_chart->BottomAxis->AutomaticMinimum = false;
	_chart->BottomAxis->Axis->Width = 1;
	_chart->BottomAxis->ExactDateTime = false;
	_chart->BottomAxis->Increment = 1;
	_chart->BottomAxis->Maximum = _maxZones;
	_chart->BottomAxis->MaximumOffset = 1;
	// _chart->BottomAxis->MinorTickCount = 0;
	// _chart->DepthAxis->Automatic = false;
	// _chart->DepthAxis->AutomaticMaximum = false;
	// _chart->DepthAxis->AutomaticMinimum = false;
	// _chart->DepthAxis->ExactDateTime = false;
	// _chart->DepthAxis->Increment = 1;
	// _chart->DepthTopAxis->Automatic = false;
	// _chart->DepthTopAxis->AutomaticMaximum = false;
	// _chart->DepthTopAxis->AutomaticMinimum = false;
	// _chart->DepthTopAxis->ExactDateTime = false;
	// _chart->DepthTopAxis->Increment = 1;
	_chart->Emboss->Color = clLime;
	_chart->LeftAxis->Automatic = false;
	_chart->LeftAxis->AutomaticMaximum = false;
	_chart->LeftAxis->AutomaticMinimum = false;
	_chart->LeftAxis->AxisValuesFormat = "#,##";
	_chart->LeftAxis->ExactDateTime = false;
	_chart->LeftAxis->LabelsMultiLine = true;
	_chart->LeftAxis->LabelsOnAxis = false;
	_chart->LeftAxis->MinorTicks->Visible = false;
	_chart->Pages->AutoScale = true;
	// _chart->Pages->MaxPointsPerPage = 8;
	_chart->RightAxis->Automatic = false;
	_chart->RightAxis->AutomaticMaximum = false;
	_chart->RightAxis->AutomaticMinimum = false;
	_chart->RightAxis->Visible = false;
	_chart->Shadow->Color = clRed;
	_chart->Shadow->Visible = false;
	_chart->TopAxis->Automatic = false;
	_chart->TopAxis->AutomaticMaximum = false;
	_chart->TopAxis->AutomaticMinimum = false;
	_chart->TopAxis->Visible = false;
	_chart->View3D = false;
	_chart->Zoom->Allow = false;
	_chart->Align = alClient;
	_chart->BevelOuter = bvNone;
	// series
	_chart->SeriesList->Clear();
	for (int i = 0; i < _countSensors; i++) {
		TBarSeries* series = new TBarSeries(_chart);
		// TChartSeries* series = new TChartSeries(_chart);
		series->Depth = 0;
		series->ColorEachPoint = true;
		series->Marks->Visible = false;
		series->Marks->Arrow->Visible = false;
		series->Marks->Callout->Brush->Color = clBlack;
		series->Marks->Callout->Arrow->Visible = false;
		series->Marks->Margins->Left = 44;
		series->ShowInLegend = false;
		series->AutoMarkPosition = false;
		series->BarRound = brNone;
		// series->AutoRepaint = false;
		// ---------------------------дополнительные
		// int a = series->BarWidth;
		if (_maxZones < 50) {
			series->CustomBarWidth = 60; // ширина метки в пикселах
		}
		else {
			series->CustomBarWidth = 30;
		}
		if (_maxZones < 25) {
			series->CustomBarWidth = 90; // ширина метки в пикселах
		}
		else {
			series->CustomBarWidth = 65;
		}
		if (_maxZones < 15) {
			series->CustomBarWidth = 120; // ширина метки в пикселах
		}
		else {
			series->CustomBarWidth = 85;
		}
		// series->BarWidthPercent = 50; //в процентах работает криво
		series->BarStyle = bsRectangle; // примитив метки
		// градиент нафиг, ибо записывается цвет криво
		// series->BarStyle = bsRectGradient;
		// series->BarWidthPercent = 100;
		// series->CustomHorizAxis=
		// ---------------------------дополнительные
		series->Dark3D = false;
		series->MarksOnBar = true;
		series->MultiBar = mbStacked;
		series->OffsetPercent = 50;
		series->Shadow->Visible = false;
		series->YOrigin = 3.0;
		series->XValues->Name = "X";
		series->Emboss->Color = clWhite; //
		series->Emboss->HorizSize = 4;
		series->MultiBar = mbStacked;
		series->SideMargins = false;
		series->XValues->Order = loAscending;
		series->YValues->Name = "Bar";
		series->YValues->Order = loNone;
		// ---------------------------дополнительные
		series->Emboss->Visible = true;
		// series->BarWidthPercent = 5;
		// series->CustomBarWidth=1;
		// Series1->CustomBarWidth
		// series->Shadow->HorizSize = 4;
		// series->Shadow->VertSize = 5;
		// привязка событий к серии
		// series->OnClick=_chart->
		// series->OnDblClick = _chart->;
		// -----------------
		_chart->AddSeries(series);
	}
	_chart->LeftAxis->Minimum = 0;
	_chart->LeftAxis->Maximum = _countSensors + 1;
	_chart->Axes->Behind = false;
	// _chart->LeftAxis->Maximum = 1;
	_chart->Refresh();
}

void TExtFunction::PrepareFastLineChart(int _countSensors, int _lengthChart,
	TChart* _chart) {
	_chart->BackWall->Color = clBtnFace;
	_chart->BackWall->Transparent = false;
	_chart->BottomWall->Visible = false;
	_chart->Foot->AdjustFrame = false;
	_chart->Foot->Alignment = taLeftJustify;
	_chart->Foot->Visible = false;
	_chart->LeftWall->Visible = false;
	_chart->Legend->Visible = false;
	_chart->MarginBottom = 0;
	_chart->MarginLeft = 0;
	_chart->MarginRight = 5;
	_chart->MarginTop = 0;
	_chart->MarginUnits = muPixels;
	_chart->PrintProportional = false;
	_chart->SubFoot->Alignment = taLeftJustify;
	_chart->SubFoot->Visible = false;
	_chart->SubTitle->Alignment = taLeftJustify;
	_chart->SubTitle->Visible = false;
	_chart->Title->Alignment = taLeftJustify;
	// убрать прокрутку по колесу мыши
	// _chart->AllowPanning = Vcltee::Teeprocs::pmNone;
	_chart->AllowPanning = Teeprocs::pmNone;
	// _chart->Title->Text = (L"");
	_chart->Title->Visible = false;
	_chart->BottomAxis->Automatic = false;
	_chart->BottomAxis->AutomaticMaximum = false;
	_chart->BottomAxis->AutomaticMinimum = false;
	_chart->BottomAxis->Axis->Width = 1;
	_chart->BottomAxis->ExactDateTime = false;
	_chart->BottomAxis->Increment = 1;
	_chart->BottomAxis->Maximum = _lengthChart;
	_chart->BottomAxis->MaximumOffset = 1;
	// _chart->BottomAxis->MinorTickCount = 0;
	// _chart->DepthAxis->Automatic = false;
	// _chart->DepthAxis->AutomaticMaximum = false;
	// _chart->DepthAxis->AutomaticMinimum = false;
	// _chart->DepthAxis->ExactDateTime = false;
	// _chart->DepthAxis->Increment = 1;
	// _chart->DepthTopAxis->Automatic = false;
	// _chart->DepthTopAxis->AutomaticMaximum = false;
	// _chart->DepthTopAxis->AutomaticMinimum = false;
	// _chart->DepthTopAxis->ExactDateTime = false;
	// _chart->DepthTopAxis->Increment = 1;
	_chart->Emboss->Color = clLime;
	_chart->LeftAxis->Automatic = false;
	_chart->LeftAxis->AutomaticMaximum = false;
	_chart->LeftAxis->AutomaticMinimum = false;
	_chart->LeftAxis->AxisValuesFormat = "#,##";
	_chart->LeftAxis->ExactDateTime = false;
	_chart->LeftAxis->LabelsMultiLine = true;
	_chart->LeftAxis->LabelsOnAxis = false;
	_chart->LeftAxis->MinorTicks->Visible = false;
	_chart->Pages->AutoScale = true;
	// _chart->Pages->MaxPointsPerPage = 8;
	_chart->RightAxis->Automatic = false;
	_chart->RightAxis->AutomaticMaximum = false;
	_chart->RightAxis->AutomaticMinimum = false;
	_chart->RightAxis->Visible = false;
	_chart->Shadow->Color = clRed;
	_chart->Shadow->Visible = false;
	_chart->TopAxis->Automatic = false;
	_chart->TopAxis->AutomaticMaximum = false;
	_chart->TopAxis->AutomaticMinimum = false;
	_chart->TopAxis->Visible = false;
	_chart->View3D = false;
	_chart->Zoom->Allow = false;
	_chart->Align = alClient;
	_chart->BevelOuter = bvNone;
	// series
	_chart->SeriesList->Clear();
	for (int i = 0; i < _countSensors; i++) {
		TFastLineSeries* series = new TFastLineSeries(_chart);
		// TChartSeries* series = new TChartSeries(_chart);
		series->Depth = 0;
		series->ColorEachPoint = true;
		series->Marks->Visible = false;
		series->Marks->Arrow->Visible = false;
		series->Marks->Callout->Brush->Color = clBlack;
		series->Marks->Callout->Arrow->Visible = false;
		series->Marks->Margins->Left = 44;
		series->ShowInLegend = true;
		// series->AutoRepaint = false;

		// градиент нафиг, ибо записывается цвет криво
		// series->BarStyle = bsRectGradient;
		// series->BarWidthPercent = 100;
		// series->CustomHorizAxis=
		// ---------------------------дополнительные
		// series->Dark3D = false;
		// series->MarksOnBar = true;
		// series->MultiBar = mbStacked;
		// series->OffsetPercent = 50;
		// series->Shadow->Visible = false;
		// series->YOrigin = 3.0;
		series->XValues->Name = "X";
		series->XValues->Order = loAscending;
		series->YValues->Name = "Bar";
		series->YValues->Order = loNone;
		// ---------------------------дополнительные
		// series->BarWidthPercent = 5;
		// series->CustomBarWidth=1;
		// Series1->CustomBarWidth
		// series->Shadow->HorizSize = 4;
		// series->Shadow->VertSize = 5;
		// привязка событий к серии
		// series->OnClick=_chart->
		// series->OnDblClick = _chart->;
		// -----------------
		_chart->AddSeries(series);
	}
	_chart->LeftAxis->Minimum = 0;
	_chart->LeftAxis->Maximum = _countSensors + 1;
	_chart->Axes->Behind = false;
	// _chart->LeftAxis->Maximum = 1;
	_chart->Refresh();
}

// лучше, конечно пользовать параметры
// записываем измерения по цветам в базу
int TExtFunction::SaveChartToDB(AnsiString _serialTubeNum, AnsiString _tubeNum,
	int _codeTubeTypeSize, int _moduleType, int _maxZones, int _codeCustomer,
	int _codeOperatorU, int _codeStatusTube, TChart* _chart) {
	int err = -1;
	int chCount = _chart->SeriesCount();
	TDateTime currentDT;
	// гребаный амеровский формат даты!!!
	AnsiString strCurrentDT = FormatDateTime("yyyy/dd/mm hh:mm:ss",
		currentDT.CurrentDateTime());
	try {
		for (int s = 0; s < chCount; s++) { // серии
			AnsiString strSQL = "";
			strSQL = "insert into SavedTube ";
			strSQL +=
				"(serialTubeNum,TubeNUM,codeTubeTypeSize,tubeModule, sensorNum,saveDataTime,codeStatusTube,codeCustomer,codeOperatorU,maxZones,Zone0,Zone1,Zone2,Zone3,Zone4,Zone5";
			strSQL +=
				",Zone6,Zone7,Zone8,Zone9,Zone10,Zone11,Zone12,Zone13,Zone14,Zone15,Zone16,Zone17,Zone18,Zone19,Zone20,Zone21,Zone22,Zone23";
			strSQL +=
				",Zone24,Zone25,Zone26,Zone27,Zone28,Zone29,Zone30,Zone31,Zone32,Zone33,Zone34,Zone35,Zone36,Zone37";
			strSQL +=
				",Zone38,Zone39,Zone40,Zone41,Zone42,Zone43,Zone44,Zone45,Zone46,Zone47,Zone48,Zone49,Zone50,Zone51,Zone52,Zone53";
			strSQL +=
				",Zone54,Zone55,Zone56,Zone57,Zone58,Zone59,Zone60,Zone61,Zone62,Zone63,Zone64,Zone65,Zone66,Zone67,Zone68,Zone69";
			strSQL +=
				",Zone70,Zone71,Zone72,Zone73,Zone74,Zone75,Zone76,Zone77,Zone78,Zone79,Zone80,Zone81,Zone82,Zone83,Zone84,Zone85";
			strSQL +=
				",Zone86,Zone87,Zone88,Zone89,Zone90,Zone91,Zone92,Zone93,Zone94,Zone95,Zone96,Zone97,Zone98,Zone99) VALUES (";
			// значения полей
			strSQL += "'" + _serialTubeNum + "'";
			strSQL += ",'" + _tubeNum + "'";
			strSQL += ",";
			strSQL += IntToStr(_codeTubeTypeSize);
			strSQL += ",";
			strSQL += IntToStr(_moduleType); ;
			strSQL += ",";
			strSQL += IntToStr(s);
			strSQL += ",";
			strSQL += "CAST('" + strCurrentDT + "' as datetime)";
			strSQL += "," + IntToStr(_codeTubeTypeSize);
			strSQL += "," + IntToStr(_codeCustomer);
			strSQL += "," + IntToStr(_codeOperatorU);
			strSQL += ",";
			strSQL += IntToStr(_maxZones);
			strSQL += ",";
			for (int z = 0; z < 99; z++) { // зоны записываем цвета из чарта
				if (z > _maxZones) {
					strSQL += IntToStr(clWhite);
				}
				else {
					strSQL += _chart->Series[s]->ValueColor[z];
				}
				strSQL += ",";
			}
			// последняя зона
			if (_maxZones < 100) {
				strSQL += IntToStr(clWhite);
			}
			else {
				strSQL += _chart->Series[s]->ValueColor[99];
			}
			strSQL += ")";
			SqlDBModule->ExecStrSql(strSQL);
			err = 0;
		}
	}
	catch (Exception *ex) {
		err = -2;
		// TLog::SaveStrLog(ex->Message);
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
	return err;
}

// int(*_arrDataModule)[8][100]
int TExtFunction::FillArrayModule(AnsiString _tubeNum, int _tubeModule,
	int _maxZones, int _countSensors, int _arrDataModule[8][100]) {
	int err = -1;
	int rec = 0;
	AnsiString msg;
	try {
		// получим данные по сохраненной трубе
		SqlDBModule->ADOQueryDB->Close();
		AnsiString strSql =
			"select rec_id,tubeNUM,codeTubeTypeSize,codeStatusTube,codeCustomer,codeOperatorU,TubeModule,sensorNum";
		for (int z = 0; z < _maxZones; z++) {
			strSql += ",zone" + IntToStr(z);
		}
		strSql += " FROM SavedTube where";
		strSql += " TubeNUM='" + _tubeNum + "'";
		strSql += " and TubeModule=" + IntToStr(_tubeModule);
		strSql += " order by tubeNUM,TubeModule,sensorNum";
		SqlDBModule->ADOQueryDB->SQL->Text = strSql;
		SqlDBModule->ADOQueryDB->Open();
		err = SqlDBModule->ADOQueryDB->RecordCount;
		if (err != _countSensors) {
			err = -33;
			msg = "Ошибка чтения данных по датчикам из БД!!!";
			TLog::SaveStrMsgLog(msg);
		}
		else {
			//
		}
		int s = 0; // номер датчика
		while (!SqlDBModule->ADOQueryDB->Eof) {
			// бежим по записям, как по датчикам, а по полям, как по зонам
			for (int z = 0; z < _maxZones; z++) // номер зоны
			{
				rec = SqlDBModule->ADOQueryDB->FieldByName("rec_id")->AsInteger;
				_arrDataModule[s][z] =
					SqlDBModule->ADOQueryDB->FieldByName("zone" + IntToStr(z))
					->AsInteger;
				// проверка
				// if (_tubeModule == 2 && z == 3 && s == 3) {
				// int a = _arrDataModule[s][z];
				// int b = _arrDataModule[s][z];
				// }
				// else {
				// }
			}
			SqlDBModule->ADOQueryDB->Next();
			s++;
		}
		err = 0;
		// // иммитация дефекта
		// switch (_tubeModule) {
		// case 1: {
		// _arrDataModule[0][0] = clRed;
		// _arrDataModule[1][1] = clRed;
		// break;
		// }
		// case 2: {
		// _arrDataModule[0][0] = clRed;
		// _arrDataModule[1][1] = clYellow;
		// break;
		// }
		// case 5: {
		// _arrDataModule[0][0] = clRed;
		// _arrDataModule[1][1] = clFuchsia;
		// break;
		// }
		// default:
		// //
		// break;
		// }
	}
	catch (Exception *ex) {
		err = -2;
		TLog::ErrFullSaveLog(ex);
		// +MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
	return err;
}

int TExtFunction::ShowArrayModule(int _countSensors, int _maxZones,
	int _arrDataModule[8][100], TChart* _chart) {
	for (int s = 0; s < _countSensors; s++) { // серии
		for (int z = 0; z < _maxZones; z++) { // шаги
			if (z < _maxZones) {
				_chart->Series[s]->AddXY(z, 1, "",
				TColor(_arrDataModule[s][z]));
			}
			else {
				_chart->Series[s]->AddXY(z, 1, "", clWhite);
			}
		};
	};
}

int TExtFunction::UpdateStatusBar(TStatusBar *_StatusBar, AnsiString _strTitle,
	AnsiString _strText, TColor _colorFont) {
	int err = 0;
	// messColor = _colorFont;
	_StatusBar->Panels->Items[0]->Text = _strTitle;
	_StatusBar->Panels->Items[1]->Text = _strText;
	_StatusBar->Refresh();
	return err;
}

int TExtFunction::UpdateLabelStatus(TLabel *_label, AnsiString _strTitle,
	AnsiString _strText, TColor _colorFont) {
	int err = -1;
	try {
		_label->Caption = _strTitle + ": " + _strText;
		_label->Font->Color = _colorFont;
		_label->Refresh();
	}
	catch (Exception *ex) {
		err = -2;
		TLog::ErrFullSaveLog(ex);
		MessageDlg(ex->Message, mtError, TMsgDlgButtons() << mbOK, NULL);
	}
	return err;
}

int TExtFunction::ShowBigModalMessage(AnsiString _strMsg, TColor _color) {
	// TfmMessage* fmMsg = static_cast<TfmMessage*>(_msgFm);
	fmMessage = new TfmMessage(NULL, _strMsg, _color);
	fmMessage->ShowModal();
	delete fmMessage;
}

void TExtFunction::FATAL(AnsiString _msg) {
	// WideString w = _msg;
	// Application->MessageBoxW(w.c_bstr(), L"Аварийное завершение", MB_ICONERROR | MB_OK);
	fmMessage = new TfmMessage(NULL, _msg, clRed);
	fmMessage->ShowModal();
	delete fmMessage;
	throw;
}

void TExtFunction::PrepareChartToTst(TChart *chart, int _countChLog,
	int _lengthChart, int _maxYChart) {
	// настраиваем чарт
	// вырубаем 3Д
	chart->View3D = false;
	chart->View3DWalls = false;
	// вырубаем автоматику
	// chart->AutoRepaint = false;
	chart->BottomAxis->Automatic = false;
	// chart->BottomAxis->Automatic = true;
	chart->BottomAxis->AutomaticMaximum = false;
	if (_lengthChart != 0) {
		chart->BottomAxis->AutomaticMaximum = false;
	}
	else
	{
		chart->BottomAxis->AutomaticMaximum = true;
	}
	if (_maxYChart != 0) {
		chart->LeftAxis->Automatic = false;
		chart->LeftAxis->AutomaticMaximum = false;
		chart->LeftAxis->AutomaticMinimum = false;
		chart->RightAxis->Automatic = false;
		chart->RightAxis->AutomaticMaximum = false;
		chart->RightAxis->AutomaticMinimum = false;
	}
	else {
		chart->LeftAxis->Automatic = true;
		chart->LeftAxis->AutomaticMaximum = true;
		chart->LeftAxis->AutomaticMinimum = true;
		chart->RightAxis->Automatic = true;
		chart->RightAxis->AutomaticMaximum = true;
		chart->RightAxis->AutomaticMinimum = true;
	}
	// контуры чарта, отступы от края
	//и где бля, присвоение размера?
	//chart->Border->Color = clGreen;
//	chart->Border->Width = 3;
//	chart->Border->Visible = true;
	chart->MarginBottom = 1;
	chart->MarginLeft = 1;
	chart->MarginRight = 1;
	chart->MarginTop = 1;
	chart->MarginUnits = muPixels;
	// цвет фона, видимость координатных линий
	// chart->Color = clMedGray;
	chart->Color = clBtnFace;
	chart->AxisVisible = true;
	// число точек   по вертикали, оси
	if (_maxYChart != 0) {
		chart->LeftAxis->Minimum = -_maxYChart;
		chart->LeftAxis->Maximum = _maxYChart;
		chart->LeftAxis->StartPosition = 1;
		chart->RightAxis->Minimum = -_maxYChart;
		chart->RightAxis->Maximum = _maxYChart;
		chart->RightAxis->StartPosition = 1;
	}
	chart->BottomAxis->Minimum = 0;
	chart->BottomAxis->MinimumOffset = 0; // смещение в начале
	// число точек   по горизонтали забьем, от балды
	if (_lengthChart != 0)
		chart->BottomAxis->Maximum = _lengthChart; // viewOffset;
	chart->Title->Text->Clear();
	chart->Title->Text->Add("Сигналы датчиков");
	// поведение мыши
	chart->Zoom->MouseButton = mbLeft;
	// chart->Zoom->MouseWheel = pmwNormal;
	// chart->ZoomWheel = pmwNormal;
	// настройка легенды
	chart->Legend->CheckBoxes = True;
	chart->Legend->LegendStyle = lsSeries;
	// chart->Legend->Alignment=laTop;
	chart->Legend->Alignment = laRight;
	chart->LeftAxis->PositionUnits = muPixels;
	chart->BackWall->Color = clBtnFace;
	chart->BackWall->Transparent = false;
	chart->BottomAxis->Increment = 0;
	chart->BottomAxis->LabelStyle = talValue;
	// дополнительные оси с помощью свойств StartPosition и EndPosition.
	// chart->BottomAxis->StartPosition = 1;
	// chart->BottomAxis->EndPosition = 100;
	chart->BottomAxis->Axis->Width = 1;
	chart->BottomAxis->ExactDateTime = false;
	chart->BottomAxis->Increment = 1;
	chart->LeftAxis->AxisValuesFormat = "#,##";
	// прокрутка разрешена в обоих направлениях
	chart->AllowPanning = pmBoth;
	// позволяет изменять во время выполнения масштаб изображения, вырезая фрагменты диаграммы или графика курсором мыши
	chart->Zoom->Allow = true;
	// chart->Zoom->Allow = false;
	//chart->Align = alClient;
	chart->BevelOuter = bvNone;
	// series
	chart->SeriesList->Clear();
	// currZoomPercent = 100;
	for (int i = 0; i < _countChLog + 1; i++) {
		// TLineSeries* series = new TLineSeries(ChartTest);
		TFastLineSeries* series = new TFastLineSeries(chart);
		// TFastLineSeries* series = new TFastLineSeries(ChartTest);
		// TChartSeries* series = new TChartSeries(ChartTest);
		// series->HorizAxis = aTopAxis;
		// series->AutoRepaint = false;
		// series->AutoRepaint = false;
		// число дополнительных делений между основными
		// series->Depth = 5;
		series->ColorEachPoint = true;
		series->Marks->Visible = false;
		// скругленный
		// series->DrawStyle = dsCurve;
		// толщина линии
		series->LinePen->Width = 1;

		// series->Title=X+IntToStr(i);
		// series->Dark3D = false;
		// TColor colors[] = {clWhite, clBlack, clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clSilver, clRed, clLime, clYellow, clBlue, clAqua, clFuchsia, clCream};
		// if (i < 16) {
		// series->Color = colorsLine[i];
		// }
		// else {
		// series->Color = colorsLine[i - 16];
		// }
		chart->AddSeries(series);
		// нафига нам ось в легенде
		if (i < _countChLog) {
			series->Title = IntToStr(i);
			series->ShowInLegend = true;
		}
		else {
			series->ShowInLegend = false;
			series->Color = clBlack;
			series->LinePen->Width = 3;
		}
		// series->Title += " Мюнхаузен"
	}
	// chart->Repaint();
	// chart->Refresh();
//	chart->Series[0]->Title += " Скачки";
//	chart->Series[1]->Title += " Напряжение";
//	chart->Series[2]->Title += " Ток";
}
