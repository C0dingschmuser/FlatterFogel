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
            t.pos = QPoint(195,1615);
            t.size = 40;
        break;
        default:
            t.text = "Back";
            t.pos = QPoint(220,1615);
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

Text Translation::getBtn_Shop_Page()
{
    Text t;
    t.size = 32;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Seite";
        break;
        default:
            t.text = "Page";
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
                     "Boostet den Spieler bis zu einer Score von 65.";
            t.pos = QPoint(7,1688);
            t.size = 25;
        break;
        default:
            t.text = "Can only used before the game starts.\n"
                     "Boosts the Player to a Score of 45.";
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
            t.text = "Erlaubte Länge: 2-13, Erlaubte Zeichen: 'a-Z A-Z 0-9 .,-_:/?+$%'";
            t.pos = QPoint(180,450);
            t.size = 56;
        break;
        default:
            t.text = "Allowed length: 2-13, Allowed Letters: 'a-Z A-Z 0-9 .,-_:/?+$%'";
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
            t.text = "Name ändern";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Change Name";
            t.pos = QPoint(530,1415);
            t.size = 50;
        break;
    }
    return t;
}

Text Translation::getText_Scoreboard_NameChanged()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Name geändert!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Name changed!";
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
                     "-> DLC 1 Flatterfogel: Attack of the Schmuser\n"
                     "-> Bugfixes";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "New Features:\n"
                     "-> DLC\n"
                     "-> Bugfixes";
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
                     "jedes mal wenn du die 200 knackst\n"
                     "einen Coin.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Tap on a Skin to equip it after you\n"
                     "have purchased the Skin. You can\n"
                     "find the Coins required for a\n"
                     "Purchase in Crates. In addition\n"
                     "everytime you get a score dividable\n"
                     "by 200 you get a coin.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Shop_Background()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Tippe einen Hintergrund an um ihn auszuwählen<br>"
                     "nachdem du ihn gekauft hast. <b>Rot hinterlegte<br>"
                     "Hintergründe beinhalten einen besonderen Modus.</b><br>"
                     "Die für den Kauf benötigten Coins findest du<br>"
                     "in Kisten. Zusätzlich bekommst du jedes mal<br>"
                     "wenn du die 200 knackst einen Coin.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Tap on a Background to equip it\n"
                     "after you have purchased it. You can\n"
                     "find the Coins required for a\n"
                     "Purchase in Crates. In addition\n"
                     "everytime you get a score dividable\n"
                     "by 200 you get a coin.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Shop_BC()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "zu";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "to";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Shop_Coin()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Hier kannst du Coins kaufen und verkaufen.<br>"
                     "Mit Coins kannst du dir <b>neue Skins, Hintergründe,<br>"
                     "Säulenskins usw. kaufen</b> um dein Spielerlebnis zu<br>"
                     "verschönern. Alle 200 Punkte erhältst du einen Gratis-Coin.";
        break;
        default:
            t.text = "Here you can buy and sell Coins.<br>"
                     "With Coins you can <b>purchase Skins, Backgrounds,<br>"
                     "etc.</b>";
        break;
    }
    return t;
}

Text Translation::getText_Shop_Pipes()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Tippe einen Säulenskin an um ihn auszuwählen\n"
                     "nachdem du ihn gekauft hast. Die für\n"
                     "den Kauf benötigten Coins findest du\n"
                     "in Kisten. Zusätzlich bekommst du\n"
                     "jedes mal wenn du die 200 knackst\n"
                     "einen Coin.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Tap on a Pipeskin to equip it after you\n"
                     "have purchased the Skin. You can\n"
                     "find the Coins required for a\n"
                     "Purchase in Crates. In addition\n"
                     "everytime you get a score dividable\n"
                     "by 200 you get a coin.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Shop_Tail()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Tippe einen Schweif an um ihn auszuwählen\n"
                     "nachdem du ihn gekauft hast. Die für\n"
                     "den Kauf benötigten Coins findest du\n"
                     "in Kisten. Zusätzlich bekommst du\n"
                     "jedes mal wenn du die 200 knackst\n"
                     "einen Coin.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Tap on a Tail to equip it after you\n"
                     "have purchased the Skin. You can\n"
                     "find the Coins required for a\n"
                     "Purchase in Crates. In addition\n"
                     "everytime you get a score dividable\n"
                     "by 200 you get a coin.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Powerup()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Hier kannst du Powerups kaufen & verkaufen<br>"
                     "oder deine Multiplikatoren erhöhen. Für mehr<br>"
                     "Infos über spezielle Powerups wähle bitte eines aus.";
        break;
        default:
            t.text = "Here you can buy Powerups and increase<br>"
                     "the multiplier. For more specific Infos<br>"
                     "about a Powerup please select one first.";
        break;
    }
    return t;
}

