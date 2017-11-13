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
            t.pos = QPoint(195,1545);
            t.size = 40;
        break;
        default:
            t.text = "Back";
            t.pos = QPoint(220,1545);
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

Text Translation::getBtn_Shop_Sell()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Verkaufen";
            t.pos = QPoint(630,1540);
            t.size = 30;
        break;
        default:
            t.text = "Sell";
            t.pos = QPoint(665,1545);
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
            t.text = "Erhöht den Benismultiplikator bei Hindernissen & Gegnern";
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
            t.text = "Kann nur vor Spielbeginn aktiviert werden.\n"
                     "Boostet den Spieler bis zu einer Score von 20.";
            t.pos = QPoint(25,1688);
            t.size = 25;
        break;
        default:
        t.text = "Can only used before the game starts.\n"
                 "Boosts the Player to a Score of 20.";
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
            t.text = "Wenn aktiviert hast du ein extra Leben\n"
                     "bis du stirbst";
            t.pos = QPoint(25,1688);
            t.size = 27;
        break;
        default:
            t.text = "One extra Life until you die";
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
            t.text = "Kann nur vor Spielbeginn aktiviert werden.\n"
                     "Boostet den Spieler bis zu einer Score von 40.";
            t.pos = QPoint(7,1688);
            t.size = 25;
        break;
        default:
            t.text = "Can only used before the game starts.\n"
                     "Boosts the Player to a Score of 40.";
            t.pos = QPoint(20,1696);
            t.size = 35;
        break;
    }
    return t;
}

Text Translation::getText_Shop_NotEnough(QString obj)
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Du hast nicht genug "+obj+"!";
            t.pos = QPoint(25,1692);
            t.size = 25;
        break;
        default:
            t.text = "You don't have enough "+obj+"!";
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
            t.text = "Wähle zuerst etwas aus!";
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

Text Translation::getText_PauseError()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Keine Zeitpowerups dürfen aktiv sein!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Timepowerups must not be activated!";
            t.pos = QPoint(530,1415);
            t.size = 50;
        break;
    }
    return t;
}

Text Translation::getText_Changelog()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Neue Features:\n"
                     "- Coins & Skins:\n"
                     "  - Skins können nur mit Coins gekauft\n"
                     "    werden\n"
                     "  - Coins findest du in Kisten und\n"
                     "    jedes mal wenn du die 100 knackst\n"
                     "- Animationen\n"
                     "- Medaille im Hauptmenü & im Scoreboard\n"
                     "- 'Info'-Button im Shop\n"
                     "- InApp Changelog\n"
                     "- Powerups können verkauft werden\n"
                     "- 'Pause'-Button\n"
                     "- Preis vom 30s-Revivepowerup angepasst\n"
                     "- Multitasking-Support\n"
                     "Nicht vergessen: Ganze Kisten auf der \nU-Bahn können eingesammelt werden!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "New Features:\n"
                     "- Coins & Skins:\n"
                     "  - Skins can only be purchased\n"
                     "    with Coins\n"
                     "  - You find the Coins required\n"
                     "    for a Purchase in Crates and\n"
                     "    you get a Coin everytime your\n"
                     "    Score is greater than 100\n"
                     "- Animations\n"
                     "- Medal on Home Menu & Scoreboard\n"
                     "- 'Info'-Button in Shop\n"
                     "- InApp changelog\n"
                     "- Powerups can now be sold\n"
                     "- 'Pause'-Button\n"
                     "- Changed Price of 30s-Revivepowerup\n"
                     "- Multitasking-Support\n"
                     "Don't forget that the crates on the \nSubway can be collected!";
            t.pos = QPoint(530,1415);
            t.size = 50;
        break;
    }
    return t;
}

Text Translation::getText_Shop_NoSell()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Du kannst Skins nicht verkaufen!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "You can't sell Skins!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Shop_Skin()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Tippe einen Skin an um ihn auszuwählen\n"
                     "nachdem du ihn gekauft hast. Die für\n"
                     "den Kauf benötigten Coins findest du\n"
                     "in Kisten. Zusätzlich bekommst du\n"
                     "jedes mal wenn du die 100 knackst\n"
                     "einen Coin.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Tap on a Skin to equip it after you\n"
                     "have purchased the Skin. You can\n"
                     "find the Coins required for a\n"
                     "Purchase in Crates. In addition\n"
                     "everytime you get a score greater\n"
                     "than 100 you get a coin.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}
