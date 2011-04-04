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

#include "WlanMaemo.h"
#include <string.h>

DBusHandlerResult DBusMsgHandler(DBusConnection *connection, DBusMessage *msg, void *data)
{
  WlanMaemo *statusHildon=static_cast<WlanMaemo*>(data);

  statusHildon->HandleMessage(connection,msg);

  return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

void callback(DBusPendingCall* call, void* /*data*/)
{
  DBusMessage *reply;

  reply=dbus_pending_call_steal_reply(call);

  std::cout << "Call finished with reply of type " << dbus_message_type_to_string(dbus_message_get_type(reply)) << std::endl;

  if (dbus_message_get_type(reply)==DBUS_MESSAGE_TYPE_ERROR) {
    std::cout << "Error: " << dbus_message_get_error_name(reply) << std::endl;
  }

  dbus_message_unref(reply);
}

WlanMaemo::WlanMaemo()
{
  if (GetDBusConnection()==NULL) {
    std::cerr << "No DBus connection!" << std::endl;
    return;
  }

  dbus_connection_add_filter(GetDBusConnection(),DBusMsgHandler,this,NULL);
}

std::string WlanMaemo::GetDefaultInterface() const
{
    return "wlan0";
}

DBusConnection* WlanMaemo::GetDBusConnection()
{
    //TODO
    //hehe:
    return NULL;
}

bool WlanMaemo::HandleMessage(DBusConnection *connection, DBusMessage *msg)
{
    if (dbus_message_get_type(msg)==DBUS_MESSAGE_TYPE_METHOD_CALL) {
        DBusMessage *response;
        std::string appName;
        std::string error;

        response = dbus_message_new_error(msg,"Message not implemented","Message not implemented");
        dbus_connection_send(connection,response,NULL);
        dbus_message_unref(response);
        return true;
    }
    else if (dbus_message_get_type(msg) == DBUS_MESSAGE_TYPE_SIGNAL) {
        if (strcmp(dbus_message_get_interface(msg),"com.nokia.wlancond.signal")!=0 ||
            strcmp(dbus_message_get_path(msg),"/com/nokia/wlancond/signal")!=0 ||
            strcmp(dbus_message_get_member(msg),"scan_results")!=0) {
                  return false;
        }
    }
    else {
        return false;
    }

    return true;
}

bool WlanMaemo::SupportsNetworkRetrieval() const
{
  return true;
}

bool WlanMaemo::UpdateNetworks()
{
  DBusMessage     *msg;
  DBusPendingCall *call;
  dbus_int32_t    power=4;
  dbus_int32_t    flags=2;
  unsigned char   a[] = { 0 };
  unsigned char*  ap=a;

  std::cout << "Requesting network scan..." << std::endl;

  if (GetDBusConnection()==NULL) {
    std::cerr << "No DBus connection!" << std::endl;
    return false;
  }

  msg=dbus_message_new_method_call("com.nokia.wlancond",
                                   "/com/nokia/wlancond/request",
                                   "com.nokia.wlancond.request",
                                   "scan");

  dbus_message_append_args(msg,
                           DBUS_TYPE_INT32,&power,
                           DBUS_TYPE_ARRAY,DBUS_TYPE_BYTE,&ap,0,
                           DBUS_TYPE_UINT32,&flags,
                           DBUS_TYPE_INVALID);

  if (!dbus_connection_send_with_reply(GetDBusConnection(),msg,&call,-1)) {
    std::cout << "Cannot send with reply" << std::endl;
    return false;
  }

  dbus_pending_call_set_notify(call,callback,NULL,NULL);

  std::cout << "Requesting network scan done." << std::endl;

  dbus_message_unref(msg);

  return true;
}