Text Translation::getText_Referral_Get(QString key, QString leftKeys)
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Weiterempfehlungen\n\n"
                     "Du kannst noch "+leftKeys+" Leute einladen. Für jeden "
                     "Spieler den du einlädst erhältst du einen "
                     "Bonus von 250k Benis und der eingeladene "
                     "bekommt 100k Benis.\n\n"
                     "Key: "+key+"\n\n"
                     "Anleitung:\n\n"
                     "1. Den oben angezeigten Key\n"
                     "   bei der eingeladenen\n"
                     "   Person eingeben ('Ich\n"
                     "   wurde eingeladen')\n\n"
                     "2. Die eingeladene Person\n"
                     "   erhält nun den Bonus.\n"
                     "   Gib den dort angezeigten\n"
                     "   Bestätigungscode hier\n"
                     "   bei 'Einladung\n"
                     "   bestätigen' ein.\n\n"
                     "3. Alle sind glücklich.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Referrals\n\n"
                     "You have "+leftKeys+" Invites left. For every Player "
                     "you Invite you receive 250k Benis and the Invited gets "
                     "100k Benis.\n\n"
                     "Key: "+key+"\n\n"
                     "Tutorial:\n\n"
                     "1. Enter the Key displayed\n"
                     "   above on the Device from\n"
                     "   the Person you want to\n"
                     "   invite ('I was invited').\n\n"
                     "2. The Invited Person\n"
                     "   receives his Bonus. Enter\n"
                     "   the displayed\n"
                     "   confirmation key back on\n"
                     "   your Device under\n"
                     "   'Confirm Invite'\n\n"
                     "3. Everybody is happy.";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Referral_WrongKey()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Falscher key!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Wrong key!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Referral_Confirmed()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Key bestätigt!\nBestätigungscode: ";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Key confirmed!\nConfirmation code: ";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Referral_Confirmed2()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Einladung bestätigt!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Invite confirmed!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Referral_btnConfirm()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Einladung\nbestätigen";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Confirm\nInvite";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Referral_btnInvite()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Ich wurde\neingeladen";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "I was\ninvited";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Donate()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Hilf bei der Entwicklung von Flatterfogel<br><br>"
                     "Weil ich nicht EA bin, gibt es keine unfairen<br>"
                     "In-App Käufe und/oder Werbung. Flatterfogel<br>"
                     "ist nicht aus Geldgier entstanden, sondern<br>"
                     "aus Liebe zum Pr0. Wenn dir Flatterfogel<br>"
                     "so gut gefällt, dass du die Entwicklung<br>"
                     "unterstützen möchtest, kannst du das indem<br>"
                     "du mir einen beliebigen Betrag spendest.<br>"
                     "Im Gegenzug für deine Großzügigkeit kommst<br>"
                     "du auf eine Spenderliste, darfst an der Entwicklung<br>"
                     "mitwirken und <b>erhältst 2 exklusive<br>"
                     "Hintergründe und Säulenskins & einen<br>"
                     "Spielerskin.</b><br><br>"
                     "Edle Spender:<br>"
                     "- Holzklotzkiller 30€<br>"
                     "- Lunaaa          15€<br>"
                     "- LuxusDrea       15€<br>"
                     "- ICQ             13.37€<br>"
                     "- Archos405       10€<br>"
                     "- TimBeam         10€<br>"
                     "- KaisersNEEDU    10€<br>"
                     "- CX500           7.77€<br>"
                     "- X6              6.66€<br>"
                     "- Elevate         5€<br><br>"
                     "<b>Möchtest du Spenden?</b>";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Paypal-Email:\n"
                     "firediver98@gmail.com";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_NHS()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "NEUE HIGHSCORE!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "NEW HIGHSCORE!";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Neu()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "NEU";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "NEW";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_CN()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Namen ändern?";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
        default:
            t.text = "Change Name?";
            t.pos = QPoint(525,1405);
            t.size = 30;
        break;
    }
    return t;
}

