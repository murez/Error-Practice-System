// �����δ�����ã�������707wkд�ġ�#^_^#
//��������ã��Ҳ�֪����˭д�ġ��r( �s���t )�q
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "filedlg.h"
#include "main.h"
#include "dialogs.h"
#include "resource.h"

int model=1 ;
int num_ec=1 ;
int flag_ans=0 ;
int *num_extract ;
int *num_ans ;
int num_eec=0 ;
int num_temp ;
int num_shows=0 ;

void Filesopen(  ) ;
int Fileslead(  ) ;
void Start(  ) ;
void Findoutoption(  ) ;
void Division(  ) ;
int checkouttext(  ) ;

void Filetemp( char *files , char *filetitle )     //this is �r( �s���t )�q
{
    FILE *fp ;
    //char s[30000] ;
    //getcwd( s , 30000 ) ;
    fp=fopen( "temp.txt" , "w" ) ;
    //fprintf( fp , "ok" ) ;
    fprintf( fp , "%s\n%s\n" , files , filetitle ) ;
    fclose( fp ) ;
    //char s[30000] ="notepad" , n[3000] ="DRAGON.TXT" ;
    //	spawnlp( 0 , s , n ) ;
}

void Init( int num )                             //��¼��ʼ��
{
    FILE *fp ;
    int n=0 ;
    char s[30000] ;
    if( ( fp=fopen( "data\\ec.ini" , "w" ) ) == NULL )
        MessageBox( NULL , "< init:������ļ�δ�ܴ����ɹ� >" , "��ʼ��" , MB_OK ) ;
    while( n<num )
    {
        s[n++ ] ='0' ;
    }
    s[num] =0 ;
    fprintf( fp , "%s" , s ) ;
    fclose( fp ) ;
}

void Inie( int num , int sum , char c )              //�洢����
{
    FILE *fp ;
    int n=0 ;
    char s[30000] ;
    if( ( fp=fopen( "data\\ec.ini" , "r" ) ) == NULL )
        MessageBox( NULL , "< inie:������ļ�δ�ҵ� >" , "�洢����" , MB_OK ) ;
    fgets( s , 30000 , fp ) ;
    s[sum] =0 ;
    s[num - 1] =c ;
    fclose( fp ) ;
    if( ( fp=fopen( "data\\ec.ini" , "w" ) ) == NULL )
        MessageBox( NULL , "< inie:������ļ�δ�ܴ����ɹ� >" , "�洢����" , MB_OK ) ;
    fprintf( fp , "%s" , s ) ;
    fclose( fp ) ;
}

int Ude(  )                                      //ͳ�ƴ�����
{
    char c ;
    int n=0 ;
    FILE *fp ;
    fp=fopen( "data\\ec.ini" , "r" ) ;
    while( ( c=fgetc( fp ) ) != EOF )if( c != '0' )n++  ;
    fclose( fp ) ;
    return n ;
}

void Numtotext( char *num_char , int num_option )  //��ֵת�ַ�
{
    int num_i=num_option ;
	int num_j=0 ;
    char *p=num_char ;
    if( num_option == 0 )
    {
        *p++ ='0' ;
        *p='\0' ;
        return  ;
    }
    while( num_i>0 )
    {
        num_j++  ;
        num_i/=10 ;
    }
    num_i=num_j ;
    while( num_option )
    {
        *( p + num_j - 1 )=num_option%10 + '0' ;
        num_option/=10 ;
        num_j--  ;
    }
    *( p + num_i )='\0' ;
}

int Texttonum( char *num_char )                  //�ַ�ת��ֵ
{
    int num_i=0 ;
    while( *num_char )
    {
        num_i=num_i*10 + *num_char - '0' ;
        num_char++  ;
    }
    return num_i ;
}

int Checkleapyear( int year )                    //�߿�����ʱ4
{
    if( year % 100  ==  0 )
    {
        if( year % 400  ==  0 ) return 1 ;
        else return 0 ;
    }
    else if( year % 4  ==  0 ) return 1 ;
    return 0 ;
}

int Dayinmonth( int month , int year )             //�߿�����ʱ3
{
    switch( month )
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31 ;
        break ;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30 ;
        break ;
    case 2:
        if( Checkleapyear( year ) ) return 29 ;
        else return 28 ;
        break ;
    default:
        return 0 ;
    }
    return 0 ;
}

void Date( HWND hwnd , int year , int mon , int day )  //�߿�����ʱ2
{
    int sum=0 ;
	int num=year ;
    char str[1000] ="��" ;
	char temp[100] ;
    if( ( mon == 6&&day>6 )||( mon>6 ) )num=year + 1 ;
    for(  ; !( year == num&&mon == 6 ) ; sum=sum + Dayinmonth( mon , year ) , mon++  )if( mon>12 )
        {
            mon=1 ;
            year++  ;
        }
    Numtotext( temp , num ) ;
    strcat( str , temp ) ;
    strcat( str , "��߿�����" ) ;
    Numtotext( temp , sum + 6 - day ) ;
    strcat( str , temp ) ;
    strcat( str , "��" ) ;
    SetDlgItemText( hwnd , IDC_DAY , str ) ;
}

void Onlyday( HWND hwnd )                        //�߿�����ʱ1
{
    time_t rawtime ;
    struct tm * timeinfo ;
    time( &rawtime ) ;
    timeinfo=localtime( &rawtime ) ;
    Date( hwnd , 1900 + timeinfo->tm_year , 1 + timeinfo->tm_mon , timeinfo->tm_mday ) ;
}

void Currentsum( HWND hwnd , int num )             //��ʾ������ 
{
    char sum[10] ;
    Numtotext( sum , num ) ;
    SetDlgItemText( hwnd , IDC_TEXT2 , sum ) ;
}

void Currentnum( HWND hwnd , int num )             //��ʾ��ǰ���
{
    char sum[10] ;
    Numtotext( sum , num ) ;
    SetDlgItemText( hwnd , IDC_TEXT3 , sum ) ;
}

void Numerror( HWND hwnd )                       //��ʾ������
{
    char str[100] ;
    Numtotext( str , Ude(  ) ) ;
    SetDlgItemText( hwnd , IDC_TEXT4 , str ) ;
    return  ;
}

int ELFHash( char str[] )                        //�ַ���hashת�� 
{
    int hash=0  ;
    int x=0  ;
    int i  ;
    for( i=0 ; i<strlen( str ) ; i++  )
    {
        hash=( hash<<4 ) + str[i] ;
        if( ( x=( int )( hash&0xF0000000L ) ) != 0 )
        {
            hash^=( x>>24 ) ;
            hash&=~x  ;
        }
    }
    return( hash&0x7FFFFFFF ) ;
}

