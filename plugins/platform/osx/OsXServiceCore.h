/*
 * OsXServiceCore.h - declaration of OsXServiceCore class
 *
 * Copyright (c) 2017-2018 Tobias Junghans <tobydox@veyon.io>
 *
 * This file is part of Veyon - https://veyon.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#pragma once

#include <QProcessEnvironment>

#include "OsXCoreFunctions.h"
#include "PlatformServiceCore.h"

// clazy:excludeall=copyable-polymorphic

class OsXServiceCore : public QObject, PlatformServiceCore
{
	Q_OBJECT
public:
	OsXServiceCore( QObject* parent = nullptr );
	~OsXServiceCore();

	void run();

private slots:
	void connectToLoginManager();
	void startServer( const QString& login1SessionId);
	void stopServer( const QString& login1SessionId);
	void stopAllServers();

private:
	enum {
		LoginManagerReconnectInterval = 3000,
		ServerTerminateTimeout = 3000,
		ServerStopSleepInterval = 100,
		ServerKillDelayTime = 1000,
		SessionEnvironmentProbingInterval = 1000,
		SessionUptimeSecondsMinimum = 3,
		SessionUptimeProbingInterval = 1000,
	};

	QStringList listSessions();

	static QVariant getSessionProperty( const QString& session, const QString& property );

	static int getSessionLeaderPid( const QString& session );
	static qint64 getSessionUptimeSeconds( const QString& session );
	static QString getSessionType( const QString& session );
	static QString getSessionDisplay( const QString& session );
	static QString getSessionId( const QString& session );
	static QProcessEnvironment getSessionEnvironment( int sessionLeaderPid );

    QMap<QString, QProcess *> m_serverProcesses;
	bool m_multiSession;

};