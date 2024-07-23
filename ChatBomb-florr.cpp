#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

POINT cursorPos1,cursorPos2;
//int x1,y1,x2,y2;

RECT desktop;
//��������Ϣ�����̲����ļ��������Ϣ�������3��������ʹ��10������λ�����룩
int sleeptime = 10;
//��������Ϣ�ļ������ֹ����Ϣ�ٶȹ��졣����ʹ��5000������λ�����룩
int gaptime = 5000;
int method = 1;
int sendtimes;
string inputString;

int setsleeptime() {
    cout << "�����뷢��Ϣ�����̲����ļ��������Ϣ�������3����\n����ʹ��10���루Ĭ�ϣ���\n���Ҫ�ı�������һ�����ڵ���10��������������Ĭ���趨��\n�������Ӧ�����֣���Ҫ������ĸ��";
    int custom_sleeptime;
    if (cin >> custom_sleeptime && custom_sleeptime >= 10) { // ��������Ƿ�Ϊ�������Լ��Ƿ����10
        sleeptime = custom_sleeptime;
    }
    cout << "\n��ǰ�ȴ�ʱ����" << sleeptime << "����һ��������\nҲ����˵����һ����Ϣ��Լ��Ҫ"<< sleeptime*3 << "���롣" << endl << endl;
    return 0; 
}

int setgaptime() {
    cout << "�����뷢��Ϣ�ļ�������ڵ���100������������ֹ����Ϣ�ٶȹ��졣\n����ʹ��5000���루Ĭ�ϣ���\n�������Ӧ�����֣���Ҫ������ĸ��";
    int custom_gaptime;
    if (cin >> custom_gaptime && custom_gaptime >= 100) { // ��������Ƿ�Ϊ�������Լ��Ƿ����100
        gaptime = custom_gaptime;
    }
    cout << "\n��ǰ����Ϣ�ļ��" << gaptime << "����" << endl << endl;
    return 0;
}

int editclipboard() {
    // ��������ַ������Ƶ����а�
    if (OpenClipboard(NULL)) {
        EmptyClipboard();
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, inputString.size() + 1);
        if (hMem) {
            char* pMem = (char*)GlobalLock(hMem);
            if (pMem) {
                strcpy(pMem, inputString.c_str());
                GlobalUnlock(hMem);
                SetClipboardData(CF_TEXT, hMem);
            }
            else {
                GlobalFree(hMem);
            }
        }
        CloseClipboard();
    }
    // ��ȡ���а����ݲ���ӡ
    if (OpenClipboard(NULL)) {
        HANDLE hData = GetClipboardData(CF_TEXT);
        if (hData) {
            char* pMem = (char*)GlobalLock(hData);
            if (pMem) {
                cout << "���а嵱ǰ�������ǣ�" << pMem << endl;
                GlobalUnlock(hData);
            }
        }
        CloseClipboard();
    }
    return 0;
}

int get_message(){
    // ��ȡ�û����벢��ֵ���ַ���
  	cout << "�������뷢�͵���Ϣ���ݣ�";
  	cin >> inputString;
  	//getline(cin,inputString);

  	// ����Ļ�ϴ�ӡ������ַ���
  	cout << "������������ǣ�" << inputString << endl;

    editclipboard();

    return 0;
}

int wait(){
	int seconds;

  	// ��ȡ�û����������
  	cout << "����������Ҫ����׼����������\n�������Ӧ�����֣���Ҫ������ĸ��";
  	cin >> seconds;

  	// ������ת��Ϊ�ַ���
  	stringstream ss;
  	ss << seconds;
  	string timeStr = ss.str();

  	// ƴ���ַ���
  	string command = "timeout /t " + timeStr;
	
  	// ʹ�� system() ִ������
  	system(command.c_str());
} 

int getmouse1(){
	// ��ȡ��Ļ�ֱ���
  	GetWindowRect(GetDesktopWindow(), &desktop);
  	int screenWidth = desktop.right - desktop.left;
  	int screenHeight = desktop.bottom - desktop.top;

    // ��ȡ���λ�ò���ӡ 
  	GetCursorPos(&cursorPos1);
  	cout << "\n��굱ǰλ��: (" << cursorPos1.x << ", " << cursorPos1.y << ")" << endl;

  	// ��ȡҪ����ĵ��λ��
  	//cout << "������Ҫ����ĵ�� X ���� (0 �� " << screenWidth << "): ";
  	//cin >> x1;
  	//x1 = cursorPos1.x ;
  	//cout << "������Ҫ����ĵ�� Y ���� (0 �� " << screenHeight << "): ";
  	//cin >> y1;
  	//y1 = cursorPos1.y ;
	
	cout << "\n�벻Ҫ�ƶ�����������̡�" << endl;
	//cout << "\nĿ��ĵ��λ��: (" << x1 << ", " << y1 << ")" << endl;
    cout << "\nĿ��ĵ��λ��: (" << cursorPos1.x << ", " << cursorPos1.y << ")" << endl;
    return 0;
}

