#include "main.h"
#include "dialogs.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	if( checkoutdate( 2014 , 4 , 26 ) )
	{
		MessageBox ( NULL ,  TEXT ( "        < ������ѳ���ʹ����� �r( �s���t )�q >\n< ��Ҫ�������ͬѧ�뷢�͵����ʼ��� 1174843091@qq.com ��ȡ >" ) , TEXT ( "EPS" ) ,  MB_OK | MB_ICONINFORMATION ) ;
		exit( 0 );
	}
	Findoutoption( NULL );
    DialogBox( hInstance , MAKEINTRESOURCE(IDD_MAIN) , NULL , Main_Proc );
    return( 0 );
}
