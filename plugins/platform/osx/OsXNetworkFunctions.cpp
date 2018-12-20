/*
 * OsXNetworkFunctions.cpp - implementation of OsXNetworkFunctions class
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

#include <netinet/in.h>
#include <netinet/tcp.h>

#include <QProcess>

#include "OsXNetworkFunctions.h"

bool OsXNetworkFunctions::ping( const QString& hostAddress )
{
	QProcess pingProcess;
	pingProcess.start( QStringLiteral("ping"), { QStringLiteral("-W"), QStringLiteral("1"), QStringLiteral("-c"), QString::number( PingTimeout / 1000 ), hostAddress } );
	pingProcess.waitForFinished( PingProcessTimeout );

	return pingProcess.exitCode() == 0;
}



bool OsXNetworkFunctions::configureFirewallException( const QString& applicationPath, const QString& description, bool enabled )
{
	Q_UNUSED(applicationPath)
	Q_UNUSED(description)
	Q_UNUSED(enabled)

	return true;
}



bool OsXNetworkFunctions::configureSocketKeepalive( Socket socket, bool enabled, int idleTime, int interval, int probes )
{
	int optval;
	socklen_t optlen = sizeof(optval);
	auto fd = static_cast<int>( socket );

	// Try to set the option active
	optval = enabled ? 1 : 0;
	if( setsockopt( fd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen ) < 0 )
	{
		qWarning() << Q_FUNC_INFO << "could not set SO_KEEPALIVE";
		return false;
	}

// Linux specific? Ref: https://stackoverflow.com/questions/15860127/how-to-configure-tcp-keepalive-under-mac-os-x/23900051
//    optval = std::max<int>( 1, idleTime / 1000 );
//    if( setsockopt( fd, IPPROTO_TCP, TCP_KEEPIDLE, &optval, optlen ) < 0 )
//    {
//        qWarning() << Q_FUNC_INFO << "could not set TCP_KEEPIDLE";
//        return false;
//    }

	optval = std::max<int>( 1, interval / 1000 );
	if( setsockopt( fd, IPPROTO_TCP, TCP_KEEPINTVL, &optval, optlen ) < 0 )
	{
		qWarning() << Q_FUNC_INFO << "could not set TCP_KEEPINTVL";
		return false;
	}

	optval = probes;
	if( setsockopt( fd, IPPROTO_TCP, TCP_KEEPCNT, &optval, optlen ) < 0 )
	{
		qWarning() << Q_FUNC_INFO << "could not set TCP_KEEPCNT";
		return false;
	}

	return true;
}