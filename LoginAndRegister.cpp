#include "LoginAndRegister.h"

extern GameStatus Status;

typedef enum frameStatus
{
    NONE,
    USERNAME,
    PASSPORT,
    ENTER
} frameStatus;

void loginBox()
{
    /*���õ�¼��*/
    frameStatus frame_status = NONE;
    IMAGE login_box;
    ExMessage action;
    userData *head, *userPtr; //�����û�����
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
    settextstyle(&login_font); //�����������

    setfillcolor(WHITE); //����������ɫ

    loadimage(&login_box, _T("resource/login.png"), 350, 350); //������С��ĵ�¼��ͼƬ
    putimage(305, 95, &login_box);
    while (1)
    {
        action = getmessage();
        /*�����갴��*/
        if (action.message == WM_LBUTTONUP || frame_status != NONE)
        {
            /*�˳���ť*/
            if (determineMouse(action, 606, 123, 637, 153))
            {
                Status = MAIN_MENU;
                return;
            }
            /*�����û�������*/
            else if (determineMouse(action, 351, 238, 614, 284) || frame_status == USERNAME)
            {
                while (1)
                {
                    action = getmessage();
                    if (action.message == WM_LBUTTONUP) //�ж�����������ʱ��λ��
                    {
                        if (determineMouse(action, 606, 123, 637, 153))
                        {
                            Status = MAIN_MENU;
                            return;
                        }
                        else if (determineMouse(action, 351, 342, 614, 387))
                        {
                            frame_status = PASSPORT;
                            break;
                        }
                        else if (!determineMouse(action, 351, 238, 614, 284))
                        {
                            frame_status = NONE;
                            break;
                        }
                    }
                    else if (action.message == WM_KEYDOWN) //�жϰ��������¼�
                    {
                        solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                        if (GetAsyncKeyState(VK_SHIFT))
                        {
                            if (action.vkcode >= 'A' && action.vkcode <= 'Z' && name_length < 20)
                            {
                                temp_name[name_length] = action.vkcode;
                                name_length++;
                            }
                        }
                        else if (action.vkcode >= 'A' && action.vkcode <= 'Z' && name_length < 20)
                        {
                            temp_name[name_length] = tolower(action.vkcode);
                            name_length++;
                        }
                        else if (action.vkcode >= '0' && action.vkcode <= '9' && name_length < 20)
                        {
                            temp_name[name_length] = action.vkcode;
                            name_length++;
                        }
                        else if (action.vkcode == VK_BACK && name_length > 0)
                        {
                            name_length--;
                        }
                        outtextxy(351, 245, charInRange(temp_name, 0, name_length));
                    }
                }
            }
            /*�������봰��*/
            else if (determineMouse(action, 351, 342, 614, 387) || frame_status == PASSPORT)
            {
                while (1)
                {
                    action = getmessage();
                    if (action.message == WM_LBUTTONUP) //�ж�����������ʱ��λ��
                    {
                        if (determineMouse(action, 606, 123, 637, 153))
                        {
                            Status = MAIN_MENU;
                            return;
                        }
                        else if (determineMouse(action, 351, 238, 614, 284))
                        {
                            frame_status = USERNAME;
                            break;
                        }
                        else if (!determineMouse(action, 351, 342, 614, 387))
                        {
                            frame_status = NONE;
                            break;
                        }
                    }
                    else if (action.message == WM_KEYDOWN) //�жϰ��������¼�
                    {
                        solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                        if (GetAsyncKeyState(VK_SHIFT))
                        {
                            if (action.vkcode >= 'A' && action.vkcode <= 'Z' && passport_length < 18)
                            {
                                temp_passport[passport_length] = action.vkcode;
                                passport_length++;
                            }
                        }
                        else if (action.vkcode >= 'A' && action.vkcode <= 'Z' && passport_length < 18)
                        {
                            temp_passport[passport_length] = tolower(action.vkcode);
                            passport_length++;
                        }
                        else if (action.vkcode >= '0' && action.vkcode <= '9' && passport_length < 18)
                        {
                            temp_passport[passport_length] = action.vkcode;
                            passport_length++;
                        }
                        else if (action.vkcode == VK_BACK && passport_length > 0)
                        {
                            passport_length--;
                        }
                        else if (action.vkcode == VK_RETURN && passport_length > 0)
                        {
                            frame_status = ENTER;
                            break;
                        }
                        outtextxy(351, 342, charInRange(star, 0, passport_length));
                    }
                }
            }
        }
        /*����¼���û����������Ƿ�һ��*/
        else if (action.vkcode == VK_RETURN || frame_status == ENTER)
        {
            if (name_length != 0 && passport_length != 0)
            {
                userPtr = searchUserData(head, charInRange(temp_name, 0, name_length));
                if (userPtr != NULL)
                {
                    if (!strcmp(userPtr->pasport, charInRange(temp_passport, 0, passport_length)))
                    {
                        Status = MAIN_MENU;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

void registerBox()
{
    /*����ע���*/
    frameStatus frame_status = NONE;
    IMAGE register_box;
    ExMessage action;
    userData user_input, *head; //�洢�û�����Ľṹ��
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
    settextstyle(&register_font); //�����������

    setfillcolor(WHITE);

    loadimage(&register_box, _T("resource/register.png"), 350, 350); //������С��ĵ�¼��ͼƬ
    putimage(305, 95, &register_box);
    while (1)
    {
        action = getmessage();
        /*�����갴��*/
        if (action.message == WM_LBUTTONUP || frame_status != NONE)
        {
            /*�˳���ť*/
            if (determineMouse(action, 606, 123, 637, 153))
            {
                Status = MAIN_MENU;
                return;
            }
            /*�����û�������*/
            else if (determineMouse(action, 351, 238, 614, 284) || frame_status == USERNAME)
            {
                while (1)
                {
                    action = getmessage();
                    if (action.message == WM_LBUTTONUP) //�ж�����������ʱ��λ��
                    {
                        if (determineMouse(action, 606, 123, 637, 153))
                        {
                            Status = MAIN_MENU;
                            return;
                        }
                        else if (determineMouse(action, 351, 342, 614, 387))
                        {
                            frame_status = PASSPORT;
                            break;
                        }
                        else if (!determineMouse(action, 351, 238, 614, 284))
                        {
                            frame_status = NONE;
                            break;
                        }
                    }
                    else if (action.message == WM_KEYDOWN) //�жϰ��������¼�
                    {
                        solidrectangle(351, 245, 351 + textwidth(charInRange(temp_name, 0, name_length)), 245 + textheight(charInRange(temp_name, 0, name_length)));
                        if (GetAsyncKeyState(VK_SHIFT))
                        {
                            if (action.vkcode >= 'A' && action.vkcode <= 'Z' && name_length < 20)
                            {
                                temp_name[name_length] = action.vkcode;
                                name_length++;
                            }
                        }
                        else if (action.vkcode >= 'A' && action.vkcode <= 'Z' && name_length < 20)
                        {
                            temp_name[name_length] = tolower(action.vkcode);
                            name_length++;
                        }
                        else if (action.vkcode >= '0' && action.vkcode <= '9' && name_length < 20)
                        {
                            temp_name[name_length] = action.vkcode;
                            name_length++;
                        }
                        else if (action.vkcode == VK_BACK && name_length > 0)
                        {
                            name_length--;
                        }
                        outtextxy(351, 245, charInRange(temp_name, 0, name_length));
                    }
                }
            }
            /*�������봰��*/
            else if (determineMouse(action, 351, 342, 614, 387) || frame_status == PASSPORT)
            {
                while (1)
                {
                    action = getmessage();
                    if (action.message == WM_LBUTTONUP) //�ж�����������ʱ��λ��
                    {
                        if (determineMouse(action, 606, 123, 637, 153))
                        {
                            Status = MAIN_MENU;
                            return;
                        }
                        else if (determineMouse(action, 351, 238, 614, 284))
                        {
                            frame_status = USERNAME;
                            break;
                        }
                        else if (!determineMouse(action, 351, 342, 614, 387))
                        {
                            frame_status = NONE;
                            break;
                        }
                    }
                    else if (action.message == WM_KEYDOWN) //�жϰ��������¼�
                    {
                        solidrectangle(351, 342, 351 + textwidth(charInRange(temp_passport, 0, passport_length + 1)), 342 + textheight(charInRange(temp_passport, 0, passport_length)));
                        if (GetAsyncKeyState(VK_SHIFT))
                        {
                            if (action.vkcode >= 'A' && action.vkcode <= 'Z' && passport_length < 18)
                            {
                                temp_passport[passport_length] = action.vkcode;
                                passport_length++;
                            }
                        }
                        else if (action.vkcode >= 'A' && action.vkcode <= 'Z' && passport_length < 18)
                        {
                            temp_passport[passport_length] = tolower(action.vkcode);
                            passport_length++;
                        }
                        else if (action.vkcode >= '0' && action.vkcode <= '9' && passport_length < 18)
                        {
                            temp_passport[passport_length] = action.vkcode;
                            passport_length++;
                        }
                        else if (action.vkcode == VK_BACK && passport_length > 0)
                        {
                            passport_length--;
                        }
                        else if (action.vkcode == VK_RETURN && passport_length > 0)
                        {
                            frame_status = ENTER;
                            break;
                        }
                        outtextxy(351, 342, charInRange(star, 0, passport_length));
                    }
                }
            }
        }
        /*�洢�û���������*/
        else if (action.vkcode == VK_RETURN || frame_status == ENTER)
        {
            if (name_length != 0 && passport_length != 0)
            {
                strcpy(user_input.username, charInRange(temp_name, 0, name_length));
                strcpy(user_input.pasport, charInRange(temp_passport, 0, passport_length));
                head = loadUserData();
                addUserData(head, user_input);
                Status = MAIN_MENU;
                break;
            }
        }
    }
}
