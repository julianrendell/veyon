/*
 * OsXInputDeviceFunctions.cpp - implementation of OsXInputDeviceFunctions class
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

#include "PlatformServiceFunctions.h"
#include "OsXInputDeviceFunctions.h"
#include "OsXKeyboardShortcutTrapper.h"

OsXInputDeviceFunctions::OsXInputDeviceFunctions() :
	m_inputDevicesDisabled( false ),
	m_origKeyTable( nullptr ),
	m_keyCodeMin( 0 ),
	m_keyCodeMax( 0 ),
	m_keyCodeCount( 0 ),
	m_keySymsPerKeyCode( 0 )
{
}



void OsXInputDeviceFunctions::enableInputDevices()
{
	if( m_inputDevicesDisabled )
	{
		restoreKeyMapTable();

		m_inputDevicesDisabled = false;
	}
}



void OsXInputDeviceFunctions::disableInputDevices()
{
	if( m_inputDevicesDisabled == false )
	{
		setEmptyKeyMapTable();

		m_inputDevicesDisabled = true;
	}
}



KeyboardShortcutTrapper* OsXInputDeviceFunctions::createKeyboardShortcutTrapper( QObject* parent )
{
	return new OsXKeyboardShortcutTrapper( parent );
}



bool OsXInputDeviceFunctions::configureSoftwareSAS( bool enabled )
{
	Q_UNUSED(enabled);

	return true;
}



void OsXInputDeviceFunctions::setEmptyKeyMapTable()
{

}



void OsXInputDeviceFunctions::restoreKeyMapTable()
{

}