void settextsize( HWND hwnd , int sizetext )
{
    // �����������
    LOGFONT LogFont  ;
    memset( &LogFont , 0 , sizeof( LOGFONT ) ) ;
    lstrcpy( LogFont.lfFaceName , "����" ) ;//����
    LogFont.lfWeight=400  ;
    LogFont.lfHeight= - sizetext  ;// �����С
    LogFont.lfCharSet=134  ;
    LogFont.lfOutPrecision=3  ;
    LogFont.lfClipPrecision=2  ;
    LogFont.lfOrientation=45  ;
    LogFont.lfQuality=1  ;
    LogFont.lfPitchAndFamily=2  ;
    HFONT hFont=CreateFontIndirect( &LogFont ) ;
    HWND hWndStatic=GetDlgItem( hwnd , IDC_TEXT1 ) ;
    SendMessage( hWndStatic , WM_SETFONT , ( WPARAM )hFont , 0 ) ;
}

int Option( char rw , int nb , int n )               //�洢����
{
    int nu[5] ;
    FILE *fp ;
    if( ( fp=fopen( "data\\option.ini" , "r" ) ) == NULL )
    {
        fclose( fp ) ;
        Findoutoption(  ) ;
        fp=fopen( "data\\option.ini" , "r" ) ;
    }
    fscanf( fp , "num = %d\nsum = %d\npassword = %d\nkey = %d\ntextsize = %d" , &nu[0] , &nu[1] , &nu[2] , &nu[3] , &nu[4] ) ;
    fclose( fp ) ;
    switch( rw )
    {
    case 'r':
        switch( n )
        {
        case 0:
            if( nu[0] == 0 )return 1 ;
            else return nu[0] ;
            break ;
        case 1:
            return nu[1] ;
            break ;
        case 2:
            return nu[2] ;
            break ;
        case 3:
            return nu[3] ;
            break ;
        case 4:
            return nu[4] ;
            break ;
        }
        break ;
    case 'w':
        if( ( fp=fopen( "data\\option.ini" , "w" ) ) == NULL )
        {
            fclose( fp ) ;
            MessageBox( NULL , "< �ļ�����:�����ļ�δ�ܴ����ɹ� >" , "����" , MB_OK ) ;
            exit( 0 ) ;
        }
        switch( n )
        {
        case 0:
            if( nb == 0 )nu[0] =1 ;
            else nu[0] =nb ;
            break ;
        case 1:
            nu[1] =nb ;
            break ;
        case 2:
            nu[2] =nb ;
            break ;
        case 3:
            nu[3] =nb ;
            break ;
        case 4:
            nu[4] =nb ;
            break ;
        }
        fprintf( fp , "num = %d\nsum = %d\npassword = %d\nkey = %d\ntextsize = %d" , nu[0] , nu[1] , nu[2] , nu[3] , nu[4] ) ;
        fclose( fp ) ;
        return 1 ;
    }
    return 0 ;
}

void Division( HWND hwnd )                                //��ʼ�����
{
    FILE *fpin ;
	FILE *fpout ;
    char c_temp ;
	char files[] ="data\\select001.db" ;
    char file[30000] ="" ;
	char filetitle[30000] ="" ;
	char place[30000] ="" ;
    int num_titles ;
	int num_subject=0 ;
    if( ( fpin=fopen( "data\\select.db" , "r" ) ) == NULL )
    {
        fclose( fpin ) ;
		MessageBox( NULL , "< FileOpenDlg:δѡ������ļ� >" , "��ʼ�����" , MB_OK ) ;
		exit( 0 ) ;
    }
    while( !feof( fpin ) )
    {
        num_titles=0 ;
        if( files[13]>'9' )
        {
            files[12]++  ;
            files[13] ='0' ;
        }
        if( files[12]>'9' )
        {
            files[11]++  ;
            files[12] ='0' ;
        }
        if( files[11]>'9' )break ;
        fpout=fopen( files , "w" ) ;
        while( !feof( fpin ) )
        {
            fputc( c_temp=fgetc( fpin ) , fpout ) ;
            if( c_temp == '^' )
            {
                num_titles++  ;
                num_subject++  ;
            }
            if( num_titles == 500 )
            {
                fputc( fgetc( fpin ) , fpout ) ;
                fputc( fgetc( fpin ) , fpout ) ;
                break ;
            }
        }
        fclose( fpout ) ;
        files[13]++  ;
    }
    fclose( fpin ) ;
    if( fopen( "data\\option.ini" , "r" ) == NULL )
    {
        fpin=fopen( "data\\option.ini" , "w" ) ;
        fprintf( fpin , "num = 1\nsum = 10\npassword = 6796286\nkey = 0\ntextsize = 12" ) ;
        fclose( fpin ) ;
    }
    Option( 'w' , num_subject , 1 ) ;
}

int Fileslead( char *file )                     //�������
{
    FILE *fpin ;
	FILE *fpout ;
    char c_temp ;
	char files[] ="data\\select001.db" ;
    int num_titles ;
	int num_subject=0 ;
	if( !checkouttext( file ) ) 
	{
        MessageBox( NULL , "< checkouttext:�Ƿ�������ļ� >" , "�������" , MB_OK ) ;
        return 1 ;
    }
    if( ( fpin=fopen( file , "r" ) ) == NULL )
    {
        fclose( fpin ) ;
        MessageBox( NULL , "< filesopen:����ļ�δ�ҵ� >" , "�������" , MB_OK ) ;
        exit( 0 ) ;
    }
    fpout=fopen( "data\\select.db" , "w" ) ;
    while( !feof( fpin ) )
    {
        fputc( fgetc( fpin ) , fpout ) ;
    }
    fclose( fpout ) ;
    rewind( fpin ) ;
    while( !feof( fpin ) )
    {
        num_titles=0 ;
        if( files[13]>'9' )
        {
            files[12]++  ;
            files[13] ='0' ;
        }
        if( files[12]>'9' )
        {
            files[11]++  ;
            files[12] ='0' ;
        }
        if( files[11]>'9' )break ;
        fpout=fopen( files , "w" ) ;
        while( !feof( fpin ) )
        {
            fputc( c_temp=fgetc( fpin ) , fpout ) ;
            if( c_temp == '^' )
            {
                num_titles++  ;
                num_subject++  ;
            }
            if( num_titles == 500 )
            {
                fputc( fgetc( fpin ) , fpout ) ;
                fputc( fgetc( fpin ) , fpout ) ;
                break ;
            }
        }
        fclose( fpout ) ;
        files[13]++  ;
    }
    fclose( fpin ) ;
    fclose( fpout ) ;
    if( fopen( "data\\option.ini" , "r" ) == NULL )
    {
        fpin=fopen( "data\\option.ini" , "w" ) ;
        fprintf( fpin , "num = 1\nsum = 10\npassword = 6796286\nkey = 0\ntextsize = 12" ) ;
        fclose( fpin ) ;
    }
    Option( 'w' , num_subject , 1 ) ;
    return 0 ;
}

