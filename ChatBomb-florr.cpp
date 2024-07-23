#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

POINT cursorPos1,cursorPos2;
//int x1,y1,x2,y2;

RECT desktop;
//调整发消息鼠标键盘操作的间隔，发消息间隔是其3倍，建议使用10。（单位：毫秒）
int sleeptime = 10;
//调整发消息的间隔，防止发消息速度过快。建议使用5000。（单位：毫秒）
int gaptime = 5000;
int method = 1;
int sendtimes;
string inputString;

int setsleeptime() {
    cout << "请输入发消息鼠标键盘操作的间隔，发消息间隔是其3倍。\n建议使用10毫秒（默认）。\n如果要改变请输入一个大于等于10的整数，否则按照默认设定。\n请输入对应的数字，不要输入字母：";
    int custom_sleeptime;
    if (cin >> custom_sleeptime && custom_sleeptime >= 10) { // 检查输入是否为整数，以及是否大于10
        sleeptime = custom_sleeptime;
    }
    cout << "\n当前等待时间是" << sleeptime << "毫秒一个动作。\n也就是说发送一条消息大约需要"<< sleeptime*3 << "毫秒。" << endl << endl;
    return 0; 
}

int setgaptime() {
    cout << "请输入发消息的间隔（大于等于100的整数），防止发消息速度过快。\n建议使用5000毫秒（默认）。\n请输入对应的数字，不要输入字母：";
    int custom_gaptime;
    if (cin >> custom_gaptime && custom_gaptime >= 100) { // 检查输入是否为整数，以及是否大于100
        gaptime = custom_gaptime;
    }
    cout << "\n当前发消息的间隔" << gaptime << "毫秒" << endl << endl;
    return 0;
}

int editclipboard() {
    // 将输入的字符串复制到剪切板
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
    // 获取剪切板内容并打印
    if (OpenClipboard(NULL)) {
        HANDLE hData = GetClipboardData(CF_TEXT);
        if (hData) {
            char* pMem = (char*)GlobalLock(hData);
            if (pMem) {
                cout << "剪切板当前的内容是：" << pMem << endl;
                GlobalUnlock(hData);
            }
        }
        CloseClipboard();
    }
    return 0;
}

int get_message(){
    // 获取用户输入并赋值给字符串
  	cout << "请输入想发送的消息内容：";
  	cin >> inputString;
  	//getline(cin,inputString);

  	// 在屏幕上打印输入的字符串
  	cout << "您输入的内容是：" << inputString << endl;

    editclipboard();

    return 0;
}

int wait(){
	int seconds;

  	// 获取用户输入的秒数
  	cout << "请输入你需要用来准备的秒数。\n请输入对应的数字，不要输入字母：";
  	cin >> seconds;

  	// 将秒数转换为字符串
  	stringstream ss;
  	ss << seconds;
  	string timeStr = ss.str();

  	// 拼接字符串
  	string command = "timeout /t " + timeStr;
	
  	// 使用 system() 执行命令
  	system(command.c_str());
} 

int getmouse1(){
	// 获取屏幕分辨率
  	GetWindowRect(GetDesktopWindow(), &desktop);
  	int screenWidth = desktop.right - desktop.left;
  	int screenHeight = desktop.bottom - desktop.top;

    // 获取鼠标位置并打印 
  	GetCursorPos(&cursorPos1);
  	cout << "\n鼠标当前位置: (" << cursorPos1.x << ", " << cursorPos1.y << ")" << endl;

  	// 获取要点击的点的位置
  	//cout << "请输入要点击的点的 X 坐标 (0 到 " << screenWidth << "): ";
  	//cin >> x1;
  	//x1 = cursorPos1.x ;
  	//cout << "请输入要点击的点的 Y 坐标 (0 到 " << screenHeight << "): ";
  	//cin >> y1;
  	//y1 = cursorPos1.y ;
	
	cout << "\n请不要移动鼠标或操作键盘。" << endl;
	//cout << "\n目标的点击位置: (" << x1 << ", " << y1 << ")" << endl;
    cout << "\n目标的点击位置: (" << cursorPos1.x << ", " << cursorPos1.y << ")" << endl;
    return 0;
}

