/*
 * OsXCoreFunctions.cpp - implementation of OsXCoreFunctions class
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

#include <QDBusPendingCall>
#include <QProcess>
#include <QProcessEnvironment>
#include <QStandardPaths>
#include <QWidget>

#include <unistd.h>
#include <stdio.h>

//#include <Foundation/Foundation.h>

#include "OsXCoreFunctions.h"
#include "OsXDesktopIntegration.h"
#include "OsXUserFunctions.h"
#include "PlatformUserFunctions.h"

OsXCoreFunctions::OsXCoreFunctions() :
	m_screenSaverTimeout( 0 ),
	m_screenSaverPreferBlanking( 0 ),
	m_dpmsEnabled( false ),
	m_dpmsStandbyTimeout( 0 ),
	m_dpmsSuspendTimeout( 0 ),
	m_dpmsOffTimeout( 0 )
{
}

void OsXCoreFunctions::initNativeLoggingSystem( const QString& appName )
{
	Q_UNUSED(appName)
}

void OsXCoreFunctions::writeToNativeLoggingSystem( const QString& message, Logger::LogLevel loglevel )
{
	Q_UNUSED(message)
	Q_UNUSED(loglevel)
}

void OsXCoreFunctions::reboot()
{
    OSStatus error = noErr;
    
	if( isRunningAsAdmin() )
	{
		QProcess::startDetached( QStringLiteral("reboot") );
	}
	else
	{
        error = SendAppleEventToSystemProcess(kAERestart);
        if (error == noErr)
        {
            // add log that reboot request was successfull
        }
        else
        {
            // add log that reboot request was not successfull
        }
	}
}

void OsXCoreFunctions::powerDown()
{
    OSStatus error = noErr;
    
    if( isRunningAsAdmin() )
	{
		QProcess::startDetached( QStringLiteral("poweroff") );
	}
	else
	{
        error = SendAppleEventToSystemProcess(kAEShutDown);
        if (error == noErr)
        {
            // add log that reboot request was successfull
        }
        else
        {
            // add log that reboot request was not successfull
        }
    }
}

void OsXCoreFunctions::raiseWindow( QWidget* widget )
{
	widget->activateWindow();
	widget->raise();
}


void OsXCoreFunctions::disableScreenSaver()
{
    // some hints re ScreenSaver API: https://stackoverflow.com/questions/1976520/lock-screen-by-api-in-mac-os-x
    // NOTE: original also turns off screen blanking
}



void OsXCoreFunctions::restoreScreenSaverSettings()
{
}



QString OsXCoreFunctions::activeDesktopName()
{
	return QString();
}



bool OsXCoreFunctions::isRunningAsAdmin() const
{
	return getuid() == 0 || geteuid() == 0;
}



bool OsXCoreFunctions::runProgramAsAdmin( const QString& program, const QStringList& parameters )
{
// Keeping below snippet- investigate possible solutions from https://apple.stackexchange.com/questions/23494/what-option-should-i-give-the-sudo-command-to-have-the-password-asked-through-a/23514
    
//    const auto commandLine = QStringList( program ) + parameters;
//
//    const auto desktop = QProcessEnvironment::systemEnvironment().value( QStringLiteral("XDG_CURRENT_DESKTOP") );
//    if( desktop == QStringLiteral("KDE") &&
//            QStandardPaths::findExecutable( QStringLiteral("kdesudo") ).isEmpty() == false )
//    {
//        return QProcess::execute( QStringLiteral("kdesudo"), commandLine ) == 0;
//    }
//
//    if( QStandardPaths::findExecutable( QStringLiteral("gksudo") ).isEmpty() == false )
//    {
//        return QProcess::execute( QStringLiteral("gksudo"), commandLine ) == 0;
//    }
//
//    return QProcess::execute( QStringLiteral("pkexec"), commandLine ) == 0;
    
    return false; // hard coded as "fail"
}



bool OsXCoreFunctions::runProgramAsUser( const QString& program, const QStringList& parameters,
										   const QString& username, const QString& desktop )
{
	Q_UNUSED(desktop);

	class UserProcess : public QProcess // clazy:exclude=missing-qobject-macro
	{
	public:
		explicit UserProcess( uid_t uid, QObject* parent = nullptr ) :
			QProcess( parent ),
			m_uid( uid )
		{
		}

		void setupChildProcess() override
		{
			if( setuid( m_uid ) != 0 )
			{
				qFatal( "Could not set UID for child process!" );
			}
		}

	private:
		const uid_t m_uid;
	};

	const auto uid = OsXUserFunctions::userIdFromName( username );
	if( uid <= 0 )
	{
		return false;
	}

	auto process = new UserProcess( uid );
	process->connect( process, QOverload<int>::of( &QProcess::finished ), &QProcess::deleteLater );
	process->start( program, parameters );

	return true;
}


QString OsXCoreFunctions::genericUrlHandler() const
{
	return QStringLiteral( "open" );
}

OSStatus OsXCoreFunctions::SendAppleEventToSystemProcess(AEEventID eventToSendID)
{
    /*
     * OS X Reboot code from: https://stackoverflow.com/questions/6271300/finder-scripting-bridge-to-shutdown/6283690#6283690
     * This suggests a newer way: https://forums.developer.apple.com/thread/90702
     * https://www.64k-tec.de/2010/11/creating-file-shortcuts-on-three-different-operation-systems/
     */

//    AEAddressDesc targetDesc;
//    static const ProcessSerialNumber kPSNOfSystemProcess = {0, kSystemProcess };
//    AppleEvent eventReply = {typeNull, NULL};
//    AppleEvent eventToSend = {typeNull, NULL};
//
//    OSStatus status = AECreateDesc(typeProcessSerialNumber,
//                                   &kPSNOfSystemProcess, sizeof(kPSNOfSystemProcess), &targetDesc);
//
//    if (status != noErr) return status;
//
//    status = AECreateAppleEvent(kCoreEventClass, eventToSendID,
//                                &targetDesc, kAutoGenerateReturnID, kAnyTransactionID, &eventToSend);
//
//    AEDisposeDesc(&targetDesc);
//
//    if (status != noErr) return status;
//
//    status = AESendMessage(&eventToSend, &eventReply,
//                           kAENormalPriority, kAEDefaultTimeout);
//
//    AEDisposeDesc(&eventToSend);
//    if (status != noErr) return status;
//    AEDisposeDesc(&eventReply);
//    return status;
    return *(new OSStatus());
}