char Displaytext( HWND hwnd , char *s , int num_option , int num_sum )    //��ʾ��Ŀ����
{
    FILE *fp ;
	FILE *fp_temp ;
    char c ;
	char ques ;
	char str[100] ="" ;
	char files[] ="data\\select001.db" ;
    int num_i ;
	int num_flag=0 ;
	int num_files=num_option/500 ;
    num_i=num_option - num_option/500*500 ;
    if( num_option%500 == 0 )
    {
        num_files--  ;
        num_i=500 ;
    }
    files[13] =num_files%10 + '1' ;
    num_files/=10 ;
    files[12] =num_files%10 + '0' ;
    num_files/=10 ;
    files[11] =num_files%10 + '0' ;
    if( ( fp=fopen( files , "rb" ) ) == NULL )
    {
    	MessageBox ( hwnd ,  TEXT( "< TEXT:δ�ҵ�����ļ� >" ) , TEXT ( "TEXT" ) ,  MB_OK | MB_ICONINFORMATION ) ;
    	exit( 0 ) ;
        //Division( hwnd ) ;
        //fp=fopen( files , "rb" ) ;
    }
    if( num_i>1 )
    {
        while( num_i>1&&!feof( fp ) )
            if( ( c=fgetc( fp ) ) == '^' )num_i--  ;
        fgetc( fp ) ;
        fgetc( fp ) ;
        fgetc( fp ) ;
    }
    fp_temp=fopen( "data\\temp" , "w" ) ;
    while( ( c=fgetc( fp ) ) != '^'&&!feof( fp ) )
    {
    	fputc( c , fp_temp ) ;
    }
    fclose( fp_temp ) ;
    fp_temp=fopen( "data\\temp" , "rb" ) ;
    for( num_i=0 ; ( c=fgetc( fp_temp ) ) != '^'&&!feof( fp_temp ) ; num_i++  )
    {
        s[num_i] =c ;
    }
    s[num_i] ='\0' ;
    SetDlgItemText( hwnd , IDC_TEXT1 , s ) ;
    ques=fgetc( fp ) ;
    fclose( fp ) ;
    return ques ;
}

char Displayerror( HWND hwnd , char *s , int num_option , int num_sum )    //��ʾ����Ŀ����
{
    FILE *fp ;
    int num_i=0 ;
    fp=fopen( "data\\ec.ini" , "r" ) ;
    while( num_option&&!feof( fp ) )
    {
        if( fgetc( fp ) != '0' )num_option--  ;
        num_i++  ;
    }
    fclose( fp ) ;
    return Displaytext( hwnd , s , num_i , Option( 'r' , 1 , 1 ) ) ;
}

void Eexam( HWND hwnd )
{
    char s[1000] ="\t\t\t   �ɼ�\n ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  == \n������:" , temp[100] ;
    int num_i ;
	int num_n=0 ;
    for( num_i=0 ; num_i<num_temp ; num_i++  )
        if( num_ans[num_i] == 1 )num_n++  ;
    Numtotext( temp , num_temp ) ;
    strcat( s , temp ) ;
    strcat( s , "\n������:" ) ;
    Numtotext( temp , num_n ) ;
    strcat( s , temp ) ;
    strcat( s , "\n������:" ) ;
    Numtotext( temp , num_temp - num_n ) ;
    strcat( s , temp ) ;
    strcat( s , "\n��ȷ��:" ) ;
    Numtotext( temp , num_n*100/num_temp ) ;
    strcat( s , temp ) ;
    strcat( s , "��\n\n ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  == " ) ;
    MessageBox ( hwnd ,  s , TEXT ( "������ϰ" ) ,  MB_OK | MB_ICONINFORMATION ) ;
}

void Start( HWND hwnd )
{
    FILE *fp ;
    char s[30000] ="" ;
	char char_sum[10] ="" ;
    if( fopen( "data\\ec.ini" , "r" ) == NULL )Init( Option( 'r' , 1 , 1 ) ) ;
    Displaytext( hwnd , s , Option( 'r' , 1 , 0 ) , Option( 'r' , 1 , 1 ) ) ;
    Onlyday( hwnd ) ;
    Currentnum( hwnd , num_ec ) ;
    Numtotext( char_sum , Option( 'r' , 1 , 1 ) ) ;
    SetDlgItemText( hwnd , IDC_TEXT2 , char_sum ) ;
    Numtotext( char_sum , Option( 'r' , 1 , 0 ) ) ;
    SetDlgItemText( hwnd , IDC_TEXT3 , char_sum ) ;
    Numtotext( char_sum , Ude(  ) ) ;
    SetDlgItemText( hwnd , IDC_TEXT4 , char_sum ) ;
    SetDlgItemText( hwnd , IDC_MODEL , "������ϰ" ) ;
}

void Findoutoption( HWND hwnd )
{
    //FILE *fpin ;
    if( fopen( "data\\option.ini" , "r" ) == NULL )
    {
    	MessageBox ( hwnd ,  "< �����ļ�δ�ҵ� >" , TEXT ( "EPS" ) ,  MB_OK | MB_ICONINFORMATION ) ;
    	exit( 0 ) ;
        //fpin=fopen( "data\\option.ini" , "w" ) ;
        //fprintf( fpin , "num = 1\nsum = 10\npassword = 6796286" ) ;
        //fclose( fpin ) ;
        //Division( hwnd ) ;
    }
    if( fopen( "data\\select.db" , "r" ) == NULL )
    {
    	MessageBox ( hwnd ,  "< ����ļ�δ�ҵ� >" , TEXT ( "EPS" ) ,  MB_OK | MB_ICONINFORMATION ) ;
    	exit( 0 ) ; 
    }
}

void Filesbak(  )
{
	FILE *fpin ;
	FILE *fpout ;
	if( ( fpin=fopen( "data\\select.db" , "r" ) ) == NULL )
	{
		MessageBox( NULL , "< Filesopen:001 >" , "�������" , MB_OK ) ;
	}
	if( ( fpout=fopen( "data\\select.bak" , "w" ) ) == NULL )
	{
		MessageBox( NULL , "< Filesopen:002 >" , "�������" , MB_OK ) ;
	}
	while( !feof( fpin ) )
	{
		fputc( fgetc( fpin ) , fpout ) ;
	}
	fclose( fpin ) ;
	fclose( fpout ) ;
}

void Filesopen( HWND hwnd , char *s )
{
	char files[30000] ="" ;
	char filetitle[30000] ="" ;
	char place[30000] ="" ;
	getcwd( place , 30000 ) ;
	Filesbak(  ) ;
	FileDlgInit(  hwnd  ) ;
	if( FileOpenDlg ( hwnd ,  files ,  filetitle ) )
	{
		chdir( place ) ;
		mkdir( "data" ) ;
		if( Fileslead( files ) )
		{
			return  ;
		}
		Start( hwnd ) ;
		Option( 'w' , 1 , 0 ) ;
		Currentnum( hwnd , 1 ) ;
		Displaytext( hwnd , s , 1 , Option( 'r' , 1 , 1 ) ) ;
		Init( Option( 'r' , 1 , 1 ) ) ;
		Numerror( hwnd ) ;
		MessageBox( NULL , "< Filesopen:����ļ��ѵ��� >" , "�������" , MB_OK ) ;
	}
}

