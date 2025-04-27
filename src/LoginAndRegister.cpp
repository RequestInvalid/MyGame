#include "LoginAndRegister.h"

extern GameStatus Status;
extern userData *user;

typedef enum frameStatus
{
    NONE,
    USERNAME,
    PASSPORT,
} frameStatus;

void loginBox()
{
    /*设置登录框*/
    frameStatus frame_status = NONE;
    IMAGE login_box;
    ExMessage action;
    userData *head, *userPtr; //加载用户数据
    head = loadUserData();
    int name_length = 0, passport_length = 0;
    char temp_name[21], temp_passport[19];
    char star[19] = "******************";
    FILE *file = fopen("user.dat", "ab+");
    LOGFONT login_font;

    settextstyle(30, 0, _T("Times New Roman"));
    setbkmode(TRANSPARENT);
    gettextstyle(&login_font);
    login_font.lfQuality = ANTIALIASED_QUALITY;
    login_font.lfWeight = FW_BOLD;
    settextcolor(BLACK);
    settextstyle(&login_font); //设置输出字体
    setfillcolor(WHITE);       //设置填充框颜色

    loadimage(&login_box, _T("img/login.png"), 350, 350); //加载缩小后的登录框图片
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
    frameStatus frame_status = NONE;
    IMAGE register_box;
    ExMessage action;
    userData *head, user_input; //加载用户数据
    head = loadUserData();
    int name_length = 0, passport_length = 0;
    char temp_name[21], temp_passport[19];
    char star[19] = "******************";
    FILE *file = fopen("user.dat", "ab+");
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
                if (name_length > 0 && passport_length > 0)
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