#include "main.h"
#include "dialogs.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	if( checkoutdate( 2014 , 4 , 26 ) )
	{
		MessageBox ( NULL ,  TEXT ( "        < 本软件已超出使用期喽 ╮( ╯▽╰ )╭ >\n< 需要本软件的同学请发送电子邮件至 1174843091@qq.com 索取 >" ) , TEXT ( "EPS" ) ,  MB_OK | MB_ICONINFORMATION ) ;
		exit( 0 );
	}
	Findoutoption( NULL );
    DialogBox( hInstance , MAKEINTRESOURCE(IDD_MAIN) , NULL , Main_Proc );
    return( 0 );
}