void Landingtime( int num_flag )
{
    time_t rawtime ;
    struct tm * timeinfo ;
    FILE *fpout ;
    time( &rawtime ) ;
    timeinfo=localtime( &rawtime ) ;
    fpout=fopen( "data\\log.ini" , "at" ) ;
    switch( num_flag )
    {
    case 0:
        fprintf( fpout , "%4d - %2d - %2d %2d:%2d:%2d	LAND FAIL\n" , 1900 + timeinfo->tm_year , 1 + timeinfo->tm_mon , timeinfo->tm_mday , timeinfo->tm_hour , timeinfo->tm_min , timeinfo->tm_sec ) ;
        break ;
    case 1:
        fprintf( fpout , "%4d - %2d - %2d %2d:%2d:%2d	LAND TRY\n" , 1900 + timeinfo->tm_year , 1 + timeinfo->tm_mon , timeinfo->tm_mday , timeinfo->tm_hour , timeinfo->tm_min , timeinfo->tm_sec ) ;
        break ;
    case 2:
        fprintf( fpout , "%4d - %2d - %2d %2d:%2d:%2d	LAND SUCCEED\n" , 1900 + timeinfo->tm_year , 1 + timeinfo->tm_mon , timeinfo->tm_mday , timeinfo->tm_hour , timeinfo->tm_min , timeinfo->tm_sec ) ;
        break ;
    case 3:
        fprintf( fpout , "%4d - %2d - %2d %2d:%2d:%2d	LAND END\n" , 1900 + timeinfo->tm_year , 1 + timeinfo->tm_mon , timeinfo->tm_mday , timeinfo->tm_hour , timeinfo->tm_min , timeinfo->tm_sec ) ;
        break ;
    }
    fclose( fpout ) ;
}

LRESULT CALLBACK Password( HWND hDlg ,  UINT message ,  WPARAM wParam ,  LPARAM lParam )        //2014/2/10 ������ʱ�ĸ��ٵ�¼����
{
    char passwords[1000] ="" ;
    switch ( message )
    {
    case WM_COMMAND:
        switch( LOWORD( wParam ) )
        {
        case IDC_BTN1:
            GetDlgItemText( hDlg , IDC_EDT2 , passwords , sizeof( passwords ) ) ;
            if( ELFHash( passwords ) == Option( 'r' , 1 , 2 ) )
            {
                Landingtime( 2 ) ;
                EndDialog( hDlg ,  LOWORD( wParam ) ) ;
                return TRUE ;
            }
            else
            {
                SetDlgItemText( hDlg , IDC_EDT2 , "" ) ;
                Landingtime( 0 ) ;
                MessageBox ( hDlg ,  TEXT ( "< �������! >" ) , TEXT ( "��½" ) ,  MB_OK | MB_ICONINFORMATION ) ;
            }
            break ;
        case IDC_BTN2:
        case IDCANCEL:
            exit( 0 ) ;
            break ;
        }
        break ;
    }
    return FALSE ;
}

LRESULT CALLBACK Setpassword( HWND hDlg ,  UINT message ,  WPARAM wParam ,  LPARAM lParam )
{
    char passwords[1000] ="" ;
    switch ( message )
    {
    case WM_COMMAND:
        switch( LOWORD( wParam ) )
        {
        case IDC_BTN3:
            GetDlgItemText( hDlg , IDC_EDT4 , passwords , sizeof( passwords ) ) ;
            if( strcmp( passwords , "" ) == 0 )MessageBox ( hDlg ,  TEXT ( "< ������������ >" ) , TEXT ( "��������" ) ,  MB_OK | MB_ICONINFORMATION ) ;
            else
            {
                if( !Option( 'w' , ELFHash( passwords ) , 2 ) )MessageBox ( hDlg ,  TEXT ( "< �������ó������������� >" ) , TEXT ( "��������" ) ,  MB_OK | MB_ICONINFORMATION ) ;
                else EndDialog( hDlg ,  LOWORD( wParam ) ) ;
            }
            break ;
        case IDC_BTN4:
        case IDCANCEL:
            EndDialog( hDlg ,  LOWORD( wParam ) ) ;
            break ;
        }
        break ;
    }
    return FALSE ;
}

void Showet(  )                                  //�������� 
{
	FILE *fp_in_ec ;
	FILE *fp_in_e ;
	FILE *fp_out ;
	char c_ec ;
	char c_e ;
	fp_in_ec=fopen( "data\\ec.ini" , "r" ) ;
	fp_in_e=fopen( "data\\select.db" , "rb" ) ;
	fp_out=fopen( "data\\ec.db" , "w" ) ;
	while( !feof( fp_in_ec ) )
	{
		c_ec=fgetc( fp_in_ec ) ;
		if( c_ec != '0' )
		{
			while( ( c_e=fgetc( fp_in_e ) ) != '^'&&!feof( fp_in_e ) )
			fputc( c_e , fp_out ) ;
			fputc( c_e , fp_out ) ;
			fputc( fgetc( fp_in_e ) , fp_out ) ;
			fputc( fgetc( fp_in_e ) , fp_out ) ;
			fputc( fgetc( fp_in_e ) , fp_out ) ;
		}
		else
		{
			while( ( c_e=fgetc( fp_in_e ) ) != '^'&&!feof( fp_in_e ) ) ;
			fgetc( fp_in_e ) ;
			fgetc( fp_in_e ) ;
			fgetc( fp_in_e ) ;
		}
	}
	fclose( fp_in_ec ) ;
	fclose( fp_in_e ) ;
	fclose( fp_out ) ;
}

void copyec( char *files , char *filetitle )       //�������⵽�ļ� 
{
	FILE *fp_in ;
	FILE *fp_out ;
 	fp_in=fopen( "data\\ec.db" , "r" ) ;
 	fp_out=fopen( files , "w" ) ;
 	while( !feof( fp_in ) )
 	{
 		fputc( fgetc( fp_in ) , fp_out ) ; 
 	} 
 	fclose( fp_in ) ;
 	fclose( fp_out ) ;
}

/*LRESULT CALLBACK Showerror( HWND hDlg ,  UINT message ,  WPARAM wParam ,  LPARAM lParam )
{
	char files[30000] ;
	char filetitle[30000] ;
	char place[30000] ;
    char c_temp[300000] ;
    switch ( message )
    {
   	case WM_INITDIALOG:
   		Numtotext( c_temp , Ude(  ) ) ;
   		SetDlgItemText( hDlg , IDC_EDT3 , c_temp ) ;
   		Showet(  ) ;
   		getcwd( place , 30000 ) ;
   		FileDlgInit(  hDlg  ) ;
   		if( FileSaveDlg ( hDlg ,  files ,  filetitle ) )
   		{
  			chdir( place ) ;
  			copyec( files , filetitle ) ;
   		}
       		break ;
       	case IDC_BTN6:
        case IDCANCEL:
            EndDialog( hDlg ,  LOWORD( wParam ) ) ;
            break ;
        }
        break ;
    }
    return FALSE ;
}*/