int getmouse2() {
    // 获取屏幕分辨率
    GetWindowRect(GetDesktopWindow(), &desktop);
    int screenWidth = desktop.right - desktop.left;
    int screenHeight = desktop.bottom - desktop.top;

    // 获取鼠标位置并打印 
    GetCursorPos(&cursorPos2);
    //cout << "\n鼠标当前位置: (" << cursorPos2.x << ", " << cursorPos2.y << ")" << endl;

    // 获取要点击的点的位置
    //cout << "请输入要点击的点的 X 坐标 (0 到 " << screenWidth << "): ";
    //cin >> x2;
    //x2 = cursorPos2.x ;
    //cout << "请输入要点击的点的 Y 坐标 (0 到 " << screenHeight << "): ";
    //cin >> y2;
    //y2 = cursorPos2.y ;

    //cout << "\n请不要移动鼠标或操作键盘。" << endl;
    //cout << "\n目标的点击位置: (" << x2 << ", " << y2 << ")" << endl;
    //cout << "\n目标的点击位置: (" << cursorPos2.x << ", " << cursorPos2.y << ")" << endl;
    return 0;
}

int move_back(){
    // 将鼠标移动到目标点
    //SetCursorPos(x2, y2);
    SetCursorPos(cursorPos2.x, cursorPos2.y);
}

bool judge() {
    char ifstop;
    cout << "请再次确认坐标是否正确!" << endl;
    cout << "确认的话，请输入 N 或 n 或 1: ";
    cin >> ifstop;
    if (!(ifstop == 'N' || ifstop == 'n' || ifstop == '1')) {
        cout << "我们从头开始，重新来！";
        Sleep(3000);
        return 1;
    }
    return 0;
}

int send_message() {
    for (int i = 1;i <= sendtimes;i++) {
        getmouse2();
        // 将鼠标移动到目标点
        //SetCursorPos(x1, y1);
        SetCursorPos(cursorPos1.x, cursorPos1.y);
        Sleep(sleeptime);
        // 模拟左键点击
        //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x1, y1, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, cursorPos1.x, cursorPos1.y, 0, 0);
        cout << "\t 左键点击 操作成功！" << endl;

        Sleep(sleeptime);
        // 模拟 Ctrl+V
        keybd_event(VK_CONTROL, 0, 0, 0); // 按下 Ctrl 键
        keybd_event(0x56, 0, 0, 0);  // 按下 V 键
        keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0); // 释放 V 键
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // 释放 Ctrl 键
        cout << "\t Ctrl+v 操作成功！" << endl;

        // 模拟Enter
        keybd_event(VK_RETURN, 0, 0, 0);  // 按下回车键
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); // 释放回车键

        move_back();

        cout << "\t Enter 操作成功！" << endl;
        cout << "第" << i << "轮消息已发送。\t消息内容：\t"<< inputString << endl << endl;
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
    cout << "请支持作者 Midairlogn ：https://github.com/midairlogn" << endl << endl;
    setsleeptime();
    setgaptime();

    cout << "\n请将此窗口移动到一边，不要遮挡目标窗口！\n并将鼠标移动至消息发送框！（大约在[ENTER]的E处）\n不要过左，防止点到聊天方式切换的按钮。" << endl << endl;
    wait();
    cout << "\n请不要移动鼠标。\n1秒后获取鼠标位置！" << endl << endl;
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
        cout << "请支持作者 Midairlogn ：https://github.com/midairlogn" << endl << endl;
        cout << "快捷消息：\n1.\tygg pls!(5次）\n2.\tThank you!(3次)\n3.\t/squad-leave （1次）\n4.\t自定义。\n请输入对应的数字，不要输入字母：";
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
            cout << "\n请输入你想发送消息的次数:";
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