int getmouse2() {
    // ��ȡ��Ļ�ֱ���
    GetWindowRect(GetDesktopWindow(), &desktop);
    int screenWidth = desktop.right - desktop.left;
    int screenHeight = desktop.bottom - desktop.top;

    // ��ȡ���λ�ò���ӡ 
    GetCursorPos(&cursorPos2);
    //cout << "\n��굱ǰλ��: (" << cursorPos2.x << ", " << cursorPos2.y << ")" << endl;

    // ��ȡҪ����ĵ��λ��
    //cout << "������Ҫ����ĵ�� X ���� (0 �� " << screenWidth << "): ";
    //cin >> x2;
    //x2 = cursorPos2.x ;
    //cout << "������Ҫ����ĵ�� Y ���� (0 �� " << screenHeight << "): ";
    //cin >> y2;
    //y2 = cursorPos2.y ;

    //cout << "\n�벻Ҫ�ƶ�����������̡�" << endl;
    //cout << "\nĿ��ĵ��λ��: (" << x2 << ", " << y2 << ")" << endl;
    //cout << "\nĿ��ĵ��λ��: (" << cursorPos2.x << ", " << cursorPos2.y << ")" << endl;
    return 0;
}

int move_back(){
    // ������ƶ���Ŀ���
    //SetCursorPos(x2, y2);
    SetCursorPos(cursorPos2.x, cursorPos2.y);
}

bool judge() {
    char ifstop;
    cout << "���ٴ�ȷ�������Ƿ���ȷ!" << endl;
    cout << "ȷ�ϵĻ��������� N �� n �� 1: ";
    cin >> ifstop;
    if (!(ifstop == 'N' || ifstop == 'n' || ifstop == '1')) {
        cout << "���Ǵ�ͷ��ʼ����������";
        Sleep(3000);
        return 1;
    }
    return 0;
}

int send_message() {
    for (int i = 1;i <= sendtimes;i++) {
        getmouse2();
        // ������ƶ���Ŀ���
        //SetCursorPos(x1, y1);
        SetCursorPos(cursorPos1.x, cursorPos1.y);
        Sleep(sleeptime);
        // ģ��������
        //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x1, y1, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, cursorPos1.x, cursorPos1.y, 0, 0);
        cout << "\t ������ �����ɹ���" << endl;

        Sleep(sleeptime);
        // ģ�� Ctrl+V
        keybd_event(VK_CONTROL, 0, 0, 0); // ���� Ctrl ��
        keybd_event(0x56, 0, 0, 0);  // ���� V ��
        keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0); // �ͷ� V ��
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // �ͷ� Ctrl ��
        cout << "\t Ctrl+v �����ɹ���" << endl;

        // ģ��Enter
        keybd_event(VK_RETURN, 0, 0, 0);  // ���»س���
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // �ͷŻس���

        move_back();

        cout << "\t Enter �����ɹ���" << endl;
        cout << "��" << i << "����Ϣ�ѷ��͡�\t��Ϣ���ݣ�\t"<< inputString << endl << endl;
        if ( i<sendtimes ){
        	Sleep(gaptime);
		}
		else {
			Sleep(1000);
		}
    }
    return 0;
}

int main() {
	startagain:
    cout << "��֧������ Midairlogn ��https://github.com/midairlogn" << endl << endl;
    setsleeptime();
    setgaptime();

    cout << "\n�뽫�˴����ƶ���һ�ߣ���Ҫ�ڵ�Ŀ�괰�ڣ�\n��������ƶ�����Ϣ���Ϳ򣡣���Լ��[ENTER]��E����\n��Ҫ���󣬷�ֹ�㵽���췽ʽ�л��İ�ť��" << endl << endl;
    wait();
    cout << "\n�벻Ҫ�ƶ���ꡣ\n1����ȡ���λ�ã�" << endl << endl;
    Sleep(1000);

    getmouse1();
    if (judge()) {
    	system("cls");
        goto startagain;
    }
    Sleep(1000);
    
    while (1) {
        loop:
        system("cls");
        cout << "��֧������ Midairlogn ��https://github.com/midairlogn" << endl << endl;
        cout << "�����Ϣ��\n1.\tygg pls!(5�Σ�\n2.\tThank you!(3��)\n3.\t/squad-leave ��1�Σ�\n4.\t�Զ��塣\n�������Ӧ�����֣���Ҫ������ĸ��";
        cin >> method;
        switch (method) {
        case 1:
            inputString = "ygg pls!";
            editclipboard();
            sendtimes = 5;
            send_message();
            break;
        case 2:
            inputString = "Thank you!";
            editclipboard();
            sendtimes = 3;
            send_message();
            break;
        case 3:
            inputString = "/squad-leave ";
            editclipboard();
            sendtimes = 1;
            send_message();
            break;
        case 4:
            get_message();
            cout << "\n���������뷢����Ϣ�Ĵ���:";
            cin >> sendtimes;
            send_message();
            break;
        default:
          	goto loop;
        }
    }

 	system("pause");
  	return 0;
}






