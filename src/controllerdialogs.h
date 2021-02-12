#pragma once

#include "viewnewissue.h"
#include "viewnewsession.h"

class ControllerDialogs
{
    public:
        ViewNewIssue* newissue;
        ViewNewSession* newsession;

        ~ControllerDialogs();

        int openNewIssue(QWidget *caller_widget = nullptr);
        QString getNewIssueID();
        QString getNewIssueTitle();


        int openNewSession(QWidget *caller_widget = nullptr);
        QString getNewSessionName();
};

