/*
 * LdapClient.h - class implementing an LDAP client
 *
 * Copyright (c) 2016-2018 Tobias Junghans <tobydox@veyon.io>
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

#include <QObject>
#include <QUrl>

#include "VeyonCore.h"

#include "ldapurl.h"

namespace KLDAP {
class LdapConnection;
}

class LdapConfiguration;

class LdapClient : public QObject
{
	Q_OBJECT
public:
	enum ConnectionSecurity
	{
		ConnectionSecurityNone,
		ConnectionSecurityTLS,
		ConnectionSecuritySSL,
		ConnectionSecurityCount,
	};
	Q_ENUM(ConnectionSecurity)

	enum TLSVerifyMode
	{
		TLSVerifyDefault,
		TLSVerifyNever,
		TLSVerifyCustomCert,
		TLSVerifyModeCount
	};
	Q_ENUM(TLSVerifyMode)

	LdapClient( const LdapConfiguration& configuration, const QUrl& url = QUrl(), QObject* parent = nullptr );
	~LdapClient();

	const LdapConfiguration& configuration() const
	{
		return m_configuration;
	}

	KLDAP::LdapConnection& connection() const;

	bool isConnected() const;
	bool isBound() const;

	QStringList queryAttributes(const QString &dn, const QString &attribute,
								const QString& filter = QStringLiteral( "(objectclass=*)" ),
								KLDAP::LdapUrl::Scope scope = KLDAP::LdapUrl::Base );

	QStringList queryDistinguishedNames( const QString& dn, const QString& filter, KLDAP::LdapUrl::Scope scope );

	QString errorDescription() const;

	QStringList queryBaseDn();

	QString queryNamingContext();

	const QString& baseDn() const;

	static QString parentDn( const QString& dn );
	QString toRelativeDn( const QString& fullDn );
	QString toFullDn( const QString& relativeDn );

	QStringList toRelativeDnList( const QStringList& fullDnList );

	static QString constructSubDn( const QString& subtree, const QString& baseDn );

	static QString constructQueryFilter( const QString& filterAttribute,
										 const QString& filterValue,
										 const QString& extraFilter = QString() );

	static QString escapeFilterValue( const QString& filterValue );


private:
	bool reconnect( const QUrl& url );
	void initTLS();

	class LdapClientPrivate;

	const LdapConfiguration& m_configuration;
	LdapClientPrivate* d;

};
