#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QString>
#include <QPoint>
#include <QLocale>
#include "text.h"
class Translation
{
public:
    Translation();
    QLocale locale;
    Text getBtn_Go();
    Text getBtn_Shop();
    Text getBtn_Shop_Back();
    Text getBtn_Shop_Buy();
    Text getBtn_Shop_Sell();
    Text getBtn_Shop_Page();
    Text getText_Shop_Item1();
    Text getText_Shop_MP1();
    Text getText_Shop_MP2();
    Text getText_Shop_Item2();
    Text getText_Shop_Item3();
    Text getText_Shop_Item4();
    Text getText_Shop_NotEnough(QString obj="Benis");
    Text getText_Shop_NotSelected();
    Text getText_Schmuser1();
    Text getText_Schmuser2();
    Text getText_Schmuser3();
    Text gettext_Scoreboard_Falsch();
    Text getText_Scoreboard_WrongName();
    Text getText_Scoreboard_ConnectionFail();
    Text getBtn_Scoreboard_Back();
    Text getText_Scoreboard_SetName();
    Text getBtn_Scoreboard_Change();
    Text getText_Scoreboard_NameChanged();
    Text getText_PauseError();
    Text getText_Changelog();
    Text getText_Shop_NoSell();
    Text getText_Shop_Skin();
    Text getText_Shop_Background();
    Text getText_Shop_BC();
    Text getText_Shop_Coin();
    Text getText_Shop_Pipes();
    Text getText_Shop_Tail();
    Text getText_Powerup();
    Text getText_Referral_Get(QString key, QString leftKeys);
    Text getText_Referral_WrongKey();
    Text getText_Referral_Confirmed();
    Text getText_Referral_Confirmed2();
    Text getText_Referral_btnConfirm();
    Text getText_Referral_btnInvite();
    Text getText_Donate();
    Text getText_NHS();
    Text getText_Neu();
    Text getText_CN();
    Text getText_Begin();
    Text getText_BeginSpaceTop();
    Text getText_BeginSpaceBottom();
    Text getText_AOTS();
    Text getText_MaybeLater();
    Text getText_Continue();
    Text getText_Options_Music();
    Text gettext_Options_Schmuser();
    Text getText_Options_Mieser();
    Text getText_Options_Animations();
    Text getText_Options_SoundEffects();
    Text getText_Options_FPS();
    Text getText_Options_DSGVO();
    Text getText_Options_DSGVO_Request();
    Text getText_Options_DSGVO_Info();
    Text getText_Options_DSGVO_EMail();
    Text getText_Options_DSGVO_None();
    Text getText_Options_WrongEMail();
    Text getText_Options_DSGVO_Success();
    Text getText_Options_DSGVO_Time();
    int getLanguageCode();
};

#endif // LOCALE_H
