/**
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
*/

#ifndef SYSTEM_SETUP_H_
#define SYSTEM_SETUP_H_

#include <string.h>
#include "intorobot_config.h"
#include "wiring_usbserial.h"

#if PLATFORM_ID>2
#define SETUP_OVER_SERIAL1 1
#endif

#ifndef SETUP_OVER_SERIAL1
#define SETUP_OVER_SERIAL1 0
#endif


typedef int (*ConnectCallback)( void* data,
                                const char *ssid,
                                const char *password,
                                unsigned long security_type,
                                unsigned long cipher,
                                bool dry_run);

class WiFiTester;

struct SystemSetupConsoleConfig
{

};


#ifdef configWIRING_WIFI_ENABLE
struct WiFiSetupConsoleConfig : SystemSetupConsoleConfig
{
    ConnectCallback connect_callback;
    void* connect_callback_data;
};
#endif

template<typename Config> class SystemSetupConsole
{
public:
    SystemSetupConsole(Config& config);
    ~SystemSetupConsole() = default;
    virtual void loop(void);
protected:
    virtual void exit()=0;
    /**
     * Handle a character received over serial.
     */
    virtual void handle(char c);

    /**
     * Handle a character peeked over serial.
     * Returns true if the character was pulled from the stream and handled.
     * Returns false if the character isn't recognized.
     */
    virtual bool handle_peek(char c);

    Config& config;
    void print(const char *s);
    void read_line(char *dst, int max_len);

private:
    USBSerial serial;

};

#ifdef configWIRING_WIFI_ENABLE
class WiFiSetupConsole : public SystemSetupConsole<WiFiSetupConsoleConfig>
{
    using super = SystemSetupConsole<WiFiSetupConsoleConfig>;

public:
    WiFiSetupConsole(WiFiSetupConsoleConfig& config);
    ~WiFiSetupConsole();
    virtual void loop() override;

protected:
    virtual void handle(char c) override;
    virtual void exit() override;
private:
#if SETUP_OVER_SERIAL1
    bool serial1Enabled;
    uint8_t magicPos;                   // how far long the magic key we are
    WiFiTester* tester;
#endif
    char ssid[33];
    char password[65];
    char security_type_string[2];
};
#endif

#ifdef configWIRING_CELLULAR_ENABLE
class CellularSetupConsoleConfig : SystemSetupConsoleConfig
{

};

class CellularSetupConsole : public SystemSetupConsole<CellularSetupConsoleConfig>
{
    using super = SystemSetupConsole<CellularSetupConsoleConfig>;

public:
    CellularSetupConsole(CellularSetupConsoleConfig& config);
    ~CellularSetupConsole() = default;

    virtual void exit() override;
    virtual void handle(char c) override;
};

#endif
#endif