int checkouttext( char *files )
{
	int sum_subject=0 ;
	int num_ans=0 ;
	int num_subject_sizeof=0 ;
	char s[3] ;
	FILE *fpin ;
	if( ( fpin=fopen( files , "r" ) ) == NULL )
	{
		printf( "no files\n" ) ;
	}
	if( !feof( fpin ) )
	{
		s[0] =fgetc( fpin ) ;
		num_subject_sizeof++  ;
	}
	if( !feof( fpin ) )
	{
		s[1] =fgetc( fpin ) ;
		num_subject_sizeof++  ;
	}
	if( !feof( fpin ) )
	{
		s[2] =fgetc( fpin ) ;
		num_subject_sizeof++  ;
	}
	for(  ;!feof( fpin ) ; )
	{
		if( s[1] == '^' )
		{
			sum_subject++  ;
		}
		if( s[0] == '\n' )
		{
			if( s[1] == '^' )
			{
				if( s[2]>='A'&&s[2]<='D' )
				{
					num_ans++  ;
					num_subject_sizeof=0 ;
				}
			}
		}
		if( num_subject_sizeof>4000 )
		{
			fclose( fpin ) ;
			return 0 ;
		}
		if( sum_subject != num_ans )
		{
			fclose( fpin ) ;
			return 0 ;
		}
		s[0] =s[1] ;
		s[1] =s[2] ;
		if( !feof( fpin ) )
		{
			s[2] =fgetc( fpin ) ;
			num_subject_sizeof++  ;
		}
		else
		{
			break ;
		}
	}
	fclose( fpin ) ;
	if( sum_subject == 0 )
	{
		return 0 ;
	}
	return 1 ;
}

int checkoutdate(int date_year , int date_mon , int date_day ) //����ʱ�䷵��1�����򷵻�0 
{
	int flag;
	time_t rawtime;
    struct tm * timeinfo;
   	time(&rawtime);
   	timeinfo=localtime(&rawtime);
    if( 1900+timeinfo->tm_year > date_year )
    {
    	return 1;
    }
    else if( 1900+timeinfo->tm_year == date_year )
    {
    	if( 1+timeinfo->tm_mon > date_mon )
    	{
    		return 1;
    	}
    	else if( 1+timeinfo->tm_mon == date_mon )
    	{
    		if( timeinfo->tm_mday > date_day )
    		{
    			return 1;
    		}
    	}
    }
    return 0;
}

LRESULT CALLBACK Settext( HWND hDlg ,  UINT message ,  WPARAM wParam ,  LPARAM lParam )
{
	int num_sizeof ;
	char textsizeof[100] ; 
	HICON hIcon ;
	HINSTANCE hInstance ;
	int index=0 ;
    switch ( message )
    {
    case WM_INITDIALOG:
    	//���ô��ڵ�ͼ��
		hInstance = GetModuleHandle( NULL ) ;
		hIcon = LoadIcon( hInstance , MAKEINTRESOURCE( IDI_ICONAPP ) ) ;
		SendMessage( hDlg , WM_SETICON , ICON_BIG , ( long )hIcon ) ;
		SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"6" ) ;
		SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"8" ) ;
		SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"10" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"12" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"14" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"16" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"18" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"20" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"22" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"24" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"26" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"28" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"30" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"32" ) ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_ADDSTRING ,  0 ,  ( LPARAM )"34" ) ;
        index=( Option( 'r' , 1 , 4 ) - 6 )/2 ;
        SendDlgItemMessage( hDlg ,  IDC_CBO1 ,  CB_SETCURSEL ,  index ,  0 ) ;
		return TRUE ;
	case WM_PAINT:
		break ;  
    case WM_COMMAND:
        switch( LOWORD( wParam ) )
		{ 
		case IDC_BTN7:		
			GetDlgItemText( hDlg ,  IDC_CBO1 ,  textsizeof ,  100 ) ;
			Option( 'w' , Texttonum( textsizeof ) , 4 ) ;
			EndDialog( hDlg ,  LOWORD( wParam ) ) ;
            return TRUE ;
		case IDC_BTN8:
		case IDCANCEL:
        {
            EndDialog( hDlg ,  LOWORD( wParam ) ) ;
            return TRUE ;
        }
		}
        break ;
    }
    return FALSE ;
}
/*
LRESULT CALLBACK ProcLink( HWND hWnd , UINT Msg , WPARAM wParam , LPARAM lParam )
{
    switch( Msg )
    {
        case WM_SETCURSOR :
        //�������������ʱ����״�����ͣ�
        SetCursor( LoadCursor( NULL , IDC_HAND ) ) ;
        break  ;
        case WM_LBUTTONDOWN :
        //ʵ�ֳ�������
        ShellExecute( NULL , "open" , "http://www.baidu.com" , NULL , NULL , SW_SHOWNORMAL ) ;
        break  ;
        default :
        return CallWindowProc( NULL , hWnd , Msg , wParam , lParam ) ;
        //��Ϣ�ص�
    }
    return 0  ;
}
*/
LRESULT CALLBACK About( HWND hDlg ,  UINT message ,  WPARAM wParam ,  LPARAM lParam )
{
	HICON hIcon ;
	HWND  hImage ;
	HBITMAP hBitmap ;
	HINSTANCE hInstance ;
	PAINTSTRUCT   ps ;     
	HDC   hDC ;   
	RECT   rc ;
	//extern  StaticProc ;
	/*
	��ܳ��������ʾͼƬ�� ( �Уߩ� )
	*/
    switch ( message )
    {
    case WM_INITDIALOG:
    	//���ô��ڵ�ͼ��
		hInstance = GetModuleHandle( NULL ) ;
		//hIcon = LoadIcon( hInstance , MAKEINTRESOURCE( IDI_ICONAPP ) ) ;
		//SendMessage( hDlg , WM_SETICON , ICON_BIG , ( long )hIcon ) ;
		//�����Ǹ�ͼƬ
		hBitmap = LoadBitmap( hInstance , MAKEINTRESOURCE( IDB_ABOUT ) ) ;
		hImage = GetDlgItem( hDlg , IDC_IMG1 ) ;
		SendMessage( hImage , STM_SETIMAGE , IMAGE_BITMAP , ( long )hBitmap ) ;
		hBitmap = LoadBitmap( hInstance , MAKEINTRESOURCE( IDB_BG_ABOUT ) ) ;
		hImage = GetDlgItem( hDlg , IDC_IMG2 ) ;
		SendMessage( hImage , STM_SETIMAGE , IMAGE_BITMAP , ( long )hBitmap ) ;
		//StaticProc=( WNDPROC )SetWindowLong( GetDlgItem( hDlg , IDC_STC8 ) , GWL_WNDPROC , ( LONG )ProcLink ) ;
        return TRUE ;
	case WM_PAINT:   
		//�����Ǹ�������䱳��
		//GetClientRect( hDlg , &rc ) ;   
		//hDC   =   BeginPaint( hDlg , &ps ) ;   
		//FillRect( hDC , &rc , ( HBRUSH )CreateSolidBrush( RGB( 200 ,  227 ,  255 ) ) ) ;
		//EndPaint( hDlg , &ps ) ; 
		break ;  
    case WM_COMMAND:
        if ( LOWORD( wParam )  ==  IDC_ABOUTOK || LOWORD( wParam )  ==  IDCANCEL )
        {
            EndDialog( hDlg ,  LOWORD( wParam ) ) ;
            return TRUE ;
        }
        break ;
    }
    return FALSE ;
}

