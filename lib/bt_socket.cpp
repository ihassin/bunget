/**
    Copyright: zirexix 2016

    This program is distributed
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    This program, or portions of it cannot be used in commercial
    products without the written consent of the author: marrius9876@gmail.com

*/
#include "bt_socket.h"
#include "uguid.h"

#include "bu_hci.h"
#include "libbungetpriv.h"

#undef DEBUG
#undef ERROR
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

/****************************************************************************************
*/
typedef enum
{
    BT_IO_L2CAP,
    BT_IO_RFCOMM,
    BT_IO_SCO,
    BT_IO_INVALID,
} BtIOType;

/****************************************************************************************
*/
bt_socket::bt_socket(hci_data_eater* hci):_sock(0),_hci(hci)
{
  log4cpp::PropertyConfigurator::configure("log4cpp.properties");
}

/****************************************************************************************
*/
bt_socket::~bt_socket()
{
  close();
}

/****************************************************************************************
*/
void bt_socket::close()
{
  if(_sock > 0)
  {
    ::close(_sock);
    _sock = 0;
    log4cpp::Category& log = log4cpp::Category::getInstance(std::string("socket"));
    log.info("Closed socket");
  }
}

/****************************************************************************************
*/
int bt_socket::read(uint8_t* buffer, int sizeb)
{
  ssize_t bytes = ::read(this->_sock, buffer, sizeb);
  return bytes;
}

/****************************************************************************************
*/
int bt_socket:: writeocts(const uint8_t* buffer, int sizeb)
{
  bybuff data(buffer, sizeb);

  int r = ::write(this->_sock, buffer, sizeb);

  log4cpp::Category& log = log4cpp::Category::getInstance(std::string("socket"));
  char buff[256];
  sprintf(buff, "Writing Len: %d", int(data.length()));
  std::string logString = buff;
  logString = logString + ": " + data.to_string();
  log.info(logString);

//  TRACE("\n<--[" <<int(data.length())<<"/"<<r<<"]" << data.to_string());
  ::fsync(this->_sock);
  return r;
}
