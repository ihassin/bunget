/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hci_event.h
 * Author: ita
 *
 * Created on February 8, 2018, 3:52 PM
 */

#ifndef HCI_EVENT_H
#define HCI_EVENT_H

class hci_event
{
public:
    virtual void on_disconnect(const evt_disconn_complete* evdc)=0;
    virtual void on_encrypt_chnage(const evt_encrypt_change* pecc)=0;
    virtual void on_acl_packet(uint16_t handle, uint16_t cid, const sdata& data)=0;
    virtual void on_read_version(uint8_t hciver, uint16_t hcirev, uint8_t lmpver, uint16_t man, uint16_t lmpsubver)=0;
    virtual void on_mac_change(const bdaddr_t& addr)=0;
    virtual void on_adv_status(HCI_STATE status)=0;
    virtual void on_adv_data_status(uint8_t status)=0;
    virtual void on_scan_resp_datat_status(uint8_t status)=0;
    virtual void on_adv_enable(uint8_t status)=0;
    virtual void on_rssi(uint16_t handle, uint8_t rssi)=0;
    virtual void le_ltk_neg_reply(uint16_t handle)=0;
    virtual void le_get_adv_interval(int& interval)const=0;
    virtual void on_le_connected(uint8_t status, uint16_t handle,
                                uint8_t role,
                                HCI_ADDRTYPE addressType,
                                const bdaddr_t& address,
                                uint16_t interval,
                                uint16_t latency,
                                uint16_t  supervisionTimeout=0,
                                uint8_t masterClockAccuracy=0)=0;
    virtual void on_le_conn_update_complette_shit(uint8_t status,
                                                    uint16_t handle,
                                                    uint16_t interval,
                                                    uint16_t latency,
                                                    uint16_t supervisionTimeout)=0;
    virtual void on_dev_status(bool onoff)=0;
    virtual void on_configure_device(int devid)=0;
};



#endif /* HCI_EVENT_H */

