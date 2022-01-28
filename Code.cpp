#include<Windows.h>
#include<tchar.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4
#pragma warning(disable : 4996)/*This is done so that secure coding is eliminated because commands like strtok can be used.*/
LRESULT CALLBACK WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
void AddMenus(HWND);/*Function protopye for adding a menu in the GUI*/
void AddControls(HWND);/*Function prototype for adding controls to buttons in the GUI.*/
void loadImages();
HWND hEdit;
HMENU hMenu;
HWND hOut;
HWND hOut1;
HWND hOut2;
HWND hLogo;
HBITMAP hLogoImage, hGenerateImage;
int main(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR atgs, int ncmdshow)
{
    
    // Register the window class.

    WNDCLASS wc = {0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = L"MyWindowClass";

    if (!RegisterClassW(&wc))
        return -1;

    // Create the window.

    CreateWindowW(L"MyWindowClass",L"My Window",WS_OVERLAPPEDWINDOW|WS_VISIBLE,100,100,1000,800,NULL,NULL,NULL,NULL);

    MSG msg = {0};
    
    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    char emailMessage[1000];/*pointer is declared which contains the list of trigger words below*/
    char* spamwordlist[] = { "act","additional","beneficiary","junk","promise","billion","dont","hesitate","delete","offer","offers","traffic","obligation","refund","sales","click","here","sale","quote","casino","unlimited","instant","presently","satisfaction","serious","trial","luxury","luxurious","bonus","now","affordable","amazed","amazing","boss","compare","call","free","apply","cheap","freedom","guarantee","deal","discount","congratulations","earn","only","risk","order","$money","lowest","urgent","guaranteed","win","winner","refinance","terms","agreement","income","investment","trial","double","expire" };
    char uppercase[50], firstcharupper[50];
    double spamscore = 0, wordcount = 0, rate;
    int i = 0;
    char* strToken;
    strToken = (char*)malloc(sizeof(char) * 80);/*Dynamic Memory Allocation is done which sends the 80 bytes of data to heap.*/
    switch (Msg)
    {
    case WM_COMMAND:
        switch (wParam)
        {
        case FILE_MENU_EXIT:
            MessageBeep(MB_OK);/*command to add message beep sound to the menu which conatins the parameter FILE_MENU_EXIT in it.*/
            DestroyWindow(hwnd);
            break;
        case FILE_MENU_OPEN:
            MessageBeep(MB_OK);/*command to add message beep sound to the menu which conatins the parameter FILE_MENU_OPEN in it.*/
            break;
        case FILE_MENU_NEW:
            MessageBeep(MB_OK);/*command to add message beep sound to the menu which conatins the parameter FILE_MENU_NEW in it.*/
            break;
        case GENERATE_BUTTON:/*The code for the processing which has to be done when the button is pressed.*/
            
            MessageBeep(MB_OK);
            GetWindowTextA(hEdit, emailMessage, 1000);/*This command takes the text which was typed by the user in the box and stores in the array emailMessage*/
            strToken = strtok(emailMessage, " ,.-");
            while (strToken != NULL)
            {
                wordcount++;
                for (i = 0; i < 62; i++)
                {
                    if (strcmp(strToken, spamwordlist[i]) == 0)
                    {
                        spamscore++;
                    }
                    strcpy(uppercase, spamwordlist[i]);
                    for (size_t j = 0; j < strlen(uppercase); j++)
                    {
                        uppercase[j] = toupper(uppercase[j]);
                    }
                    strcpy(firstcharupper, uppercase);
                    for (size_t j = 1; j < strlen(firstcharupper); j++)
                    {
                        firstcharupper[j] = tolower(firstcharupper[j]);
                    }
                    if (strcmp(strToken, uppercase) == 0)
                    {
                        spamscore++;
                    }
                    if (strcmp(strToken, firstcharupper) == 0)
                    {
                        spamscore++;
                    }
                }
                strcpy(uppercase, "");/*Setting uppercase and firstcharupper to Null so that they may be used again in the program.*/
                strcpy(firstcharupper, "");
                strToken = strtok(NULL, " ,.-");/*Declares the next space,comma,period and dash as a delimiter, if such are not present then the string is set to Null.*/
            }
            rate = (spamscore / (wordcount ? wordcount : 1)) * 100;
            char s1[50],s2[50],s3[50];/*Strings are initialized to store strings which contains the processed float int or dounle data.*/
            sprintf(s1,"No. of words is %.1f",wordcount);/*It is used for creating a string which contains the float,double,int data as this cannot be directly outputted.*/
            SetWindowTextA(hOut, s1);/*This will transfer the final string from the string array to the hOut variable*/
            sprintf(s2, "No. of spam words is %.1f", spamscore);
            SetWindowTextA(hOut1, s2);/*This will transfer the final string from the string array to the hOut1 variable*/
            sprintf(s3, "The spam rate is %.1f", rate);
            SetWindowTextA(hOut2,s3);/*This will transfer the final string from the string array to the hOut2 variable*/
            break;
        }
        break;
    case WM_CREATE:
        loadImages();/*Function call to add Images*/
        AddMenus(hwnd);/*Function call to add menu*/
        AddControls(hwnd);/*Function call to add controls and power to the button*/
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, Msg, wParam, lParam);
    }
}
void AddMenus(HWND hwnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();/*A variable is declared which helps in creation of a main menu*/
    HMENU hSubMenu = CreateMenu();/*A variable is declared which helps in creation of a sub-menu*/

    AppendMenu(hSubMenu, MF_STRING,NULL, L"Change Title");/*options in the pop-up*/


    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"Create new");/*options in the pop-up*/
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Open SubMenu");/*options in the pop-up*/
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");/*options in the pop-up, this will close the window as it contains FILE_MENU_EXIT*/


    AppendMenu(hMenu, MF_POPUP,(UINT_PTR)hFileMenu, L"File");/*for creating pop-up menu*/
    AppendMenu(hMenu, MF_STRING, 1, L"settings");/*the main menu*/
    AppendMenu(hMenu, MF_STRING, 1, L"help");/*the main menu*/

    SetMenu(hwnd, hMenu);
}
void AddControls(HWND hwnd)
{
    hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 350, 60, 100, 100, hwnd, NULL, NULL, NULL);
    SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);
    CreateWindowW( L"static", L"Welcome to Spam Email Scanner", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 400, 10, 250, 20, hwnd, NULL, NULL, NULL);
    
    CreateWindowW(L"static",L"Enter Mail in Plain Text Here:",WS_VISIBLE | WS_CHILD| SS_CENTER,250,220,200,30,hwnd,NULL,NULL,NULL);

    hEdit=CreateWindowW( L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE| ES_AUTOVSCROLL, 250, 252, 200, 100, hwnd, NULL, NULL, NULL);
    CreateWindowW( L"Button", L"SCAN", WS_VISIBLE | WS_CHILD, 250,354, 100, 50, hwnd,(HMENU)GENERATE_BUTTON, NULL, NULL);

    CreateWindowW(L"static", L"No. of words", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 443, 100, 50, hwnd, NULL, NULL, NULL);
    hOut = CreateWindowW( L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 430, 200, 50,hwnd, NULL, NULL, NULL);/*This will output the results obtained by processing into the edit box*/

    CreateWindowW(L"static", L"No. of spam words", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 520, 100, 50, hwnd, NULL, NULL, NULL);
    hOut1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 510, 200, 50, hwnd, NULL, NULL, NULL);/*This will do the same outputting*/

    CreateWindowW(L"static", L"Spam rate", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 603, 100, 50, hwnd, NULL, NULL, NULL);
    hOut2 = CreateWindowW( L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 300, 590, 200, 50, hwnd, NULL, NULL, NULL);/*This will do the same outputting*/

}
void loadImages()
{
    hLogoImage= (HBITMAP)LoadImageW(NULL,L"(E:)\\mydir\\logo.bmp",IMAGE_BITMAP,100,100,LR_LOADFROMFILE);
}
