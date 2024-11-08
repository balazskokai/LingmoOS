/*
    SPDX-FileCopyrightText: 2021 Waqar Ahmed <waqar.17a@gmail.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QFutureWatcher>

#include "git/gitutils.h"
#include "quickdialog.h"

class QTreeView;
class QLineEdit;
class BranchesDialogModel;
class QAction;
class BranchFilterModel;
class KActionCollection;
class KateProjectPluginView;

namespace KTextEditor
{
class MainWindow;
}

class BranchesDialog : public HUDDialog
{
    Q_OBJECT
public:
    BranchesDialog(QWidget *window, QString projectPath);
    void openDialog(GitUtils::RefType r);
    void sendMessage(const QString &message, bool warn);
    QString branch() const
    {
        return m_branch;
    }

Q_SIGNALS:
    void branchSelected(const QString &branch);

private:
    void slotReturnPressed(const QModelIndex &index) override;

protected:
    BranchesDialogModel *const m_model;
    QString m_projectPath;

private:
    QString m_branch;
};
