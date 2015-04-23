/*
 * Copyright (C) by Olivier Goffart <ogoffart@woboq.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#pragma once

#include "account.h"
#include "accountstate.h"

namespace OCC {

typedef QSharedPointer<AccountState> AccountStatePtr;

class OWNCLOUDSYNC_EXPORT AccountManager : public QObject {
    Q_OBJECT
public:
    static AccountManager *instance();
    ~AccountManager() {}

    /**
     * Saves the accounts to a given settings file
     */
    void save();

    /**
     * Creates account objects from from a given settings file.
     * return true if the account was restored
     */
    bool restore();

    /**
     * Add this account in the list of saved account.
     * Typically called from the wizard
     */
    void addAccount(const AccountPtr &newAccount);

    /**
     * remove all accounts
     */
    void shutdown();

    QList<AccountStatePtr> accounts() { return _accounts; }

private:
    void save(const AccountPtr& account, QScopedPointer<QSettings>& settings);
    AccountPtr load(const QScopedPointer<QSettings>& settings);
    bool restoreFromLegacySettings();


Q_SIGNALS:
    void accountAdded(AccountState *account);
    void accountRemoved(AccountState *account);

private:
    AccountManager() {}
    QList<AccountStatePtr> _accounts;
};

}