LRESULT CALLBACK Showstart( HWND hDlg , UINT message , WPARAM wParam , LPARAM lParam )
{
	HICON hIcon ;
	HWND  hImage ;
	HBITMAP hBitmap ;
	HINSTANCE hInstance ;
	PAINTSTRUCT   ps ;     
	HDC   hDC ;   
	RECT   rc ;
    switch( message )
    {
    case WM_INITDIALOG :
    	hInstance = GetModuleHandle( NULL ) ;
    	hBitmap = LoadBitmap( hInstance , MAKEINTRESOURCE( IDI_SHOW ) ) ;
		hImage = GetDlgItem( hDlg , IDC_IMG3 ) ;
		SendMessage( hImage , STM_SETIMAGE , IMAGE_BITMAP , ( long )hBitmap ) ;
        break  ;
    case WM_PAINT :
        break  ;
    case WM_COMMAND :
        switch( LOWORD( wParam ) )
        {
        case IDCANCEL :
            break  ;
        }
        break  ;
    }
    if( num_shows++ >150 )
	{
		EndDialog( hDlg , LOWORD( wParam ) ) ;
		num_shows=0 ;
	}
    return FALSE  ;
}

BOOL WINAPI Main_Proc( HWND hWnd ,  UINT uMsg ,  WPARAM wParam ,  LPARAM lParam )
{
    // Set app icons
    switch( uMsg )
    {
        /* BEGIN MESSAGE CRACK */
        HANDLE_MSG( hWnd ,  WM_INITDIALOG ,  Main_OnInitDialog ) ;
        HANDLE_MSG( hWnd ,  WM_COMMAND ,  Main_OnCommand ) ;
        HANDLE_MSG( hWnd , WM_CLOSE ,  Main_OnClose ) ;
        /* END MESSAGE CRACK */
    }
    return FALSE ;
}

/*******************************************************************************
*  Main_OnInitDialog
*/
BOOL Main_OnInitDialog( HWND hwnd ,  HWND hwndFocus ,  LPARAM lParam )
{
    // Set app icons
    HICON hIcon ;
	HWND  hImage ;
	HBITMAP hBitmap ;
	HINSTANCE hInstance ;
	PAINTSTRUCT   ps ;     
	HDC   hDC ;   
	RECT   rc ;
	//Findoutoption( hwnd ) ;
    //DialogBox( NULL ,  ( LPCTSTR )IDD_UPW ,  hwnd ,  ( DLGPROC )Password ) ;
    //DialogBox( NULL , ( LPCTSTR )IDD_SHOWST , hwnd , ( DLGPROC )Showstart ) ;
    Landingtime( 2 ) ;
    Start( hwnd ) ;
    settextsize( hwnd , Option( 'r' , 1 , 4 ) ) ;
    
    hIcon = LoadIcon( ( HINSTANCE ) GetWindowLong( hwnd ,  GWL_HINSTANCE )  , MAKEINTRESOURCE( IDI_ICONAPP ) ) ;
    SendMessage( hwnd ,  WM_SETICON ,  TRUE ,   ( LPARAM )hIcon ) ;
    SendMessage( hwnd ,  WM_SETICON ,  FALSE ,  ( LPARAM )hIcon ) ;
    
    hInstance = GetModuleHandle( NULL ) ;
    hBitmap = LoadBitmap( hInstance , MAKEINTRESOURCE( IDB_ABOUT ) ) ;
	hImage = GetDlgItem( hwnd , IDC_IMG4 ) ;
	SendMessage( hImage , STM_SETIMAGE , IMAGE_BITMAP , ( long )hBitmap ) ;

    /*
    * Add initializing code here
    */

    return TRUE ;
}

