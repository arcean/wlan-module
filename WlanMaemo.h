#ifndef WLANMAEMO_H
#define WLANMAEMO_H

/*
  Placeholder for the project name...
  Copyright (C) 2011  Tomasz Pieniążek

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <dbus/dbus.h>
#include <iostream>

class WlanMaemo
{
private:
  DBusConnection* GetDBusConnection();

public:
  WlanMaemo();

  std::string GetDefaultInterface() const;

  bool SupportsNetworkRetrieval() const;
  bool UpdateNetworks();

  bool CanChangePowerSaving() const;
  bool SetPowerSaving(bool savePower);

  bool HandleMessage(DBusConnection *connection, DBusMessage *msg);
};

#endif // WLANMAEMO_H
