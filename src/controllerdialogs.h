#pragma once

#include "viewnewissue.h"

class ControllerDialogs
{
    public:
        ViewNewIssue* newissue;

        ControllerDialogs();

        int openNewIssue(QWidget *caller_widget = nullptr);
        QString getNewIssueID();
        QString getNewIssueTitle();
};

