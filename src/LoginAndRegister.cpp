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
    static boolean showCursor = true;                                   // 控制光标显示状态
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

void setLogFont()
{
    LOGFONT f;
    settextstyle(30, 0, _T("Times New Roman"));
    setbkmode(TRANSPARENT);
    gettextstyle(&f);
    f.lfQuality = ANTIALIASED_QUALITY;
    f.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&f);
    setfillcolor(WHITE);
}

boolean isKeyPressed(ExMessage *action)
{
    static boolean isDown = false;
    if (action->message == WM_KEYDOWN && !isDown)
    {
        isDown = true;
    }
    else if (action->message == WM_KEYUP && isDown)
    {
        isDown = false;
        return true;
    }
    return false;
}

void testLogin()
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
    while (1)
    {
        peekmessage(&action, EM_MOUSE | EM_KEY); //获取鼠标消息
        BeginBatchDraw();
        EasyPutImage(305, 95, "img/login.png", 350, 400);
        /*检测左键按下*/
        if (action.message == WM_LBUTTONUP)
        {
            if (determineMouse(action, 606, 123, 637, 153)) //退出按钮
            {
                Status = MAIN_MENU;
                break;
            }
            else if (determineMouse(action, 351, 238, 614, 284)) //用户名
            {
                frameStatus = USERNAME;
            }
            else if (determineMouse(action, 351, 342, 614, 387)) //密码
            {
                frameStatus = PASSPORT;
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
                        break;
                    }
                }
            }
            solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
            solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
            outtextxy(351, 245, charInRange(temp_name, 0, name_length));
            outtextxy(351, 342, charInRange(star, 0, passport_length));
        }
        else
        {
            if (frameStatus == USERNAME)
            {
                solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                outtextxy(351, 245, getUserNameString(temp_name, 0, name_length));
                outtextxy(351, 342, charInRange(star, 0, passport_length));
            }
            else if (frameStatus == PASSPORT)
            {
                solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                outtextxy(351, 245, charInRange(temp_name, 0, name_length));
                outtextxy(351, 342, getUserNameString(star, 0, passport_length));
            }
        }
        FlushBatchDraw();
    }
}

void loginBox()
{
    /*设置登录框*/
    FrameStatus frameStatus = NONE;
    IMAGE login_box;
    ExMessage action;
    UserData *head, *userPtr; //加载用户数据
    head = loadUserData();
    int name_length = 0, passport_length = 0;
    char temp_name[21], temp_passport[19];
    char star[19] = "******************";
    LOGFONT login_font;

    settextstyle(30, 0, _T("Times New Roman"));
    setbkmode(TRANSPARENT);
    gettextstyle(&login_font);
    login_font.lfQuality = ANTIALIASED_QUALITY;
    login_font.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&login_font); //设置输出字体
    setfillcolor(WHITE);       //设置填充框颜色

    loadimage(&login_box, _T("img/login.png"), 350, 400); //加载缩小后的登录框图片
    putimage(305, 95, &login_box);
    while (1)
    {
        action = getmessage();
        /*检测鼠标按下，并切换状态*/
        if (action.message == WM_LBUTTONUP)
        {
            if (determineMouse(action, 606, 123, 637, 153)) //退出按钮
            {
                Status = MAIN_MENU;
                break;
            }
            else if (determineMouse(action, 351, 238, 614, 284)) //用户名
            {
                frameStatus = USERNAME;
            }
            else if (determineMouse(action, 351, 342, 614, 387)) //密码
            {
                frameStatus = PASSPORT;
            }
            else
            {
                frameStatus = NONE;
            }
        }
        /*检测按键按下*/
        else if (action.message == WM_KEYDOWN)
        {
            if (GetAsyncKeyState(VK_SHIFT)) //按下SHIFT时输入大写字母
            {
                if (frameStatus == USERNAME && name_length < 20)
                {
                    solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                    if (action.vkcode >= 'A' && action.vkcode <= 'Z')
                    {
                        temp_name[name_length] = action.vkcode;
                        name_length++;
                    }
                    outtextxy(351, 245, charInRange(temp_name, 0, name_length));
                }
                else if (frameStatus == PASSPORT && passport_length < 18)
                {
                    solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                    if (action.vkcode >= 'A' && action.vkcode <= 'Z')
                    {
                        temp_passport[passport_length] = action.vkcode;
                        passport_length++;
                    }
                    outtextxy(351, 342, charInRange(star, 0, passport_length));
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
                    solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                    temp_name[name_length] = tolower(action.vkcode);
                    name_length++;
                    outtextxy(351, 245, charInRange(temp_name, 0, name_length));
                }
                else if (frameStatus == PASSPORT && passport_length < 18)
                {
                    solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                    temp_passport[passport_length] = tolower(action.vkcode);
                    passport_length++;
                    outtextxy(351, 342, charInRange(star, 0, passport_length));
                }
            }
            else if (action.vkcode == VK_BACK) //输入BACKSPACE时退格
            {
                if (frameStatus == USERNAME && name_length > 0)
                {
                    solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                    name_length--;
                    outtextxy(351, 245, charInRange(temp_name, 0, name_length));
                }
                else if (frameStatus == PASSPORT && passport_length > 0)
                {
                    solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                    passport_length--;
                    outtextxy(351, 342, charInRange(star, 0, passport_length));
                }
            }
            else if (action.vkcode == VK_RETURN) //输入ENTER时确认用户名及密码
            {
                if (name_length > 0 && passport_length > 0)
                {
                    userPtr = searchUserData(head, (char *)charInRange(temp_name, 0, name_length));
                    if (userPtr != NULL && !strcmp(userPtr->pasport, (char *)charInRange(temp_passport, 0, passport_length)))
                    {
                        user = userPtr;
                        Status = GAMING; //登录成功跳转
                        break;
                    }
                }
            }
        }
        flushmessage();
    }
}

