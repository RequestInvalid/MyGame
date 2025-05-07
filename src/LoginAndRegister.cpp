#include "LoginAndRegister.h"

extern GameStatus Status;
extern UserData *user;

typedef enum FrameStatus
{
    NONE,
    USERNAME,
    PASSPORT,
} FrameStatus;

TCHAR *getUserNameString(char *name, int start, int end)
{
    static DWORD currentTime, lastTime = 0;
    static bool showCursor = true;                                      // 控制光标显示状态
    TCHAR *result = (TCHAR *)malloc((end - start + 2) * sizeof(TCHAR)); // 分配内存

    // 截取指定范围内的字符串
    int i;
    for (i = start; i < end && name[i] != '\0'; i++)
    {
        result[i - start] = name[i];
    }
    result[i - start] = '\0'; // 添加字符串结束符
    currentTime = GetTickCount();
    if (currentTime - lastTime >= 300)
    {
        showCursor = !showCursor;
        lastTime = currentTime;
    }
    if (showCursor)
    {
        result[i - start] = '|';
        result[i - start + 1] = '\0'; // 添加字符串结束符
    }
    return result;
}

void loginBox()
{
    FrameStatus frameStatus = NONE;
    ExMessage action;
    UserData *userPtr, *head = loadUserData();
    int name_length = 0, passport_length = 0;
    char temp_name[21], temp_passport[19];
    char star[19] = "******************";

    LOGFONT f;
    settextstyle(30, 0, _T("Times New Roman"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&f);
    setfillcolor(WHITE);

    while (true)
    {
        peekmessage(&action, EM_MOUSE | EM_KEY); //获取鼠标消息
        BeginBatchDraw();
        EasyPutImage(305, 75, "img/login.png", 350, 400);
        /*检测左键按下*/
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            if (determineMouse(action, 606, 103, 637, 133) || determineMouse(action, 505, 400, 595, 440)) //退出按钮
            {
                Status = MAIN_MENU;
                break;
            }
            else if (determineMouse(action, 351, 218, 614, 264)) //用户名
            {
                frameStatus = USERNAME;
            }
            else if (determineMouse(action, 351, 322, 614, 367)) //密码
            {
                frameStatus = PASSPORT;
            }
            else if (determineMouse(action, 371, 400, 462, 440)) //确定
            {
                if (name_length > 0 && passport_length > 0)
                {
                    userPtr = searchUserData(head, (char *)getUserNameString(temp_name, 0, name_length));
                    if (userPtr != NULL && !strcmp(userPtr->pasport, (char *)getUserNameString(temp_passport, 0, passport_length)))
                    {
                        user = userPtr;
                        Status = GAMING; //登录成功跳转
                        EndBatchDraw();
                        return;
                    }
                }
            }
            else
            {
                frameStatus = NONE;
            }
        }
        /*检测键盘按下*/
        else if (isKeyPressed(&action))
        {
            if (GetAsyncKeyState(VK_SHIFT)) //按下SHIFT时输入大写字母
            {
                if (frameStatus == USERNAME && name_length < 20)
                {
                    if (action.vkcode >= 'A' && action.vkcode <= 'Z')
                    {
                        temp_name[name_length] = action.vkcode;
                        name_length++;
                    }
                }
                else if (frameStatus == PASSPORT && passport_length < 18)
                {
                    if (action.vkcode >= 'A' && action.vkcode <= 'Z')
                    {
                        temp_passport[passport_length] = action.vkcode;
                        passport_length++;
                    }
                }
            }
            else if (action.vkcode == VK_TAB) //按下TAB时切换窗口
            {
                if (frameStatus == USERNAME)
                {
                    frameStatus = PASSPORT;
                }
                else if (frameStatus == PASSPORT)
                {
                    frameStatus = USERNAME;
                }
            }
            else if ((action.vkcode >= 'A' && action.vkcode <= 'Z') ||
                     (action.vkcode >= '0' && action.vkcode <= '9')) //输入小写字母及数字
            {
                if (frameStatus == USERNAME && name_length < 20)
                {
                    temp_name[name_length] = tolower(action.vkcode);
                    name_length++;
                }
                else if (frameStatus == PASSPORT && passport_length < 18)
                {
                    temp_passport[passport_length] = tolower(action.vkcode);
                    passport_length++;
                }
            }
            else if (action.vkcode == VK_BACK) //输入BACKSPACE时退格
            {
                if (frameStatus == USERNAME && name_length > 0)
                {
                    name_length--;
                }
                else if (frameStatus == PASSPORT && passport_length > 0)
                {
                    passport_length--;
                }
            }
            else if (action.vkcode == VK_RETURN) //输入ENTER时确认用户名及密码
            {
                if (name_length > 0 && passport_length > 0)
                {
                    userPtr = searchUserData(head, (char *)getUserNameString(temp_name, 0, name_length));
                    if (userPtr != NULL && !strcmp(userPtr->pasport, (char *)getUserNameString(temp_passport, 0, passport_length)))
                    {
                        user = userPtr;
                        Status = GAMING; //登录成功跳转
                        EndBatchDraw();
                        return;
                    }
                }
            }
            solidrectangle(351, 225, 351 + textwidth(charInRange(temp_name, 0, name_length)), 225 + textheight(charInRange(temp_name, 0, name_length)));
            solidrectangle(351, 322, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 322 + textheight(charInRange(temp_passport, 0, passport_length)));
            outtextxy(351, 225, charInRange(temp_name, 0, name_length));
            outtextxy(351, 322, charInRange(star, 0, passport_length));
        }
        else
        {
            if (frameStatus == USERNAME)
            {
                solidrectangle(351, 225, 351 + textwidth(charInRange(temp_name, 0, name_length)), 225 + textheight(charInRange(temp_name, 0, name_length)));
                solidrectangle(351, 322, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 322 + textheight(charInRange(temp_passport, 0, passport_length)));
                outtextxy(351, 225, getUserNameString(temp_name, 0, name_length));
                outtextxy(351, 322, charInRange(star, 0, passport_length));
            }
            else if (frameStatus == PASSPORT)
            {
                solidrectangle(351, 225, 351 + textwidth(charInRange(temp_name, 0, name_length)), 225 + textheight(charInRange(temp_name, 0, name_length)));
                solidrectangle(351, 322, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 322 + textheight(charInRange(temp_passport, 0, passport_length)));
                outtextxy(351, 225, charInRange(temp_name, 0, name_length));
                outtextxy(351, 322, getUserNameString(star, 0, passport_length));
            }
        }
        FlushBatchDraw();
    }
}

