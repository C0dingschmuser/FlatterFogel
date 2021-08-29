#ifndef SCOREBOARDPLAYER_H
#define SCOREBOARDPLAYER_H

#include <QString>

class ScoreboardPlayer
{
public:
    ScoreboardPlayer();
    QString name;
    //Warum string? Wird eh nur gezeichnet
    QString score = 0;
    bool own = false;
    int donator = 0;
    int medal = 0;
};

#endif // SCOREBOARDPLAYER_H
