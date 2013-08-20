//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MCProj.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#define SAVE_PROMPT "��������� ��������� � �����"
#define SAVE_PROMPT_CAPTION "����������"
//---------------------------------------------------------------------------
__fastcall TEventTab::TEventTab(TComponent *AOwner):TTabSheet(AOwner)
{
	OnPaint = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TEventTab::WndProc(Messages::TMessage &Message)
{
	TTabSheet::WndProc(Message);
   switch(Message.Msg)
   {
   	case WM_PAINT: if(OnPaint) OnPaint(this); break;
   }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall CProj::AddValue(void *&Data, DWORD &DataSize,
                                void *Value, int ValSize)
{
   DataSize += ValSize;
   Data = (byte*)realloc(Data, DataSize);
   memcpy((void*)((DWORD)Data + DataSize - ValSize), Value, ValSize);
}
//---------------------------------------------------------------------------
void __fastcall GetValue(void *&Data, DWORD &DataSize,
                         void *Value, int ValSize)
{
   memcpy(Value, (void*)((DWORD)Data + DataSize), ValSize);
   DataSize += ValSize;
}
//---------------------------------------------------------------------------
void __fastcall CProj::GetPRJDump(void *&Dump, DWORD &DumpSize)
{
	int Count = Field->Els->TLs->Count;
	AddValue(Dump, DumpSize, &Count, sizeof(int));
	for(int ci = 0; ci < Field->Els->TLs->Count; ci++)
   {
      void *ElDump = NULL; DWORD ElDumpSize = 0;
   	((CStdElement*)Field->Els->TLs->Items[ci])->GetDump(ElDump, ElDumpSize);
      int ID = (int)((CStdElement*)Field->Els->TLs->Items[ci])->ID_OBJECT;
		AddValue(Dump, DumpSize, &ID, sizeof(int));
		AddValue(Dump, DumpSize, &ElDumpSize, sizeof(DWORD));
		AddValue(Dump, DumpSize, ElDump, ElDumpSize);
      ElDump = (byte*)realloc(ElDump, 0);
   }
	Count = Field->Els->Sms->Count;
	AddValue(Dump, DumpSize, &Count, sizeof(int));
	for(int ci = 0; ci < Field->Els->Sms->Count; ci++)
   {
      void *ElDump = NULL; DWORD ElDumpSize = 0;
   	((CSummator*)Field->Els->Sms->Items[ci])->GetDump(ElDump, ElDumpSize);
      int ID = (int)((CSummator*)Field->Els->Sms->Items[ci])->ID_OBJECT;
		AddValue(Dump, DumpSize, &ID, sizeof(int));
		AddValue(Dump, DumpSize, &ElDumpSize, sizeof(DWORD));
		AddValue(Dump, DumpSize, ElDump, ElDumpSize);
      ElDump = (byte*)realloc(ElDump, 0);
   }
	Count = Field->Els->Us->Count;
	AddValue(Dump, DumpSize, &Count, sizeof(int));
	for(int ci = 0; ci < Field->Els->Us->Count; ci++)
   {
      void *ElDump = NULL; DWORD ElDumpSize = 0;
   	((CUnit*)Field->Els->Us->Items[ci])->GetDump(ElDump, ElDumpSize);
      int ID = (int)((CUnit*)Field->Els->Us->Items[ci])->ID_OBJECT;
		AddValue(Dump, DumpSize, &ID, sizeof(int));
		AddValue(Dump, DumpSize, &ElDumpSize, sizeof(DWORD));
		AddValue(Dump, DumpSize, ElDump, ElDumpSize);
      ElDump = (byte*)realloc(ElDump, 0);
   }
	Count = Field->Els->Ins->Count;
	AddValue(Dump, DumpSize, &Count, sizeof(int));
	for(int ci = 0; ci < Field->Els->Ins->Count; ci++)
   {
      void *ElDump = NULL; DWORD ElDumpSize = 0;
   	((CIn*)Field->Els->Ins->Items[ci])->GetDump(ElDump, ElDumpSize);
      int ID = (int)((CIn*)Field->Els->Ins->Items[ci])->ID_OBJECT;
		AddValue(Dump, DumpSize, &ID, sizeof(int));
		AddValue(Dump, DumpSize, &ElDumpSize, sizeof(DWORD));
		AddValue(Dump, DumpSize, ElDump, ElDumpSize);
      ElDump = (byte*)realloc(ElDump, 0);
   }
	Count = Field->Els->Outs->Count;
	AddValue(Dump, DumpSize, &Count, sizeof(int));
	for(int ci = 0; ci < Field->Els->Outs->Count; ci++)
   {
      void *ElDump = NULL; DWORD ElDumpSize = 0;
   	((COut*)Field->Els->Outs->Items[ci])->GetDump(ElDump, ElDumpSize);
      int ID = (int)((COut*)Field->Els->Outs->Items[ci])->ID_OBJECT;
		AddValue(Dump, DumpSize, &ID, sizeof(int));
		AddValue(Dump, DumpSize, &ElDumpSize, sizeof(DWORD));
		AddValue(Dump, DumpSize, ElDump, ElDumpSize);
      ElDump = (byte*)realloc(ElDump, 0);
   }
	Count = Field->Els->Ls->Count;
	AddValue(Dump, DumpSize, &Count, sizeof(int));
   for(int ci = 0; ci < Field->Els->Ls->Count; ci++)
   {
   	CLink *L = (CLink*)Field->Els->Ls->Items[ci];
      int ID = (int)L->InEl->ID_ELEM, index;
		AddValue(Dump, DumpSize, &ID, sizeof(int));
      int OR = (int)L->IN_OR;
		AddValue(Dump, DumpSize, &OR, sizeof(int));
      switch(L->InEl->ID_ELEM)
      {
      	case ID_STDELEMENT:
         	index = Field->Els->TLs->IndexOf(L->InEl);
				AddValue(Dump, DumpSize, &index, sizeof(int));
         break;
      	case ID_IN:
         	index = Field->Els->Ins->IndexOf(L->InEl);
				AddValue(Dump, DumpSize, &index, sizeof(int));
         break;
      	case ID_OUT:
         	index = Field->Els->Outs->IndexOf(L->InEl);
				AddValue(Dump, DumpSize, &index, sizeof(int));
         break;
      	case ID_SUMMATOR:
         	index = Field->Els->Sms->IndexOf(L->InEl);
				AddValue(Dump, DumpSize, &index, sizeof(int));
         break;
      	case ID_UNIT:
         	index = Field->Els->Us->IndexOf(L->InEl);
				AddValue(Dump, DumpSize, &index, sizeof(int));
         break;
      }
      ID = (int)L->OutEl->ID_ELEM;
		AddValue(Dump, DumpSize, &ID, sizeof(int));
      OR = (int)L->OUT_OR;
		AddValue(Dump, DumpSize, &OR, sizeof(int));
      switch(L->OutEl->ID_ELEM)
      {
      	case ID_STDELEMENT:
         	index = Field->Els->TLs->IndexOf(L->OutEl);
				AddValue(Dump, DumpSize, &index, sizeof(int));
         break;
      	case ID_IN:
         	index = Field->Els->Ins->IndexOf(L->OutEl);
				AddValue(Dump, DumpSize, &index, sizeof(int));
         break;
      	case ID_OUT:
         	index = Field->Els->Outs->IndexOf(L->OutEl);
				AddValue(Dump, DumpSize, &index, sizeof(int));
         break;
      	case ID_SUMMATOR:
         	index = Field->Els->Sms->IndexOf(L->OutEl);
				AddValue(Dump, DumpSize, &index, sizeof(int));
         break;
      	case ID_UNIT:
         	index = Field->Els->Us->IndexOf(L->OutEl);
				AddValue(Dump, DumpSize, &index, sizeof(int));
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall CProj::SetPRJDump(void *Dump, DWORD DumpSize)
{
	int Count = 0; DWORD DS = 0;
	GetValue(Dump, DS, &Count, sizeof(int));
   for(int ci = 0; ci < Count; ci++)
   {
   	int ID = 0;
		GetValue(Dump, DS, &ID, sizeof(int));
      void *ElDump = NULL; DWORD ElDumpSize = 0;
		GetValue(Dump, DS, &ElDumpSize, sizeof(DWORD));
      ElDump = (byte*)realloc(ElDump, ElDumpSize);
		GetValue(Dump, DS, ElDump, ElDumpSize);
      Field->Els->Add((T_ID)ID, 0, 0, 0, 0, ElDump, 0);
      ElDump = (byte*)realloc(ElDump, 0);
   }
	Count = 0;
	GetValue(Dump, DS, &Count, sizeof(int));
   for(int ci = 0; ci < Count; ci++)
   {
   	int ID = 0;
		GetValue(Dump, DS, &ID, sizeof(int));
      void *ElDump = NULL; DWORD ElDumpSize = 0;
		GetValue(Dump, DS, &ElDumpSize, sizeof(DWORD));
      ElDump = (byte*)realloc(ElDump, ElDumpSize);
		GetValue(Dump, DS, ElDump, ElDumpSize);
      Field->Els->Add((T_ID)ID, 0, 0, 0, 0, ElDump, 0);
      ElDump = (byte*)realloc(ElDump, 0);
   }
	Count = 0;
	GetValue(Dump, DS, &Count, sizeof(int));
   for(int ci = 0; ci < Count; ci++)
   {
   	int ID = 0;
		GetValue(Dump, DS, &ID, sizeof(int));
      void *ElDump = NULL; DWORD ElDumpSize = 0;
		GetValue(Dump, DS, &ElDumpSize, sizeof(DWORD));
      ElDump = (byte*)realloc(ElDump, ElDumpSize);
		GetValue(Dump, DS, ElDump, ElDumpSize);
      Field->Els->Add((T_ID)ID, 0, 0, 0, 0, ElDump, 0);
      ElDump = (byte*)realloc(ElDump, 0);
   }
	Count = 0;
	GetValue(Dump, DS, &Count, sizeof(int));
   for(int ci = 0; ci < Count; ci++)
   {
   	int ID = 0;
		GetValue(Dump, DS, &ID, sizeof(int));
      void *ElDump = NULL; DWORD ElDumpSize = 0;
		GetValue(Dump, DS, &ElDumpSize, sizeof(DWORD));
      ElDump = (byte*)realloc(ElDump, ElDumpSize);
		GetValue(Dump, DS, ElDump, ElDumpSize);
      Field->Els->Add((T_ID)ID, 0, 0, 0, 0, ElDump, 0);
      ElDump = (byte*)realloc(ElDump, 0);
   }
	Count = 0;
	GetValue(Dump, DS, &Count, sizeof(int));
   for(int ci = 0; ci < Count; ci++)
   {
   	int ID = 0;
		GetValue(Dump, DS, &ID, sizeof(int));
      void *ElDump = NULL; DWORD ElDumpSize = 0;
		GetValue(Dump, DS, &ElDumpSize, sizeof(DWORD));
      ElDump = (byte*)realloc(ElDump, ElDumpSize);
		GetValue(Dump, DS, ElDump, ElDumpSize);
      Field->Els->Add((T_ID)ID, 0, 0, 0, 0, ElDump, 0);
      ElDump = (byte*)realloc(ElDump, 0);
   }

   Count = 0;
	GetValue(Dump, DS, &Count, sizeof(int));
   CElement *InEl = NULL, *OutEl = NULL;
   for(int ci = 0; ci < Count; ci++)
   {
      int In_ID = 0, Out_ID = 0, index;
		GetValue(Dump, DS, &In_ID, sizeof(int));
      int In_OR = 0, Out_OR = 0;
		GetValue(Dump, DS, &In_OR, sizeof(int));
      switch((T_ID)In_ID)
      {
      	case ID_STDELEMENT:
				GetValue(Dump, DS, &index, sizeof(int));
            InEl = (CElement*)Field->Els->TLs->Items[index];
         break;
      	case ID_IN:
				GetValue(Dump, DS, &index, sizeof(int));
            InEl = (CElement*)Field->Els->Ins->Items[index];
         break;
      	case ID_OUT:
				GetValue(Dump, DS, &index, sizeof(int));
            InEl = (CElement*)Field->Els->Outs->Items[index];
         break;
      	case ID_SUMMATOR:
				GetValue(Dump, DS, &index, sizeof(int));
            InEl = (CElement*)Field->Els->Sms->Items[index];
         break;
      	case ID_UNIT:
				GetValue(Dump, DS, &index, sizeof(int));
            InEl = (CElement*)Field->Els->Us->Items[index];
         break;
      }
      Out_ID = 0;
		GetValue(Dump, DS, &Out_ID, sizeof(int));
      Out_OR = 0;
		GetValue(Dump, DS, &Out_OR, sizeof(int));
      switch((T_ID)Out_ID)
      {
      	case ID_STDELEMENT:
				GetValue(Dump, DS, &index, sizeof(int));
            OutEl = (CElement*)Field->Els->TLs->Items[index];
         break;
      	case ID_IN:
				GetValue(Dump, DS, &index, sizeof(int));
            OutEl = (CElement*)Field->Els->Ins->Items[index];
         break;
      	case ID_OUT:
				GetValue(Dump, DS, &index, sizeof(int));
            OutEl = (CElement*)Field->Els->Outs->Items[index];
         break;
      	case ID_SUMMATOR:
				GetValue(Dump, DS, &index, sizeof(int));
            OutEl = (CElement*)Field->Els->Sms->Items[index];
         break;
      	case ID_UNIT:
				GetValue(Dump, DS, &index, sizeof(int));
            OutEl = (CElement*)Field->Els->Us->Items[index];
         break;
      }
      Field->Els->AddLink(InEl, OutEl, (T_ORIENT)In_OR, (T_ORIENT)Out_OR);
   }
   int SP = 0;
   Field->OnScroll(NULL, scTrack, SP);
	TSScheme->SetFocus();
}
//---------------------------------------------------------------------------
CProj::CProj(void):CObject()
{
   ValHintShow = false;
   OneEnabled = true;
   TSScheme = NULL;
   Active = false;
	Modifyed = false;
   IsNew = false;
   Left = 0;
   Top = 0;
   Width = 0;
   Height = 0;
   FieldWidth = 0;
   FieldHeight = 0;
   CFGFile = NULL;
   DSKFile = NULL;
   DefaultProjName = "";
   ProjExt = "";
   ProjFolder = "";
   ProjName = "";
	PRJ = NULL;
   FProj = NULL;

   StBrProj = NULL;
   PCProj = NULL;
   Field = NULL;
   ElMove = false;

   OnActivate = NULL;
   OnClose = NULL;
}
//---------------------------------------------------------------------------
void __fastcall CProj::SetFieldView(bool AlignToGrid, bool SmartLink,
                                    DWORD FieldColor, DWORD GridColor,
                                    int GridStep)
{
	Field->EnableAlignToGreed = AlignToGrid;
	Field->SmartLink = SmartLink;
   Field->SetColor(FieldColor, GridColor);
   TSScheme->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall CProj::SetFieldMetrix(int FieldWidth, int FieldHeight)
{
	Field->SetMetrix(FieldWidth, FieldHeight);
   TSScheme->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall CProj::OnActivateWnd(TObject *Sender)
{
	if(OnActivate) OnActivate(this);
}
//---------------------------------------------------------------------------
void __fastcall CProj::Init(CBase *Parent)
{
   CObject::Init(Parent);
   PRJ = new CPRJ;
	PRJ->DefaultFolder = ProjFolder;
   PRJ->DefaultExt = ProjExt;
   PRJ->Init(this);
   PRJ->PRJFile.FieldWidth = 500;
   PRJ->PRJFile.FieldHeight = 300;
   PRJ->PRJFile.DT = 0.01;
   PRJ->PRJFile.T = 5;
   PRJ->PRJFile.DW = 1.0;
   PRJ->PRJFile.W = 500;
	FProj = new TFProj(Application);
   FProj->OnActivate = OnActivateWnd;
   FProj->OnClose = OnClose;
}
//---------------------------------------------------------------------------
void __fastcall CProj::New(void)
{
   IsNew = true;
   FProj->Caption = ProjName;
   PRJ->PRJFile.FieldWidth = 500;
   PRJ->PRJFile.FieldHeight = 300;
   PRJ->PRJFile.CalcOrder = 0;
   PRJ->PRJFile.DT = 0.01;
   PRJ->PRJFile.T = 5;
   PRJ->PRJFile.DW = 1;
   PRJ->PRJFile.W = 500;
   CreateWorkSpace();
   PRJ->PRJFile.FieldWidth = TSScheme->ClientWidth;
   PRJ->PRJFile.FieldHeight = TSScheme->ClientHeight;
   if(PRJ->PRJFile.FieldWidth > 1000) PRJ->PRJFile.FieldWidth = 1000;
   if(PRJ->PRJFile.FieldHeight > 1000) PRJ->PRJFile.FieldHeight = 1000;
   Field->SetMetrix(PRJ->PRJFile.FieldWidth, PRJ->PRJFile.FieldHeight);
}
//---------------------------------------------------------------------------
void __fastcall CProj::CreateWorkSpace(void)
{
   FProj->Left = Left;
   FProj->Top = Top;
   FProj->Width = Width;
   FProj->Height = Height;
   FProj->OnActivate = OnActivateWnd;
   FProj->OnClose = OnClose;
   StBrProj = new TStatusBar(FProj);
   StBrProj->Align = alBottom;
   StBrProj->Parent = FProj;
	PCProj = new TPageControl(FProj);
   PCProj->Align = alClient;
   PCProj->Parent = FProj;
   TSScheme = new TEventTab(PCProj);
   TSScheme->Caption = "����������� �����";
   TSScheme->PageControl = PCProj;
   TSScheme->OnMouseDown = OnFieldMD;
   TSScheme->OnMouseMove = OnFieldMM;
   TSScheme->OnMouseUp = OnFieldMU;
   TSScheme->OnKeyDown = OnFieldKD;
   TSScheme->OnPaint = OnPaint;
   Field = new CField;
   Field->SetParent(TSScheme);
   Field->Init(FProj);
   FProj->Show();

   Field->SetMetrix(PRJ->PRJFile.FieldWidth, PRJ->PRJFile.FieldHeight);
   Field->Els->CalcOrder = PRJ->PRJFile.CalcOrder;
   Field->Els->DT = PRJ->PRJFile.DT;
   Field->Els->T = PRJ->PRJFile.T;
   Field->Els->DW = PRJ->PRJFile.DW;
   Field->Els->W = PRJ->PRJFile.W;
   Field->Render();
}
//---------------------------------------------------------------------------
bool __fastcall CProj::Open(void)
{
	if(!PRJ->Open(ProjName))
   {
   	Application->MessageBox(PRJ->IODsc, "IOError",
                              MB_OK | MB_ICONERROR);
      return false;
   }
   if(PRJ->FileOpened)
   {
   	char drive[MAXDRIVE];
   	char dir[MAXDIR];
   	char file[MAXFILE];
   	char ext[MAXEXT];
   	fnsplit(ProjName.c_str(), drive, dir, file, ext);
   	FProj->Caption = file;
   	CreateWorkSpace();
   	void *Dump = NULL; DWORD DumpSize = 0;
   	PRJ->GetPRJDump(Dump, DumpSize);
   	SetPRJDump(Dump, DumpSize);
      PRJ->DonePRJDump();
   }
   else
   	return false;
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall CProj::Open(AnsiString FileName)
{
	if(!PRJ->Read(FileName))
   {
   	Application->MessageBox(PRJ->IODsc, "IOError",
                              MB_OK | MB_ICONERROR);
      return false;
   }
   ProjName = FileName;
   char drive[MAXDRIVE];
   char dir[MAXDIR];
   char file[MAXFILE];
   char ext[MAXEXT];
   fnsplit(ProjName.c_str(), drive, dir, file, ext);
   FProj->Caption = file;
   CreateWorkSpace();
   void *Dump = NULL; DWORD DumpSize = 0;
   PRJ->GetPRJDump(Dump, DumpSize);
   SetPRJDump(Dump, DumpSize);
   PRJ->DonePRJDump();
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall CProj::SaveAs(void)
{
   void *Dump = NULL; DWORD DumpSize = 0;
   GetPRJDump(Dump, DumpSize);
   PRJ->SetPRJDump(Dump, DumpSize);
	if(!PRJ->SaveAs(ProjName))
   {
   	Application->MessageBox(PRJ->IODsc, "IOError",
                              MB_OK | MB_ICONERROR);
   	PRJ->DonePRJDump();
      return false;
   }
   PRJ->DonePRJDump();
   if(!PRJ->FileSaved) return false;
   if(IsNew) IsNew = false;
   if(!Application->Terminated)
   {
   	char drive[MAXDRIVE];
   	char dir[MAXDIR];
   	char file[MAXFILE];
   	char ext[MAXEXT];
   	fnsplit(ProjName.c_str(), drive, dir, file, ext);
   	FProj->Caption = file;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall CProj::Save(void)
{
	if(IsNew)
   {
   	if(!SaveAs()) return false;
   	IsNew = false;
   }
   else
   {
   	void *Dump = NULL; DWORD DumpSize = 0;
   	GetPRJDump(Dump, DumpSize);
      PRJ->SetPRJDump(Dump, DumpSize);
   	if(!PRJ->Write(ProjName))
      {
      	Application->MessageBox(PRJ->IODsc, "IOError",
                                 MB_OK | MB_ICONERROR);
   		PRJ->DonePRJDump();
      	return false;
      }
   	PRJ->DonePRJDump();
   }
   return true;
}
//---------------------------------------------------------------------------
TCloseAction __fastcall CProj::OnProjClose(bool CloseApp)
{
   Modifyed = false;
   bool SaveToDSK = true;
   if(Modifyed)
   {
      int DlgResult = IDYES;
      if(!CFGFile->AutoSavePRJ || IsNew)
      {
      	AnsiString SavePrompt = SAVE_PROMPT;
         SavePrompt += " ";
      	SavePrompt += ProjName;
   		DlgResult = Application->MessageBox(SavePrompt.c_str(),
                                             SAVE_PROMPT_CAPTION,
                                             MB_YESNOCANCEL |
                                             MB_ICONWARNING);
      }
      switch(DlgResult)
      {
      	case IDYES:
         	if(!Save()) return caNone;
         break;
         case IDCANCEL:
            return caNone;
         case IDNO:
         	if(IsNew) SaveToDSK = false;
         break;
      }
   }
   if(CloseApp && SaveToDSK && !IsNew)
   {
      TLastProj *LP = new TLastProj;
      LP->Active = Active;
      LP->Left = FProj->Left;
      LP->Top = FProj->Top;
      LP->Width = FProj->Width;
      LP->Height = FProj->Height;
      LP->Name = ProjName;
   	DSKFile->LastProjs->Add(LP);
   }
	return caHide;
}
//---------------------------------------------------------------------------
TCloseAction __fastcall CProj::CloseProject(bool CloseWnd,
                                            bool CloseApp)
{
   Modifyed = false;
   bool SaveToDSK = true;
   if(Modifyed)
   {
      int DlgResult = IDYES;
      if(!CFGFile->AutoSavePRJ || IsNew)
      {
      	AnsiString SavePrompt = SAVE_PROMPT;
         SavePrompt += " ";
      	SavePrompt += ProjName;
   		DlgResult = Application->MessageBox(SavePrompt.c_str(),
                                             SAVE_PROMPT_CAPTION,
                                             MB_YESNOCANCEL |
                                             MB_ICONWARNING);
      }
      switch(DlgResult)
      {
      	case IDYES:
         	if(!Save()) return caNone;
         break;
         case IDCANCEL:
            return caNone;
         case IDNO:
         	SaveToDSK = false;
         break;
      }
   }
   if(CloseApp && SaveToDSK && !IsNew)
   {
      TLastProj *LP = new TLastProj;
      LP->Active = Active;
      LP->Left = FProj->Left;
      LP->Top = FProj->Top;
      LP->Width = FProj->Width;
      LP->Height = FProj->Height;
      LP->Name = ProjName;
   	DSKFile->LastProjs->Add(LP);
   }
   if(!Application->Terminated && CloseWnd)
   	FProj->Close();
	return caHide;
}
//---------------------------------------------------------------------------
void __fastcall CProj::OnPaint(TObject *Sender)
{
	if(Field) Field->Render();
}
//---------------------------------------------------------------------------
void __fastcall CProj::OnFieldMD(TObject *Sender,
                                    TMouseButton Button,
                                    TShiftState Shift, int X, int Y)
{
	TSScheme->SetFocus();
   if((DWORD)X <= Field->DDRender->Width &&
      (DWORD)Y <= Field->DDRender->Height)
   {
      CElement *El;
   	switch(((CProjCont*)Parent)->GetID())
      {
      	case ID_ARROW:
            if(Button == mbLeft)
            {
               El = Field->ElemClick(X, Y);
               if(!El)
               {
            		Field->Selector->UnSelect();
      				Field->Selector->StartFrame(X, Y);
               }
               else
               {
                  ElMove = TRUE;
    					El->ScrPosX = El->Left + Field->ScrPosX;
      				El->ScrPosY = El->Top + Field->ScrPosY;
    					if(Shift.Contains(ssShift) || Field->Selector->Consist(El))
      				{
         				if(!Field->Selector->Consist(El))
                     	Field->Selector->Select(El);
      				}
      				else
      				{
      					Field->Selector->UnSelect();
      					Field->Selector->Select(El);
     	 				}
                  if(Shift.Contains(ssCtrl))
                  {
                  	ShowVal(El, X, Y);
                  }
                  if(Shift.Contains(ssDouble))
                  {
                  	ElMove = false;
                  	El->SetData();
                  }
                  if(Field->Selector->Consist(El))
                  	for(int ci = 0; ci < Field->Selector->SelBuf->Count; ci++)
                  	{
                  		((CElement*)Field->Selector->SelBuf->Items[ci])->DragLeft =
                     		X - ((CElement*)Field->Selector->SelBuf->Items[ci])->Left;
                  		((CElement*)Field->Selector->SelBuf->Items[ci])->DragTop =
                     		Y - ((CElement*)Field->Selector->SelBuf->Items[ci])->Top;
                  	}
               }
            }
            else
            {
               TPoint P;
            	El = Field->ElemClick(X, Y);
               if(El)
               {
               	P = TSScheme->ClientToScreen(Point(X, Y));
                  El->ShowPopupMenu(P.x, P.y);
                  CurEl = El;
               }
         	}
         break;
         case ID_LINK:
         	El = Field->ElemClick(X, Y);
            if(El) Field->Linking(El, Field->Selector->CURRENT_OR);
         break;
         case ID_NONE:
         break;
         default:
         if(Button == mbLeft)
         {
         	Field->AddElem(((CProjCont*)Parent)->GetID(), X, Y);
   			Field->Selector->UnSelect();
   			Field->Selector->Select(Field->Els->CurrentAdd);
         	Field->Render();
         	((CProjCont*)Parent)->ResetElBts();
         }
      }
   }
}
void __fastcall CProj::OnFieldMM(TObject *Sender, TShiftState Shift,
                                    int X, int Y)
{
   if(Field->Selector->SelFrame)
   {
      Field->Selector->UpDateFrame(X, Y);
   }
   else
   {
   	CElement *El;
   	if(ElMove)
   	{
     		for(int ci = 0; ci < Field->Selector->SelBuf->Count; ci++)
      	{
      		El = (CElement*)Field->Selector->SelBuf->Items[ci];
   			El->Left = X - El->DragLeft;
         	El->Top = Y - El->DragTop;
         	El->ScrPosX = El->Left + Field->ScrPosX;
         	El->ScrPosY = El->Top + Field->ScrPosY;
      	}
   	}
      if(((CProjCont*)Parent)->GetID() == ID_LINK)
      {
         El = Field->ElemClick(X, Y);
         if(El)
         {
         	Field->Selector->CalcLinkOrient(El, X, Y);
            if(El->OrientBusy(Field->Selector->CURRENT_OR))
               Field->Selector->CURRENT_OR = OR_BUSY;
         }
         else
         {
         	Field->Selector->DoneLinkOrient();
         }
      }
   }
   Field->Render();
}
void __fastcall CProj::OnFieldMU(TObject *Sender,
                                 TMouseButton Button,
                                 TShiftState Shift, int X, int Y)
{
 	if(Field->Selector->SelFrame && Button == mbLeft)
   {
		Field->Selector->EndFrame();
      Field->Selector->SelGroup(Field->Els);
   	Field->Render();
   }
   if(ElMove)
   {
   	CElement *El;
   	ElMove = FALSE;
     	for(int ci = 0; ci < Field->Selector->SelBuf->Count; ci++)
      {
      	El = (CElement*)Field->Selector->SelBuf->Items[ci];
         Field->AlignToGreed((DWORD)El->Left, (DWORD)El->Top);
         El->ScrPosX = El->Left + Field->ScrPosX;
         El->ScrPosY = El->Top + Field->ScrPosY;
      }
      Field->Render();
   }
   if(ValHintShow) ReliseValHint();
}

void __fastcall CProj::OnFieldKD(TObject *Sender, Word &Key,
                                 Classes::TShiftState Shift)
{
	if(Key == VK_DELETE)
   {
   	if(Field) Field->DelSelected();
   }
}

void __fastcall CProj::OnEnter(TObject *Sender)
{
	int g;
   g++;
}

void __fastcall CProj::Calc(void)
{
   OneEnabled = true;
	Field->Els->CalcOrder = PRJ->PRJFile.CalcOrder;
   Field->Els->DT = PRJ->PRJFile.DT;
   Field->Els->T = PRJ->PRJFile.T;
   Field->Els->DW = PRJ->PRJFile.DW;
   Field->Els->W = PRJ->PRJFile.W;
	Field->Els->Opredelenie_Up_Svz();
	Field->Els->RASCHET_SISTEM();
}
void __fastcall CProj::CalcByStep(void)
{
   if(OneEnabled)
   {
		Field->Els->CalcOrder = PRJ->PRJFile.CalcOrder;
   	Field->Els->DT = PRJ->PRJFile.DT;
   	Field->Els->T = PRJ->PRJFile.T;
   	Field->Els->DW = PRJ->PRJFile.DW;
   	Field->Els->W = PRJ->PRJFile.W;
		Field->Els->Opredelenie_Up_Svz();
   	Field->Els->CountStep = 0;
   	OneEnabled = false;
   }
	Field->Els->RASCHET_SISTEM_STEP();
}
void __fastcall CProj::OpenGraph(void)
{
	Field->OpenGraph();
}
void __fastcall CProj::ShowVal(CElement *El, int MX, int MY)
{
   if(ValHintShow) return;
   long double Y = 0.0, X = 0.0;
	switch(El->ID_ELEM)
   {
   	case ID_STDELEMENT:
      	Y = real(((CStdElement*)El)->Y_out);
         if(((CStdElement*)El)->In)
         	X = real(((CStdElement*)El)->In[Field->Els->CountStep]);
      break;
   }
   HW = new THintWindow(TSScheme);
   HW->Parent = TSScheme;
   SIZE TS;
   AnsiString ResultStr = "X: ";
   ResultStr += FloatToStr(X);
   ResultStr += "; ";
   ResultStr += "Y: ";
   ResultStr += FloatToStr(Y);
   GetTextExtentPoint32(HW->Canvas->Handle, ResultStr.c_str(),
                        ResultStr.Length() + 2, &TS);
   Windows::TRect rect(TSScheme->ClientToScreen(Point(MX, MY - TS.cy - 4)),
                       TSScheme->ClientToScreen(Point(MX + TS.cx, MY - 3)));
   HW->ActivateHint(rect, ResultStr);
   ValHintShow = true;
}
void __fastcall CProj::ReliseValHint(void)
{
   if(!ValHintShow) return;
	HW->ReleaseHandle();
   HW->Free();
   ValHintShow = false;
}

//---------------------------------------------------------------------------
void __fastcall CProj::Done(void)
{
   Active = false;
	Modifyed = false;
   IsNew = false;
   Left = 0;
   Top = 0;
   Width = 0;
   Height = 0;
   FieldWidth = 0;
   FieldHeight = 0;
   CFGFile = NULL;
   DSKFile = NULL;
   DefaultProjName = "";
   ProjExt = "";
   ProjFolder = "";
   ProjName = "";
	if(PRJ)
   {
   	PRJ->Done();
      delete PRJ;
      PRJ = NULL;
   }

   if(Field)
   {
   	Field->Done();
      delete Field;
      Field = NULL;
   }

   OnActivate = NULL;
   OnClose = NULL;
	CObject::Done();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
CProjCont::CProjCont(TCFGFile *CFGFile, TDSKFile *DSKFile):CObject()
{
   CURRENT_ID = ID_ARROW;
   CloseAllBreak = false;
   CloseApp = false;
   LockOnClose = false;
   ProjCounter = 0;
   DefaultWndLeft = 0;
   DefaultWndTop = 0;
   DefaultWndWidth = 0;
   DefaultWndHeight = 0;
   DefaultFieldWidth = 0;
   DefaultFieldHeight = 0;
   this->CFGFile = CFGFile;
   this->DSKFile = DSKFile;
   DefaultProjName = "";
   DefaultProjExt = "";
   DefaultProjFolder = "";
	PWnds = NULL;
   Parent = NULL;
   AcProj = NULL;
   OnResetButtons = NULL;
   //Application->OnIdle = RenderLoop;
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::SetConfig(bool AlignToGrid, bool SmartLink,
												 DWORD FieldColor, DWORD GridColor,
                                     int AcFieldWidth, int AcFieldHeight,
                                     int AcGridStep)
{
	for(int ci = 0; ci < PWnds->Count; ci++)
   	((CProj*)PWnds->Items[ci])->SetFieldView(AlignToGrid, SmartLink,
                                               FieldColor, GridColor,
                                               AcGridStep);
   AcProj->SetFieldMetrix(AcFieldWidth, AcFieldHeight);
}




//---------------------------------------------------------------------------
void __fastcall CProjCont::Init(CBase *Parent)
{
	CObject::Init(Parent);
	PWnds = new TList;
}
//---------------------------------------------------------------------------
T_ID __fastcall CProjCont::GetID(void)
{
	return CURRENT_ID;
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::ResetElBts(void)
{
   if(OnResetButtons) OnResetButtons();
	CURRENT_ID = ID_ARROW;
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::OnActivate(CBase *Sender)
{
   if(AcProj) AcProj->Active = false;
	AcProj = (CProj*)Sender;
   AcProj->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::OnClose(TObject *Sender,
                                   TCloseAction &Action)
{
   for(int ci = 0; ci < PWnds->Count; ci++)
   	if(Sender == ((CProj*)PWnds->Items[ci])->FProj)
      {
      	Action = ((CProj*)PWnds->Items[ci])->OnProjClose(CloseApp);
         if(Action != caNone)
         {
         	((CProj*)PWnds->Items[ci])->Done();
            delete (CProj*)PWnds->Items[ci];
            PWnds->Delete(ci);
            if(PWnds->Count)
            	AcProj = (CProj*)PWnds->Items[PWnds->Count - 1];
            else
            	AcProj = NULL;
         }
         else CloseAllBreak = true;
         break;
      }
   Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::NewProject()
{
	CProj *Proj = new CProj;
   Proj->Left = DefaultWndLeft;
   Proj->Top = DefaultWndTop;
   Proj->Width = DefaultWndWidth;
   Proj->Height = DefaultWndHeight;
   Proj->FieldWidth = DefaultFieldWidth;
   Proj->FieldHeight = DefaultFieldHeight;
   Proj->ProjName = DefaultProjName;
   Proj->ProjName += ProjCounter;
   Proj->ProjFolder = DefaultProjFolder;
   Proj->ProjExt = DefaultProjExt;
   Proj->CFGFile = CFGFile;
   Proj->DSKFile = DSKFile;
   Proj->OnClose = OnClose;
   Proj->OnActivate = OnActivate;


   Proj->Init(this);
   Proj->New();
	ProjCounter++;
   PWnds->Add(Proj);
   AcProj = Proj;
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::OpenProject()
{
	CProj *Proj = new CProj;
   Proj->Left = DefaultWndLeft;
   Proj->Top = DefaultWndTop;
   Proj->Width = DefaultWndWidth;
   Proj->Height = DefaultWndHeight;
   Proj->ProjFolder = DefaultProjFolder;
   Proj->ProjExt = DefaultProjExt;
   Proj->CFGFile = CFGFile;
   Proj->DSKFile = DSKFile;
   Proj->OnClose = OnClose;
   Proj->OnActivate = OnActivate;
   Proj->Init(this);


   if(Proj->Open())
   {
   	PWnds->Add(Proj);
   	AcProj = Proj;
   }
   else
   {
   	Proj->Done();
      delete Proj;
      Proj = NULL;
   }
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::OpenLastProjects()
{
   CProj *TmpProj = NULL;
   for(int ci = DSKFile->LastProjs->Count - 1; ci >= 0 ; ci--)
   {
		CProj *Proj = new CProj;
   	Proj->Left = ((TLastProj*)DSKFile->LastProjs->Items[ci])->Left;
   	Proj->Top = ((TLastProj*)DSKFile->LastProjs->Items[ci])->Top;
   	Proj->Width = ((TLastProj*)DSKFile->LastProjs->Items[ci])->Width;
   	Proj->Height = ((TLastProj*)DSKFile->LastProjs->Items[ci])->Height;
   	Proj->ProjFolder = DefaultProjFolder;
   	Proj->ProjExt = DefaultProjExt;
   	Proj->CFGFile = CFGFile;
   	Proj->DSKFile = DSKFile;
   	Proj->OnClose = OnClose;
   	Proj->OnActivate = OnActivate;
   	Proj->Init(this);


   	if(Proj->Open(((TLastProj*)DSKFile->LastProjs->Items[ci])->Name))
   	{
   		PWnds->Add(Proj);
   		AcProj = Proj;
         if(((TLastProj*)DSKFile->LastProjs->Items[ci])->Active)
         	TmpProj = Proj;
   	}
   	else
   	{
   		Proj->Done();
      	delete Proj;
      	Proj = NULL;
   	}
   }
   if(TmpProj) SetActiveWindow(TmpProj->FProj->Handle);
   TmpProj = NULL;
   for(int ci = 0; ci < DSKFile->LastProjs->Count; ci++)
   	delete (TLastProj*)DSKFile->LastProjs->Items[ci];
   DSKFile->LastProjs->Clear();
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::SaveActiveProj(void)
{
	if(AcProj) AcProj->Save();
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::SaveAllProjs(void)
{
	for(int ci = 0; ci < PWnds->Count; ci++)
   	((CProj*)PWnds->Items[ci])->Save();
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::SaveAsActiveProj(void)
{
	if(AcProj) AcProj->SaveAs();
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::CloseActiveProj(void)
{
	if(AcProj) AcProj->FProj->Close();
}
//---------------------------------------------------------------------------
TCloseAction __fastcall CProjCont::CloseAllProjs(bool CloseApp)
{
	this->CloseApp = CloseApp;
   for(int ci = PWnds->Count - 1; ci >= 0 ; ci--)
   {
   	((CProj*)PWnds->Items[ci])->FProj->Close();
   	if(CloseAllBreak)
      {
      	if(CloseApp)
         {
            for(int ci = 0; ci < DSKFile->LastProjs->Count; ci++)
         		delete (TLastProj*)DSKFile->LastProjs->Items[ci];
            DSKFile->LastProjs->Clear();
         }
         CloseAllBreak = false;
      	return caNone;
      }
   }
   return caHide;
}
//---------------------------------------------------------------------------
bool __fastcall CProjCont::ElBtsVisible(void)
{
	return true;
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::ShowElBts(void)
{
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::HideElBts(void)
{
}
//---------------------------------------------------------------------------

void __fastcall CProjCont::BtnClick(TObject *Sender)
{
	//CURRENT_ID = ((TElButton*)Sender)->ID_ELEM;
}
void __fastcall CProjCont::RenderLoop(TObject* Sender, bool &Done)
{
   /*
	if(PWnds)
   	for(int ci = 0; ci < PWnds->Count; ci++)
      	((CProj*)PWnds->Items[ci])->Render();
   */
}
void __fastcall CProjCont::CalcActive(void)
{
	if(AcProj) AcProj->Calc();
}
void __fastcall CProjCont::CalcActiveByStep(void)
{
	if(AcProj) AcProj->CalcByStep();
}
void __fastcall CProjCont::OpenGraph(void)
{
	if(AcProj) AcProj->OpenGraph();
}

//---------------------------------------------------------------------------
void __fastcall CProjCont::SetDSK(void)
{
}
//---------------------------------------------------------------------------
void __fastcall CProjCont::Done(void)
{
   LockOnClose = false;
   ProjCounter = 0;
   DefaultWndLeft = 0;
   DefaultWndTop = 0;
   DefaultWndWidth = 0;
   DefaultWndHeight = 0;
   DefaultFieldWidth = 0;
   DefaultFieldHeight = 0;
   CFGFile = NULL;
	DSKFile = NULL;
	DefaultProjName = "";
   DefaultProjExt = "";
   DefaultProjFolder = "";
   AcProj = NULL;
   Parent = NULL;
	if(PWnds)
   {
   	for(int ci = 0; ci < PWnds->Count; ci++)
      {
      	((CProj*)PWnds->Items[ci])->Done();
   		delete (CProj*)PWnds->Items[ci];
      }
		PWnds->Clear();
      delete PWnds;
   }
   CObject::Done();
}
//---------------------------------------------------------------------------