void registerBox()
{
    FrameStatus frameStatus = NONE;
    ExMessage action;
    UserData user, *head = loadUserData();
    int name_length = 0, passport_length = 0;
    char temp_name[21], temp_passport[19];
    char star[19] = "******************";

    LOGFONT f;
    settextstyle(30, 0, _T("Times New Roman"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&f);
    setfillcolor(WHITE);

    while (true)
    {
        peekmessage(&action, EM_MOUSE | EM_KEY); //获取鼠标消息
        BeginBatchDraw();
        EasyPutImage(305, 75, "img/register.png", 350, 400);
        /*检测左键按下*/
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            if (determineMouse(action, 606, 103, 637, 133) || determineMouse(action, 505, 400, 595, 440)) //退出按钮
            {
                Status = MAIN_MENU;
                break;
            }
            else if (determineMouse(action, 351, 218, 614, 264)) //用户名
            {
                frameStatus = USERNAME;
            }
            else if (determineMouse(action, 351, 322, 614, 367)) //密码
            {
                frameStatus = PASSPORT;
            }
            else if (determineMouse(action, 371, 400, 462, 440)) //确定
            {
                if (name_length > 0 && passport_length > 0 && !searchUserData(head, (char *)charInRange(temp_name, 0, name_length)))
                {
                    strcpy(user.username, (const char *)charInRange(temp_name, 0, name_length));
                    strcpy(user.pasport, (const char *)charInRange(temp_passport, 0, passport_length));
                    head = loadUserData();
                    addUserData(head, user);
                    Status = MAIN_MENU; //注册成功切换到主菜单界面
                    EndBatchDraw();
                    return;
                }
            }
            else
            {
                frameStatus = NONE;
            }
        }
        /*检测键盘按下*/
        else if (isKeyPressed(&action))
        {
            if (GetAsyncKeyState(VK_SHIFT)) //按下SHIFT时输入大写字母
            {
                if (frameStatus == USERNAME && name_length < 20)
                {
                    if (action.vkcode >= 'A' && action.vkcode <= 'Z')
                    {
                        temp_name[name_length] = action.vkcode;
                        name_length++;
                    }
                }
                else if (frameStatus == PASSPORT && passport_length < 18)
                {
                    if (action.vkcode >= 'A' && action.vkcode <= 'Z')
                    {
                        temp_passport[passport_length] = action.vkcode;
                        passport_length++;
                    }
                }
            }
            else if (action.vkcode == VK_TAB) //按下TAB时切换窗口
            {
                if (frameStatus == USERNAME)
                {
                    frameStatus = PASSPORT;
                }
                else if (frameStatus == PASSPORT)
                {
                    frameStatus = USERNAME;
                }
            }
            else if ((action.vkcode >= 'A' && action.vkcode <= 'Z') ||
                     (action.vkcode >= '0' && action.vkcode <= '9')) //输入小写字母及数字
            {
                if (frameStatus == USERNAME && name_length < 20)
                {
                    temp_name[name_length] = tolower(action.vkcode);
                    name_length++;
                }
                else if (frameStatus == PASSPORT && passport_length < 18)
                {
                    temp_passport[passport_length] = tolower(action.vkcode);
                    passport_length++;
                }
            }
            else if (action.vkcode == VK_BACK) //输入BACKSPACE时退格
            {
                if (frameStatus == USERNAME && name_length > 0)
                {
                    name_length--;
                }
                else if (frameStatus == PASSPORT && passport_length > 0)
                {
                    passport_length--;
                }
            }
            else if (action.vkcode == VK_RETURN) //输入ENTER时确认用户名及密码
            {
                if (name_length > 0 && passport_length > 0 && !searchUserData(head, (char *)charInRange(temp_name, 0, name_length)))
                {
                    strcpy(user.username, (const char *)charInRange(temp_name, 0, name_length));
                    strcpy(user.pasport, (const char *)charInRange(temp_passport, 0, passport_length));
                    head = loadUserData();
                    addUserData(head, user);
                    EndBatchDraw();
                    Status = MAIN_MENU; //注册成功切换到主菜单界面
                    break;
                }
            }
            solidrectangle(351, 225, 351 + textwidth(charInRange(temp_name, 0, name_length)), 225 + textheight(charInRange(temp_name, 0, name_length)));
            solidrectangle(351, 322, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 322 + textheight(charInRange(temp_passport, 0, passport_length)));
            outtextxy(351, 225, charInRange(temp_name, 0, name_length));
            outtextxy(351, 322, charInRange(star, 0, passport_length));
        }
        else
        {
            if (frameStatus == USERNAME)
            {
                solidrectangle(351, 225, 351 + textwidth(charInRange(temp_name, 0, name_length)), 225 + textheight(charInRange(temp_name, 0, name_length)));
                solidrectangle(351, 322, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 322 + textheight(charInRange(temp_passport, 0, passport_length)));
                outtextxy(351, 225, getUserNameString(temp_name, 0, name_length));
                outtextxy(351, 322, charInRange(star, 0, passport_length));
            }
            else if (frameStatus == PASSPORT)
            {
                solidrectangle(351, 225, 351 + textwidth(charInRange(temp_name, 0, name_length)), 225 + textheight(charInRange(temp_name, 0, name_length)));
                solidrectangle(351, 322, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 322 + textheight(charInRange(temp_passport, 0, passport_length)));
                outtextxy(351, 225, charInRange(temp_name, 0, name_length));
                outtextxy(351, 322, getUserNameString(star, 0, passport_length));
            }
        }
        FlushBatchDraw();
    }
}