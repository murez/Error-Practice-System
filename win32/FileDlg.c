#include <windows.h>
#include <commdlg.h>

static OPENFILENAME ofn;

void FileDlgInit (HWND hwnd)
{
    static TCHAR szFileFilter[] =TEXT ("TXT Files (*.TXT)\0*.TXT\0") \
								 TEXT ("EPS Files (*.EPS)\0*.EPS\0") \
								 TEXT ("DOC Files (*.DOC)\0*.DOC\0") \
								 TEXT ("All Files (*.*)\0*.*\0\0") ;
     
     ofn.lStructSize       = sizeof (OPENFILENAME);
     ofn.hwndOwner         = hwnd;
     ofn.hInstance         = NULL;
     ofn.lpstrFilter       = szFileFilter;
     ofn.lpstrCustomFilter = NULL;
     ofn.nMaxCustFilter    = 0;
     ofn.nFilterIndex      = 0;
     ofn.lpstrFile         = NULL; 
     ofn.nMaxFile          = MAX_PATH;
     ofn.lpstrFileTitle    = NULL;
     ofn.nMaxFileTitle     = MAX_PATH;
     ofn.lpstrInitialDir   = NULL;
     ofn.lpstrTitle        = NULL;
     ofn.Flags             = 0;
     ofn.nFileOffset       = 0;
     ofn.nFileExtension    = 0;
     ofn.lpstrDefExt       = TEXT ("txt");
     ofn.lCustData         = 0L;
     ofn.lpfnHook          = NULL;
     ofn.lpTemplateName    = NULL;
}

BOOL FileOpenDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofn.hwndOwner         = hwnd;
     ofn.lpstrFile         = pstrFileName;
     ofn.lpstrFileTitle    = pstrTitleName;
     ofn.Flags             = OFN_HIDEREADONLY | OFN_CREATEPROMPT;
     
     return GetOpenFileName (&ofn) ;
}

BOOL FileSaveDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofn.hwndOwner         = hwnd;
     ofn.lpstrFile         = pstrFileName;
     ofn.lpstrFileTitle    = pstrTitleName;
     ofn.Flags             = OFN_OVERWRITEPROMPT;
     
     return GetSaveFileName (&ofn);
}