Text Translation::getText_Begin()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Tippe um zu fliegen";
        break;
        default:
            t.text = "Tap to stay in air";
        break;
    }
    return t;
}

Text Translation::getText_BeginSpaceTop()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "über spieler = nach oben";
        break;
        default:
            t.text = "above player = up";
        break;
    }
    return t;
}

Text Translation::getText_BeginSpaceBottom()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "unter spieler = nach unten";
        break;
        default:
            t.text = "below player = down";
        break;
    }
    return t;
}

Text Translation::getText_AOTS()
{
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Tippe um zu beginnen";
        break;
        default:
            t.text = "Tap to begin";
        break;
    }
    return t;
}

Text Translation::getText_MaybeLater() {
    Text t;
    switch(locale.language()) {
        case QLocale::German:
            t.text = "Vielleicht später";
        break;
        default:
            t.text = "Maybe later";
        break;
    }
    return t;
}

Text Translation::getText_Continue()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Weiter";
        break;
        default:
            t.text = "Continue";
        break;
    }

    return t;
}

Text Translation::getText_Options_Music()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Musik";
        break;
        default:
            t.text = "Music";
        break;
    }

    return t;
}

Text Translation::gettext_Options_Schmuser()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Schmuser";
        break;
        default:
            t.text = "SadCat";
        break;
    }

    return t;
}

Text Translation::getText_Options_Mieser()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Mieser";
        break;
        default:
            t.text = "BadCat";
        break;
    }

    return t;
}

Text Translation::getText_Options_Animations()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Animationen";
        break;
        default:
            t.text = "Animations";
        break;
    }

    return t;
}

Text Translation::getText_Options_SoundEffects()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Toneffekte";
        break;
        default:
            t.text = "Soundeffects";
        break;
    }

    return t;
}

Text Translation::getText_Options_FPS()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Bilder pro Sekunde";
        break;
        default:
            t.text = "Frames per Second";
        break;
    }

    return t;
}

Text Translation::getText_Options_DSGVO()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "DSGVO Abfrage";
        break;
        default:
            t.text = "GDPR Request";
        break;
    }

    return t;
}

Text Translation::getText_Options_DSGVO_Request()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Daten abfragen";
        break;
        default:
            t.text = "Request Data";
        break;
    }

    return t;
}

Text Translation::getText_Options_DSGVO_Info()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Tippe auf OK um deine von uns gespeicherten Daten abzurufen\nDu kannst dies einmal monatlich tun.";
        break;
        default:
            t.text = "Tap on OK to request your personal saved Data by us\nYou can do this once a month.";
        break;
    }

    return t;
}

Text Translation::getText_Options_DSGVO_EMail()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Wir brauchen eine E-Mail Adresse zu der wir die Daten senden können.\nDie E-Mail wird nicht gespeichert.";
        break;
        default:
            t.text = "We need an E-Mail Adress to which we can send your Data.\nThe E-Mail will not be saved.";
        break;
    }

    return t;
}

Text Translation::getText_Options_DSGVO_None()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Wir haben keine personenbezogenen Daten von dir gespeichert.";
        break;
        default:
            t.text = "We currently have no personal data from you saved.";
        break;
    }

    return t;
}

Text Translation::getText_Options_WrongEMail()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Ungültige E-Mail!";
        break;
        default:
            t.text = "Invalid E-Mail!";
        break;
    }

    return t;
}

Text Translation::getText_Options_DSGVO_Success()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "E-Mail versendet!\nBitte schaue auch im Spam Ordner nach";
        break;
        default:
            t.text = "E-Mail sent!\nPlease also check your Spam folder";
        break;
    }

    return t;
}

Text Translation::getText_Options_DSGVO_Time()
{
    Text t;

    switch(locale.language()) {
        case QLocale::German:
            t.text = "Du hast deine Daten erst vor weniger als einem Monat angefragt.";
        break;
        default:
            t.text = "Your last GDPR Request was less than a month ago.";
        break;
    }

    return t;
}

int Translation::getLanguageCode() {
    int t = 0;

    switch(locale.language()) {
        case QLocale::German:
            t = 1;
        break;
        default:
            t = 0;
        break;
    }

    return t;
}
