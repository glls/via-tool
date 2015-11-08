//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UnitMain.cpp", FormMain);
USEFORM("UnitAbout.cpp", FormAbout);
USEFORM("UnitHelp.cpp", FormHelp);
USEFORM("UnitLog.cpp", FormLog);
USEFORM("UnitImport.cpp", FormImport);
USEFORM("UnitOptions.cpp", FormOptions);
USEFORM("UnitNewImgProject.cpp", FormNewImg);
USEFORM("UnitNewVidProject.cpp", FormNewVid);
USEFORM("UnitMerge.cpp", FormMerge);
USEFORM("UnitSelectMPEG7.cpp", FormExtractMPEG7);
USEFORM("UnitFormWait.cpp", FormWait);
USEFORM("UnitFormImage.cpp", FormImage);
USEFORM("UnitFormVideo.cpp", FormVideo);
USEFORM("UnitPoints.cpp", FormPoints);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
    Application->Initialize();
    Application->Title = "VIA";
    Application->CreateForm(__classid(TFormMain), &FormMain);
    Application->CreateForm(__classid(TFormLog), &FormLog);
    Application->CreateForm(__classid(TFormOptions), &FormOptions);
    Application->CreateForm(__classid(TFormNewImg), &FormNewImg);
    Application->CreateForm(__classid(TFormNewVid), &FormNewVid);
    Application->CreateForm(__classid(TFormHelp), &FormHelp);
    Application->CreateForm(__classid(TFormImport), &FormImport);
    Application->CreateForm(__classid(TFormPoints), &FormPoints);
    Application->Run();
  }
  catch (Exception &exception)
  {
  	Application->ShowException(&exception);
  }
  catch (...)
  {
    try
    {
    	throw Exception("");
    }
    catch (Exception &exception)
    {
    	Application->ShowException(&exception);
    }
  }
  return 0;
}
//---------------------------------------------------------------------------

