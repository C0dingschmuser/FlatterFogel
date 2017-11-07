#include "translation.h"

Translation::Translation()
{
    locale = QLocale().system();
}

Text Translation::getBtn_Go()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Los";
            t.pos = QPoint(445,1010);
            t.size = 68;
        break;
        default:
            t.text = "Go";
            t.pos = QPoint(475,1010);
            t.size = 68;
        break;
    }
    return t;
}

Text Translation::getBtn_Shop()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Shop";
            t.pos = QPoint(412,1210);
            t.size = 68;
        break;
        default:
            t.text = "Shop";
            t.pos = QPoint(412,1210);
            t.size = 68;
        break;
    }
    return t;
}

Text Translation::getBtn_Shop_Back()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Zurück";
            t.pos = QPoint(195,1415);
            t.size = 40;
        break;
        default:
            t.text = "Back";
            t.pos = QPoint(220,1415);
            t.size = 50;
        break;
    }
    return t;
}

Text Translation::getBtn_Shop_Buy()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Kaufen";
            t.pos = QPoint(640,1415);
            t.size = 40;
        break;
        default:
            t.text = "Buy";
            t.pos = QPoint(680,1415);
            t.size = 50;
        break;
    }
    return t;
}

Text Translation::getText_Shop_Item1()
{
    //f.setPixelSize(20);
    //painter.setFont(f);
    //painter.drawText(30,1600,"Wenn aktiviert hast du für 30 Sekunden 1 extra Leben");
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Wenn aktiviert hast du für 30s 1 extra Leben";
            t.pos = QPoint(12,1688);
            t.size = 24;
        break;
        default:
            t.text = "One extra Life while activated for 30s";
            t.pos = QPoint(30,1688);
            t.size = 27;
        break;
    }
    return t;
}

Text Translation::getText_Shop_MP1()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Erhöht den Benismultiplikator (Hindernisse & Gegner)";
            t.pos = QPoint(0,1688);
            t.size = 21;
        break;
        default:
            t.text = "Increases Benis multiplier (Obstacles & Enemys)";
            t.pos = QPoint(5,1688);
            t.size = 23;
        break;
    }
    return t;
}

Text Translation::getText_Shop_MP2()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Erhöht den Benismultiplikator (Benis pro Touch)";
            t.pos = QPoint(5,1688);
            t.size = 23;
        break;
        default:
            t.text = "Increases Benis multiplier (Benis per Touch)";
            t.pos = QPoint(10,1688);
            t.size = 24;
        break;
    }
    return t;
}

Text Translation::getText_Shop_Item2()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Kann für einen Schnellstart benutzt werden";
            t.pos = QPoint(25,1688);
            t.size = 25;
        break;
        default:
            t.text = "Can be used for a Quick start";
            t.pos = QPoint(30,1696);
            t.size = 35;
        break;
    }
    return t;
}

Text Translation::getText_Shop_Item3()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Wenn aktiviert hast du ein extra Leben";
            t.pos = QPoint(25,1688);
            t.size = 27;
        break;
        default:
            t.text = "One extra Life until death";
            t.pos = QPoint(80,1696);
            t.size = 35;
        break;
    }
    return t;
}

Text Translation::getText_Shop_Item4()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Kann für einen Schnellstart+ benutzt werden";
            t.pos = QPoint(7,1688);
            t.size = 25;
        break;
        default:
            t.text = "Can be used for a Quick start+";
            t.pos = QPoint(20,1696);
            t.size = 35;
        break;
    }
    return t;
}

Text Translation::getText_Shop_NotEnough()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Du hast nicht genug Benis!";
            t.pos = QPoint(25,1692);
            t.size = 25;
        break;
        default:
            t.text = "You don't have enough Benis!";
            t.pos = QPoint(30,1696);
            t.size = 35;
        break;
    }
    return t;
}

Text Translation::getText_Shop_NotSelected()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Wähle zuerst etwas zum kaufen aus!";
            t.pos = QPoint(25,1692);
            t.size = 25;
        break;
        default:
            t.text = "You don't have anything selected!";
            t.pos = QPoint(30,1696);
            t.size = 35;
        break;
    }
    return t;
}

Text Translation::getText_Schmuser1()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Oh Nein!";
            t.pos = QPoint(320,450);
            t.size = 56;
        break;
        default:
            t.text = "Oh No!";
            t.pos = QPoint(365,450);
            t.size = 56;
        break;
    }
    return t;
}

Text Translation::getText_Schmuser2()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Ein ";
            t.pos = QPoint(30,450);
            t.size = 56;
        break;
        default:
            t.text = "A ";
            t.pos = QPoint(30,450);
            t.size = 56;
        break;
    }
    return t;
}

Text Translation::getText_Schmuser3()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Schnell gib -";
            t.pos = QPoint(180,450);
            t.size = 56;
        break;
        default:
            t.text = "Downvote fast!";
            t.pos = QPoint(180,450);
            t.size = 56;
        break;
    }
    return t;
}

Text Translation::gettext_Scoreboard_Falsch()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Nickname darf nicht leer sein, muss kürzer als 13 Zeichen sein und darf folgende Zeichen nicht enthalten: #~äöü";
            t.pos = QPoint(180,450);
            t.size = 56;
        break;
        default:
            t.text = "Nickname cant be empty, has to be shorter than 13 letters and must only contain normal letters and numbers";
            t.pos = QPoint(180,450);
            t.size = 56;
        break;
    }
    return t;
}

Text Translation::getText_Scoreboard_WrongName()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Name ist bereits vergeben!";
            t.pos = QPoint(180,450);
            t.size = 56;
        break;
        default:
            t.text = "Nickname is already taken!";
            t.pos = QPoint(180,450);
            t.size = 56;
        break;
    }
    return t;
}

Text Translation::getText_Scoreboard_ConnectionFail()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Verbindung zum Server Fehlgeschlagen!";
            t.pos = QPoint(180,450);
            t.size = 56;
        break;
        default:
            t.text = "Connection to Server failed!";
            t.pos = QPoint(180,450);
            t.size = 56;
        break;
    }
    return t;
}

Text Translation::getBtn_Scoreboard_Back()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Zurück";
            t.pos = QPoint(55,1415);
            t.size = 40;
        break;
        default:
            t.text = "Back";
            t.pos = QPoint(70,1415);
            t.size = 50;
        break;
    }
    return t;
}

Text Translation::getText_Scoreboard_SetName()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Nickname:";
            t.pos = QPoint(135,1415);
            t.size = 40;
        break;
        default:
            t.text = "Nickname:";
            t.pos = QPoint(160,1415);
            t.size = 50;
        break;
    }
    return t;
}

Text Translation::getBtn_Scoreboard_Change()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Name zurücksetzen";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Reset Name";
            t.pos = QPoint(530,1415);
            t.size = 50;
        break;
    }
    return t;
}