void registerBox()
{
    /*设置注册框*/
    FrameStatus frame_status = NONE;
    IMAGE register_box;
    ExMessage action;
    UserData *head, user_input; //加载用户数据
    head = loadUserData();
    int name_length = 0, passport_length = 0;
    char temp_name[21], temp_passport[19];
    char star[19] = "******************";
    LOGFONT register_font;

    settextstyle(30, 0, _T("Times New Roman"));
    setbkmode(TRANSPARENT);
    gettextstyle(&register_font);
    register_font.lfQuality = ANTIALIASED_QUALITY;
    register_font.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&register_font); //设置输出字体
    setfillcolor(WHITE);          //设置填充框颜色

    loadimage(&register_box, _T("img/register.png"), 350, 350); //加载缩小后的登录框图片
    putimage(305, 95, &register_box);
    while (1)
    {
        action = getmessage();
        /*检测鼠标按下，并切换状态*/
        if (action.message == WM_LBUTTONUP)
        {
            if (determineMouse(action, 606, 123, 637, 153)) //退出按钮
            {
                Status = MAIN_MENU;
                break;
            }
            else if (determineMouse(action, 351, 238, 614, 284)) //用户名
            {
                frame_status = USERNAME;
            }
            else if (determineMouse(action, 351, 342, 614, 387)) //密码
            {
                frame_status = PASSPORT;
            }
            else
            {
                frame_status = NONE;
            }
        }
        /*检测按键按下*/
        else if (action.message == WM_KEYDOWN)
        {
            if (GetAsyncKeyState(VK_SHIFT)) //按下SHIFT时输入大写字母
            {
                if (frame_status == USERNAME && name_length < 20)
                {
                    solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                    if (action.vkcode >= 'A' && action.vkcode <= 'Z')
                    {
                        temp_name[name_length] = action.vkcode;
                        name_length++;
                    }
                    outtextxy(351, 245, charInRange(temp_name, 0, name_length));
                }
                else if (frame_status == PASSPORT && passport_length < 18)
                {
                    solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                    if (action.vkcode >= 'A' && action.vkcode <= 'Z')
                    {
                        temp_passport[passport_length] = action.vkcode;
                        passport_length++;
                    }
                    outtextxy(351, 342, charInRange(star, 0, passport_length));
                }
            }
            else if (action.vkcode == VK_TAB) //按下TAB时切换窗口
            {
                if (frame_status == USERNAME)
                {
                    frame_status = PASSPORT;
                }
                else if (frame_status == PASSPORT)
                {
                    frame_status = USERNAME;
                }
            }
            else if ((action.vkcode >= 'A' && action.vkcode <= 'Z') ||
                     (action.vkcode >= '0' && action.vkcode <= '9')) //输入小写字母及数字
            {
                if (frame_status == USERNAME && name_length < 20)
                {
                    solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                    temp_name[name_length] = tolower(action.vkcode);
                    name_length++;
                    outtextxy(351, 245, charInRange(temp_name, 0, name_length));
                }
                else if (frame_status == PASSPORT && passport_length < 18)
                {
                    solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                    temp_passport[passport_length] = tolower(action.vkcode);
                    passport_length++;
                    outtextxy(351, 342, charInRange(star, 0, passport_length));
                }
            }
            else if (action.vkcode == VK_BACK) //输入BACKSPACE时退格
            {
                if (frame_status == USERNAME && name_length > 0)
                {
                    solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                    name_length--;
                    outtextxy(351, 245, charInRange(temp_name, 0, name_length));
                }
                else if (frame_status == PASSPORT && passport_length > 0)
                {
                    solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                    passport_length--;
                    outtextxy(351, 342, charInRange(star, 0, passport_length));
                }
            }
            else if (action.vkcode == VK_RETURN) //输入ENTER时存储用户名及密码
            {
                if (name_length > 0 && passport_length > 0 && !searchUserData(head, (char *)charInRange(temp_name, 0, name_length)))
                {
                    strcpy(user_input.username, (const char *)charInRange(temp_name, 0, name_length));
                    strcpy(user_input.pasport, (const char *)charInRange(temp_passport, 0, passport_length));
                    head = loadUserData();
                    addUserData(head, user_input);
                    Status = MAIN_MENU; //注册成功切换到主菜单界面
                    break;
                }
            }
        }
        flushmessage();
    }
}