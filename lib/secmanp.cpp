/**
    Copyright: zirexix 2016

    This program is distributed
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    This program, or portions of it cannot be used in commercial
    products without the written consent of the author: marrius9876@gmail.com.

*/
/// **** requires  libcrypto++-dev  *****

#include <iostream>
#include <iomanip>
#include "secmanp.h"
#include "bu_hci.h"
#include "bu_asc.h"
#include "libbungetpriv.h"

/****************************************************************************************
*/
secmanp::secmanp(Icryptos* pc, bu_asc* acl, bu_hci*  hci, const bdaddr_t& local, int ltyp,
                 const bdaddr_t& remote, int rtyp):_crypt(pc), _aclbuffer(acl),_hci(hci)
{
  bdaddr_t tmp;

  _iat << (ADDR_RANDOM==rtyp ? uint8_t(0x01) : uint8_t(0x00));
  really_baswap(&tmp, &remote);
  _ia << remote;
  _rat << (ADDR_RANDOM==ltyp ? uint8_t(0x01) : uint8_t(0x00));
  really_baswap(&tmp, &local);
  _ra << local;
  _hci->srv()->data_subscribe(this);
  bybuff bbb;
}

/****************************************************************************************
*/
secmanp::~secmanp()
{
  _hci->srv()->data_unsubscribe(this);
}

/****************************************************************************************
*/
int secmanp::on_sock_data(uint8_t cid, const sdata& data)
{
  if (cid != SMP_CID)
  {
      return false;
  }
  bybuff  buff(data.data, data.len);
  uint8_t code = buff.read<uint8_t>();

  switch(code)
  {
    case SMP_PAIRING_REQUEST:
        _pairing_req(buff);
        break;
    case SMP_PAIRING_CONFIRM:
        _pairing_confirm(buff);
        break;
    case SMP_PAIRING_RANDOM:
        _pairing_random(buff);
        break;
    case SMP_PAIRING_FAILED:
        _pairing_failure(buff);
        break;
    case SMP_CMD_PUBLIC_KEY:
        /// TODO
        break;
    default:
        _pairing_unknown(code, buff);
        break;
  }
  return true;
}

/****************************************************************************************
*/
void secmanp::on_encryption_changed(bool is_encrypted)
{
  if (is_encrypted)
  {
    if (_stk.length() && _mangaler.length() && _random.length())
    {
      bybuff stream;

      stream << uint8_t(SMP_ENCRYPT_INFO) << _stk;
      write(stream);
      stream.reset();
      stream << uint8_t(SMP_MASTER_IDENT) << _mangaler << _random;
      write(stream);
    }
  }
}

/****************************************************************************************
*/
void secmanp::on_ltk_neg()
{
  bybuff stream;

  stream << uint8_t(SMP_PAIRING_FAILED) << uint8_t(SMP_UNSPECIFIED);
  write(stream);
}

/****************************************************************************************
*/
void secmanp::on_stream_end()
{
  _hci->srv()->data_unsubscribe(this);
}

/****************************************************************************************
*/
void secmanp::_pairing_req(const bybuff& data)
{
  _preq = data;
  _pres.reset();
  _pres << uint8_t(SMP_PAIRING_RESPONSE) << uint8_t(0x03) << uint8_t(0x00) << uint8_t(0x01) <<
                                            uint8_t(0x10) << uint8_t(0x00) << uint8_t(0x01);
/**
    SMP_PAIRING_RESPONSE,
    0x03, // IO capability: NoInputNoOutput
    0x00, // OOB data: Authentication data not present
    0x01, // Authentication requirement: Bonding - No MITM
    0x10, // Max encryption key size
    0x00, // Initiator key distribution: <none>
    0x01  // Responder key distribution: EncKey
*/
    write(_pres);
}

/****************************************************************************************
*/
void secmanp::_pairing_confirm(const bybuff& data)
{
  bybuff  plain;
  bybuff  is_encrypted;

  _pncf.reset();
  _tk.reset();
  _pcnf = data;
  _tk << 0x00000000 << 0x00000000 << 0x00000000 << 0x00000000; //
  _r.reset();
  _crypt->gen_random(16, _r);
  _crypt->c1(_tk, _r, _pres, _preq, _iat, _ia, _rat, _ra, is_encrypted);
  bybuff  stream;
  stream << uint8_t(SMP_PAIRING_CONFIRM) << is_encrypted;
  write(stream);
}

/****************************************************************************************
*/
void secmanp::_pairing_random(const bybuff& data)
{
  bybuff  r(data.buffer()+1,data.length()-1);
  bybuff  is_encrypted;
  bybuff  pncf,tosend;

  _crypt->c1(_tk, r, _pres, _preq, _iat, _ia, _rat,_ra,is_encrypted);
  pncf << uint8_t(SMP_PAIRING_CONFIRM) << is_encrypted;
  if(pncf ==_pncf)
  {
    _mangaler.reset();
    _random.reset();
    _stk.reset();
    _mangaler << uint16_t(0x0000);
    _random  << 0x00000000 << 0x00000000;
    _crypt->s1(_tk, _r, r, _stk);
    tosend << uint8_t(SMP_PAIRING_RANDOM) << _r;
  }
  else
  {
       tosend << uint8_t(SMP_PAIRING_FAILED) << uint8_t(SMP_PAIRING_CONFIRM);
       _pairing_failure(data);
  }
  write(tosend);
}

/****************************************************************************************
*/
void  secmanp::_pairing_unknown(uint8_t code, const bybuff& data)
{
    return;
/**
    bybuff  pncf,tosend;
    tosend << uint8_t(code) << uint8_t(SMP_PAIRING_NOTSUPP );
     write(tosend);
   _hci->disconnect(0, 0);
*/
}

/****************************************************************************************
*/
void secmanp::_pairing_failure(const bybuff& data)
{
  _hci->disconnect(0, 0);
};

/****************************************************************************************
*/
void secmanp::write(const bybuff& data)
{
  _aclbuffer->write(SMP_CID, data);
}

/****************************************************************************************
*/
void secmanp::on_error(const hci_error& error)
{
}

/****************************************************************************************
*/
bool secmanp::onSpin(bt_socket* sock)
{
  return true;
}