/*******************************************************************************
*  Main_OnCommand
*/
void Main_OnCommand( HWND hwnd ,  int id ,  HWND hwndCtl ,  UINT codeNotify )
{
    FILE *fp ;
    char s[30000] ="" ;
	char ques[] ="\n��ȷ����A" ;
	char ans_c='A' ;
    char str[100] ="" ;
    char files[30000] ="" ;
	char filetitle[30000] ="" ;
	char place[30000] ="" ;
    int num_i ;
	int num_j ;
	int num_option ;
	int num_sum=0 ;
	int num_flag=0 ;
    switch( model )
    {
    case 1:
        ques[11] =Displaytext( hwnd , s , num_i=num_option=Option( 'r' , 1 , 0 ) , num_sum=Option( 'r' , 1 , 1 ) ) ;
        break ;
    case 2:
        ques[11] =Displayerror( hwnd , s , num_ec , Ude(  ) ) ;
        break ;
    case 3:
        ques[11] =Displaytext( hwnd , s , num_extract[num_eec] , Option( 'r' , 1 , 1 ) ) ;
        break ;
    }
    switch( id )
    {
    case IDC_LAST:
        switch( model )
        {
        case 1:
            if( num_option>1 )-- num_option ;
            else MessageBox ( hwnd ,  TEXT ( "< ��һ��� �r( �s���t )�q >" ) , TEXT ( "��һ��" ) ,  MB_OK | MB_ICONINFORMATION ) ;
            Option( 'w' , num_option , 0 ) ;
            Currentnum( hwnd , num_option ) ;
            break ;
        case 2:
            if( num_ec>1 )num_ec--  ;
            Displayerror( hwnd , s , num_ec , Ude(  ) ) ;
            num_flag=1 ;
            break ;
        case 3:
            if( num_eec>0 )
            {
                num_eec--  ;
                Currentnum( hwnd , num_eec + 1 ) ;
            }
            Displaytext( hwnd , s , num_extract[num_eec] , Option( 'r' , 1 , 1 ) ) ;
            num_flag=1 ;
            break ;
        }
        break ;
    case IDC_NEXT:
        switch( model )
        {
        case 1:
            if( num_option<num_sum )++ num_option ;
            else MessageBox ( hwnd ,  TEXT ( "< ���һ��� �r( �s���t )�q >" ) , TEXT ( "��һ��" ) ,  MB_OK | MB_ICONINFORMATION ) ;
            Option( 'w' , num_option , 0 ) ;
            Currentnum( hwnd , num_option ) ;
            flag_ans=1 ;
            break ;
        case 2:
            if( num_ec<Ude(  ) )num_ec++  ;
            Displayerror( hwnd , s , num_ec , Ude(  ) ) ;
            num_flag=1 ;
            break ;
        case 3:
            if( num_eec<num_temp - 1 )
            {
                num_eec++  ;
                Currentnum( hwnd , num_eec + 1 ) ;
            }
            Displaytext( hwnd , s , num_extract[num_eec] , Option( 'r' , 1 , 1 ) ) ;
            num_flag=1 ;
            break ;
        }
        break ;
    case IDR_D:
    case IDC_D:ans_c++  ;
    case IDR_C:
    case IDC_C:ans_c++  ;
    case IDR_B:
    case IDC_B:ans_c++  ;
    case IDR_A:
    case IDC_A:
        switch( model )
        {
        case 1:
            if( ans_c != ques[11] )
            {
                strcat( s , ques ) ;
                SetDlgItemText( hwnd , IDC_TEXT1 , s ) ;
                Inie( num_option , num_sum , ans_c ) ;
				num_flag=1 ;
            }
            else
            {
                Option( 'w' , ++ num_option , 0 ) ;
                Currentnum( hwnd , num_option ) ;
            }
            break ;
        case 2:
            if( ans_c != ques[11] )
            {
                strcat( s , ques ) ;
                SetDlgItemText( hwnd , IDC_TEXT1 , s ) ;
                num_flag=1 ;
            }
            else
            {
                if( num_ec<Ude(  ) )num_ec++  ;
                Currentnum( hwnd , num_ec ) ;
            }
            break ;
        case 3:
            if( ans_c == ques[11] )num_ans[num_eec] =1 ;
            else num_ans[num_eec] =0 ;
            if( num_eec<num_temp - 1 )
            {
                num_eec++  ;
                Currentnum( hwnd , num_eec + 1 ) ;
            }
            break ;
        }
        break ;
    case IDC_JUMP:
    	GetDlgItemText( hwnd , IDC_TEXT3 , str , sizeof( str ) ) ;
     	num_i=Texttonum( str ) ;
        switch( model )
        {
        case 1:
            if( num_sum>=num_i&&num_i>0 )
            {
                Option( 'w' , num_i , 0 ) ;
                Displaytext( hwnd , s , num_i , Option( 'r' , 1 , 1 ) ) ;
            }
            else
            {
                MessageBox ( hwnd ,  TEXT ( "< ��ֵ����:�Ƿ���ֵ ���أ� >" ) , TEXT ( "����" ) ,  MB_OK | MB_ICONINFORMATION ) ;
                num_i=num_option ;
            }
            break ;
        case 2:
            if( Ude(  )>=num_i&&num_i>0 )
            {
                Displayerror( hwnd , s , num_ec=num_i , Ude(  ) ) ;
            }
            else
            {
                MessageBox ( hwnd ,  TEXT ( "< ��ֵ����:�Ƿ���ֵ ���أ� >" ) , TEXT ( "����" ) ,  MB_OK | MB_ICONINFORMATION ) ;
            }
            break ;
        case 3:
            if( num_temp>=num_i&&num_i>=0 )
            {
                num_eec=num_i - 1 ;
                Displaytext( hwnd , s , num_extract[num_eec] , Option( 'r' , 1 , 1 ) ) ;
            }
            else
            {
                MessageBox ( hwnd ,  TEXT ( "< ��ֵ����:�Ƿ���ֵ ���أ� >" ) , TEXT ( "eps" ) ,  MB_OK | MB_ICONINFORMATION ) ;
            }
            break ;
        }
        break ;
    case IDC_NORMAL:
        if( model != 1 )
        {
            SetDlgItemText( hwnd , IDC_MODEL , "������ϰ" ) ;
            Currentnum( hwnd , Option( 'r' , 1 , 0 ) ) ;
            Displaytext( hwnd , s , Option( 'r' , 1 , 0 ) , Option( 'r' , 1 , 1 ) ) ;
            model=1 ;
        }
        break ;
    case IDC_ERROR:
        if( model != 2 )
        {
            if( !Ude(  ) )MessageBox ( hwnd ,  TEXT ( "< Ŀǰû�д���  - _ - ||| >" ) , TEXT ( "������ϰ" ) ,  MB_OK | MB_ICONINFORMATION ) ;
            else
            {
                num_ec=1 ;
                Currentnum( hwnd , num_ec ) ;
                SetDlgItemText( hwnd , IDC_MODEL , "������ϰ" ) ;
                Displayerror( hwnd , s , num_ec , Ude(  ) ) ;
                model=2 ;
            }
        }
        break ;
    case IDC_EXTRACT:
        if( model != 3 )
        {
            GetDlgItemText( hwnd , IDC_TEXT6 , str , sizeof( str ) ) ;
            num_temp=Texttonum( str ) ;
            if( num_temp>=Option( 'r' , 1 , 1 )||num_temp<1 )
            {
                MessageBox ( hwnd ,  TEXT ( "< ��ֵ����:�Ƿ���ֵ ( �Уߩ� ) >" ) , TEXT ( "������ϰ" ) ,  MB_OK | MB_ICONINFORMATION ) ;
                break ;
            }
            srand( time( NULL ) ) ;
            num_extract=( int * )malloc( sizeof( int )*num_temp ) ;
            num_ans=( int * )malloc( sizeof( int )*num_temp ) ;
            num_eec=0 ;
            for( num_i=0 ; num_i<num_temp ; num_i++  )
            {
                num_extract[num_i] =rand(  )%Option( 'r' , 1 , 1 ) + 1 ;
                for( num_j=0 ; num_j<num_i ; num_j++  )
                    if( num_extract[num_i] == num_extract[num_j] )
                    {
                        num_i--  ;
                        break ;
                    }
            }
            SetDlgItemText( hwnd , IDC_MODEL , "������ϰ" ) ;
            Currentnum( hwnd , num_eec + 1 ) ;
            model=3 ;
            Displaytext( hwnd , s , num_extract[num_eec] , Option( 'r' , 1 , 1 ) ) ;
        }
        break ;
    case IDC_PRESENT:
        if( model == 3 )
        {
            Eexam( hwnd ) ;
            model=1 ;
            SetDlgItemText( hwnd , IDC_MODEL , "������ϰ" ) ;
            Currentnum( hwnd , Option( 'r' , 1 , 0 ) ) ;
            SetDlgItemText( hwnd , IDC_TEXT6 , "0" ) ;
            Displaytext( hwnd , s , Option( 'r' , 1 , 0 ) , Option( 'r' , 1 , 1 ) ) ;
        }
        break ;
    case IDM_OPEN:
 		if( model == 1 )
 		{
        	Filesopen( hwnd , s ) ;
 		}
 		else
 		{
 			MessageBox ( hwnd ,  TEXT ( "< ֻ��������ģʽ�²��ܵ�������ļ� �r( �s_�t )�q >" ) , TEXT ( "�������" ) ,  MB_OK | MB_ICONINFORMATION ) ;
 		}
        break ;
    case IDM_RESET:
    	if( model == 1 )
    	{ 
    	if( MessageBox( hwnd , TEXT( "ȷ�������ѵ�������?( ������������ ) ( O_O )��" ) , TEXT( "��������" ) , MB_YESNO ) == 6 )
    	{
    		Fileslead( "data\\select.bak" ) ;
    		SetDlgItemText( hwnd , IDC_MODEL , "������ϰ" ) ;
    		Option( 'w' , 1 , 0 ) ;
            Currentnum( hwnd , 1 ) ;
            SetDlgItemText( hwnd , IDC_TEXT4 , "0" ) ;
            Currentsum( hwnd , Option( 'r' , 1 , 1 ) ) ;
            Init( Option( 'r' , 1 , 1 ) ) ;
            Displaytext( hwnd , s , Option( 'r' , 1 , 0 ) , Option( 'r' , 1 , 1 ) ) ;
            //model=1 ;
            //Start( hwnd ) ;
    	}
    	}
		else
		{
			MessageBox ( hwnd ,  TEXT ( "< ֻ��������ģʽ�²��ܳ������� �r( �s_�t )�q >" ) , TEXT ( "��������" ) ,  MB_OK | MB_ICONINFORMATION ) ;
		}
    	break ;
    case IDM_EXAMPLE:
    	MessageBox ( hwnd ,  TEXT ( "\
example:\n\n\
1.Do you think there is any room for us ________ ?\n\
A.two	B.the two		C.second		D.the second\n\
^A\n\
2.The People��s Liberation Army was founded _____ .\n\
A.on August 1 , 1927	B.in 1927 , 1 August		\n\
C.on Aaugust 1st , 1927	D.in August 1 , 1927\n\
^C\n\
3.��What year is it ?�� ��It is ______ .��\n\
A.nineteen hundred and ninety - seven	B.nineteen and ninety - seven\n\
C.nineteen ninety and seven			D.nineteen ninety - seven\n\
^D" ) , TEXT ( "���ģ��" ) ,  MB_OK | MB_ICONINFORMATION ) ;
    break ;
    case IDM_HELP:
        MessageBox ( hwnd ,  "\
��������⡿\n\
	����ļ�����Ϊ�ı��ļ�����Ŀ��ʽ��ο������ģ�塿\n\
	ѡ������ļ����������򿪡���ť���ɵ�����⡣�������������Զ�ˢ������ļ�����մ����¼�������������־\n\
��ˢ����⡿\n\
	�����Ŀ�������룬��ˢ����⣬�����¼�������ļ�\n\
��������ϰ��\n\
	��ģ�鰴������˳����ϰ��Ŀ���������Ŀ���Զ���¼�ڴ�����ļ��� , ���Ե���Ŀ�����¼��������ڡ���ǰ��š��������������Ҫ��������ţ�Ȼ�󰴡���������ť���ܵ���ָ����Ŀ\n\
��������ϰ��\n\
	�������Ŀ�����ڱ�ģ��������ϰ�������Ժ󲻻�ɾ��\n\
��������ϰ��\n\
	��ģ�齫������������ȡ����������������밴��������ť\n\
�������־��\n\
	��ģ��Ὣ��ÿ�ε�½��ʱ�䱣����data�ļ���log.ini�ļ�\n" , TEXT ( "EPS����" ) ,  MB_OK | MB_ICONINFORMATION ) ;
        break ;
    case IDM_ABOUT:
        DialogBox( NULL ,  ( LPCTSTR )IDD_ABOUT ,  hwnd ,  ( DLGPROC )About ) ;
        break ;
    case IDM_SHOWERROR:
    	if( !Ude(  ) )MessageBox ( hwnd ,  TEXT ( "< Ŀǰû�д��� �r( �s_�t )�q >" ) , TEXT ( "�鿴����" ) ,  MB_OK | MB_ICONINFORMATION ) ;
    	else
    	{
	    	Showet(  ) ;
   			getcwd( place , 30000 ) ;
   			FileDlgInit(  hwnd  ) ;
   			if( FileSaveDlg ( hwnd ,  files ,  filetitle ) )
   			{
  				chdir( place ) ;
  				copyec( files , filetitle ) ;
   			}
	    }
        break ;
    case IDM_CLEAR:
        if( Ude(  ) != 0 )
        {
            if( MessageBox( hwnd , TEXT( "ȷ����մ���? ( O_O )��" ) , TEXT( "��մ���" ) , MB_YESNO ) == 6 )
            {
                Init( Option( 'r' , 1 , 1 ) ) ;
                Numerror( hwnd ) ;
                num_ec=1 ;
                num_flag=1 ;
            }
        }
        else MessageBox ( hwnd ,  TEXT ( "< Ŀǰû�д��� �r( �s_�t )�q >" ) , TEXT ( "��մ���" ) ,  MB_OK | MB_ICONINFORMATION ) ;
        break ;
    case IDM_CLOG:
        if( MessageBox( hwnd , TEXT( "ȷ�������־? �r( �s_�t )�q " ) , TEXT( "�����־" ) , MB_YESNO ) == 6 )
        {
            if( fopen( "data\\log.ini" , "w" ) != NULL )MessageBox ( hwnd ,  TEXT ( "< ��־����� >" ) , TEXT ( "�����־" ) ,  MB_OK | MB_ICONINFORMATION ) ;
            else MessageBox ( hwnd ,  TEXT ( "< ��־���ʧ�� o( ���� )o >" ) , TEXT ( "�����־" ) ,  MB_OK | MB_ICONINFORMATION ) ;
        }
        break ;
    case IDM_REFRESH:
        Division( hwnd ) ;
        if( model == 3 )Start( hwnd ) ;
        Displaytext( hwnd , s , Option( 'r' , 1 , 0 ) , Option( 'r' , 1 , 1 ) ) ;
        break ;
    case IDM_TEXTSIZE:
    	DialogBox( NULL ,  ( LPCTSTR )IDD_SETTEXT ,  hwnd ,  ( DLGPROC )Settext ) ;
    	settextsize( hwnd , Option( 'r' , 1 , 4 ) ) ;
    	switch( model )
    	{
    	case 1:
            	SetDlgItemText( hwnd , IDC_TEXT1 , s ) ;
        break ;
    	case 2:
            	Displayerror( hwnd , s , num_ec , Ude(  ) ) ;

        	break ;
    	case 3:
         	   Displaytext( hwnd , s , num_extract[num_eec] , Option( 'r' , 1 , 1 ) ) ;
        	break ;
    	}
    	break ;
    case IDM_SUP:
        DialogBox( NULL ,  ( LPCTSTR )IDD_SUP ,  hwnd ,  ( DLGPROC )Setpassword ) ;
        break ;
    case IDM_EXIT:
        EndDialog( hwnd ,  id ) ;
        break ;
    default:
    	return  ;
        break ;
    }
    if( num_flag )
    switch( model )
    {
    case 1:
        if( num_flag )
        {
            Numerror( hwnd ) ;
            SetDlgItemText( hwnd , IDC_TEXT1 , s ) ;
        }
        break ;
    case 2:
        if( num_flag )
        {
            Currentnum( hwnd , num_ec ) ;
            SetDlgItemText( hwnd , IDC_TEXT1 , s ) ;
        }
        else
        {
            Displayerror( hwnd , s , num_ec , Ude(  ) ) ;
        }
        break ;
    case 3:
        if( num_flag )
        {
            SetDlgItemText( hwnd , IDC_TEXT1 , s ) ;
        }
        else
        {
            Displaytext( hwnd , s , num_extract[num_eec] , Option( 'r' , 1 , 1 ) ) ;
        }
        break ;
    }
}

/*******************************************************************************
*  Main_OnClose
*/
void Main_OnClose( HWND hwnd )
{
    EndDialog( hwnd ,  0 ) ;
}
