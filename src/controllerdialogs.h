#pragma once

#include "viewnewissue.h"
#include "viewnewsession.h"
#include "viewexistingsessions.h"

class ControllerDialogs
{
    public:
        ViewNewIssue* newissue;
        ViewNewSession* newsession;
        ViewExistingSessions* existingsessions;

        ~ControllerDialogs();

        int openNewIssue(QWidget *caller_widget = nullptr);
        QString getNewIssueID();
        QString getNewIssueTitle();

        // TODO: allow here passing of dManager object for checking if new session name already exists
        int openNewSession(QWidget *caller_widget = nullptr);
        QString getNewSessionName();

        int openExistingSessions(QWidget *caller_widget = nullptr, ControllerDB *dbManager = nullptr);
        QString getSelectedSessionName();
};

