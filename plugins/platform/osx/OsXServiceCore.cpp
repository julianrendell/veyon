/*
 * OsXServiceFunctions.cpp - implementation of OsXServiceFunctions class
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

#include <QDateTime>
#include <QDBusReply>
#include <QElapsedTimer>
#include <QEventLoop>
#include <QProcess>
#include <QThread>
#include <QTimer>

#include "Filesystem.h"
#include "OsXCoreFunctions.h"
#include "OsXServiceCore.h"
#include "VeyonConfiguration.h"


OsXServiceCore::OsXServiceCore( QObject* parent ) :
	QObject( parent ),
	m_multiSession( VeyonCore::config().isMultiSessionServiceEnabled() )
{
	connectToLoginManager();
}



OsXServiceCore::~OsXServiceCore()
{
	stopAllServers();
}



void OsXServiceCore::run()
{
	const auto sessions = listSessions();

	for( const auto& s : sessions )
	{
		startServer(s);
	}

	QEventLoop eventLoop;
	eventLoop.exec();
}



void OsXServiceCore::connectToLoginManager()
{
}



void OsXServiceCore::startServer( const QString& login1SessionId)
{
//    qInfo() << "Starting server for new session" << sessionPath
//            << "with display" << display
//            << "at seat" << seat.path;
//
//    auto process = new QProcess( this );
//    process->setProcessEnvironment( sessionEnvironment );
//    process->start( VeyonCore::filesystem().serverFilePath() );
//
//    m_serverProcesses[sessionPath] = process;
}



void OsXServiceCore::stopServer( const QString& login1SessionId)
{
//    Q_UNUSED( login1SessionId );
//
//    const auto sessionPath = sessionObjectPath.path();
//
//    if( m_serverProcesses.contains( sessionPath ) )
//    {
//        stopServer( sessionPath );
//    }
}


// This implementation might be more appropriate for OS X?
//void OsXServiceCore::stopServer( const QString& sessionPath )
//{
//    if( m_serverProcesses.contains( sessionPath ) == false )
//    {
//        return;
//    }
//
//    qInfo() << "Stopping server for removed session" << sessionPath;
//
//    auto process = qAsConst(m_serverProcesses)[sessionPath];
//    process->terminate();
//
//    QElapsedTimer serverStopTimer;
//    serverStopTimer.start();
//
//    while( process->state() != QProcess::NotRunning )
//    {
//        if( serverStopTimer.elapsed() >= ServerTerminateTimeout )
//        {
//            qWarning() << "Server for session" << sessionPath << "still running - killing now";
//            process->kill();
//            QThread::msleep( ServerKillDelayTime );
//            break;
//        }
//
//        QThread::msleep( ServerStopSleepInterval );
//    }
//
//    delete process;
//    m_serverProcesses.remove( sessionPath );
//}



void OsXServiceCore::stopAllServers()
{
	while( m_serverProcesses.isEmpty() == false )
	{
		stopServer( m_serverProcesses.firstKey() );
	}
}



QStringList OsXServiceCore::listSessions()
{
	QStringList sessions;
	return sessions;
}



QVariant OsXServiceCore::getSessionProperty( const QString& session, const QString& property )
{
    QVariant bla = QVariant();
    return bla;
}



int OsXServiceCore::getSessionLeaderPid( const QString& session )
{
    return -1;
}



qint64 OsXServiceCore::getSessionUptimeSeconds( const QString& session )
{
    return -1;
}



QString OsXServiceCore::getSessionType( const QString& session )
{
    return *(new QString());
}



QString OsXServiceCore::getSessionDisplay( const QString& session )
{
    return *(new QString());
}



QString OsXServiceCore::getSessionId( const QString& session )
{
    return *(new QString());
}
